unsigned long comInt;
unsigned int binaryNumber[17];
void setup() {
  Serial.begin(115200);
  DDRD = B11111110;
  DDRD = DDRD | B11111110; //配置Pin1~7为输出模式，Pin0为输入模式
  PORTD = B00000000; //起始配置为低电平
  pinMode(13,OUTPUT);  
}

void loop() {
  if(Serial.available() > 0){
    PORTD = B00001100;//起始位
    delay(1);
    PORTD = B00000000;
    comInt = Serial.parseInt();
    unsigned long n = comInt;
    
    DecimalNumberToBinary(n);
    
    showDecimalNumberToBinary();
    
    BinaryNumberToTTL();

    PORTD =  B00000100;//结束位
    delay(1);
    PORTD =  B00000000;
    while(Serial.read()>=0){};
    }
}

void DecimalNumberToBinary(unsigned long decimalNumber)
{
    for(int i = 0; i < 17; i++)
    {
      binaryNumber[i] = bitRead(decimalNumber,i);
    }
}

void showDecimalNumberToBinary(void)
{
    for(int j = 0; j < 17; j++)
      Serial.print(binaryNumber[j]);
}

void BinaryNumberToTTL(void)
{
  unsigned int flag =1;
  
  for(int k =0; k < 17; k++)
  {
    if(binaryNumber[k] == flag){
        digitalWrite(13,HIGH);
        PORTD =  B00000100;
        delay(1000);
        PORTD =  B00000000;
        digitalWrite(13,LOW);
      }
    else if(binaryNumber[k] != flag)
    {
        digitalWrite(13,LOW);
        PORTD =  B00000000;
        delay(1000);
     }
    else
    {
        digitalWrite(13,LOW);
        PORTD =  B00000000; 
    }
  }
}
