/****************************************
 * Define Constants
 ****************************************/
namespace {
  bool flow_control = true; // control the flow of the requests
  const char * USER_AGENT = "UbidotsESP8266"; // Assgin the user agent
  const char * VERSION =  "1.0"; // Assign the version
  const char * METHOD = "POST"; // Set the method
  const char * TOKEN = "A1E-2XFeEv14k0TsWFzoQxPJyuY18utbw5"; // Assign your Ubidots TOKEN
  const char * DEVICE_LABEL = "my_farm"; // Assign the device label
  const char * VARIABLE_LABEL = "soil moisture"; // Assign the variable label
  const char * VARIABLE_LABEL2 = "light"; // Assign the variable label
  const char * VARIABLE_LABEL3 = "temperature"; // Assign the variable label
  const char * VARIABLE_LABEL4 = "humidity"; // Assign the variable label
}

#define pino_umisolo A1
#define pino_luz A6
#define pino_tempumi 3
#define DHTTYPE DHT22


#include "DHT.h"
DHT dht(pino_tempumi, DHTTYPE);

char telemetry_unit[100]; // response of the telemetry unit
int order = 0;
/* Space to store values to send */
char str_sensor1[10];
char str_sensor2[10];
char str_sensor3[10];
char str_sensor4[10];


/****************************************
 * Main Functions
 ****************************************/
void setup() {
  
  Serial.begin(115200);
  Serial1.begin(115200);
  
  pinMode(pino_luz, INPUT);
  pinMode(pino_umisolo, INPUT);
  pinMode(pino_tempumi, INPUT);
}

void loop() {
  char* command = (char *) malloc(sizeof(char) * 128);
  /* Wait for the server response to read the values and built the command */
  /* While the flag is true it will take the sensors readings, build the command,
     and post the command to Ubidots */
  if (flow_control and order == 0) {
    /* Analog reading */
    float sensor1 = analogRead(pino_umisolo)*(-1)+1023;

    /* 4 is mininum width, 2 is precision; float value is copied onto str_sensor*/
    dtostrf(sensor1, 4, 2, str_sensor1);


    /* Building the logger command */
    sprintf(command, "init#");
    sprintf(command, "%s%s/%s|%s|%s|", command, USER_AGENT, VERSION, METHOD, TOKEN);
    sprintf(command, "%s%s=>", command, DEVICE_LABEL);
    sprintf(command, "%s%s:%s", command, VARIABLE_LABEL, str_sensor1);
    sprintf(command, "%s|end#final", command);

    /* Prints the command sent */
    Serial.println(command);// uncomment this line to print the command
    Serial.print("Umid_Solo: ");
    Serial.println(sensor1);

    /* Sends the command to the telemetry unit */
    Serial1.print(command);

    /* free memory*/
    free(command);
    
    /* Change the status of the flag to false. Once the data is sent, the status
       of the flag will change to true again */
    flow_control = false;
    order = 1;
  }

  /* Reading the telemetry unit */
  int i = 0;
  while (Serial1.available() > 0) {
    telemetry_unit[i++] = (char)Serial1.read();
    /* Change the status of the flag; allows the next command to be built */
    flow_control = true;
  }

  if (flow_control) {
    /* Print the server response -> OK */
    Serial.write(telemetry_unit);
    /* free memory */
    memset(telemetry_unit, 0, i);
  }

  delay(1000);


if (flow_control and order == 1) {
    /* Analog reading */
    float sensor2 = analogRead(pino_luz);

    /* 4 is mininum width, 2 is precision; float value is copied onto str_sensor*/
    dtostrf(sensor2, 4, 2, str_sensor2);

    /* Building the logger command */
    sprintf(command, "init#");
    sprintf(command, "%s%s/%s|%s|%s|", command, USER_AGENT, VERSION, METHOD, TOKEN);
    sprintf(command, "%s%s=>", command, DEVICE_LABEL);
    sprintf(command, "%s%s:%s", command, VARIABLE_LABEL2, str_sensor2);
    sprintf(command, "%s|end#final", command);

    /* Prints the command sent */
    Serial.println(command);// uncomment this line to print the command
    Serial.print("Luminosidade: ");
    Serial.println(sensor2);

    /* Sends the command to the telemetry unit */
    Serial1.print(command);

    /* free memory*/
    free(command);
    
    /* Change the status of the flag to false. Once the data is sent, the status
       of the flag will change to true again */
    flow_control = false;
    order=2;
  }

float h = dht.readHumidity();
float t = dht.readTemperature();
 if (isnan(t) || isnan(h)) 
 
  {
    Serial.println("Failed to read from DHT");
    order=0;
  } 
  else 
  {
if (flow_control and order == 2) {
    /* Analog reading */
    float sensor3 = dht.readTemperature();

    /* 4 is mininum width, 2 is precision; float value is copied onto str_sensor*/
    dtostrf(sensor3, 4, 2, str_sensor3);

    /* Building the logger command */
    sprintf(command, "init#");
    sprintf(command, "%s%s/%s|%s|%s|", command, USER_AGENT, VERSION, METHOD, TOKEN);
    sprintf(command, "%s%s=>", command, DEVICE_LABEL);
    sprintf(command, "%s%s:%s", command, VARIABLE_LABEL3, str_sensor3);
    sprintf(command, "%s|end#final", command);

    /* Prints the command sent */
    Serial.println(command);// uncomment this line to print the command
    Serial.print("Temperadura: ");
    Serial.println(sensor3);

    /* Sends the command to the telemetry unit */
    Serial1.print(command);

    /* free memory*/
    free(command);
    
    /* Change the status of the flag to false. Once the data is sent, the status
       of the flag will change to true again */
    flow_control = false;
    order=3;
  }

  if (flow_control and order == 3) {
    /* Analog reading */
    float sensor4 = dht.readHumidity();

    /* 4 is mininum width, 2 is precision; float value is copied onto str_sensor*/
    dtostrf(sensor4, 4, 2, str_sensor4);

    /* Building the logger command */
    sprintf(command, "init#");
    sprintf(command, "%s%s/%s|%s|%s|", command, USER_AGENT, VERSION, METHOD, TOKEN);
    sprintf(command, "%s%s=>", command, DEVICE_LABEL);
    sprintf(command, "%s%s:%s", command, VARIABLE_LABEL4, str_sensor4);
    sprintf(command, "%s|end#final", command);

    /* Prints the command sent */
    Serial.println(command);// uncomment this line to print the command
    Serial.print("Umidade: ");
    Serial.println(sensor4);

    /* Sends the command to the telemetry unit */
    Serial1.print(command);

    /* free memory*/
    free(command);
    
    /* Change the status of the flag to false. Once the data is sent, the status
       of the flag will change to true again */
    flow_control = false;
    order=0;
  }
  }
}
