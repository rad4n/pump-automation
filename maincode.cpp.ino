#define sensorPower  17 
#define sensorPin 34
#define sensorPindua 35

//#define sensorPower 4
//const int sensorPower = 35;

// water sensor is connected to GPIO 34 (Analog ADC1_CH6) 
//const int sensorPin = 34;
//#define sensorPin A0

int val = 0;
int valsensordua = 0;

void setup() {
  pinMode(sensorPower, OUTPUT);
  digitalWrite(sensorPower, LOW);
  Serial.begin(9600);
}

void loop() {
  digitalWrite(sensorPower, HIGH);
  delay(10);
  val = analogRead(sensorPin);
  valsensordua = analogRead(sensorPindua);
  digitalWrite(sensorPower, LOW);
  Serial.print("Water level: ");
  Serial.println(val);

  Serial.print("Water level sensor dua: ");
  Serial.println(valsensordua);
  delay(1000);
}