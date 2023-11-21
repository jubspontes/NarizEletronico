
#include <DHT.h>
#include <SD.h>

// Pinos dos sensores
#define MQ02_PIN A2
#define MQ03_PIN A1
#define MQ04_PIN A0
#define MQ05_PIN A3
#define MQ06_PIN A4
#define MQ07_PIN A10
#define MQ08_PIN A5
#define MQ09_PIN A9
#define MQ131_PIN A6
#define MQ135_PIN A8
#define DHTPIN A11 // Pino digital ao qual o sensor DHT22 está conectado
#define DHTTYPE DHT22
DHT dht(DHTPIN, DHTTYPE);
#define cooler 3
  byte lock = 1;
#define pulsePin 32
int S[11] = {0};
// Pino do módulo SD
const int chipSelect = 4;

// Tempo de aquecimento dos sensores (em segundos)
const int WARMUP_TIME = 1;

void setup() {
  pinMode(cooler, OUTPUT);
  analogWrite(cooler,255);
  // Inicialização da comunicação serial 
  Serial.begin(9600);
  // Aguarda a inicialização da porta serial
  while (!Serial) {
    delay(10);
  }
  dht.begin(); // Inicialização do sensor DHT22
 pinMode(pulsePin, OUTPUT);
 // Inicialização do módulo SD
 if (SD.begin(chipSelect)) {
    Serial.println("Módulo SD inicializado.");
  } else {

    Serial.println("Falha na inicialização do módulo SD.");
  }
  // Aquecimento dos sensores
  Serial.println("Aquecendo os sensores...");
  delay(WARMUP_TIME * 1000); // Aguarda o tempo de aquecimento em milissegundos
  
}

void loop() {
   
// Abra um arquivo no módulo SD
  File dataFile = SD.open("dados.txt", FILE_WRITE);
  // Imprime cabeçalho da tabela
  Serial.println("data   temp     humi   MQ02  MQ03   MQ04  MQ05  MQ06   MQ07   MQ08   MQ09  MQ131  MQ135");
  dataFile.print("data   temp     humi   MQ02  MQ03   MQ04  MQ05  MQ06   MQ07   MQ08   MQ09  MQ131  MQ135");
  // Leitura dos valores dos sensores
  int mq02Value = analogRead(MQ02_PIN);
  int mq03Value = analogRead(MQ03_PIN);
  int mq04Value = analogRead(MQ04_PIN);
  int mq05Value = analogRead(MQ05_PIN);
  int mq06Value = analogRead(MQ06_PIN);
  int mq07Value = analogRead(MQ07_PIN);
  int mq08Value = analogRead(MQ08_PIN);
  int mq09Value = analogRead(MQ09_PIN);
  int mq131Value = analogRead(MQ131_PIN);
  int mq135Value = analogRead(MQ135_PIN);
  float temperatura = dht.readTemperature();
  float umidade = dht.readHumidity();

  // Impressão dos valores dos sensores em formato de tabela horizontal
  Serial.print("     ");
  Serial.print(temperatura);
  Serial.print("°C   ");
  Serial.print(umidade);
  Serial.print("%");
  Serial.print("   ");
  Serial.print(mq02Value);
  Serial.print("   ");
  Serial.print(mq03Value);
  Serial.print("   ");
  Serial.print(mq04Value);
  Serial.print("    ");
  Serial.print(mq05Value);
  Serial.print("    ");
  Serial.print(mq06Value);
  Serial.print("    ");
  Serial.print(mq07Value);
  Serial.print("    ");
  Serial.print(mq08Value);
  Serial.print("     ");
  Serial.print(mq09Value);
  Serial.print("     ");
  Serial.print(mq131Value);
  Serial.print("    ");
  Serial.print(mq135Value);
  Serial.println();
if(digitalRead(pulsePin) == HIGH){
        analogReference(INTERNAL1V1); S[5] += analogRead(mq07Value); S[7] += analogRead(mq09Value); analogReference(DEFAULT);
      }
      else {
        analogReference(DEFAULT); S[5] += analogRead(mq07Value); S[7] += analogRead(mq09Value);
      }
   delay(1000);
  


  if (dataFile) {
    // Escreva os dados no arquivo
    dataFile.print(temperatura);
    dataFile.print("%");
    dataFile.print(umidade);
    dataFile.print(",");
    dataFile.print(mq02Value);
    dataFile.print(",");
    dataFile.print(mq03Value);
    dataFile.print(",");
    dataFile.print(mq04Value);
    dataFile.print(",");
    dataFile.print(mq05Value);
    dataFile.print(",");
    dataFile.print(mq06Value);
    dataFile.print(",");
    dataFile.print(mq07Value);
    dataFile.print(",");
    dataFile.print(mq08Value);
    dataFile.print(",");
    dataFile.print(mq09Value);
    dataFile.print(",");
    dataFile.print(mq131Value);
    dataFile.print(",");
    dataFile.print(mq135Value);
    dataFile.println();

    // Feche o arquivo
    dataFile.close();
  } else {
    Serial.println("Erro ao abrir o arquivo.");
  }

  // Delay e loop
  delay(1000); // Aguarda 1 segundo antes de fazer a próxima leitura
}
