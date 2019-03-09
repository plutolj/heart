#include "MAX30100_PulseOximeter.h"
#include "stdlib.h"
#include "usart.h"
#include "myiic.h"
#include "delay.h"
#include "stdio.h"

float onBeatDetected;
signed short HeartRate = 0;		//心率值
u8  SPO2 = 0;									//血氧值

PulseOximeterState state;
PulseOximeterDebuggingMode debuggingMode;
uint32_t tsFirstBeatDetected;
uint32_t tsLastBeatDetected;
uint32_t tsLastSample;
uint32_t tsLastBiasCheck;
uint32_t tsLastCurrentAdjustment;
uint8_t redLedPower;

DCRemover irDCRemover;
DCRemover redDCRemover;

u8  ID=0;
u8  TempINT=0;
u8  TempFRAC=0;

//初始化

void SPO2_Init(void)
{
	IIC_Init();
	ID=Read_One_Byte(MAX30100_REG_PART_ID);//读取ID
	if(ID==17)
	{
		Delay_ms(100);
		Write_One_Byte(MAX30100_REG_MODE_CONFIGURATION, MAX30100_MC_TEMP_EN);
		TempINT=Read_One_Byte(MAX30100_REG_TEMPERATURE_DATA_INT);						 
		TempFRAC=Read_One_Byte(MAX30100_REG_TEMPERATURE_DATA_FRAC);				   
		Delay_ms(300);
		setMode(MAX30100_MODE_SPO2_HR);																
		setLedsPulseWidth(MAX30100_SPC_PW_1600US_16BITS);							
		setSamplingRate(MAX30100_SAMPRATE_100HZ);											
		setLedsCurrent( MAX30100_LED_CURR_24MA,MAX30100_LED_CURR_24MA);
		setHighresModeEnabled(1);
		BeatDetector();
		setOnBeatDetectedCallback(&onBeatDetected);
		begin(PULSEOXIMETER_DEBUGGINGMODE_PULSEDETECT);
	}		
}

void PulseOximeter(void)
{ 
	state=PULSEOXIMETER_STATE_INIT;
	tsFirstBeatDetected=0;
	tsLastBeatDetected=0;
	tsLastSample=0;
	tsLastBiasCheck=0;
	tsLastCurrentAdjustment=0;
	redLedPower=((uint8_t)RED_LED_CURRENT_START);
	onBeatDetected=NULL;
}

void begin(PulseOximeterDebuggingMode mode)
{
	debuggingMode = mode;
	PulseOximeter();
	//消除Ir  Red 直流分量
	DCRemover1(DC_REMOVER_ALPHA,&irDCRemover.alpha,&irDCRemover.dcw);
	DCRemover1(DC_REMOVER_ALPHA,&redDCRemover.alpha,&redDCRemover.dcw);

	state = PULSEOXIMETER_STATE_IDLE;//闲置状态
}

//检测心率血氧

void POupdate(void)
{
	checkSample();
//	checkCurrentBias();
}

float getHeartRate(void)
{
	return getRate();
}

uint8_t POgetSpO2(void)
{
	return getSpO2();
}

uint8_t getRedLedCurrentBias(void)
{
	return redLedPower;
}

void setOnBeatDetectedCallback(float *cb)
{
	onBeatDetected = *cb;
}

void checkSample(void)
{	
	u8 beatDetected;
	float filteredPulseValue;
	float irACValue;
	float redACValue;
	if (millis() - tsLastSample > 1.0 / SAMPLING_FREQUENCY * 1000.0) 
	{
		tsLastSample = millis();
		update();
		irACValue = step(rawIRValue,&irDCRemover.alpha,&irDCRemover.dcw);
		redACValue = step(rawRedValue,&redDCRemover.alpha,&redDCRemover.dcw);
		filteredPulseValue = FBstep(-irACValue);
		beatDetected = addSample(filteredPulseValue);
		if (getRate() > 0) 
		{	
			state = PULSEOXIMETER_STATE_DETECTING;
			SPO2update(irACValue, redACValue, beatDetected);
			HeartRate=getRate();
			SPO2=getSpO2();
		}
		else if (state == PULSEOXIMETER_STATE_DETECTING) 
		{
			state = PULSEOXIMETER_STATE_IDLE;
			reset();
		}
		if (beatDetected && onBeatDetected) 
		{
			onBeatDetected1();
		}
	}
}

void onBeatDetected1(void)
{
  
}
void checkCurrentBias()
{
	if (millis() - tsLastBiasCheck > CURRENT_ADJUSTMENT_PERIOD_MS) 
	{
		u8 changed = 0;
		if (getDCW(&irDCRemover.dcw)-getDCW(&redDCRemover.dcw) > 70000 && redLedPower < MAX30100_LED_CURR_50MA) 
		{
			++redLedPower;
			changed = 1;
		} 
		else if (getDCW(&redDCRemover.dcw) - getDCW(&irDCRemover.dcw) > 70000 && redLedPower > 0) 
		{
			--redLedPower;
			changed = 1;
		}
		if (changed) 
		{			
			setLedsCurrent(IR_LED_CURRENT, (LEDCurrent)redLedPower);
			tsLastCurrentAdjustment = millis();
		}
		tsLastBiasCheck = millis();
	}
}



