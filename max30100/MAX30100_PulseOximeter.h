#ifndef MAX30100_PULSEOXIMETER_H
#define MAX30100_PULSEOXIMETER_H

#define SAMPLING_FREQUENCY                  100
#define CURRENT_ADJUSTMENT_PERIOD_MS        500
#define IR_LED_CURRENT                      MAX30100_LED_CURR_50MA
#define RED_LED_CURRENT_START               MAX30100_LED_CURR_27_1MA
#define DC_REMOVER_ALPHA                    0.95

#include <stdint.h>

#include "MAX30100.h"
#include "MAX30100_BeatDetector.h"
#include "MAX30100_Filters.h"
#include "MAX30100_SpO2Calculator.h"

typedef enum PulseOximeterState 
{
    PULSEOXIMETER_STATE_INIT,
    PULSEOXIMETER_STATE_IDLE,
    PULSEOXIMETER_STATE_DETECTING
} PulseOximeterState;

typedef enum PulseOximeterDebuggingMode 
{
    PULSEOXIMETER_DEBUGGINGMODE_NONE,
    PULSEOXIMETER_DEBUGGINGMODE_RAW_VALUES,
    PULSEOXIMETER_DEBUGGINGMODE_AC_VALUES,
    PULSEOXIMETER_DEBUGGINGMODE_PULSEDETECT
} PulseOximeterDebuggingMode;



void PulseOximeter(void);

void begin(PulseOximeterDebuggingMode mode);
void POupdate(void);
float getHeartRate(void);
uint8_t POgetSpO2(void);
uint8_t getRedLedCurrentBias(void);
void setOnBeatDetectedCallback(float *cb);
void checkSample(void);
void checkCurrentBias(void);
void onBeatDetected1(void);

extern    float onBeatDetected;
extern    PulseOximeterState state;
extern    PulseOximeterDebuggingMode debuggingMode;
extern    uint32_t tsFirstBeatDetected;
extern    uint32_t tsLastBeatDetected;
extern    uint32_t tsLastSample;
extern    uint32_t tsLastBiasCheck;
extern    uint32_t tsLastCurrentAdjustment;
extern	uint8_t redLedPower;

extern DCRemover irDCRemover;
extern DCRemover redDCRemover;

extern signed short HeartRate;
extern u8  SPO2;

void SPO2_Init(void);

#endif
