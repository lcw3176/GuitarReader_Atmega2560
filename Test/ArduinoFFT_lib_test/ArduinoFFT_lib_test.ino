/* Arduino Code */

#include "arduinoFFT.h"

arduinoFFT FFT = arduinoFFT(); /* Create FFT object */
/*
These values can be changed in order to evaluate the functions
*/
const uint16_t samples = 128; //This value MUST ALWAYS be a power of 2
double signalFrequency = 1000;

double vReal[samples];
double vImag[samples];

void setup()
{
  Serial.begin(115200);
}

void loop()
{
  for (uint8_t i = 0; i < samples; i++)
  {
    vReal[i] = analogRead(A0);
//    delayMicroseconds(100);
    vImag[i] = 0;
  }
  FFT.Windowing(vReal, samples, FFT_WIN_TYP_HAMMING, FFT_FORWARD);  /* Weigh data */
  FFT.Compute(vReal, vImag, samples, FFT_FORWARD); /* Compute FFT */
  FFT.ComplexToMagnitude(vReal, vImag, samples); /* Compute magnitudes */
  PrintVector(vReal);
}

void PrintVector(double *vData)
{
  for (uint16_t i = 0; i < samples / 2; i++)
  {
    uint8_t val_temp = map(vData[i],0,1000,0,255);
    Serial.write(val_temp);
  }
  Serial.write('\n');
}


//출처: https://geronimob.tistory.com/27 [Geronimo]
