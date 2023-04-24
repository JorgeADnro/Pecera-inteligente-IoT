#include <Arduino.h>
#if defined(ESP32)
#include <WiFi.h>
#elif defined(ESP8266)
#include <ESP8266WiFi.h>
#endif
#include <Firebase_ESP_Client.h>
#include <Wire.h>
#include <Adafruit_Sensor.h>

#include <OneWire.h>
#include <DallasTemperature.h>
#include <Servo.h>  // Incluimos la librería del Servo

#include <driver/ledc.h>

// Provide the token generation process info.
#include "addons/TokenHelper.h"
// Provide the RTDB payload printing info and other helper functions.
#include "addons/RTDBHelper.h"

// Insert your network credentials
#define WIFI_SSID "DESKTOP-ONRCU7C 8237"
#define WIFI_PASSWORD "82h6F$14"

// Insert Firebase project API Key
#define API_KEY "AIzaSyCNR5AzznMTE0341budXMRZBVjRSyBQg6o"

// Insert Authorized Email and Corresponding Password
#define USER_EMAIL "proyectodev7@gmail.com"
#define USER_PASSWORD "gran_turismo"

// Insert RTDB URLefine the RTDB URL
#define DATABASE_URL "https://dashboardesp32-default-rtdb.firebaseio.com/"


// Define Firebase objects
FirebaseData fbdo;
FirebaseAuth auth;
FirebaseConfig config;

// Variable to save USER UID
String uid;

// Variables to save database paths
String databasePath;
String tempPath;
String luzPath;
String ledPath;
String comidaPath;
String proximidadPath;
String porcentajePath;
String motorPath;

//SERVO***********
#define SERVO_PIN 14
Servo servo1;
unsigned long tiempoAnterior = 0;
unsigned long retardo = 5000;


// Timer variables (send new readings every three minutes)
unsigned long sendDataPrevMillis = 0;
unsigned long timerDelay = 2000;
//******************

// BME280 sensor
//Adafruit_BME280 bme; // I2C
float temperature;
float luz2;
const int led = 32;  //led
const int luz = 33;  //luz
//******************TEMPERATURA
OneWire ourWire(4);                   //Se establece el pin 2  como bus OneWire
DallasTemperature sensors(&ourWire);  //Se declara una variable u objeto para nuestro sensor
//*****************************

//Sensor ultrasonico
const int trigPin = 19;
const int echoPin = 18;

// //Motor
// const int ENA = 5; // Canal de PWM para el motor A
// const int IN1 = 2; // Dirección de rotación del motor A
// const int IN2 = 15; // Dirección de rotación del motor A


// Initialize WiFi
void initWiFi() {
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  Serial.print("Connecting to WiFi ..");
  while (WiFi.status() != WL_CONNECTED) {
    Serial.print('.');
    delay(1000);
  }
  Serial.println(WiFi.localIP());
  Serial.println();
}

// Write float values to the database
void sendFloat(String path, float value) {
  if (Firebase.RTDB.setFloat(&fbdo, path.c_str(), value)) {
    Serial.print("Writing value: ");
    Serial.print(value);
    Serial.print(" on the following path: ");
    Serial.println(path);
    Serial.println("PASSED");
    Serial.println("PATH: " + fbdo.dataPath());
    Serial.println("TYPE: " + fbdo.dataType());
  } else {
    Serial.println("FAILED");
    Serial.println("REASON: " + fbdo.errorReason());
  }
}
void readData(String path) {
  String readIncoming = "";
  if (Firebase.RTDB.getString(&fbdo, path.c_str())) {
    Serial.println("PATH: " + fbdo.dataPath());
    Serial.println("TYPE: " + fbdo.dataType());
    if (fbdo.dataType() == "string") {
      readIncoming = fbdo.stringData();
      Serial.println("DATA: " + readIncoming);
      if (readIncoming == "LED ON") {
        digitalWrite(led, HIGH);  // turn the LED on (HIGH is the voltage level)
      }
      if (readIncoming == "LED OFF") {
        digitalWrite(led, LOW);
      }
      /*if(analogRead(luz)<=800){
              digitalWrite(led, LOW);   
          }else{
               digitalWrite(led, HIGH); 
      }*/
    }
  } else {
    Serial.println("FAILED");
    Serial.println("REASON: " + fbdo.errorReason());
  }
}


void readData2(String path) {
  String readIncoming = "";
  if (Firebase.RTDB.getString(&fbdo, path.c_str())) {
    Serial.println("PATH: " + fbdo.dataPath());
    Serial.println("TYPE: " + fbdo.dataType());
    if (fbdo.dataType() == "string") {
      readIncoming = fbdo.stringData();
      Serial.println("DATA: " + readIncoming);
      if (readIncoming == "COMIDA ON") {
          servo1.write(0);
      }
      if (readIncoming == "COMIDA OFF") {
          servo1.write(35);
      }
    } else {
      Serial.println("FAILED");
      Serial.println("REASON: " + fbdo.errorReason());
    }
  }
}

void readData3(String path) {
  // String readIncoming = "";
  // if (Firebase.RTDB.getString(&fbdo, path.c_str())) {
  //   Serial.println("PATH: " + fbdo.dataPath());
  //   Serial.println("TYPE: " + fbdo.dataType());

  //     readIncoming = fbdo.stringData();
  //     int speed = readIncoming.toInt();
//  Serial.println("MOTOR: " + readIncoming);
  //    // Controlar la velocidad del motor A
  //      //Direccion motor A
  //      digitalWrite(IN1, HIGH);
  //      digitalWrite(IN2, LOW);
  //     ledcWrite(ENA, 50); //Velocidad motor A

  // }

}

void setup() {
  Serial.begin(115200);
  pinMode(led, OUTPUT);
  
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);

  // // Configurar los pines del motor como salidas
  // pinMode(ENA, OUTPUT);
  // pinMode(IN1, OUTPUT);
  // pinMode(IN2, OUTPUT);

  // // Configurar el canal PWM para el motor A
  // ledcSetup(0, 5000, 8); // Canal 0, frecuencia de 5 kHz, resolución de 8 bits
  // ledcAttachPin(ENA, 0); // Asignar el canal PWM al pin ENA

  servo1.attach(SERVO_PIN);
  // Initialize BME280 sensor
  //initBME();
  initWiFi();
  pinMode(luz, INPUT);
  // Assign the api key (required)
  config.api_key = API_KEY;

  // Assign the user sign in credentials
  auth.user.email = USER_EMAIL;
  auth.user.password = USER_PASSWORD;

  // Assign the RTDB URL (required)
  config.database_url = DATABASE_URL;

  Firebase.reconnectWiFi(true);
  fbdo.setResponseSize(4096);

  // Assign the callback function for the long running token generation task */
  config.token_status_callback = tokenStatusCallback;  //see addons/TokenHelper.h

  // Assign the maximum retry of token generation
  config.max_token_generation_retry = 5;

  // Initialize the library with the Firebase authen and config
  Firebase.begin(&config, &auth);

  // Getting the user UID might take a few seconds
  Serial.println("Getting User UID");
  while ((auth.token.uid) == "") {
    Serial.print('.');
    delay(1000);
  }
  // Print user UID
  uid = auth.token.uid.c_str();
  Serial.print("User UID: ");
  Serial.println(uid);

  // Update database path
  databasePath = "/UsersData/" + uid;

  // Update database path for sensor readings
  tempPath = databasePath + "/temperature";  // --> UsersData/<user_uid>/temperature
  luzPath = databasePath + "/luz";           // --> UsersData/<user_uid>/led
  ledPath = databasePath + "/led";           // --> UsersData/<user_uid>/led
  proximidadPath = databasePath + "/proximidad";           // --> UsersData/<user_uid>/led
  comidaPath = databasePath + "/comida";
  motorPath = databasePath + "/velocidad";
  porcentajePath = databasePath + "/proximidadPorcentaje";
}


void loop() {
  // Send new readings to database
  if (Firebase.ready() && (millis() - sendDataPrevMillis > timerDelay || sendDataPrevMillis == 0)) {
    sendDataPrevMillis = millis();




    //******************TEMPERATURA
    sensors.requestTemperatures();             //Se envía el comando para leer la temperatura
    temperature = sensors.getTempCByIndex(0);  //Se obtiene la temperatura en ºC

    Serial.print("Temperatura= ");
    Serial.print(temperature);
    Serial.println(" C");
    //******************************

    //******************LUZ

    luz2=analogRead(luz);
    Serial.print("Luz= ");
    Serial.print(luz2);
    //****************************** Proximidad
    long duration, distance, per;
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  duration = pulseIn(echoPin, HIGH);
  distance = duration * 0.034 / 2;
  per = (10-distance)*100/8;
  Serial.print("Distance: ");
  Serial.print(distance);
  Serial.println(" cm");
    Serial.print("Porcen: ");
  Serial.print(per);
  Serial.println(" %");
  delay(500);

    // Send readings to database:
    sendFloat(tempPath, temperature);
    sendFloat(luzPath, luz2);
    sendFloat(proximidadPath, distance);
    sendFloat(porcentajePath, per);
    readData(ledPath);
    readData2(comidaPath);
    //readData3(motorPath);
  }
}