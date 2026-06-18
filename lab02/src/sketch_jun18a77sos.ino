// 定义LED引脚，ESP32通常板载LED连接在GPIO 2
const int ledPin = 2; 

void setup() {
  // 初始化串口通信，设置波特率为115200
  Serial.begin(115200);
  // 将LED引脚设置为输出模式
  pinMode(ledPin, OUTPUT);
}

void loop() {
  // ========== 第一段 S：短闪3次 ==========
  Serial.println("发送S：三短闪");
  for(int i=0; i<3; i++){
    digitalWrite(ledPin, HIGH);
    Serial.println("LED ON 短亮");
    delay(200);
    digitalWrite(ledPin, LOW);
    Serial.println("LED OFF");
    delay(200);
  }
  delay(500); // S与O之间字母间隔

  // ========== 第二段 O：长闪3次 ==========
  Serial.println("发送O：三长闪");
  for(int i=0; i<3; i++){
    digitalWrite(ledPin, HIGH);
    Serial.println("LED ON 长亮");
    delay(600);
    digitalWrite(ledPin, LOW);
    Serial.println("LED OFF");
    delay(200);
  }
  delay(500); // O与S之间字母间隔

  // ========== 第三段 S：短闪3次 ==========
  Serial.println("发送S：三短闪");
  for(int i=0; i<3; i++){
    digitalWrite(ledPin, HIGH);
    Serial.println("LED ON 短亮");
    delay(200);
    digitalWrite(ledPin, LOW);
    Serial.println("LED OFF");
    delay(200);
  }
  delay(2000); // 完整SOS一轮结束，单词间隔，循环下一轮
}