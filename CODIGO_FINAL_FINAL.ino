#include <TinyGPS++.h>
#include <TinyGPSPlus.h>
#include <SoftwareSerial.h>


//------------------------------------------------------
//GPS
static const int RXPin = 4, TXPin = 3;  // CONECTAR AL REVES!!! RX=3 Y TX=4 . Pines de GPS
SoftwareSerial gpsSerial(RXPin, TXPin); // RX, TX
TinyGPSPlus gps;

String latitude, longitude;
//------------------------------------------------------
//SIM800L
SoftwareSerial MOD_SIM800L(7, 8);

const String EMERGENCY_PHONE = "+5491168997933";  // (rocio)

//------------------------------------------------------
//PULSADOR
#define SIM800_PULSADOR 9
int contador = 0;


//--------------SETUP-----------------------------------
void setup () {
  Serial.begin(9600);
  while(!Serial);
  MOD_SIM800L.begin(9600);
  delay(1000);
  gpsSerial.begin(9600);
  pinMode (SIM800_PULSADOR, INPUT_PULLUP);
  
  }

//--------------LOOP------------------------------------

void loop (){
   if((digitalRead(SIM800_PULSADOR) == 1)&&(contador == 0)){
  Serial.println("Configuracion Completa!");
  Serial.println("Enviando SMS...");
  getGps();
  delay(1000);
  sendAlert();
  
  }
}
      

//----------------VOIDS---------------------------------

void getGps(){
  // Can take up to 60 seconds
  boolean newData = false;
  for (unsigned long start = millis(); millis() - start < 2000;){
    while (gpsSerial.available()){
      if (gps.encode(gpsSerial.read())){
        newData = true;
        break;
      }
    }
  }
  
  if (newData) //If newData is true
  {
    latitude = String(gps.location.lat(), 6);
    longitude = String(gps.location.lng(), 6);
    newData = false;
  }
  else {
    Serial.println("No GPS data is available");
    latitude = "";
    longitude = "";
  }
  Serial.print("Latitude= "); Serial.println(latitude);
  Serial.print("Lngitude= "); Serial.println(longitude);
}
  
///////////////////////////////////////////////////////////

void sendAlert(){
  String sms_data;
  sms_data = "Estoy en peligro, esta es mi ubicacion\r";
  sms_data += "http://maps.google.com/maps?q=loc:";
  sms_data += latitude + "," + longitude;
  sendSms(sms_data);
}


/////////////////////////////////////////////////////////////

void sendSms(String text){
   MOD_SIM800L.print("AT+CMGF=1\r");
  delay(1000);
  MOD_SIM800L.print("AT+CMGS=\""+EMERGENCY_PHONE+"\"\r");
  delay(1000);
  MOD_SIM800L.print(text);
  delay(100);
  MOD_SIM800L.write(0x1A); //ascii code for ctrl-26 //sim800.println((char)26); //ascii code for ctrl-26
  delay(1000);
  Serial.println("SMS Sent Successfully.");
}
