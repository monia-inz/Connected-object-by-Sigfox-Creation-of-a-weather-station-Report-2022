// THE SETUP ROUTINE RUNS ONCE WHEN YOU PRESS RESET
void setup() {
// INITIALIZE SERIAL COMMUNICATIONS AT 9600 BITS PER SECOND:
Serial.begin(9600); 
pinMode(A0,INPUT); 
pinMode(8, INPUT);
pinMode(2, OUTPUT);
}
// THE LOOP ROUTIINE RUNS OVER AND OVER AGAIN FOREVER
void loop() {
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
if(analogRead(0)<300) Serial.println("=>il pleut des cordes");
else if(analogRead(0)<500) Serial.println("=>il pleut belfort ;)");
else Serial.println("=> pas de pluie : ça ne peut pas être Belfort");
 Serial.println(" ");
delay(500); // DELAY IN BETWEEN 
}
