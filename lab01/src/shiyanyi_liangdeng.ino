#define LED_PIN 4

void setup() {
  pinMode(LED_PIN, OUTPUT);
  Serial.begin(115200); // 串口波特率115200，和IDE串口监视器一致
  Serial.println("GPIO4 LED闪烁程序启动");
}

void loop() {
  digitalWrite(LED_PIN, HIGH);
  Serial.println("LED 点亮（GPIO4输出高电平）");
  delay(1000);
  
  digitalWrite(LED_PIN, LOW);
  Serial.println("LED 熄灭（GPIO4输出低电平）");
  delay(1000);
}
