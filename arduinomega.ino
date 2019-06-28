
#include <SoftwareSerial.h>

// software serial : TX = digital pin 10, RX = digital pin 11
//SoftwareSerial mySerial(18, 19); // RX, TX
//SoftwareSerial mySerial2(17, 16);



#include "DHT.h"
#define DHTPIN 36     
#define DHTTYPE DHT11  
DHT dht(DHTPIN, DHTTYPE);


int userFanPin=48;//Kullanıcı Taraflı Fan Kullanımı; D4
int userCatiPin = 47;//Kullanıcı taraflı Çatı kullanımı D7
int userSuMotoruPin=46;//Kullanıcı taraflı Su Motoru kullanımı D6;

int catiFanPin = 38; // NodeMCU D0
int sadeceFanPin = 51;//Sadece Fan AÃ§ma Pini D3 / 51
int yagmurKontrolPini = 50;//YaÄŸmur durumu Ã§Ä±kÄ±ÅŸ pini D2 / 50
int suMotoruPin = 53;//NODEMCU D1/53
int yagmurPin = A0;

int fanPwma = 13;
int fanAin2 = 12;
int fanAin1 = 11;
int fanStdby = 10;
float nem;
float sicaklik;

int catiPwmb = 7;  
int catiBin2 = 8; 
int catiBin1 = 9;     

boolean uCati,uFan,uSuMotoru;




int acikSwitch = 22;
int kapaliSwitch = 23;

int suMotoruPwma = 6;
int suMotoruAin2 = 5;
int suMotoruAin1 = 4;
int suMotoruStby = 3;
int toprakPin = 32;




void setup()  
{
 Serial.begin(9600);
 Serial1.begin(9600);
 
 pinMode(sadeceFanPin,INPUT);
 pinMode(yagmurKontrolPini,OUTPUT); 
 pinMode(suMotoruPin, OUTPUT);
 pinMode(catiFanPin,INPUT);
 pinMode(acikSwitch,INPUT);

  pinMode (fanStdby, OUTPUT);
  pinMode (fanPwma, OUTPUT);
  pinMode (fanAin2, OUTPUT);
  pinMode (fanAin1, OUTPUT);
  
  pinMode (catiPwmb, OUTPUT);
  pinMode (catiBin2, OUTPUT);
  pinMode (catiBin1, OUTPUT);

  pinMode (suMotoruStby, OUTPUT);
  pinMode (suMotoruPwma, OUTPUT);
  pinMode (suMotoruAin2, OUTPUT);
  pinMode (suMotoruAin1, OUTPUT); 
  pinMode (toprakPin, INPUT); 

  pinMode(userFanPin,INPUT);
  pinMode(userCatiPin,INPUT);
  pinMode(userSuMotoruPin,INPUT);
  

}

void loop()
{
digitalWrite(fanStdby, HIGH);
digitalWrite(suMotoruStby, HIGH);

kullaniciTarafliDegerleriOku();
sicaklikNemOku();
delay(100);
sicaklikGonder();
delay(100);
yagmurDurumuGonder();
delay(100);
sadeceFanAcKapa();
delay(100);
catiFanAcKapa();
delay(100);
toprakOku();
delay(100);


delay(500);

}

void kullaniciTarafliDegerleriOku()
{
  if(digitalRead(userFanPin) == HIGH) uFan=true;
  else uFan=false;

  if(digitalRead(userCatiPin) == HIGH) uCati=true;
  else uCati=false;

  if(digitalRead(userSuMotoruPin) == HIGH) uSuMotoru=true;
  else uSuMotoru=false;
}

void toprakOku()
{
if(digitalRead(toprakPin) == true)
{
    if(!uSuMotoru)
    {
      analogWrite(suMotoruPwma,0);
      digitalWrite(suMotoruPin,HIGH);
      }
    else
    {
       digitalWrite(suMotoruPin,HIGH);
      analogWrite(suMotoruPwma,40);
     
        digitalWrite(suMotoruAin2,LOW);
  digitalWrite(suMotoruAin1,HIGH);
      }
}
else
{
 digitalWrite(suMotoruPin,LOW);
  analogWrite(suMotoruPwma,0);
 
}
}

void sicaklikNemOku()
{
 nem = dht.readHumidity();
 delay(500);
sicaklik = dht.readTemperature();

}




void sicaklikGonder()
{

String stringOne = "s";
String string = "";
String stringThree = stringOne + sicaklik ;
stringThree+='-';
stringThree+=string+nem;


Serial.println(stringThree);  

}



void sadeceFanAcKapa()
{
  if(digitalRead(sadeceFanPin) == HIGH)
{
    analogWrite(fanPwma,100);
    digitalWrite(fanAin1, HIGH);
    digitalWrite(fanAin2, LOW);
    uCati=false;
    catiKapa(); 
}
else
 {
  if(digitalRead(catiFanPin) == HIGH){
    analogWrite(fanPwma,100);
    digitalWrite(fanAin1, HIGH);
    digitalWrite(fanAin2, LOW);
    }
    else
    {
       if(uFan)
        analogWrite(fanPwma,100);
       else
        analogWrite(fanPwma,0);
     }
 }
}




void catiFanAcKapa()
{
  if(digitalRead(catiFanPin) == HIGH)
{
    analogWrite(fanPwma,100);
    digitalWrite(fanAin1, HIGH);
    digitalWrite(fanAin2, LOW);
    if(uCati)catiAc();//Çatı kullanıcı taraflı açık mı?Açıksa çatıyı aç,değilse açma
    else catiKapa();
}
else
{
    if(uCati)catiAc();//Çatı kullanıcı taraflı açık mı?Açıksa çatıyı aç,değilse açma
    else catiKapa();
}
}






void yagmurDurumuGonder()
{
  if(analogRead(yagmurPin) > 100)
{
  digitalWrite(yagmurKontrolPini,HIGH);
}
else if(analogRead(yagmurPin) < 100)
{
  digitalWrite(yagmurKontrolPini,LOW);


}
}

void catiAc()
{
  while(digitalRead(acikSwitch) == HIGH)//Açık Switche değene kadar Pwmb tam kapasite çalışıyor 
    {
      analogWrite(catiPwmb,255);
      digitalWrite(catiBin2,LOW);
      digitalWrite(catiBin1,HIGH);
    }
    analogWrite(catiPwmb,0);
}

void catiKapa()
{
  while(digitalRead(kapaliSwitch) == HIGH)//Kapalı Switche değene kadar Pwmb tam kapasite 
    {
      analogWrite(catiPwmb,255);
      digitalWrite(catiBin2,HIGH);
      digitalWrite(catiBin1,LOW);
    }
    analogWrite(catiPwmb,0);
    
}








