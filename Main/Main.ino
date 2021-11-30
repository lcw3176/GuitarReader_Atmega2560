#define LENGTH 256
#define sample_freq 8919


int rawData[LENGTH];
int count = 0;

unsigned long beforeMills = 0;


void setup(){
  Serial.begin(9600);
  analogReference(EXTERNAL);
}
void loop(){

  if (count < LENGTH) {

    int sample = analogRead(A0);
    rawData[count] = sample;
    count++;
    
  } else {

    long sum = 0;
    long sum_old = 0;
    int freq_per = 0;
    byte pd_state = 0;
    int thresh = 0;
    int period = 0;

    for(int i = 0; i < LENGTH; i++) {
      sum_old = sum;
      sum = 0;

      for(int k = 0; k < LENGTH - i; k++) {
        sum += (rawData[k] - 512) * (rawData[k + i] - 512) / 1024;
      }

      
      // Peak Detect State Machine
      if (pd_state == 2 && (sum - sum_old) <= 0) {
        period = i;
        break;
      }

      if (pd_state == 1 && (sum > thresh) && (sum - sum_old) > 0) {
        pd_state = 2;
      }

      if (!i) {
        thresh = sum * 0.5;
        pd_state = 1;
      }
    }
    
    // Frequency identified in Hz
    if (period != 0) {
      freq_per = sample_freq / period;

      if(freq_per < 500 && millis() - beforeMills >= 1000){
        String data = String(freq_per);
        beforeMills = millis();
        for(int j = 0; j < data.length(); j++){
          Serial.write(data[j]);
        }
        
        Serial.write("\n");
        
      }


    } 

    signalMax = 0;
    signalMin = 1024;
    count = 0;

  }
}
