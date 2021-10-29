#define LENGTH 256
#define sample_freq 8919
byte rawData[LENGTH];
int count = 0;

unsigned int signalMax = 0;
unsigned int signalMin = 1024;

void setup(){
  Serial.begin(115200);
  analogReference(EXTERNAL);
}
void loop(){
  
  if (count < LENGTH) {
    count++;
    int sample = analogRead(A0);
    rawData[count] = sample;

    if(sample > signalMax){
      signalMax = sample;
    } else if(sample < signalMin){
      signalMin = sample;
    }
    
  } else {
    long sum = 0;
    long sum_old = 0;
    int freq_per = 0;
    byte pd_state = 0;
    int thresh = 0;
    int period = 0;
    int len = sizeof(rawData);
    
    for(int i = 0; i < len; i++)
    {
      sum_old = sum;
      sum = 0;
      
      for(int k = 0; k < len-i; k++) {
        sum += (rawData[k]-128)*(rawData[k+i]-128) / 256;
      }
      
      // Peak Detect State Machine
      if (pd_state == 2 && (sum-sum_old) <=0) 
      {
        period = i;
        pd_state = 3;
      }
      if (pd_state == 1 && (sum > thresh) && (sum-sum_old) > 0) {
        pd_state = 2;
      }
      if (!i) {
        thresh = sum * 0.5;
        pd_state = 1;
      }
    }

    double volts = ((signalMax - signalMin) * 3.3) / 1024;
    // Frequency identified in Hz
 
    if (thresh >100 && period != 0 && volts >= 0.15) {
      freq_per = sample_freq / period;
      String data = String(freq_per);
 
      for(int j = 0; j < data.length(); j++){
        Serial.write(data[j]);
      }
     
      Serial.write("\n");
    }

    count = 0;
    signalMax = 0;
    signalMin = 1024;
  }
}
