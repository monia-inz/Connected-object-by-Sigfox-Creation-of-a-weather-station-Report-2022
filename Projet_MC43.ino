//version 1.8.10 
/*
Projet x? - MC43 - sujetx?
Renommer le projet (enregistrer sous) comme Projetx avec x le numéro de votre groupe de projet (cf moodle)
*/
#include <Wire.h>
#include <ArduinoLowPower.h>
#include <SigFox.h>

#include <Adafruit_Sensor.h>
#include <Adafruit_BME280.h>

#define BME_SCK 9
#define BME_MISO 10
#define BME_MOSI 8

#define SCL 12
#define SDA 11 
#define SEALEVELPRESSURE_HPA (1013.25)
#define pressionnivmer (1015.1)

  Adafruit_BME280 bme; // I2C

  unsigned long delayTime;

  typedef struct __attribute__ ((packed)) sigfox_message {
  uint8_t temperature;
  uint16_t pression;
  uint8_t humidite;
  uint8_t altitude;
} SigfoxMessage;
 

  float Internal_T=0.0;
  //#define min 10  // période d'échantillonnage avec mise en veille en mn
  //#define t_mesure 8 // durée des mesures et transmissions en s

  void setup() {
  Serial.begin(115200);
  Serial.println(F("BME280 station météo test la best"));
  if (!SigFox.begin()) {
    Serial.println("Shield error or not present!");
    NVIC_SystemReset(); // rebooting
    while(1);
  }

  
  if (! bme.begin(0x76, &Wire)) {
    Serial.println("Could not find a valid BME280 sensor, check wiring!");
    while (1);
    }

  SigFox.reset();
  delay(1000);
  SigFox.debug(); // Enable debug prints and LED indication if we are testing
  SigFox.end(); //Send module to standby until we need to send a message


  Serial.println("-- Default Test --");
  //Serial.println("normal mode, 16x oversampling for all, filter off,");
  //Serial.println("0.5ms standby period");
  //delayTime = 5000;  
      
    // weather monitoring
    Serial.println("-- Weather Station Scenario --");
    Serial.println("forced mode, 1x temperature / 1x humidity / 1x pressure oversampling,");
    Serial.println("filter off");
    bme.setSampling(Adafruit_BME280::MODE_FORCED,
                    Adafruit_BME280::SAMPLING_X1, // temperature
                    Adafruit_BME280::SAMPLING_X1, // pressure
                    Adafruit_BME280::SAMPLING_X1, // humidity
                    Adafruit_BME280::FILTER_OFF   );
                      
    // suggested rate is 1/60Hz (1m)
    //delayTime = 60000; // in milliseconds
    Serial.println();
  // Configure the sensors and populate the status field ...
  
  
}

void loop() {
  // Every 5 min minutes, read all the sensors and send them
  // Let's try to optimize the data format

  SigFox.begin(); // Start the module
  delay(100); // Wait at least 30ms after first configuration (100ms before)
  SigFox.status(); // Clears all pending interrupts
  SigfoxMessage msg;
 // bme.takeForcedMeasurement(); // has no effect in normal mode
  msg.temperature = bme.readTemperature();
  msg.pression = ((float)(bme.readPressure() / 100.0F));
  msg.humidite = bme.readHumidity();
  msg.altitude = (int)bme.readAltitude(pressionnivmer);


  printValues(msg.temperature, msg.pression, msg.humidite, msg.altitude);

  // affichage pour debug
  //Serial.println("MKRFox1200");
 
  // Envoi de la trame sur le reseau sigfox
  SigFox.beginPacket();
  SigFox.write((uint8_t*)&msg, sizeof(msg));
  SigFox.endPacket();
  SigFox.end();
  //delay(10000);
  // READ THE ANALOG INPUT ON PIN AO
  int ANALOG_VALUE = analogRead(A0); 
  // READ THE-DIGITAL INPUT ON PIN 8
  int OUTPUT_VALUE = digitalRead(8);

  //PRINT OUT THE VALUE READING   
  Serial.print("ANALOG VALUE=");
  Serial.print(ANALOG_VALUE);
  Serial.print("");
  Serial.print(" OUTPUT= ");
  Serial.println(OUTPUT_VALUE);
  Serial.println(" ");
  if(analogRead(0)<350) Serial.println("=>Il pleut énormément.");
  else if(analogRead(0)<500) Serial.println("=>Il pleut modéremment.");
  else Serial.println("=> Il n'y a pas de pluie.");
  Serial.println(" ");
  //Sleep for min minutes
  //LowPower.deepSleep(((min*60)-t_mesure) * 1000); // Durée de veille en ms

}
void printValues(uint8_t temperature, uint16_t pression, uint8_t humidite, uint8_t altitude) {
    Serial.print("Temperature = ");
    Serial.print(temperature);
    Serial.println(" °C");

    Serial.print("Pressure = ");
    Serial.print(pression);
    Serial.println(" hPa");

    Serial.print("Approx. Altitude = ");
    //Serial.print(bme.readAltitude(SEALEVELPRESSURE_HPA));
    //Serial.print(altitude);
    Serial.print(bme.readAltitude(pressionnivmer));

    Serial.println(" m");

    Serial.print("Humidity = ");
    Serial.print(humidite);
    Serial.println(" %");

    Serial.println();   
}
