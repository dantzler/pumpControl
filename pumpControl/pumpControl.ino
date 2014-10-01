#include <LiquidCrystal.h>

// initialize global variables
unsigned long stepIntervalMicros = 3749997UL;  // corresponds to 0.005 RPM
unsigned long previousMicros = 0UL;

unsigned long updateIntervalMillis = 500UL;  // update speed & LCD every 0.5 seconds
unsigned long previousMillis = 0UL;

const int CLOCK = 9;      // set pin 9 as clock pin

// initialize the library with the numbers of the interface pins
LiquidCrystal lcd(8, 3, 4, 5, 6, 7);

// define custom mu character
byte mu[8] = {
  B00000,
  B10001,
  B10001,
  B10001,
  B11011,
  B10101,
  B10000,
  B10000,
};

void setup(){
  
  pinMode(CLOCK, OUTPUT);
  
  // set up the LCDs number of columns & rows:
  lcd.begin(16,2);
  
  // create custom character, mu
  lcd.createChar(0, mu);
  
  // print "Flow (uL/min)" to row one of LCD
  lcd.setCursor(0,0);
  lcd.print("Flow (");
  lcd.setCursor(6,0);
  lcd.write((byte)0);
  lcd.setCursor(7,0);
  lcd.print("L/min)");
  
}

void loop(){
  
  // initialize local variables
  unsigned long currentMillis = millis();
  unsigned long currentMicros = micros();
  
  // check to see if it is time to move on step (actually 1/8 step)
  if( currentMicros - previousMicros > stepIntervalMicros){
    previousMicros = currentMicros;
    moveMotorOneStep();
  }
    
    // check to see if it is time to read the potentiometer and update the speed
  if( currentMillis - previousMillis > updateIntervalMillis){
    previousMillis = currentMillis;
    update();
  }
  
}

void moveMotorOneStep(){
  digitalWrite(9,HIGH);
  digitalWrite(9,LOW);
}

void update() {

	// initialize local variables
	int potPin = 0;				// potentiometer on analog pin 0
	int potValue = 0;
	int RPM = 0;
	int maxRPM = 30;
	int speed = 0;
	int conversionFactor = 10;		// RPM to uL per minute
	int flowRate = 0;       // SLOW! may want to change this to use int & uL/min
        
	// read the potentiometer
        potValue = analogRead(potPin);
        
	// map potentiometer to a number between 0 - 10
        speed = map( potValue, 0, 1023, 0, 10);

        // convert speed to RPM value
        RPM = speed * maxRPM / 10;
        
        // capture RPM = 0 condition to avoid divide by zero error
        if (RPM == 0){
          stepIntervalMicros = 3749997UL;  // corresponds to 0.005 RPM
        }
        // if RPM > 0, convert RPM value to stepIntervalMicros
        // 3 microseconds is the duration of the pulse at +5V
        else{
          stepIntervalMicros = ( 18750 - 3 * RPM ) / RPM;
        }
        
        // convert RPM value to flowRate
        flowRate = RPM * conversionFactor;
        
        // print flow rate on LCD
        lcd.setCursor( 0, 1 );
        lcd.print("    ");
        lcd.setCursor( 0, 1 );
        lcd.print( flowRate, DEC );
}
