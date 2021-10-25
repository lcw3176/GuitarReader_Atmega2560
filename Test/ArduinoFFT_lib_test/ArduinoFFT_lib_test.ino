/* Arduino Code */

#include "arduinoFFT.h"

arduinoFFT FFT = arduinoFFT(); /* Create FFT object */
/*
These values can be changed in order to evaluate the functions
*/
const uint16_t samples = 64; //This value MUST ALWAYS be a power of 2
const double samplingFrequency = 5000;
double vReal[samples];
double vImag[samples];

void setup()
{
  Serial.begin(115200);
  analogReference(EXTERNAL);
}

void loop()
{
  for (uint8_t i = 0; i < samples; i++)
  {
    vReal[i] = analogRead(A0);
    delayMicroseconds(100);
    vImag[i] = 0;
  }
  FFT.Windowing(vReal, samples, FFT_WIN_TYP_HAMMING, FFT_FORWARD);  /* Weigh data */
  FFT.Compute(vReal, vImag, samples, FFT_FORWARD); /* Compute FFT */
  FFT.ComplexToMagnitude(vReal, vImag, samples); /* Compute magnitudes */
  double x;
  double v;  
  FFT.MajorPeak(vReal, samples, samplingFrequency, &x, &v);

  Serial.print(x);
  Serial.print(", ");
  Serial.println(v);
//  PrintVector(vReal);
}

void PrintVector(double *vData)
{
  for (uint16_t i = 0; i < samples / 2; i++)
  {
    uint8_t val_temp = map(vData[i],0,1023,0,255);
    Serial.write(val_temp);
  }
  Serial.write('\n');
}


//출처: https://geronimob.tistory.com/27 [Geronimo]
