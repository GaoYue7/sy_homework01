// ex03 millis非阻塞实现标准SOS：三短、三长、三短
#define LED_PIN 2

unsigned long currentTime;
unsigned long lastTime = 0;
bool ledState = LOW;

// 时序参数
const unsigned shortOn  = 200;   // 短亮时长
const unsigned shortOff = 200;   // 短闪间隔
const unsigned longOn   = 600;   // 长亮时长
const unsigned longOff  = 200;   // 长闪间隔
const unsigned longPause = 2000; // 整套SOS结束后长停顿

int stage = 0;   // 0=3短闪 1=3长闪 2=再3短闪 3=结束停顿
int count = 0;   // 当前阶段闪烁计数

void setup() {
  pinMode(LED_PIN, OUTPUT);
  Serial.begin(115200);
  digitalWrite(LED_PIN, LOW);
}

void loop() {
  currentTime = millis();
  unsigned long delta = currentTime - lastTime;

  switch(stage)
  {
    // 第一阶段：连续3次短闪
    case 0:
      if (!ledState)
      {
        if (delta >= shortOff)
        {
          ledState = HIGH;
          digitalWrite(LED_PIN, HIGH);
          Serial.println("SOS 短亮");
          lastTime = currentTime;
        }
      }
      else
      {
        if (delta >= shortOn)
        {
          ledState = LOW;
          digitalWrite(LED_PIN, LOW);
          Serial.println("SOS 短灭");
          lastTime = currentTime;
          count++;
          // 3次短闪完成，进入长闪阶段
          if (count >= 3)
          {
            count = 0;
            stage = 1;
          }
        }
      }
      break;

    // 第二阶段：连续3次长闪
    case 1:
      if (!ledState)
      {
        if (delta >= longOff)
        {
          ledState = HIGH;
          digitalWrite(LED_PIN, HIGH);
          Serial.println("SOS 长亮");
          lastTime = currentTime;
        }
      }
      else
      {
        if (delta >= longOn)
        {
          ledState = LOW;
          digitalWrite(LED_PIN, LOW);
          Serial.println("SOS 长灭");
          lastTime = currentTime;
          count++;
          // 3次长闪完成，进入第二组短闪
          if (count >= 3)
          {
            count = 0;
            stage = 2;
          }
        }
      }
      break;

    // 第三阶段：再连续3次短闪
    case 2:
      if (!ledState)
      {
        if (delta >= shortOff)
        {
          ledState = HIGH;
          digitalWrite(LED_PIN, HIGH);
          Serial.println("SOS 短亮");
          lastTime = currentTime;
        }
      }
      else
      {
        if (delta >= shortOn)
        {
          ledState = LOW;
          digitalWrite(LED_PIN, LOW);
          Serial.println("SOS 短灭");
          lastTime = currentTime;
          count++;
          // 三组全部完成，进入长停顿
          if (count >= 3)
          {
            count = 0;
            stage = 3;
          }
        }
      }
      break;

    // 整套SOS结束，长时间熄灭等待下一轮
    case 3:
      if (delta >= longPause)
      {
        stage = 0;
        lastTime = currentTime;
        Serial.println("=== 一轮SOS完成，重新开始 ===");
      }
      break;
  }
}