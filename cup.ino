#include "HX711.h"

// HX711.DOUT  - pin #A1  데이터 출력핀
// HX711.PD_SCK - pin #A0 무게 측정 입력 핀
// factor: 인수
HX711 scale(A1, A0);    // gain(증폭값)인자는 생략됨: 기본 값 128은 라이브러리에 사용됨 -> 

void setup() {
  Serial.begin(38400);  // 시리얼 출력 
  Serial.println("HX711 Demo");

  Serial.println("Before setting up the scale:"); // 세팅 전 무게
  Serial.print("read: \t\t");
  Serial.println(scale.read());     // 스케일은 무게를 반환, 아날로그를 출력

  Serial.print("read average: \t\t");
  Serial.println(scale.read_average(20));   // 0.02초동안 측정한 값의 평균 

  Serial.print("get value: \t\t");
  Serial.println(scale.get_value(5));   // 0.005초의 평균값에 오프셋(tare에서 얻은 값)을 뺀 값 print the average of 5 readings from the ADC minus the tare weight (not set yet)

  Serial.print("get units: \t\t");
  Serial.println(scale.get_units(5), 1);  // 소수점 1자리 까지만 출력, print the average of 5 readings from the ADC minus tare weight (not set) divided 
            // by the SCALE parameter (not set yet)  

  scale.set_scale(2280.f);     // this value is obtained by calibrating the scale with known weights; see the README for details
  scale.tare();               // 그릇의 무게를 잰것, 0점 조절함  reset the scale to 0

  Serial.println("After setting up the scale:");

  Serial.print("read: \t\t");
  Serial.println(scale.read());                 // print a raw reading from the ADC

  Serial.print("read average: \t\t");
  Serial.println(scale.read_average(20));       // print the average of 20 readings from the ADC

  Serial.print("get value: \t\t");
  Serial.println(scale.get_value(5));   // print the average of 5 readings from the ADC minus the tare weight, set with tare()

  Serial.print("get units: \t\t");
  Serial.println(scale.get_units(5), 1);        // print the average of 5 readings from the ADC minus tare weight, divided 
            // by the SCALE parameter set with set_scale

  Serial.println("Readings:");
}

void loop() {
  Serial.print("one reading:\t");
  Serial.print(-scale.get_units(), 1);
  Serial.print("\t| average:\t");
  Serial.println(-scale.get_units(10), 1);

  scale.power_down();             // 무게센서 전원 끄기
  delay(1000);
  scale.power_up();               // 무게센서 전원 켜기
}
