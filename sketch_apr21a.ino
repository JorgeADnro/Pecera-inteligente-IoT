#include <Arduino.h>
#if defined(ESP32)
#include <WiFi.h>
#elif defined(ESP8266)
#include <ESP8266WiFi.h>
#endif
#include <Firebase_ESP_Client.h>
#include <Wire.h>
#include <Adafruit_Sensor.h>

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
String proximidadPath;
String motorPath;

//SERVO***********

unsigned long tiempoAnterior = 0;
unsigned long retardo = 5000;


// Timer variables (send new readings every three minutes)
unsigned long sendDataPrevMillis = 0;
unsigned long timerDelay = 2000;

//Motor
const int ENA = 5; // Canal de PWM para el motor A
const int IN1 = 15; // Dirección de rotación del motor A
const int IN2 = 2; // Dirección de rotación del motor A


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
// void sendFloat(String path, float value) {
//   if (Firebase.RTDB.setFloat(&fbdo, path.c_str(), value)) {
//     Serial.print("Writing value: ");
//     Serial.print(value);
//     Serial.print(" on the following path: ");
//     Serial.println(path);
//     Serial.println("PASSED");
//     Serial.println("PATH: " + fbdo.dataPath());
//     Serial.println("TYPE: " + fbdo.dataType());
//   } else {
//     Serial.println("FAILED");
//     Serial.println("REASON: " + fbdo.errorReason());
//   }
// }

void readData3(String path) {
  String readIncoming = "";
  if (Firebase.RTDB.getString(&fbdo, path.c_str())) {
    readIncoming = fbdo.stringData();
    int speed = readIncoming.toInt();
    Serial.println("MOTOR: " + readIncoming);
    if(speed>224){
      int s = speed;
        Serial.println("Motorsito");
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);
  ledcWrite(0, 128); // 50% de velocidad
  delay(500);

  // Gira el motor en la dirección opuesta durante 2 segundos
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, HIGH);
  ledcWrite(0, s); // 100% de velocidad
  delay(5000);

  // Detiene el motor durante 1 segundo
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, LOW);
  ledcWrite(0, 0); // 0% de velocidad
  delay(1000);
  }
    }
    // Controlar la velocidad del motor A
    //Direccion motor A
    // digitalWrite(IN1, HIGH);
    // digitalWrite(IN2, LOW);
    // ledcWrite(ENA, 50); //Velocidad motor A
      // Gira el motor en una dirección durante 2 segundos
}

void setup() {
  Serial.begin(115200);
  // Configurar los pines del motor como salidas
  pinMode(ENA, OUTPUT);
  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);

  // Configurar el canal PWM para el motor A
  ledcSetup(0, 5000, 8); // Canal 0, frecuencia de 5 kHz, resolución de 8 bits
  ledcAttachPin(ENA, 0); // Asignar el canal PWM al pin ENA

  initWiFi();

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

  proximidadPath = databasePath + "/proximidad";           // --> UsersData/<user_uid>/led
  motorPath = databasePath + "/velocidad";
}


void loop() {
  // Send new readings to database
  if (Firebase.ready() && (millis() - sendDataPrevMillis > timerDelay || sendDataPrevMillis == 0)) {
    sendDataPrevMillis = millis();
    // Send readings to database:
    //sendFloat(tempPath, temperature);
    readData3(motorPath);
  }
}