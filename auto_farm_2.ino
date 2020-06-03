//************************************************BLUETOOTH****************************************************************
//AUTO BÊN SIM QUẢN LÝ
#include <Servo.h>
Servo myservo;
int quang = 9;
int den = 10;
int nhiet = 13;//Chân lấy A1
int khoa1 = 7; //Chân kích khóa 1
int khoa2 = 8; //Chân kích khóa 2
int bom = 6; //Chân kích bơm nước
int reset = 11; //chan reset
const int trig = 5;     // chân trig của HC-SR04
const int echo = 4;     // chân echo của HC-SR04
char blue;
String x;
void setup() {
  digitalWrite(reset,HIGH);
  myservo.attach(3); //Chân phát góc cho Servo. Why chọn chân D3 ? Vì nó là chân PWM
  Serial.begin(9600);
//  Serial.println("HE THONG TUOI");
//  delay(2000);
//  Serial.println("Loading..");
//  delay(2000);
  pinMode(quang,INPUT);
  pinMode(den,OUTPUT);
  pinMode(nhiet,OUTPUT);
  pinMode(khoa1,OUTPUT);
  pinMode(khoa2,OUTPUT);
  pinMode(bom,OUTPUT);
  pinMode(A2,INPUT);
  pinMode(A3,INPUT);
  pinMode(A1,INPUT);
  pinMode(trig,OUTPUT);   // chân trig sẽ phát tín hiệu
  pinMode(echo,INPUT);    // chân echo sẽ nhận tín hiệu
  pinMode(reset,OUTPUT); 
  digitalWrite(nhiet, LOW); 
}
void loop() {
    unsigned long val_time; // biến đo thời gian
    int khoangcach;           // biến lưu khoảng cách
    
    /* Phát xung từ chân trig */
    digitalWrite(trig,0);   // tắt chân trig
    delayMicroseconds(2);
    digitalWrite(trig,1);   // phát xung từ chân trig
    delayMicroseconds(5);   // xung có độ dài 5 microSeconds
    digitalWrite(trig,0);   // tắt chân trig
    
    // Tính time
    // Đo độ rộng xung HIGH ở chân echo. 
    val_time = pulseIn(echo,HIGH);  
    // Tính khoảng cách đến vật.
    khoangcach = int(val_time/2/29.412);
    //****************************
      int value1 = map(analogRead(A2), 0, 1023, 99, 0); //đọc độ ẩm 1
      int value2 = map(analogRead(A3), 0, 1023, 99, 0); //đọc độ ẩm 2
      float value3 = (analogRead(A1)*5.0*1000.0/1024.0)/10;//TÍNH NHIỆT
      int value4 = digitalRead(quang); 
  //**********************************************************************
        if (value4 == HIGH) 
          {
              x = "ON ";
          }
        else 
             {
            x = "OFF";
             }
        if (khoangcach > 14)
            {
                digitalWrite(bom, LOW);
            }
        if (x == "OFF")
            {
                digitalWrite(den, HIGH);
            }
        else 
            {
                digitalWrite(den, LOW);
            }

  ////////////////////////////////////////////////////////////////////////////////
  Serial.print("Độ ẩm luống 1: ");
  Serial.print(value1); //Đưa lên app Bluetooth
  Serial.print("%"); 
  Serial.println("");
  Serial.print("Độ ẩm luống 2: ");
  Serial.print(value2); //Đưa lên app Bluetooth
  Serial.print("%"); 
  Serial.println("");
  Serial.print("Nhiệt độ: ");
  Serial.print(value3, 1);//Đưa lên app Bluetooth 
  Serial.print("độ C");
  Serial.println("");
  Serial.print("Khoảng cách nước: ");
  Serial.print(khoangcach);
  Serial.println("cm");
  Serial.print("Ánh sáng: ");
  Serial.print(x); 
  Serial.println("          ");
  delay(1000);
  
 //  New CODE *****************************
    if (value1 < 20 && value2 <20)
        {
          Serial.println("Vuon thieu nuoc");
          //delay(2000);
        }
        else 
        {
          Serial.println("Vuon du nuoc");
        //  delay(2000);
        }
        if (value2 < 20 && value1 > 20)
        {
          Serial.println("Luong 1 du nuoc");
          Serial.println("Luong 2 thieu nuoc");
         // delay(2000);
        }
        if (value1 < 20 && value2 > 10)
        {
          Serial.println("Luong 1 thieu nuoc");
          Serial.println("Luong 2 du nuoc");
          //delay(2000);
        }
        if (value3 > 40) 
        {
          Serial.println("Troi Nong");
          //delay(2000);
        }
        else
        {
          Serial.println("Khong khi mat me");
          //delay(2000);
        } 
       
  // *****************************************************      

    if (Serial.available() > 0)
    {
   blue = Serial.read();
   }
   // câu lệnh nhiều chọn lựa... Giống Pascal Case ...of
   switch (blue) 
   {
    case '0': //Auto 
    Serial.print("0");
    if (value1 < 10 && value2 < 10 )
        {
          digitalWrite(bom,HIGH);
          digitalWrite(khoa1,HIGH);
          digitalWrite(khoa2,HIGH);
        }
        else {
          digitalWrite(khoa1,LOW);
          digitalWrite(bom,LOW);
          digitalWrite(khoa2,LOW);
             }
     if (value1 < 10 && value2 >10)
          {
            digitalWrite(bom,HIGH);
            digitalWrite(khoa1,HIGH);
            digitalWrite(khoa2,LOW);
          }
      if (value1 > 10 && value2 <10)     
          {
            digitalWrite(bom,HIGH);
            digitalWrite(khoa1,LOW);
            digitalWrite(khoa2,HIGH);
          }
     if (value3 > 40)
         {
          digitalWrite(nhiet,HIGH);   
        }
        else {
          digitalWrite(nhiet,LOW);  
        }
   break;
   case 'W': //Auto quá khô
    if (value1 <= 2 && value2 <= 2 )
        {
          digitalWrite(bom,HIGH);
          digitalWrite(khoa1,HIGH);
          digitalWrite(khoa2,HIGH);
        }
        else {
          digitalWrite(khoa1,LOW);
          digitalWrite(bom,LOW);
          digitalWrite(khoa2,LOW);
             }
     if (value1 <= 2 && value2 > 2)
          {
            digitalWrite(bom,HIGH);
            digitalWrite(khoa1,HIGH);
            digitalWrite(khoa2,LOW);
          }
      if  ( value1 > 2 && value2 <= 2)     
          {
            digitalWrite(bom,HIGH);
            digitalWrite(khoa1,LOW);
            digitalWrite(khoa2,HIGH);
          }
     if (value3 > 41)
         {
          digitalWrite(nhiet,HIGH);   
        }
        else {
          digitalWrite(nhiet,LOW);  
        }
   break;
  case '1': //CA VUON
    digitalWrite(bom,HIGH);
    digitalWrite(khoa1,HIGH);
    digitalWrite(khoa2,HIGH);
    break;
  case '2': //reset system
     digitalWrite(reset,LOW);
     break;   
  case '3': //BAT LUONG1
    digitalWrite(bom,HIGH);
    digitalWrite(khoa1,HIGH);
    digitalWrite(khoa2,LOW);
  break;
   case '4': //TAT LUONG1
     digitalWrite(bom,LOW);
     digitalWrite(khoa1,LOW);
     digitalWrite(khoa2,LOW);
  break;
  case '5': //BATLUONG2
     digitalWrite(bom,HIGH);
     digitalWrite(khoa1,LOW);
     digitalWrite(khoa2,HIGH);
     break;
  case '6': //TAT LUONG2
     digitalWrite(bom,LOW);
     digitalWrite(khoa1,LOW);
     digitalWrite(khoa2,LOW);
     break;
   case '7': // bat ca vuon 1m
    digitalWrite(bom,HIGH);
    digitalWrite(khoa1,HIGH);
    digitalWrite(khoa2,HIGH);
    //xóa delay();
    break;       
    //xóa case 'a':
   case '8': //BAT LUONG1
    digitalWrite(bom,HIGH);
    digitalWrite(khoa1,HIGH);
    digitalWrite(khoa2,LOW);
    break;
     case '9': //BATLUONG2 1m
     digitalWrite(bom,HIGH);
     digitalWrite(khoa1,LOW);
     digitalWrite(khoa2,HIGH);  //xóa delay
     break;
     case 'p': // Chân phun (chân thứ 13) ON
     digitalWrite(nhiet,HIGH);
     break;
     case 's'://Chân phun nhiêt (chân thứ 13) OFF
     digitalWrite(nhiet,LOW);
     break; 
     case 't':
     myservo.write(0);
     break; 
     case 'f':// Nếu mở van nước 
     myservo.write(30);
     break;
     case 'r':
     myservo.write(90);
     break;
  default: 
   break; 
   }
   delay(30); // Cho code mượt 
}
