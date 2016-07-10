#include "Speedometer.h"

static float speedoMeter_cycleTime_us;
static u8 speedoMeter_channelNumber;
static u8 speedoMeter_unitDistance_cm;

static u32 speedoMeter_totalTime_us = 0;
static u8 speedoMeter_wheelState = speedoMeter_state_free;
static enum boolean speedoMeter_moving = true;

static u16 speedoMeter_distance = 0;
static u16 speedoMeter_speed_cm_s = 0;

// Initialize Timer
static void speedoMeter_initTimer(u8 frequency_MHz) {
	u16 speedoMeter_timerDividers[speedoMeter_dividersNumber] = {1, 8, 64, 256, 1024};
	u16 divider = (u16)(frequency_MHz * 1000 / speedoMeter_intermediateFrequency_KHz);
	u8 i;
	for (i = 0; i < speedoMeter_dividersNumber; i++) {
		if (divider / speedoMeter_timerDividers[i] == 0) {
			speedoMeter_cycleTime_us = (float)speedoMeter_timerDividers[i - 1] / divider;
			break;
		}
	}
	timer0_setMode(timer0_normal);
	timer0_setDivider(i);
	timer0_setOverflowInterruptEnabled(true);
}

// Initialize
void speedoMeter_init(u8 frequency_MHz, u8 channelNumber, u8 unitDistance_cm) {
	speedoMeter_channelNumber = channelNumber;
	speedoMeter_unitDistance_cm = unitDistance_cm;
	speedoMeter_initTimer(frequency_MHz);
}

// Get Distance
u16 speedoMeter_getDistance() {
	return speedoMeter_distance;
}

// Get Speed
u16 speedoMeter_getSpeed() {
	return speedoMeter_speed_cm_s;
}

// Reset
void speedoMeter_reset() {
	speedoMeter_distance = 0;
}

// Read
void speedoMeter_read() {
	if ( (analog_readChannel(speedoMeter_channelNumber) > speedoMeter_threshold_free) && (speedoMeter_wheelState == speedoMeter_state_blocked) ) {
		speedoMeter_wheelState = speedoMeter_state_free;
	} else if ( (analog_readChannel(speedoMeter_channelNumber) < speedoMeter_threshold_blocked) && (speedoMeter_wheelState == speedoMeter_state_free) ) {
		speedoMeter_wheelState = speedoMeter_state_blocked;
		speedoMeter_distance += speedoMeter_unitDistance_cm;
		if (!speedoMeter_moving) {
			timer0_start();
			speedoMeter_moving = true;
			return;
		}
		// Calculate Speed
		u32 speedoMeter_time_us = speedoMeter_totalTime_us + timer0_getCounterValue() * speedoMeter_cycleTime_us;
		speedoMeter_speed_cm_s = (u16)((u32)speedoMeter_unitDistance_cm * 1000000 / speedoMeter_time_us);
		speedoMeter_totalTime_us = 0;
	}
}

// Timer Interrupt
ISR (TIMER0_OVF_vect) {
	speedoMeter_totalTime_us += (u32)(speedoMeter_cycleTime_us * _8bit_max);
	if (speedoMeter_totalTime_us / 1000000 > speedoMeter_maxPendingTime_s) {
		speedoMeter_totalTime_us = 0;
		speedoMeter_speed_cm_s = 0;
		timer0_stop();
		timer0_setCounterValue(0);
		speedoMeter_moving = false;
	}
}