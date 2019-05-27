//Declaração de portas digitais aos quais os led e a entrada digital do sensor vão estar conectados.

int pinoledverde = 6; //Pino ligado ao led vermelho
int pinoledavermelho = 5; //Pino ligado ao led azul
int pinoSensor = 3;  //Pino ligado ao sensor PIR

int iniciaSensor; //Variavel para guardar valor do sensor

int calibracao = 2; //Variável para calibração do sensor

void setup()
{
  //configura a comunicação seria com baud rate de 9600
  Serial.begin(9600);

  pinMode(pinoledverde, OUTPUT); //Define pino como saida
  pinMode(pinoledavermelho, OUTPUT); //Define pino como saida
  pinMode(pinoSensor, INPUT);   //Define pino sensor como entrada

  Serial.print("Calibrando o sensor...");

  for (int i = 0; i < calibracao; i++) {
    Serial.print(".");
    delay(1000);
  }

  Serial.println("Sensor Ativado");
  delay(500);
}

void loop()
{
  //A cada ciclo, ele faz uma nova leitura do estado do sensor de presença
  iniciaSensor = digitalRead(pinoSensor); //Le o valor do sensor PIR

  Serial.println(iniciaSensor);

  if (iniciaSensor == LOW)  //Sem movimento, mantem led azul ligado
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
