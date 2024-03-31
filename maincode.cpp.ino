#define sensorPower  17 
#define sensorPin 34
#define sensorPindua 35
const int relaypompa = 26;
const int relayselenoid1 = 27;
const int relayselenoid2 = 25;

//#define sensorPower 4
//const int sensorPower = 35;

// water sensor is connected to GPIO 34 (Analog ADC1_CH6) 
//const int sensorPin = 34;
//#define sensorPin A0

int val = 0;
int valsensordua = 0;
int statusnyaladuluan = 0;

void setup() {
  pinMode(sensorPower, OUTPUT);
  digitalWrite(sensorPower, LOW);
  Serial.begin(9600);
  pinMode(relaypompa, OUTPUT);
  pinMode(relayselenoid1, OUTPUT);
  pinMode(relayselenoid2, OUTPUT);

}

void loop() {
  digitalWrite(sensorPower, HIGH);
  delay(10);
  val = analogRead(sensorPin);
  valsensordua = analogRead(sensorPindua);

  if(val<50){
    if(valsensordua>50 && statusnyaladuluan!=2){//sensor 2 sudah menyentuh air
      Serial.println("keran 1 di buka");
      digitalWrite(relayselenoid1, LOW);
      statusnyaladuluan = 1;
      delay(2000);     
    }
    digitalWrite(relaypompa, LOW);
    Serial.println("Pompa menyala ke toren 1");
  }else if(val>50){
    if(valsensordua>50){
      statusnyaladuluan = 0;
      digitalWrite(relaypompa, HIGH);
      Serial.println("Pompa mati, menunggu keran 1 di tutup");
    }else if(valsensordua<50){//toren 2 kosong
      statusnyaladuluan = 2;
      digitalWrite(relayselenoid2, LOW);
      delay(2000);   
    }
    digitalWrite(relayselenoid1, HIGH);
    Serial.println("keran 1 di tutup");
  }

  if(valsensordua<50){
    if(val>50 && statusnyaladuluan!=1){
      Serial.println("keran 2 di buka");
      digitalWrite(relayselenoid2, LOW);
      statusnyaladuluan = 2;
      delay(2000);
    }
    digitalWrite(relaypompa, LOW);
    Serial.println("Pompa menyala ke toren 2");
  }else if(valsensordua>50){
    if(val>50){
      digitalWrite(relaypompa, HIGH);
      Serial.println("Pompa mati, menunggu keran 2 di tutup...");
    }else if(val<50){//toren 1 kosong
      statusnyaladuluan = 1;
      digitalWrite(relayselenoid1, LOW);
      delay(2000);
    }
    digitalWrite(relayselenoid2, HIGH);
    Serial.println("keran 2 di tutup");
    delay(2000);
  }

  digitalWrite(sensorPower, LOW);
  Serial.print("Water level: ");
  Serial.println(val);

  Serial.print("Water level sensor dua: ");
  Serial.println(valsensordua);
}