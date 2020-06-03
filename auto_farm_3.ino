#include "DHT.h"
char blue;
const int DHTPIN = 7; // chan nhiet, dom am khong khi 
const int DHTTYPE = DHT11;
DHT dht(DHTPIN, DHTTYPE);
int t, h; // Temperature, Humidity
int bom = 2;
int luong1= 6;
int luong2 = 4;
int den = 3;
int cambienquang = 8;
int x, y, mLuong1, mLuong2;
void setup() {
    dht.begin();
    pinMode(cambienquang, INPUT);
    for (int i = 2; i <= 6; i++)   pinMode(i, OUTPUT);
    Serial.begin(9600);  
    
}

void loop() {
    x = analogRead(A0);
    y = analogRead(A1);

    mLuong1 = map(x, 0, 1023, 100, 0);
    mLuong2 = map(y, 0, 1023, 100, 0);
    h = dht.readHumidity();    //Đọc độ ẩm
    t = dht.readTemperature(); //Đọc nhiệt độ
    Serial.print("Nhiet do: ");
    Serial.print(t);
    Serial.print(" ");
    Serial.println();
    Serial.println();
    Serial.print("Do am khong khi: ");
    Serial.print(h); 
    Serial.print(" ");
    Serial.println();
    Serial.println();
    Serial.print("Luong 1: "); Serial.print(mLuong1); Serial.print("%"); 
    Serial.print(" ");
    Serial.println();
    Serial.println();
    Serial.print("Luong 2: "); Serial.print(mLuong2); Serial.print("%"); 
    Serial.print(" ");
    Serial.println();
    Serial.println(); 
    
    if (Serial.available() > 0){
      blue = Serial.read(); 
    }
    switch (blue){
      case 'a': 
      digitalWrite(bom, LOW);
      digitalWrite(luong1, LOW);
      digitalWrite(luong2, LOW);
      digitalWrite(den, LOW );
      break;
      case '1': // ca vuon
        digitalWrite(bom, HIGH);
        digitalWrite(luong1, HIGH);
        digitalWrite(luong2, HIGH);
      break;
      case '3': // bat luong1
        digitalWrite(bom, HIGH);
        digitalWrite(luong1, HIGH);
        digitalWrite(luong2, LOW);
      break;

      case '4': // tat luong2
        digitalWrite(bom, LOW);
        digitalWrite(luong1, LOW);
      digitalWrite(luong2, LOW);
      break;

      case '5': // bat luong2
        digitalWrite(bom, HIGH);
        digitalWrite(luong2, HIGH);
        digitalWrite(luong1, LOW);
      break;

      case '6': // tat luong2
        digitalWrite(bom, LOW);
        digitalWrite(luong1, LOW);
      digitalWrite(luong2, LOW);
      break;
      case '9': //auto
          if (mLuong1 < 30 && mLuong2 < 30) {
            
            digitalWrite(bom, HIGH);
            digitalWrite(luong1, HIGH);
            digitalWrite(luong2, HIGH);
        } else if (mLuong1 > 30 && mLuong2 > 30) {
          digitalWrite(bom, LOW);
          digitalWrite(luong1, LOW);
          digitalWrite(luong2, LOW);  
          }
          
        if (mLuong1 < 30 && mLuong2 > 30){
          digitalWrite(bom, HIGH);
          digitalWrite(luong1, HIGH);
          digitalWrite(luong2, LOW);
        } else if (mLuong1 > 30 && mLuong2 > 30){
            digitalWrite(bom, LOW);
          digitalWrite(luong1, LOW);
          digitalWrite(luong2, LOW);
          }
          
        if (mLuong1 > 30 && mLuong2 < 30){
            digitalWrite(bom, HIGH);
            digitalWrite(luong2, HIGH);
            digitalWrite(luong1, LOW);
          } else if (mLuong1 > 30 && mLuong2 > 30) {
            digitalWrite(bom, LOW);
          digitalWrite(luong1, LOW);
          digitalWrite(luong2, LOW);
            }
          if (digitalRead(cambienquang) == 1) digitalWrite(den, HIGH); else digitalWrite(den, LOW);
      break;
      
      
      default:
        
      break;    
    }
}
