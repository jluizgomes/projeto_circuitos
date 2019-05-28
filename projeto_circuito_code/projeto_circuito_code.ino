#include <Adafruit_Sensor.h>
#include <DHT.h>
#include <DHT_U.h>

// DHT sensor conectado na saida digital 2
#define DHTPIN 2

// DHT 22 (AM2302)
#define DHTTYPE DHT22

DHT_Unified dht(DHTPIN, DHTTYPE);

uint32_t delayMS;

//Declaração de portas digitais aos quais os led e a entrada digital do sensor vão estar conectados.
int pinoledverde = 6; //Pino ligado ao led vermelho
int pinoledavermelho = 5; //Pino ligado ao led azul
int pinoSensor = 3;  //Pino ligado ao sensor PIR

//Variavel para guardar valor do sensor
int iniciaSensor;

//Variável para calibração do sensor
int calibracao = 2;

void setup()
{
  //configura a comunicação seria com baud rate de 9600
  Serial.begin(9600);
  delay(1000);

  Serial.print("DHT Starting... ");

  // inicializa DHT22 sensor
  dht.begin();
  Serial.println("Successfully Started");

  // Detalhes do sensor de temperatura.
  sensor_t sensor;
  dht.temperature().getSensor(&sensor);
  Serial.println(F("------------------------------------"));
  Serial.println(F("Temperature Sensor"));
  Serial.print  (F("Sensor Type: ")); Serial.println(sensor.name);
  Serial.print  (F("Driver Ver:  ")); Serial.println(sensor.version);
  Serial.print  (F("Unique ID:   ")); Serial.println(sensor.sensor_id);
  Serial.print  (F("Max Value:   ")); Serial.print(sensor.max_value); Serial.println(F("°C"));
  Serial.print  (F("Min Value:   ")); Serial.print(sensor.min_value); Serial.println(F("°C"));
  Serial.print  (F("Resolution:  ")); Serial.print(sensor.resolution); Serial.println(F("°C"));
  Serial.println(F("------------------------------------"));

  // Detalhes do sensor de humidade.
  dht.humidity().getSensor(&sensor);
  Serial.println(F("Humidity Sensor"));
  Serial.print  (F("Sensor Type: ")); Serial.println(sensor.name);
  Serial.print  (F("Driver Ver:  ")); Serial.println(sensor.version);
  Serial.print  (F("Unique ID:   ")); Serial.println(sensor.sensor_id);
  Serial.print  (F("Max Value:   ")); Serial.print(sensor.max_value); Serial.println(F("%"));
  Serial.print  (F("Min Value:   ")); Serial.print(sensor.min_value); Serial.println(F("%"));
  Serial.print  (F("Resolution:  ")); Serial.print(sensor.resolution); Serial.println(F("%"));
  Serial.println(F("------------------------------------"));

  // Seta o tempo de leitura baseado nos detalhes do sensor.
  delayMS = sensor.min_delay / 1000;

  //Define pino como saida
  pinMode(pinoledverde, OUTPUT);

  //Define pino como saida
  pinMode(pinoledavermelho, OUTPUT);

  //Define pino sensor como entrada
  pinMode(pinoSensor, INPUT);

  Serial.print("Calibrando o sensor...");

  for (int i = 0; i < calibracao; i++) {
    Serial.print(".");
    delay(1000);
  }

  Serial.println("Sensor Ativado");
}

void loop()
{
  // Delay entre as medições.
  delay(delayMS);

  // Recupera os valores da temperatura e mostra na saída do console.
  sensors_event_t event;
  dht.temperature().getEvent(&event);
  if (isnan(event.temperature)) {
    Serial.println(F("Erro ao ler a temperatura!"));
  }
  else {
    Serial.print(F("Temperatura: "));
    Serial.print(event.temperature);
    Serial.println(F("°C"));
  }
  
  // Recupera os valores da humidade e mostra na saída do console.
  dht.humidity().getEvent(&event);
  if (isnan(event.relative_humidity)) {
    Serial.println(F("Erro ao ler a humidade!"));
  }
  else {
    Serial.print(F("Humidade: "));
    Serial.print(event.relative_humidity);
    Serial.println(F("%"));
  }

  //Le o valor do sensor PIR
  iniciaSensor = digitalRead(pinoSensor);

  Serial.println(iniciaSensor);

  //Sem movimento, mantem led azul ligado
  if (iniciaSensor == LOW)
  {
    digitalWrite(pinoledavermelho, HIGH);
    digitalWrite(pinoledverde, LOW);
  }
  else  //Caso seja detectado um movimento, aciona o led vermelho
  {
    digitalWrite(pinoledavermelho, LOW);
    digitalWrite(pinoledverde, HIGH);
  }
}
