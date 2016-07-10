#include "UltraSonicSensors.h"

static float ultraSonicSensors_cycleTime_us;
static u16 ultraSonicSensors_maxDistance;

struct Pin ultraSonicSensors_echoPin;
struct Pin ultraSonicSensors_selectPins[ultraSonicSensors_selectPinsNumber];
struct Pin ultraSonicSensors_triggerPins[ultraSonicSensors_sensorsNumber];

static u16 ultraSonicSensors_values_cm[ultraSonicSensors_sensorsNumber];
static u8 ultraSonicSensors_sensorsCounter = 0;
static enum boolean ultraSonicSensors_overflow = false;

// Initialize Timer
static void ultraSonicSensors_initTimer(u8 frequency_MHz) {
	u16 ultraSonicSensors_timerDividers[ultraSonicSensors_dividersNumber] = {1, 8, 64, 256, 1024};
	u16 divider = (u16)(frequency_MHz * 1000 / ultraSonicSensors_intermediateFrequency_KHz);
	u8 i;
	for (i = 0; i < ultraSonicSensors_dividersNumber; i++) {
		if (divider / ultraSonicSensors_timerDividers[i] == 0) {
			ultraSonicSensors_cycleTime_us = (float)ultraSonicSensors_timerDividers[i - 1] / divider;
			break;
		}
	}
	timer1_setDivider(i);
	timer1_setOverflowInterruptEnabled(true);
}

// Initialize Pins
void ultraSonicSensors_initPins(struct Pin* selectPins, struct Pin* echoPin, struct Pin* triggerPins) {
	u8 i;
	for (i = 0; i < ultraSonicSensors_selectPinsNumber; i++) {
		ultraSonicSensors_selectPins[i].port = selectPins[i].port;
		ultraSonicSensors_selectPins[i].pinNumber = selectPins[i].pinNumber;
		port_setPinDirection(&selectPins[i], port_direction_output);
	}
	
	ultraSonicSensors_echoPin.port = echoPin->port;
	ultraSonicSensors_echoPin.pinNumber = echoPin->pinNumber;
	port_setPinDirection(&echoPin, port_direction_input);
	
	for (i = 0; i < ultraSonicSensors_sensorsNumber; i++) {
		ultraSonicSensors_triggerPins[i].port = triggerPins[i].port;
		ultraSonicSensors_triggerPins[i].pinNumber = triggerPins[i].pinNumber;
		port_setPinDirection(&triggerPins[i], port_direction_output);
	}
}

//	Initialize
void ultraSonicSensors_init(u8 frequency_MHz, u16 maxDistance, struct Pin* selectPins, struct Pin* echoPin, struct Pin* triggerPins) {
	ultraSonicSensors_maxDistance = maxDistance;
	ultraSonicSensors_initTimer(frequency_MHz);
	ultraSonicSensors_initPins(selectPins, echoPin, triggerPins);
	INT_setMode(0, INT_logicalChange);
	INT_enable(0);
	ultraSonicSensors_start();
}

//	Start
static void ultraSonicSensors_start() {
	timer1_setMode(timer1_CTC_OCR1A);
	timer1_setCompareValue(1, ultraSonicSensors_triggerDelay_us);
	timer1_setCompareInterruptEnabled(1, true);
	ultraSonicSensors_selectSensor(ultraSonicSensors_sensorsCounter);
	port_writePin(&ultraSonicSensors_triggerPins[ultraSonicSensors_sensorsCounter], high);
	timer1_start();
}

//	Read Sensor
u16 ultraSonicSensors_getValue_cm(u8 SensorNumber) {
	return (ultraSonicSensors_values_cm[SensorNumber]);
}

//	Select Sensor
static void ultraSonicSensors_selectSensor(u8 SensorNumber) {
	u8 i;
	for (i = 0; i < ultraSonicSensors_selectPinsNumber; i++) {
		port_writePin(&ultraSonicSensors_selectPins[i], (SensorNumber >> i) & 0x01);
	}
}

//	External Interrupt
ISR (INT0_vect) {
	WDT_reset();
	if (port_readPin(&ultraSonicSensors_echoPin)) {
		timer1_setCompareInterruptEnabled(1, false);
		timer1_setMode(timer1_normal);
		timer1_start();
	} else {
		timer1_stop();
		if (ultraSonicSensors_overflow) {
			ultraSonicSensors_values_cm[ultraSonicSensors_sensorsCounter] = ultraSonicSensors_maxDistance;
			ultraSonicSensors_overflow = false;
		} else {
			float time_us = ultraSonicSensors_cycleTime_us * timer1_getCounterValue();
			ultraSonicSensors_values_cm[ultraSonicSensors_sensorsCounter] = (u16)(lround(time_us * ultraSonicSensors_soundSpeed_Cm_us));
		}
		ultraSonicSensors_sensorsCounter = (ultraSonicSensors_sensorsCounter + 1) % ultraSonicSensors_sensorsNumber;
		ultraSonicSensors_start();
	}
}

//	Timer Overflow Interrupt
ISR (TIMER1_OVF_vect) {
	ultraSonicSensors_overflow = true;
}

//	Timer Compare Interrupt
ISR (TIMER1_COMPA_vect) {
	timer1_stop();
	port_writePin(&ultraSonicSensors_triggerPins[ultraSonicSensors_sensorsCounter], low);
	
}