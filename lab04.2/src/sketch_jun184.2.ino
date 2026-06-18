#define TOUCH_PIN 4
#define LED_PIN 2
#define THRESHOLD 40    // 请根据实际触摸值调整（未触摸值较大，触摸后变小）

bool ledState = false;          // LED当前状态
bool prevTouchState = false;    // 上一次检测到的触摸状态（true=触摸中）
unsigned long lastActionTime = 0;
const unsigned long debounceMs = 50;  // 防抖时间（毫秒）

void setup() {
  Serial.begin(115200);
  pinMode(LED_PIN, OUTPUT);
  digitalWrite(LED_PIN, LOW);   // 初始灭
  Serial.println("触摸切换启动（边沿触发）");
}

void loop() {
  // 读取当前触摸值，并判断是否处于触摸状态
  int touchVal = touchRead(TOUCH_PIN);
  bool nowTouching = (touchVal < THRESHOLD);

  // 检测下降沿：从“未触摸”变为“触摸”的瞬间
  if (nowTouching && !prevTouchState) {
    // 防抖处理：防止短时抖动造成多次触发
    if (millis() - lastActionTime > debounceMs) {
      // 执行切换
      ledState = !ledState;
      digitalWrite(LED_PIN, ledState ? HIGH : LOW);
      
      Serial.print("触摸值: ");
      Serial.print(touchVal);
      Serial.print("，LED 切换为: ");
      Serial.println(ledState ? "亮" : "灭");
      
      lastActionTime = millis();
    }
  }

  // 更新上一次状态，供下次比较
  prevTouchState = nowTouching;

  delay(20);  // 轮询间隔，避免CPU过载
}