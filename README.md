# GuitarReader-Atmega2560
#### 본 프로젝트는 [GuitarReader_Cs](https://github.com/lcw3176/GuitarReader_Cs)와 연동된 프로젝트 입니다.
## 개요
### 소개
- 기타 연주 시 그에 맞는 주파수 값을 반환합니다.
### 기능
- 기타 주파수 분석
- ~~볼륨 컨트롤~~
    - ~~볼륨이 점점 작아지는 상황에서는 작동하지 않습니다~~
    - ~~기타 줄을 친 순간에만 인식합니다~~
- 시리얼 통신
    - [GuitarReader_Cs](https://github.com/lcw3176/GuitarReader_Cs)이랑 데이터 전송을 위해 사용됩니다.
### 기술 스택, 사용된 부품
- C++, Sketch IDE
- Atmega 2560
- OPA344 사운드 모듈

### 회로 구성
<img src="https://user-images.githubusercontent.com/59993347/143398275-069817ab-1a63-4ce6-9a4b-05fee07a63c3.jpg" height="300">

- 3.3v 사용 (OPA344 전원, 아두이노 레퍼런스 전압)
- A0 포트 사용 (데이터 읽기)

### 폴더 구조
- included_Lib: 테스트 시 사용된 라이브러리들
- Test: 테스트 했던 코드들
- Main: 프로젝트에 사용된 메인 코드

### 작동 영상
- https://www.youtube.com/watch?v=zB0uJF3MIWw
## 조사 자료
### 데이터 분석
![데이터분석](https://user-images.githubusercontent.com/59993347/139521515-095555d6-a22e-41e5-94a8-98ec07217c74.png)

### 참조
- [OpenMusicLabs - FFT] http://wiki.openmusiclabs.com/wiki/ArduinoFFT
- [Arduino Reference] https://www.arduino.cc/reference/en/libraries/arduinofft/
- [arduinoFFT Github] https://github.com/kosme/arduinoFFT
- [아두이노-푸리에 변환 (FFT)과 활용] https://geronimob.tistory.com/27
- [마이크 모듈로 주파수 측정하기] https://www.hardcopyworld.com/?p=2354
- [오픈소스 컨트롤러를 사용한 층간 소음 방지 시스템] https://www.koreascience.or.kr/article/JAKO201732663196722.pdf
- [FFT 온보드 ESP32를 수행하고 주파수와 진폭을 모두 얻는 방법] https://ichi.pro/ko/fft-onbodeu-esp32leul-suhaenghago-jupasuwa-jinpog-eul-modu-eodneun-bangbeob-76881375451098
- [OpenMusicLabs - FHT] http://wiki.openmusiclabs.com/wiki/ArduinoFHT
- [Arduino Based Guitar Tuner] https://circuitdigest.com/microcontroller-projects/arduino-uno-guitar-tuner