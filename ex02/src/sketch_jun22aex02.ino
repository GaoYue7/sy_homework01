// ex02：使用millis()实现1Hz LED闪烁（亮1s、灭1s）
// 非阻塞写法，全程不使用delay()
#define LED_PIN 2  // 板载LED引脚

unsigned long currentTime;    // 记录当前系统毫秒时间
unsigned long lastToggleTime = 0; // 上次LED翻转的时间点
const unsigned long interval = 1000; // 翻转间隔1000ms=1秒
bool ledState = LOW;          // LED当前状态

void setup() {
  pinMode(LED_PIN, OUTPUT);
  Serial.begin(115200);      // 串口波特率115200，匹配实验步骤
}

void loop() {
  currentTime = millis();    // 获取当前运行毫秒数

  // 判断是否达到1秒间隔，翻转LED
  if (currentTime - lastToggleTime >= interval) {
    lastToggleTime = currentTime; // 更新上次翻转时间
    ledState = !ledState;         // 状态取反
    digitalWrite(LED_PIN, ledState);

    // 串口打印状态，对应实验串口监视器要求
    if (ledState == HIGH) {
      Serial.println("LED ON");
    } else {
      Serial.println("LED OFF");
    }
  }

  // 这里可以添加其他任务，不会被延时阻塞
}
// ex02补充：新增串口打印LED亮灭状态，完成第3次提交