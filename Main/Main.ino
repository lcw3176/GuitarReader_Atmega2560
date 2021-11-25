#define LENGTH 256
#define sample_freq 8919


int rawData[LENGTH];
int count = 0;

unsigned int signalMax = 0;
unsigned int signalMin = 1024;

int beforeVolume = 0;
int beforeFrequency = 0;

void setup(){
  Serial.begin(115200);
  analogReference(EXTERNAL);
}
void loop(){

  if (count < LENGTH) {

    int sample = analogRead(A0);
    rawData[count] = sample;
    count++;

     
    // 소리 크기 측정
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
    
    // 특정 값을 넘지 않으면 진행 안하는 방식으로
    // 어느정도 잡음 필터링
    double volts = ((signalMax - signalMin) * 3.3) / 1024;
    int volume = volts / 3.3 * 100;

    // Frequency identified in Hz
    if (period != 0) {
      freq_per = sample_freq / period;

      // 볼륨값이 작아지는 상황은 필터링
      // 연주했을 때 한번만 입력받음
      if(freq_per < 1500 && volume > beforeVolume){
        beforeFrequency = freq_per;
        String data = String(freq_per);
  
        for(int j = 0; j < data.length(); j++){
          Serial.write(data[j]);
        }
        
        Serial.write("\n");
      }      
    }

    if(freq_per != 0 && freq_per < 1500 && abs(beforeFrequency - freq_per) >= 20){
      beforeVolume = 0;
    } else{
      beforeVolume = volume + (volume * 0.3);
    }
    
    signalMax = 0;
    signalMin = 1024;
    count = 0;

  }


}