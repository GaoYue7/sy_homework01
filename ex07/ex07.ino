#include <WiFi.h>
#include <WebServer.h>

// AP热点配置
const char* ap_ssid = "ESP32-LAB";
const char* ap_pass = "12345678"; // 密码至少8位

// 硬件配置
const int ledPin = 2;

WebServer server(80);

const char* html = R"HTML(
<!DOCTYPE html>
<html>
<head>
    <meta charset="UTF-8">
    <title>ESP32调光器</title>
</head>
<body>
    <h1>ESP32 无极调光器</h1>
    <input type="range" min="0" max="255" id="slider" oninput="sendBrightness(this.value)">
    <p>亮度: <span id="val">0</span></p>

    <script>
        function sendBrightness(b) {
            document.getElementById("val").innerText = b;
            fetch("/set?brightness=" + b);
        }
    </script>
</body>
</html>
)HTML";

void handleRoot() {
    server.send(200, "text/html; charset=UTF-8", html);
}

void handleSet() {
    if (server.hasArg("brightness")) {
        int b = server.arg("brightness").toInt();
        b = constrain(b, 0, 255);
        analogWrite(ledPin, b);
        server.send(200, "text/plain", "OK");
    } else {
        server.send(400, "text/plain", "参数错误");
    }
}

void setup() {
    Serial.begin(115200);
    
    pinMode(ledPin, OUTPUT);
    analogWrite(ledPin, 0);

    // 开启AP热点模式
    WiFi.mode(WIFI_AP);
    WiFi.softAP(ap_ssid, ap_pass);

    Serial.println("AP热点已开启");
    Serial.print("热点名称: ");
    Serial.println(ap_ssid);
    Serial.print("访问地址: http://");
    Serial.println(WiFi.softAPIP()); // 默认IP 192.168.4.1

    server.on("/", handleRoot);
    server.on("/set", handleSet);
    server.begin();
    Serial.println("Web服务器已启动");
}

void loop() {
    server.handleClient();
}