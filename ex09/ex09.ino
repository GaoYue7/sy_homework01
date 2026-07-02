#include <WiFi.h>
#include <WebServer.h>

// AP热点配置
const char* ap_ssid = "ESP32-LAB";
const char* ap_pass = "12345678"; // 密码至少8位

#define TOUCH_PIN 4
const int ledPin = 2;

WebServer server(80);

const char* htmlPage = R"HTML(
<!DOCTYPE html>
<html lang="zh-CN">
<head>
    <meta charset="UTF-8">
    <meta name="viewport" content="width=device-width, initial-scale=1.0">
    <title>ESP32 实时传感器仪表盘</title>
    <style>
        body {
            font-family: Arial, sans-serif;
            text-align: center;
            margin-top: 100px;
            background-color: #f0f0f0;
        }
        h1 { color: #333; }
        .dashboard {
            font-size: 80px;
            font-weight: bold;
            color: #2196F3;
            margin: 50px 0;
            padding: 30px;
            background: white;
            border-radius: 15px;
            box-shadow: 0 4px 8px rgba(0,0,0,0.1);
        }
        .tip { font-size: 20px; color: #666; }
    </style>
</head>
<body>
    <h1>ESP32 触摸传感器实时仪表盘</h1>
    <div class="dashboard" id="sensorValue">--</div>
    <p class="tip">手靠近引脚数值变小，离开恢复</p>

    <script>
        function updateSensor() {
            fetch('/sensor')
                .then(response => response.text())
                .then(value => {
                    document.getElementById('sensorValue').innerText = value;
                })
                .catch(err => console.error('数据拉取失败:', err));
        }
        setInterval(updateSensor, 100);
    </script>
</body>
</html>
)HTML";

void handleRoot() {
    server.send(200, "text/html; charset=UTF-8", htmlPage);
}

void handleSensor() {
    uint16_t touchValue = touchRead(TOUCH_PIN);
    server.send(200, "text/plain", String(touchValue));
}

void setup() {
    Serial.begin(115200);
    
    pinMode(ledPin, OUTPUT);
    digitalWrite(ledPin, LOW);

    // 开启AP热点模式
    WiFi.mode(WIFI_AP);
    WiFi.softAP(ap_ssid, ap_pass);

    Serial.println("AP热点已开启");
    Serial.print("热点名称: ");
    Serial.println(ap_ssid);
    Serial.print("ESP32 IP地址: http://");
    Serial.println(WiFi.softAPIP()); // 默认IP 192.168.4.1

    server.on("/", handleRoot);
    server.on("/sensor", handleSensor);

    server.begin();
    Serial.println("Web服务器已启动");
}

void loop() {
    server.handleClient();
}