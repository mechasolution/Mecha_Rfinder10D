/**
 * @file read_multi.ino
 * @author Mechasolution Tech Support Team (techms5499@gmail.com)
 * @brief R finder 10D driver library
 * @date 2024-05-03
 *
 * @copyright Copyright (c) 2024 Mechasolution (https://mechasolution.com)
 *
 */

#include <Mecha_Rfinder10D.h>

static Mecha_Rfinder10D rfinder;

void setup() {
  Serial.begin(115200);
  Serial1.begin(115200); // 센서와 연결된 Hardware Serial 포트 초기화

  /**
   * init 메소드에 Stream 타입 객체 전달
   *
   * Baud Rate 문제로 SoftwareSerial은 사용할 수 없으며 반드시 Serial, Serial1과 같은 Hardware Serial을 사용하여야 함.
   * Arduino UNO R4 또는 Mega 등을 활용해 Serial1에 센서를 연결하는것을 권장함.
   * 만약 UNO R3인 경우 센서의 Tx를 아두이노의 0번 핀에 연결한 후 Serial 객체를 공유해 사용할 수 있음.
   * (이 경우 업로드 시에는 센서를 분리해야하며, 시리얼 모니터->아두이노 입력 불가능)
   */
  if (!rfinder.init(Serial1)) {
    Serial.println("Init error!");
    while (true) {
      delay(1000);
    }
  }
}

void loop() {
  rfinder.fetchNewData(); // Serial1의 데이터를 polling함으로, 항상 실행되어야 함.

  if (rfinder.isNewData()) {                  // 마지막으로 .isNewData() 메소드 실행 후 새로운 데이터가 있다면,
    int rfinder_cnt = rfinder.getTargetCnt(); // 인식된 타겟 수 확인

    for (int i = 0; i < rfinder_cnt; i++) { // 타겟 수 만큼 출력
      Serial.print("Range : ");
      Serial.print(rfinder.getRange(i)); // .getRange() 메소드의 인자값으로 타겟 번호 전달
      Serial.print("\t\t");
    }
    Serial.println();
  }
}
