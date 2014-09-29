#include <LiquidCrystal.h>

// initialize global variables
unsigned long stepIntervalMicros = 3749997UL;
unsigned long previousMicros = 0UL;

unsigned long updateIntervalMillis = 2000UL;  // update speed & LCD every 0.333 seconds
unsigned long previousMillis = 0UL;

void setup(){
  /*
  //Initialize the library with the numbers of the interface pins
  LiquidCrystal lcd(8, 3, 4, 5, 6, 7);
  //Set up the LCDs number of columns & rows:
  lcd.begin(16,2);
  //Print a message to the LCD
  lcd.setCursor(0,0);
  lcd.print("Flow (mL/min)");
  */
}

void loop(){
  
  //initialize local variables
  unsigned long currentMillis = millis();
  unsigned long currentMicros = micros();
  
  if( currentMicros - previousMicros > stepIntervalMicros){
    previousMicros = currentMicros;
    moveMotorOneStep();
  }
  
  if( currentMillis - previousMillis > updateIntervalMillis){
    previousMillis = currentMillis;
    update();
  }
  
}

void     moveMotorOneStep(){
  pinMode (9, OUTPUT);  //Set the LED pin as output
  digitalWrite(9,HIGH);
  //PORTB |= B00000010;        // Set bit 1 high on digital pin 9
  //delayMicroseconds(10);      // wait 3 microseconds
  digitalWrite(9,LOW);
  //PORTB &= B11111101;        // Set bit 1 low on digital pin 9
}

void update() {

	// initialize local variables
	int potPin = 0;				// potentiometer on analog pin 0
	int potValue = 0;
	int RPM = 0;
	int maxRPM = 30;
	int speed = 0;
	int conversionFactor = 1000;		// RPM to mL per minute
	int flowRate = 0;       // SLOW! may want to change this to use int & uL/min
        
        //Initialize the library with the numbers of the interface pins
        LiquidCrystal lcd(8, 3, 4, 5, 6, 7);
        //Set up the LCDs number of columns & rows:
        lcd.begin(16,2);
        lcd.setCursor(0,0);
        lcd.print("Flow (mL/min)");
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
        lcd.print( flowRate, DEC );
}
