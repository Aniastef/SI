#include <LiquidCrystal.h> 

 

//Pinii pentru primul senzor ultrasonic 

const int trigPin1 = 6; 

const int echoPin1= 7; 

 

//Pinii pentru al doilea senzor ultrasonic 

const int trigPin2 = 4; 

const int echoPin2 = 5; 

 

//LED 1 - senzor 1 - verde 

const int ledPin1= 13; 

//LED 2 - senzor 1 - galben 

const int ledPin2= 12; 

//LED 3 - senzor 1 - rosu 

const int ledPin3= 11; 

 

//LED 1 - senzor 2 - verde 

const int ledPin4= 10; 

//LED 2 - senzor 2 - galben 

const int ledPin5= 9; 

//LED 3 - senzor 2 - rosu 

const int ledPin6= 8; 

 

//Pinul pentru buzzer 

int buzzerPin = 46; 

 

//Pinii pentru display-ul LCD 

const int rs = 31, en = 3, d4 = 2, d5 = 33, d6 = 44, d7 = 35; 

 

LiquidCrystal lcd(rs, en, d4, d5, d6, d7); 

 

 

void setup() { 

 

//trigger 

  pinMode(trigPin1, OUTPUT); 

  pinMode(trigPin2, OUTPUT); 

   

//echo  

  pinMode(echoPin1, INPUT); 

  pinMode(echoPin2, INPUT); 

 

//LEDs 

  pinMode(ledPin1, OUTPUT); 

  pinMode(ledPin2, OUTPUT); 

  pinMode(ledPin3, OUTPUT); 

  pinMode(ledPin4, OUTPUT); 

  pinMode(ledPin5, OUTPUT); 

  pinMode(ledPin6, OUTPUT); 

 

//Buzzer 

  pinMode(buzzerPin,OUTPUT); 

 

//Setam ecranul LCD pe 2 randuri si 16 coloane 

  lcd.begin(16, 2); 

 

//Start comunicare seriala 

  Serial.begin(9600); 

} 

 

//Controlul LED-urilor si al buzzer-ului in functie de distante 

void sensorHandler(int distance, int ledGreen, int ledYellow, int ledRed, int buzzerPin) { 

  if (distance < 5) { 

    digitalWrite(ledGreen, LOW); 

    digitalWrite(ledYellow, LOW); 

    digitalWrite(ledRed, HIGH); 

    tone(buzzerPin, 2000, 100); 

  } else if (distance > 5 && distance < 30) { 

    digitalWrite(ledGreen, LOW); 

    digitalWrite(ledYellow, HIGH); 

    digitalWrite(ledRed, LOW); 

    tone(buzzerPin, 1000, 100); 

  } else { 

    digitalWrite(ledGreen, HIGH); 

    digitalWrite(ledYellow, LOW); 

    digitalWrite(ledRed, LOW); 

    noTone(buzzerPin); 

  } 

  delay(100); 

} 

 

void loop() { 

  long duration1,duration2; 

  int distance1,distance2; 

 

//Masuram distanta pentru primul senzor 

  digitalWrite(trigPin1, LOW); 

  delayMicroseconds(2); 

  digitalWrite(trigPin1, HIGH); 

  delayMicroseconds(10); 

  digitalWrite(trigPin1, LOW); 

  duration1 = pulseIn(echoPin1, HIGH); 

  distance1 = duration1 / 58; 

 

//Masuram distanta pentru al doilea senzor 

  digitalWrite(trigPin2, LOW); 

  delayMicroseconds(2); 

  digitalWrite(trigPin2, HIGH); 

  delayMicroseconds(10); 

  digitalWrite(trigPin2, LOW); 

  duration2 = pulseIn(echoPin2, HIGH); 

  distance2 = duration2 / 58; 

 

//Afisam distanta pe monitorul serial  

  Serial.print("Distanta pentru senzorul 1: "); 

  Serial.print(distance1); 

  Serial.print(" cm, Distanta pentru senzorul 2: "); 

  Serial.print(distance2); 

  Serial.println(" cm"); 

 

 

  //Pe primul rand de pe LCD va aparea Loc 1: Ocupat/Liber 

    lcd.clear();  

    lcd.setCursor(0, 0);  

    lcd.print("Loc 1: "); 

    lcd.print(distance1 < 30 ? "Ocupat" : "Liber"); 

 

 

  //Pe al doilea rand de pe LCD va aparea Loc 2: Ocupat/Liber 

    lcd.setCursor(0, 1);  

    lcd.print("Loc 2: "); 

    lcd.print(distance2 < 30 ? "Ocupat" : "Liber"); 

 

  //Actiunile pe care le vor lua senzorii in functie de distante  

    sensorHandler(distance1,ledPin1,ledPin2,ledPin3,buzzerPin); 

    sensorHandler(distance2,ledPin4,ledPin5,ledPin6,buzzerPin); 

     

} 