/*
  STG-850 sample code
  
For more informations, see https://www.barth-elektronik.com for more informations

  This example code is open source.

  created 7. Aug 2017
*/

#include <EEPROM.h>

int inPin = 10; // first digital pin
int Val = 0;
int Channel = 0;

// the setup function runs once when you press reset or power the board
void setup() {
  
  pinMode(LED_BUILTIN, OUTPUT);  // initialize digital pin LED_BUILTIN as an output.

  pinMode(0, OUTPUT);  // initialize High and Low side digital outputs as an output.
  pinMode(1, OUTPUT);
  pinMode(2, OUTPUT);
  pinMode(3, OUTPUT);
  pinMode(4, OUTPUT);
  pinMode(5, OUTPUT);
  pinMode(6, OUTPUT);
  pinMode(7, OUTPUT);
  pinMode(8, OUTPUT);

  pinMode(10, INPUT);  // initialize digital inputs as an input.
  pinMode(11, INPUT);
  pinMode(12, INPUT);
  pinMode(13, INPUT);

  Serial.begin(9600);  // initialize TTL-RS-232.
  while (!Serial) {
    ; // wait for serial port to connect. Needed for native USB port only
  }

  // prints title with ending line break
  Serial.println("STG-850 I/O-Test");

  // Write content to the EEPROM
  for ( int I=0; I<10; I++ )
    EEPROM.write(I, I);
  Serial.println("EEPROM written");
  // Read it back to the TTL-RS-232
  for ( int I=0; I<10; I++ )
  {
    Serial.print(EEPROM.read(I));
    Serial.print(" ");
  }
  Serial.println("");

}

// the loop function runs over and over again forever
void loop() {
  digitalWrite(LED_BUILTIN, HIGH);   // turn the LED on (HIGH is the voltage level)
  delay(100);                        // wait for 100 milli second
  digitalWrite(LED_BUILTIN, LOW);    // turn the LED off by making the voltage LOW
  delay(100);                        // wait for 100 milli second

  // Read and display analog input values
  for ( int I = 0; I < 6; I++ )
  {
    Val = analogRead(A0 + I);
    Serial.print(Val);
    Serial.print("  ");
  }
  Serial.print(" -   ");

  // Read and display digital input values
  for ( int I = 0; I < 4; I++ )
  {
    Val = digitalRead(inPin + I);
    Serial.print(Val);
    Serial.print("  ");
  }

  // Clear all outputs
  for ( int I = 0; I < 8; I++ )
  {
    digitalWrite(I, LOW);
  }

  // Set one output channel dependig from the voltage on analog input 1
  Channel = analogRead(A0) / 40;
  if ( Channel > 7 )
    Channel = 7;
  digitalWrite(Channel, HIGH);
  Serial.print(" -   ");
  Serial.print(Channel);

  // Output PWM with DC depending from the voltage on analog input 1
  Channel = analogRead(A0) / 2;
  analogWrite(8, Channel); // 0..255


  Serial.println("");



  delay(500); // wait 500 milli second
}
