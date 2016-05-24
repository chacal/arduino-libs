#include <Arduino.h>
#include <avr/sleep.h>
#include <util/atomic.h>
#include "power.h"

#ifndef CUSTOM_WATCHDOG_INT_HANDLER
ISR(WDT_vect) { [](){}; }  // Set default watchdog interrupt handler to do nothing. #define CUSTOM_WATCHDOG_INT_HANDLER to use other implementation
#endif

inline void setWDTCSR(byte wdtcsr) {
  ATOMIC_BLOCK(ATOMIC_FORCEON) {
      WDTCSR |= bit(WDE) | bit(WDCE); // Timed sequence, set WDE & WDCE to allow changing WDTCSR
      WDTCSR = wdtcsr;
  }
}

void enableWDTInterrupts(WatchdogTimerPrescaler prescaler) {
    byte newWDTCSR = (WDTCSR & ~0x27) | (prescaler & 0x27);  // Set prescaler, 0x27 is mask for bits 5 & 2..0. First clear them to 0, then set if set in prescaler.
    newWDTCSR |= bit(WDIE);             // Enable watchdog interrupts
    MCUSR &= ~ bit(WDRF);               // Clear Watchdog System Reset Flag
    setWDTCSR(newWDTCSR);
}

void disableWDTInterrupts() {
  setWDTCSR(WDTCSR & ~ bit(WDIE));
}

void powerDown() {
  byte adcsraSave = ADCSRA;
  ADCSRA &= ~ bit(ADEN); // disable the ADC
  set_sleep_mode(SLEEP_MODE_PWR_DOWN);
  ATOMIC_BLOCK(ATOMIC_FORCEON) {
    sleep_enable();
#ifdef BODSE
    MCUCR = MCUCR | bit(BODSE) | bit(BODS); // timed sequence
    MCUCR = (MCUCR & ~ bit(BODSE)) | bit(BODS);
#endif
  }

  sleep_cpu();
  sleep_disable();
  ADCSRA = adcsraSave;
}

void powerDown(WatchdogTimerPrescaler prescaler) {
  if(prescaler != WAKEUP_DELAY_NO_SLEEP) {
    enableWDTInterrupts(prescaler);
    powerDown();
    disableWDTInterrupts();
  }
}

void powerDown(WatchdogTimerPrescaler prescaler1, WatchdogTimerPrescaler prescaler2) {
  powerDown(prescaler1);
  powerDown(prescaler2);
}

void powerDown(WatchdogTimerPrescaler prescaler1, WatchdogTimerPrescaler prescaler2, WatchdogTimerPrescaler prescaler3) {
  powerDown(prescaler1);
  powerDown(prescaler2);
  powerDown(prescaler3);
}
