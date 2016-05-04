#include <math.h>

// This assumes that thermistor has nominal value of 10k Ohm
float getTemperature(int RawADC, int dividerResistor, int calibration) {
  long resistance = (dividerResistor + calibration) * ((1024.0 / RawADC) - 1); 
  float temp = log(resistance); // Saving the Log(resistance) so not to calculate  it 4 times later
  temp = 1 / (0.001129148 + (0.000234125 * temp) + (0.0000000876741 * temp * temp * temp));
  temp = temp - 273.15;  // Convert Kelvin to Celsius                      
  return temp;
}
