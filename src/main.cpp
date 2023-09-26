#include <Arduino.h>
#include <Wire.h>

/* Wire connections

Mikroe-3736  ---  ESP32 DEV KITV1
-------------------------
RST ------------- 5V
STP ------------- D2 
GND ------------- GND
SDA ------------- D21
SCL ------------- D22

*******************************
*******************************


Mikroe-3736 ----- Fuente de alimentación (Puede VM por defecto)
--------------------------------------------------------------
GND ------------- GND
5V  ------------- 5V @ 2A 

*/

#define P0 0x00
#define P1 0x01
#define P2 0x02
#define P3 0x03
#define P4 0x04
#define P5 0x05

#define nSLEEP P4
#define nENBL P5
#define nFAULT P2
#define DIR P3
#define MS1 P0
#define MS2 P1
#define STEP BUILTIN_LED

#define PCA9538A_ADDRESS 0x70


void escribirRegistro(byte registro, byte valor) {
  Wire.beginTransmission(PCA9538A_ADDRESS);
  if(Wire.endTransmission() == 0){
    Serial.println("El dispositivo I2C está presente.");
  } else {
    Serial.println("El dispositivo I2C no responde.");
  }

  Wire.beginTransmission(PCA9538A_ADDRESS);
  Wire.write(registro);
  Wire.write(valor);
  byte resultado = Wire.endTransmission();

  if (resultado == 0) {
    Serial.println("Escritura exitosa.");
  } else {
    Serial.println("Error en la escritura.");
  }

  
}

void configurarPinesSalida(byte mascara) {
  escribirRegistro(0x03, mascara); // Registro de configuración de pines (Configura P4 y P5 como salidas)
}


void setup() {
  Serial.begin(9600);
  Wire.begin();
  delay(1000);
  pinMode(STEP, OUTPUT);

  configurarPinesSalida(0b00000100); // Configuramos todos los pones como salida, excepto nFault

  // Configura el pin nENBL (Pin 5) como nivel bajo (LOW)
  // Configura el pin nSLEEP (Pin 4) como nivel alto (HIGH)
  // Configura el pin MS2 (P1, penúltimo bit) a nivel Alto (Puedes modificarlo a tu gusto)
  // Configura el pin MS1 (P0, último bit) a nivel bajo (Puedes modificarlo a tu gusto)
  escribirRegistro(0x01, 0b00011011);


}

void loop() {


	delay(1000);
  
  for(int i=0; i<10000; i++){
    digitalWrite(STEP, HIGH);
    delayMicroseconds(30);
    digitalWrite(STEP, LOW);
    delayMicroseconds(600);
  }
  
  
}

