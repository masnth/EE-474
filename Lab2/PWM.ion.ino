 // Create an IntervalTimer object 
IntervalTimer myTimer;
const int red = 20;
const int blue = 22;
const int green = 21;
//const int ledPin = 13;  // the pin with a LED


void setup(void) {
  pinMode(red, OUTPUT);
  pinMode(green, OUTPUT);
  pinMode(blue, OUTPUT);
  Serial.begin(9600);
  myTimer.begin(blinkLED, 2600000);  // blinkLED to run every 0.15 seconds // call this every x second
}

// The interrupt will blink the LED, and keep
// track of how many times it has blinked.

int colorCode = 0;
int ledState = LOW;
volatile unsigned long blinkCount = 0; // use volatile for shared variables

// functions called by IntervalTimer should be short, run as quickly as
// possible, and should avoid calling other functions if possible.
void blinkLED(void) {  

  int x = 1;
  for (int i = 0; i > -1; i = i + x){
    ledState = i;
    if (i == 255) {
    blinkCount = blinkCount + 1;  // increase when LED turns on //// switch direction at peak
    x = -1;  
    } 
    delay(5); //delay 5ms each increment, 5*255=1275ms
    switch(colorCode){
      case 0: analogWrite(red, ledState);
              digitalWrite(blue, HIGH);
              digitalWrite(green, HIGH);
              break;
      case 1: analogWrite(green, ledState);
              digitalWrite(red, HIGH);
              digitalWrite(blue, HIGH);
              break;
      case 2: analogWrite(blue, ledState);
              digitalWrite(green, HIGH);
              digitalWrite(red, HIGH);
              break;
    }
  }
}

// The main program will print the blink count
// to the Arduino Serial Monitor
void loop(void) {
  unsigned long blinkCopy;  // holds a copy of the blinkCount

  // to read a variable which the interrupt code writes, we
  // must temporarily disable interrupts, to be sure it will
  // not change while we are reading.  To minimize the time
  // with interrupts off, just quickly make a copy, and then
  // use the copy while allowing the interrupt to keep working.
  noInterrupts();
  blinkCopy = blinkCount;
  interrupts();
  colorCode = blinkCopy % 3;
  Serial.print("blinkCount = ");
  Serial.println(blinkCopy);
  delay(500);
}

