// 定义两个LED引脚
const int ledPin1 = 4;  // D4
const int ledPin2 = 5;  // D5

// PWM参数
const int freq = 5000;
const int resolution = 8;

// 分配2个独立LEDC通道（ESP32共0~15通道，任选不重复数字）
const int channel1 = 0;
const int channel2 = 1;

void setup() {
  Serial.begin(115200);
  // 配置通道参数
  ledcSetup(channel1, freq, resolution);
  ledcSetup(channel2, freq, resolution);
  // 通道绑定对应LED引脚
  ledcAttachPin(ledPin1, channel1);
  ledcAttachPin(ledPin2, channel2);
}

void loop() {
  // 阶段1：D4慢慢变亮，D5同步慢慢变暗
  for(int duty = 0; duty <= 255; duty++){
    ledcWrite(channel1, duty);
    ledcWrite(channel2, 255 - duty);
    delay(10);
  }

  // 阶段2：D4慢慢变暗，D5同步慢慢变亮
  for(int duty = 255; duty >= 0; duty--){
    ledcWrite(channel1, duty);
    ledcWrite(channel2, 255 - duty);
    delay(10);
  }

  Serial.println("交替呼吸一轮完成");
}