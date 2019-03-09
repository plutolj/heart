#ifndef MAX30100_H
#define MAX30100_H

#include <stdint.h>
#include "bitband.h"
#include "MAX30100_Registers.h"

#define DEFAULT_MODE                MAX30100_MODE_HRONLY
#define DEFAULT_SAMPLING_RATE       MAX30100_SAMPRATE_100HZ
#define DEFAULT_PULSE_WIDTH         MAX30100_SPC_PW_1600US_16BITS
#define DEFAULT_RED_LED_CURRENT     MAX30100_LED_CURR_37MA
#define DEFAULT_IR_LED_CURRENT      MAX30100_LED_CURR_37MA

extern uint16_t rawIRValue;
extern uint16_t rawRedValue;
extern uint8_t PartID;

void setMode(Mode mode);
void setLedsPulseWidth(LEDPulseWidth ledPulseWidth);
void setSamplingRate(SamplingRate samplingRate);
void setLedsCurrent(LEDCurrent irLedCurrent, LEDCurrent redLedCurrent);
void setHighresModeEnabled(u8 enabled);
void update(void);					

void readFifoData(void);
u8 Write_One_Byte(u8 addr,u8 data);
u8 Read_One_Byte(u8 addr);
u8 Buff_Read(u8 address,u8 *buf, u8 len);

#endif
