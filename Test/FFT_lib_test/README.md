# 기록사항
## 성능
- arduinoFFT보다는 훨씬 속도가 빠름
- 연산이 빨라서 그런지 분석 스펙트럼도 넓게 나옴

## 에러
### 최신 아두이노 IDE에서는 컴파일 에러남
- 원인
    - prog_int16_t 타입 에러
    - 현재 사용되지 않는 타입으로 추정
- 해결
    - 스케치 버전 1.0.6 이하로 사용