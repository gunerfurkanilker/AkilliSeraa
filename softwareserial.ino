            


//FirebaseESP8266.h must be included before ESP8266WiFi.h
#include "FirebaseESP8266.h"
#include <ESP8266WiFi.h>

#define FIREBASE_HOST "akillisera-66d6a.firebaseio.com"
#define FIREBASE_AUTH "s0w7b9Tko4axLWbAA2lnfqhp8mKnwIEgeZvhRuK5"
#define WIFI_SSID "Firebase"
#define WIFI_PASSWORD "oief2019"



//Define FirebaseESP8266 data object
FirebaseData firebaseData;
#include <SoftwareSerial.h>

int yagmurPin = D2;
int fanPin=D3;
int catiFanPin = D0;
int suMotoruDurumPin=D1;
int userFanPin = D4;
int userCatiPin = D7;
int userSuMotoruPin = D6;



float anlikSicaklik;
float anlikNem;
float esikSicaklik;
float esikNem;

boolean uCati,uFan,uSuMotoru;
boolean userFanKontrol = false;



void setup() {
  // Open serial communications and wait for port to open:
  Serial.begin(9600);

  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  Serial.print("Connecting to Wi-Fi");
  while (WiFi.status() != WL_CONNECTED)
  {
    Serial.print(".");
    delay(300);
  }
  Serial.println();
  Serial.print("Connected with IP: ");
  Serial.println(WiFi.localIP());
  Serial.println();

  Firebase.begin(FIREBASE_HOST, FIREBASE_AUTH);
  Firebase.reconnectWiFi(true);
  
  pinMode(catiFanPin,OUTPUT);
  pinMode(suMotoruDurumPin,INPUT);
  pinMode(yagmurPin,INPUT);
  pinMode(fanPin,OUTPUT);

  pinMode(userCatiPin,OUTPUT);
  pinMode(userFanPin,OUTPUT);
  pinMode(userSuMotoruPin,OUTPUT);

  
  
 
}

void loop() { // run over and over
kullaniciTarafliDegerlerAl();
delay(100);
kullaniciTarafliDegerlerKontrol();
delay(100);
yagmurDurumu();
delay(100);
suMotoruDurumu();
delay(100);
sicaklikNemAlveYolla();
delay(100);
esikSicaklikNemAlYolla();
delay(100);
sicakligaBagliFanAcKapa();
delay(100);

}


void kullaniciTarafliDegerlerAl()
{
  Firebase.getBool(firebaseData,"/uCati");
  uCati = firebaseData.boolData();
  delay(50);
   Firebase.getBool(firebaseData,"/uFan");
  uFan = firebaseData.boolData();
  delay(50);
   Firebase.getBool(firebaseData,"/uSuMotoru");
  uSuMotoru = firebaseData.boolData();
}

void kullaniciTarafliDegerlerKontrol()
{

  if(uCati) digitalWrite(userCatiPin,HIGH);
  else digitalWrite(userCatiPin,LOW);

  if(uFan && userFanKontrol) digitalWrite(userFanPin,HIGH);
  else if(userFanKontrol) digitalWrite(userFanPin,LOW);

  if(uSuMotoru) digitalWrite(userSuMotoruPin,HIGH);
  else digitalWrite(userSuMotoruPin,LOW);
  
}




void yagmurDurumu()
{

   if(digitalRead(yagmurPin) == HIGH) 
  {
      Firebase.setBool(firebaseData,"/havaDurumu",false);//HAVA YAĞIŞLI
  }
 
  else if(digitalRead(yagmurPin) == LOW)
  {
      Firebase.setBool(firebaseData,"/havaDurumu",true);//HAVA AÇIK
  }
}



void suMotoruDurumu()
{
  if(digitalRead(suMotoruDurumPin) == HIGH) 
  { 
      if(uSuMotoru)
      Firebase.setBool(firebaseData,"/suMotoru",true);//Açık
      else
      Firebase.setBool(firebaseData,"/suMotoru",false);//kapalı
      delay(100);
      Firebase.setBool(firebaseData,"/toprakDurumu",false);//Kuru
  }
 
  else if(digitalRead(suMotoruDurumPin) == LOW)
  {
      Firebase.setBool(firebaseData,"/suMotoru",false);//Kapalı
      delay(100);
      Firebase.setBool(firebaseData,"/toprakDurumu",true);//Nemli
  }
}



void sicakligaBagliFanAcKapa()
{
    if(esikSicaklik < anlikSicaklik || esikNem < anlikNem)
{
  userFanKontrol = false;
  
  //
  if(digitalRead(D2) == HIGH)//Yagmur yagiyo
  {
     digitalWrite(D3,HIGH);//Sadece fan açıldı
     digitalWrite(D0,LOW);//Çatı ve fan açık durumu kapandı
      Firebase.setBool(firebaseData,"/fan",true);
      Firebase.setBool(firebaseData,"/cati",false);
      Firebase.setBool(firebaseData,"/uCati",false);
    } 
    
 else
 {
  digitalWrite(D3,LOW);//Sadece fan çalışma durmu kapandı
  digitalWrite(D0,HIGH);//Çatı ve fan açık durumu açıldı
      Firebase.setBool(firebaseData,"/fan",true);
      digitalWrite(D4,HIGH);
      if(uCati)
      {
         Firebase.setBool(firebaseData,"/cati",true);
        }
        else Firebase.setBool(firebaseData,"/cati",false);
     
  }
   
}
else{//Sıcaklık ve nem değeri istenilen değerlere ulaştığı zaman
  userFanKontrol = true;
digitalWrite(D0,LOW);//Çatı ve fan açık durumu kapandı
digitalWrite(D3,LOW);
Serial.println(uFan);
if(uFan) {
  Firebase.setBool(firebaseData,"/fan",true);
  digitalWrite(D4,HIGH);
  }
else{
   Firebase.setBool(firebaseData,"/fan",false);
   digitalWrite(D4,LOW);
  } 

if(uCati)Firebase.setBool(firebaseData,"/cati",true);
else Firebase.setBool(firebaseData,"/cati",false);
     
  if(digitalRead(D2) == HIGH)//Yagmur yagiyo
    {
     digitalWrite(D7,LOW);//UserFanPin LOWLANDI
     Firebase.setBool(firebaseData,"/cati",false);
     Firebase.setBool(firebaseData,"/uCati",false);
    } 
  }
}








void sicaklikNemAlveYolla()
{
  if(Serial.available() > 0)
{
    if(Serial.peek() == 's'){
      Serial.read();
      
       String s = Serial.readString();
       String sicaklikk = s.substring(0,s.indexOf("-"));
       String nemm = s.substring(s.indexOf("-")+1);
       anlikSicaklik = sicaklikk.toInt();
       anlikNem = nemm.toInt();
      Firebase.setFloat(firebaseData,"/anlikSicaklik",anlikSicaklik);
      delay(200);
     Firebase.setFloat(firebaseData,"/anlikNem",anlikNem);
    }
}
 }



 void esikSicaklikNemAlYolla()
{
if(Firebase.getFloat(firebaseData,"/esikSicaklik"))
{
    esikSicaklik = firebaseData.floatData();
    
}
delay(500);
if(Firebase.getFloat(firebaseData,"/esikNem"))
{
    esikNem = firebaseData.floatData();
    
}

}
