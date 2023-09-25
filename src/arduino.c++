//Incluindo as bibliotecas necessárias
#include <ESP8266WiFi.h>
// Nome da sua rede Wifi
const char* ssid = "TP-LINK_6662B0";
// Senha da rede
const char* password = "123654789";
// Site que receberá os dados - IMPORTANTE: SEM O HTTP://
const char* host = "192.168.0.100"; //www.site.com.br
void setup() {
  // Iniciando o Serial
  Serial.begin(115200);
  
  // Conectando na rede wifi
  Serial.println("");
  Serial.print("Conectando");
  WiFi.begin(ssid, password);  
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.print("Conectado a rede: ");
  Serial.println(ssid);
}
void loop() {
  // Criando uma conexao TCP
  WiFiClient client;
  const int httpPort = 8081;
  if (!client.connect(host, httpPort)) {
    return;
  }
  
  // Lendo a temperatura em graus Celsius
  int t = 90;
  
  // Enviando para o host a temperatura lida.
  client.print(String("GET /cadastrar/") + (t) +
                      " HTTP/1.1\r\n" + "Host: " + host + "\r\n" + "Connection: close\r\n\r\n");
  
  // Repetindo a cada 1 minuto
  delay(1000);
  Serial.print("Temperatura enviada: ");
  Serial.println(t);
}