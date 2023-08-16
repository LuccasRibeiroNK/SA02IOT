#include <LiquidCrystal_I2C.h>
#include <DHTesp.h>
#include <WiFi.h>
#include <HTTPClient.h>


const int dhtPin = 13;
const int primeiroLed = 4; // Primeiro LED conectado à porta D4
const int segundoLed = 5; // Segundo LED conectado à porta D5
const int buzzerPin = 2; // Buzzer conectado à porta D2
const char* ssid = "Wokwi-GUEST";
const char* password = "";

DHTesp sensor;

int lcdColumns = 16;
int lcdRows = 2;

LiquidCrystal_I2C lcd(0x27, lcdColumns, lcdRows);

void setup() {
  Serial.begin(115200);
  Serial.println("Hello turma!");


  //Configurações do Wifi
  Serial.print("Conectando a Rede");
  WiFi.begin(ssid, password); // Estancia a rede wifi para conexão
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println();
  Serial.println("Conectado a Rede Wifi");
  sensor.setup(dhtPin, DHTesp::DHT22);

  pinMode(primeiroLed, OUTPUT); // Configura o primeiro LED como saída
  pinMode(segundoLed, OUTPUT); // Configura o segundo LED como saída
  pinMode(buzzerPin, OUTPUT); // Configura o buzzer como saída

  lcd.init();
  lcd.backlight();
  lcd.clear(); // Limpa o display ao iniciar o programa
}

void exibirMensagemBoasVindas() {
  lcd.setCursor(0, 0);
  lcd.print("Ola, grupo 02!");
  lcd.setCursor(0, 1);
  lcd.print("Sejam bem-vindos!");
}

void loop() {
  // Exibe a mensagem de boas-vindas e os valores de temperatura e umidade no LCD
  float temp = sensor.getTemperature();
  float humidity = sensor.getHumidity();

  //Comunicação via protocolo http
  String url = "https://api.thingspeak.com/update?api_key=8GVG7AKIR9AYJRLQ&field1=" + String(temp) + "&field2=" + String(humidity);

  //Objeto http
  HTTPClient client;

  client.begin(url);
  int httpCode = client.GET();
  Serial.print("Código recebido da API: ");
  Serial.println(httpCode);

  if (httpCode >= 200 && httpCode <= 299) {
    String payload = client.getString();
    Serial.println(payload);
  } else {
    Serial.println("Problemas ao efetuar busca na API!");
  }
  exibirMensagemBoasVindas();

  delay(5000);

  // Limpa o display antes de exibir os valores de temperatura e umidade
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Temp: ");
  lcd.print(temp, 1);
  lcd.write(0b11011111); // Escreve o caractere especial do grau (°)
  lcd.print("C");
  lcd.setCursor(0, 1);
  lcd.print("Humidade: ");
  lcd.print(humidity, 1);
  lcd.print("%");
  // Aciona o LED e o buzzer se a temperatura for maior que 35°C

  if (temp > 35) {
    digitalWrite(primeiroLed, HIGH);
    digitalWrite(buzzerPin, HIGH);
  } else {
    digitalWrite(primeiroLed, LOW);
    digitalWrite(buzzerPin, LOW);
  }

  // Aciona o LED se a umidade for maior que 70%
  if (humidity > 70) {
    digitalWrite(segundoLed, HIGH);
    digitalWrite(buzzerPin, HIGH);
  } else {
    digitalWrite(segundoLed, LOW);
    digitalWrite(buzzerPin, LOW);
  }

  delay(5000);
}