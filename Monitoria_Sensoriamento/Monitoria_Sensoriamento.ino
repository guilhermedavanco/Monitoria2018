#define pino_umisolo A0
#define pino_ldr A1
//#define bomba 10

#define pino_tempumi 3
#define DHTTYPE DHT22  

#include "TimerOne.h"
#include "DHT.h"

int valor_analogico;
int i=0;

DHT dht(pino_tempumi, DHTTYPE);

void setup(){
   
  Serial.begin(9600);
  pinMode(pino_umisolo, INPUT);
  pinMode(pino_ldr, INPUT);
  pinMode(pino_tempumi, INPUT);
  pinMode(bomba, OUTPUT);

  analogWrite(bomba,0);  
  
  Timer1.initialize(500000);         // initialize timer1, and set a 1/2 second period
  Timer1.pwm(9, 512);                // setup pwm on pin 9, 50% duty cycle
  Timer1.attachInterrupt(callback);  // attaches callback() as a timer overflow interrupt

  dht.begin(); //initialize humidity temperature sensor 
} 
 
void loop(){
   
  //delay(100);
}

void callback(){
  
  Serial.print("timer funfando ");
  Serial.println(i);
  i++;
  umidadedosolo();
  ldr();
  tempumi();

}

void umidadedosolo(){
  
  valor_analogico = analogRead(pino_umisolo);
  // 1023 seco 
  Serial.print("Umid_Solo: ");
  Serial.println(valor_analogico);
//  bomba();
  
}

void bomba(){
  if (valor_analogico > 900){
    analogWrite(bomba,255);
  }
  else{
    analogWrite(bomba,0);
  }
}

void ldr(){
  valor_analogico = analogRead(pino_ldr);
  // 0 pouca luminosidade
  Serial.print("Luz: ");
  Serial.println(valor_analogico);
  
}


void tempumi(){
  float h = dht.readHumidity();
  float t = dht.readTemperature();
  if (isnan(t) || isnan(h)) 
  {
    Serial.println("Failed to read from DHT");
  } 
  else 
  {
    Serial.print("Umidade: ");
    Serial.print(h);
    Serial.println(" %t");
    Serial.print("Temperatura: ");
    Serial.print(t);
    Serial.println(" *C");
  }
}

