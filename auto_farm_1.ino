// làm reset
// một cái phun sương

//int phun = 11; //cái này là nó là chân phun lấy từ chân nhiệt. Biến này dư
int doam1 = 9; // Chân lấy A2
int doam2 = 10;//Chân lấy A3 //LCD 2 3 4 5 11 12
int nhiet = 13;//Chân lấy A4
int khoa1 = 7; //Chân kích khóa 1
int khoa2 = 8; //Chân kích khóa 2
int bom = 6; //Chân kích bơm nước
char blue;
char mode;
void setup() {
  Serial.begin(9600);
  Serial.println("HE THONG TUOI");
  pinMode(doam1,OUTPUT);
  pinMode(doam2,OUTPUT);
  pinMode(nhiet,OUTPUT);
  pinMode(khoa1,OUTPUT);
  pinMode(khoa2,OUTPUT);
  pinMode(bom,OUTPUT);
  pinMode(A2,INPUT);
  pinMode(A3,INPUT);
  pinMode(A4,INPUT);
  //pinMode(phun,OUTPUT); //chân dư
}
void loop() {
  int value1 = analogRead(A2);
  value1 = map(value1,0,1023,0,100); //đọc độ ẩm 1
  int value2 = analogRead(A3);
  value2 = map(value2,0,1023,0,100); //đọc độ ẩm 2
  float value3 = analogRead(A4);
   value3 = (value3*5.0*1000.0/1024.0)/10;//TÍNH NHIỆT
  Serial.print("Độ ẩm luống 1: ");
  Serial.print(value1); //Đưa lên app Bluetooth
  Serial.print("%"); 
  Serial.println("");
  Serial.print("Độ ẩm luống 2: ");
  Serial.print(value2); //Đưa lên app Bluetooth
  Serial.print("%"); 
  Serial.println("");
  Serial.print("Nhiệt độ: ");
  Serial.print(value3);//Đưa lên app Bluetooth 
  Serial.print("độ C");
  delay(1000);//Sau 5s sẽ update 1 lần
  Serial.println("");
  Serial.println("");
  Serial.println("");


  //*********************************************
   // tự động khi ko có bluetooth
   
    if (Serial.available() > 0)
    {
   blue = Serial.read();
   }
   
   // câu lệnh nhiều chọn lựa... Giống Pascal Case ...of
   switch (blue) 
   {
    case '0': //Auto farm
    if (value1 < 10 )
        {
          digitalWrite(bom,HIGH);
          digitalWrite(khoa1,HIGH);
        }
        else {
          digitalWrite(khoa1,LOW);
          digitalWrite(bom,LOW);
             }
     if (value2 < 10)
          {
            digitalWrite(bom,HIGH);
            digitalWrite(khoa2,HIGH);
          }
          else 
          {
            digitalWrite(bom,LOW);
            digitalWrite(khoa2,LOW);
          }
     if (value3 > 40)
         {
          digitalWrite(nhiet,HIGH);  //ban đầu là digitalWrite(phun,HIGH);   
        }
        else {
          digitalWrite(nhiet,LOW);   //ban đầu là digitalWrite(phun,LOW);  //Tiết kiệm đc chân 11
        }
   break;
  case '1': //CA VUON
    digitalWrite(bom,HIGH);
    digitalWrite(khoa1,HIGH);
    digitalWrite(khoa2,HIGH);
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
    delay(60000);
    break;
     case '8': //BAT LUONG1 1m
    digitalWrite(bom,HIGH);
    digitalWrite(khoa1,HIGH);
    digitalWrite(khoa2,LOW);
    delay(60000);
    break;
     case '9': //BATLUONG2 1m
     digitalWrite(bom,HIGH);
     digitalWrite(khoa1,LOW);
     digitalWrite(khoa2,HIGH);
     delay(60000);
     break;    
  default: 
   break; 
   }
}
