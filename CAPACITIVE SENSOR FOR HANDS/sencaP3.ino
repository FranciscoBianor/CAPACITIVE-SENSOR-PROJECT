#include <CapacitiveSensor.h>

const int d1 = 13;
const int d11 = 12;
const int d2 = 11;
const int d22 = 10;
const int d3 = 7;
const int d33 = 6;
const int d4 = 5;
const int d44 = 4;
const int d5 = 3;
const int d55 = 2;
const int pal = 9;
const int pall = 8;

          int    involtPin[14] = {}; //equals involt.pin.P in app
          String involtString[2] ={}; //equals involt.pin.S in app
          char involt[16];
          String fname;
          
//varia de acordo com o resistor e tamanho da superfície capacitiva, mude para testar.
const long sensibilidade = 15000; 
 
CapacitiveSensor cs1 = CapacitiveSensor(d1,d11);
CapacitiveSensor cs2 = CapacitiveSensor(d2,d22);
CapacitiveSensor cs3 = CapacitiveSensor(d3,d33);
CapacitiveSensor cs4 = CapacitiveSensor(d4,d44);
CapacitiveSensor cs5 = CapacitiveSensor(d5,d55);
CapacitiveSensor csp = CapacitiveSensor(pal,pall);
 
 

 
void setup()
{
    cs1.set_CS_AutocaL_Millis( 0xFFFFFFFF);
    cs2.set_CS_AutocaL_Millis( 0xFFFFFFFF);
    cs3.set_CS_AutocaL_Millis( 0xFFFFFFFF);
    cs4.set_CS_AutocaL_Millis( 0xFFFFFFFF);
    cs5.set_CS_AutocaL_Millis( 0xFFFFFFFF);
    csp.set_CS_AutocaL_Millis( 0xFFFFFFFF);
 
    //Inicia a serial para ajudar no debug
    Serial.begin(57600);
}
 
void loop()
{

     involtReceive();
      fname = "";
    //chama a função que lê a capacitância...
    int a = cs1.capacitiveSensor(30);
    int b = cs2.capacitiveSensor(30);
    int c = cs3.capacitiveSensor(30);
    int d = cs4.capacitiveSensor(30);
    int e = cs5.capacitiveSensor(30);
    int p = csp.capacitiveSensor(30);

    int uu= 12122323;
 
    //Imprime o valor da capacitância na serial para ajudar no debug.
    
  involtSend(13,a);
  involtSend(12,uu);
  involtSend(11,c);
  involtSend(10,d);
  involtSend(9,e);
  involtSend(8,p);
 involtString[1]=uu;
  involt[1]=uu;
   involtPin[1]=uu;   

   

   
    
    
}

void involtReceive(){
  if(Serial.available()>0) {
    Serial.readBytesUntil('\n',involt,sizeof(involt));
    int pin;
    if (involt[0] == 'P'){
      int value;
      sscanf(involt, "P%dV%d", &pin, &value);
      involtPin[pin] = value;
    }
    else if (involt[0] == 'S'){
      char value[sizeof(involt)];
      sscanf(involt, "S%dV%s", &pin, &value);
      involtString[pin] = value;
    }
    else if (involt[0] == 'F'){
      char value[sizeof(involt)];
      sscanf(involt, "F%s", &value);
      fname = value;
    };
    memset(involt,0,sizeof(involt));
  };
};

void involtSend(int pinNumber, int sendValue){
  Serial.print('A'); 
  Serial.print(pinNumber); 
  Serial.print('V'); 
  Serial.print(sendValue); 
  Serial.println('E');
  Serial.flush();
};

void involtSendString(int pinNumber, String sendString){
  Serial.print('A'); 
  Serial.print(pinNumber); 
  Serial.print('V'); 
  Serial.print(sendString); 
  Serial.println('E'); 
  Serial.flush();

};

void involtSendFunction(String functionName){
  Serial.print('F'); 
  Serial.print(functionName); 
  Serial.println('E'); 
  Serial.flush();
};

