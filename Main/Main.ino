#include "arduinoFFT.h"

arduinoFFT FFT = arduinoFFT();
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
  double frequency;
  double volume; 
  
  for (uint8_t i = 0; i < samples; i++)
  {
    vReal[i] = analogRead(A0);
    delayMicroseconds(100);
    vImag[i] = 0;
  }
  
  FFT.Windowing(vReal, samples, FFT_WIN_TYP_HAMMING, FFT_FORWARD);  /* Weigh data */
  FFT.Compute(vReal, vImag, samples, FFT_FORWARD); /* Compute FFT */
  FFT.ComplexToMagnitude(vReal, vImag, samples); /* Compute magnitudes */
 
  FFT.MajorPeak(vReal, samples, samplingFrequency, &frequency, &volume);
  
  String freStr = String(frequency, DEC);
  String volStr = String(volume, DEC);
  
  for(int i = 0; i < freStr.length(); i++){
    Serial.write(freStr[i]);
  }
  
  Serial.write(",");
  
  for(int i = 0; i < volStr.length(); i++){
    Serial.write(volStr[i]);
  }
  
}
