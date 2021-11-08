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

    // 특정 값을 넘지 않으면 진행 안하는 방식으로
    // 어느정도 잡음 필터링
    double volts = ((signalMax - signalMin) * 3.3) / 1024;
    int volume = volts / 3.3 * 100;
    
    if(volume > beforeVolume){
    
      for(int i = 0; i < LENGTH; i++){
        Serial.write(rawData[i]);
        Serial.write("\n");
      }
    }      
    
    beforeVolume = volume + (volume * 0.3);
    count = 0;
  }
}
