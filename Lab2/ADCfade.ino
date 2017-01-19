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
  myTimer.begin(blinkLED, 5100000);  // blinkLED to run every 0.15 seconds // call this every x second
}

// The interrupt will blink the LED, and keep
// track of how many times it has blinked.
int val;
unsigned long startTime = 0;

int colorCode = 0;
int ledState = LOW;
volatile unsigned long blinkCount = 0; // use volatile for shared variables
float val2;

// functions called by IntervalTimer should be short, run as quickly as
// possible, and should avoid calling other functions if possible.
void blinkLED(void) {  
  val = analogRead(2);
  val2 = val * (10.0 / 1023.0); 
  Serial.print("analog 2 is: ");
  Serial.println(val);
  int x = -1;
  for (int i = 255; i < 256; i = i + x){
    ledState = i;
    if (i == 0) {
    blinkCount = blinkCount + 1;  // increase when LED turns on //// switch direction at peak
    x = 1;  
    } 
    delay(val2); //delay 5ms each increment, 5*255=1275ms
    switch(colorCode){
      case 0: analogWrite(red, ledState);
              analogWrite(blue, 255);
              analogWrite(green, 255);
              break;
      case 1: analogWrite(green, ledState);
              analogWrite(blue, 255);
              analogWrite(red, 255);
              break;
      case 2: analogWrite(blue, ledState);
              analogWrite(red, 255);
              analogWrite(green, 255);
              break;
      default: analogWrite(blue, 255);
              analogWrite(red, 255);
              analogWrite(green, 255);
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
