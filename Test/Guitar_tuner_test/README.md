# 기록사항
## 작동 유추
- 기존 analogRead로 읽은 데이터를 사운드 분석을 위해 sin파, 교류 파형 모양으로 임의로 만드는것 같다.

## 문제
- 연산 속도가 좀 딸린다. 배열 크기도 크고, for문도 2중 중첩이라 시간 복잡도가 높다

## 테스트 사항
- 연산 주체 이동
    - Atmega2560에선 소리 볼륨 컨트롤만 해주고, 데이터 분석은 성능이 비교적 높은 쪽으로 넘기기