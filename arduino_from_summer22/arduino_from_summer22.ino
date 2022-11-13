// This example shows basic use of a Pololu High Power Stepper Motor Driver.
//
// It shows how to initialize the driver, configure various settings, and enable
// the driver.  It shows how to send pulses to the STEP pin to step the motor
// and how to switch directions using the DIR pin.
//
// Before using this example, be sure to change the setCurrentMilliamps36v4 line
// to have an appropriate current limit for your system.  Also, see this
// library's documentation for information about how to connect the driver:
//   http://pololu.github.io/high-power-stepper-driver

#include <ServoInput.h>
#include <SPI.h>
#include <HighPowerStepperDriver.h>

// ServoInputPin<2> mast;
ServoInputPin<3> rudder;

const double MastStep = 0.9 / 20;
const double RudderStep = 1.8;

const uint8_t MastDirPin = 5;
const uint8_t MastStepPin = 4;
const uint8_t MastCSPin = 6;

const uint8_t RudderDirPin = 8;
const uint8_t RudderStepPin = 9;
const uint8_t RudderCSPin = 7;

// This period is the length of the delay between steps, which controls the
// stepper motor's speed.  You can increase the delay to make the stepper motor
// go slower.  If you decrease the delay, the stepper motor will go faster, but
// there is a limit to how fast it can go before it starts missing steps.
const uint16_t StepPeriodUs = 3000;

//HighPowerStepperDriver mastsd;
HighPowerStepperDriver ruddersd;

int currRudder;


void setup()
{
  SPI.begin();
  Serial.begin(9600);
  // mastsd.setChipSelectPin(MastCSPin);
  ruddersd.setChipSelectPin(RudderCSPin);

  
  // Drive the STEP and DIR pins low initially.
  // pinMode(MastStepPin, OUTPUT);
  // digitalWrite(MastStepPin, LOW);
  // pinMode(MastDirPin, OUTPUT);
  // digitalWrite(MastDirPin, LOW);

  pinMode(RudderStepPin, OUTPUT);
  digitalWrite(RudderStepPin, LOW);
  pinMode(RudderDirPin, OUTPUT);
  digitalWrite(RudderDirPin, LOW);
  
  // Give the driver some time to power up.
  delay(1);

  // Reset the driver to its default settings and clear latched status
  // conditions.

  // mastsd.resetSettings();
  // mastsd.clearStatus();
  
  ruddersd.resetSettings();
  ruddersd.clearStatus();

  // Select auto mixed decay.  TI's DRV8711 documentation recommends this mode
  // for most applications, and we find that it usually works well.
  // mastsd.setDecayMode(HPSDDecayMode::AutoMixed);
  ruddersd.setDecayMode(HPSDDecayMode::AutoMixed);

  // Set the current limit. You should change the number here to an appropriate
  // value for your particular system.
  // mastsd.setCurrentMilliamps36v4(800);
  ruddersd.setCurrentMilliamps36v4(4000);

  // Set the number of microsteps that correspond to one full step.
  // mastsd.setStepMode(HPSDStepMode::MicroStep1);
  ruddersd.setStepMode(HPSDStepMode::MicroStep1);
  // Enable the motor outputs.
  // mastsd.enableDriver();
  ruddersd.enableDriver();
/**
  while (!ServoInput.available()) {  // wait for all signals to be ready
    Serial.println("Waiting for servo signals...");
    delay(500);
  }
  **/

  currRudder = 0;
}

void loop()
{
  //int mastAngle = (int) mast.getAngle()-90;
  int rudderAngle = (int) rudder.getAngle() - 90;
  //Serial.print(mastAngle);
  //Serial.println(rudderAngle);
  /*
  if(mastAngle > 60) {
    mastdir(1);
    
    for(unsigned int x = 0; x < 10; x++)
    {
      maststep();
      delayMicroseconds(StepPeriodUs);
    }     
    
  }
  
  else if (mastAngle < -20) {
    mastdir(0);
    for(unsigned int x = 0; x < 10; x++)
    {
      maststep();
      delayMicroseconds(StepPeriodUs);
    }
  }
*/
  if(rudderAngle >= 72 ) {
    ruddermove(-320/40);
  }
  else if (rudderAngle >=  58) {
    ruddermove(-240/40);
  }
  else if (rudderAngle >= 44 ) {
    ruddermove(-160/40);
  }
  else if (rudderAngle >= 30 ) {
    ruddermove(-80/40);
  }
  else if (rudderAngle >= 16 ) {
    ruddermove(0);
  }
  else if (rudderAngle >= 2 ) {
    ruddermove(80/40);
  }
  else if (rudderAngle >= -12 ) {
    ruddermove(160/40);
  }
  else if (rudderAngle >= -26 ) {
    ruddermove(240/40);
  }
  else {
    ruddermove(320/40);
  }

  delay(50);


/*
  if(rudderAngle > 60 && currRudder <= 90) {
    rudderdir(1);
    rudderstep();
    currRudder += 0.225;
  }
  
  else if (rudderAngle < -20 && currRudder >= -90) {
    rudderdir(0);
    rudderstep();
    currRudder -= 0.225;
  }
    
  delayMicroseconds(StepPeriodUs);
  */
}
     

  

  


  
  


// Sends a pulse on the STEP pin to tell the driver to take one step, and also
//delays to control the speed of the motor.
/*void step()
{
  // The STEP minimum high pulse width is 1.9 microseconds.
  digitalWrite(StepPin, HIGH);
  delayMicroseconds(3);
  digitalWrite(StepPin, LOW);
  delayMicroseconds(3);
}

// Writes a high or low value to the direction pin to specify what direction to
// turn the motor.
void setDirection(bool dir)
{
  // The STEP pin must not change for at least 200 nanoseconds before and after
  // changing the DIR pin.
  delayMicroseconds(1);
  digitalWrite(DirPin, dir);
  delayMicroseconds(1);
}
*/
void rudderstep() {
  digitalWrite(RudderStepPin, HIGH);
  delayMicroseconds(3);
  digitalWrite(RudderStepPin, LOW);
  delayMicroseconds(3);
}
/*
void maststep() {
  digitalWrite(MastStepPin, HIGH);
  delayMicroseconds(3);
  digitalWrite(MastStepPin, LOW);
  delayMicroseconds(3);
}
*/
void rudderdir(bool dir) {
  delayMicroseconds(1);
  digitalWrite(RudderDirPin, dir);
  delayMicroseconds(1);
  
}
/*
void mastdir(bool dir) {
  delayMicroseconds(1);
  digitalWrite(MastDirPin, dir);
  delayMicroseconds(1);

}
*/

void ruddermove(int degree) {
   if (degree > currRudder) {
      rudderdir(1);
      while (degree != currRudder) {
        rudderstep();
        currRudder++;
        delayMicroseconds(StepPeriodUs*16); 
      }
   
   }

   else if (degree < currRudder) {
      rudderdir(0);
      while (degree != currRudder) {
        rudderstep();
        currRudder--;
        delayMicroseconds(StepPeriodUs*16);
      }
    
   }
}
