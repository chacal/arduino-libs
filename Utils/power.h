#ifndef CHACAL_UTILS_POWER_H
#define CHACAL_UTILS_POWER_H

enum WatchdogTimerPrescaler {
  WAKEUP_DELAY_NO_SLEEP = -1,
  WAKEUP_DELAY_16_MS = 0x0,
  WAKEUP_DELAY_32_MS = 0x1,
  WAKEUP_DELAY_64_MS = 0x2,
  WAKEUP_DELAY_125_MS = 0x3,
  WAKEUP_DELAY_250_MS = 0x4,
  WAKEUP_DELAY_500_MS = 0x5,
  WAKEUP_DELAY_1_S = 0x6,
  WAKEUP_DELAY_2_S = 0x7,
  WAKEUP_DELAY_4_S = 0x20,  // WDP3 bit is actually bit 5, see datasheet 10.9.2
  WAKEUP_DELAY_8_S = 0x21,  // WDP3 bit is actually bit 5, see datasheet 10.9.2
};

void powerDown();
void powerDown(WatchdogTimerPrescaler prescaler);
void powerDown(WatchdogTimerPrescaler prescaler1, WatchdogTimerPrescaler prescaler2);
void powerDown(WatchdogTimerPrescaler prescaler1, WatchdogTimerPrescaler prescaler2, WatchdogTimerPrescaler prescaler3);

#endif  //CHACAL_UTILS_POWER_H
