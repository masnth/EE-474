/* LED Blink, Teensyduino Tutorial #1
   http://www.pjrc.com/teensy/tutorial.html
 
   This example code is in the public domain.
*/

// Teensy 2.0 has the LED on pin 11
// Teensy++ 2.0 has the LED on pin 6
// Teensy 3.x / Teensy LC have the LED on pin 13
const int ledPin = 13;

// the setup() method runs once, when the sketch starts

void setup() {
  // initialize the digital pin as an output.
  pinMode(ledPin, OUTPUT);
  Serial.begin(38400);
}

// the loop() methor runs over and over again,
// as long as the board has power
int val;
unsigned long startTime = 0;
int ledState = HIGH;

void loop() {
  val = analogRead(2);
  Serial.print("analog 2 is: ");
  Serial.println(val);
  unsigned long currentTime = millis();
  if ((currentTime - startTime) >= val){
    startTime = currentTime;
    if (ledState == HIGH) ledState = LOW;
    else ledState = HIGH;
    digitalWrite(ledPin, ledState);   // set the LED on
  }
}

