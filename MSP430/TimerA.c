#include "TimerA.h"

u8 timerA_modes[2] = {timerA_mode_stop, timerA_mode_stop};

void timerA_start(u8 timerNumber) {
	u16* timerControl_ptr = (u16*)((u16)&TA0CTL + 0x20 * timerNumber);
	*timerControl_ptr |= (timerA_modes[timerNumber] << 4);
}

void timerA_stop(u8 timerNumber) {
	u16* timerControl_ptr = (u16*)((u16)&TA0CTL + 0x20 * timerNumber);
	*timerControl_ptr &= ~(0x03 << 4);
}

void timerA_setClockSource(u8 timerNumber, u8 clockSource) {
	u16* timerControl_ptr = (u16*)((u16)&TA0CTL + 0x20 * timerNumber);
	*timerControl_ptr &= ~(0x03 << 8);
	*timerControl_ptr |= (clockSource << 8);
}

void timerA_setMode(u8 timerNumber, u8 mode) {
	timerA_modes[timerNumber] = mode;
}

void timerA_setDivider(u8 timerNumber, u8 prescaler) {
	u16* timerControl_ptr = (u16*)((u16)&TA0CTL + 0x20 * timerNumber);
	*timerControl_ptr &= ~(0x03 << 6);
	*timerControl_ptr |= (prescaler << 6);
}

void timerA_setCounterValue(u8 timerNumber, u16 value) {
	u16* counter_ptr = (u16*)((u16)&TA0R + 0x20 * timerNumber);
	*counter_ptr = value;
}

u16 timerA_getCounterValue(u8 timerNumber) {
	u16* counter_ptr = (u16*)((u16)&TA0R + 0x20 * timerNumber);
	return (*counter_ptr);
}

void timerA_setCompareValue(u8 timerNumber, u8 compareNumber, u16 value) {
	u16* compare_ptr = (u16*) ((u16)&TA0CCR0 + 0x20 * timerNumber + 2 * compareNumber);
	*compare_ptr = value;
}

void timerA_setCompareInterruptEnabled(u8 timerNumber, u8 compareNumber, enum boolean enable) {
	u16* compareControl_ptr = (u16*) ((u16)&TA0CCTL0 + 0x20 * timerNumber + 2 * compareNumber);
	if (enable) {
		*compareControl_ptr |= (1 << 4);
	} else {
		*compareControl_ptr &= ~(1 << 4);
	}
}

void timerA_setInterruptEnabled(u8 timerNumber, enum boolean enable) {
	u16* timerControl_ptr = (u16*)((u16)&TA0CTL + 0x20 * timerNumber);
	if (enable) {
		*timerControl_ptr |= (1 << 1);
	} else {
		*timerControl_ptr &= ~(1 << 1);
	}
}

u8 timerA_checkCompareFlag(u8 timerNumber, u8 compareNumber) {
	u16* compareControl_ptr = (u16*) ((u16)&TACCTL0 + 0x20 * timerNumber + 2 * compareNumber);
	if (*compareControl_ptr & (1 << 0)) {
		*compareControl_ptr &= ~(1 << 0);
		return 1;
	}
	return 0;
}

u8 timerA_checkFlag(u8 timerNumber) {
	u16* timerControl_ptr = (u16*)((u16)&TA0CTL + 0x20 * timerNumber);
	if (*timerControl_ptr & (1 << 0)) {
		*timerControl_ptr &= ~(1 << 0);
		return 1;
	}
	return 0;
}
