// AUTHOR: Andreas Leibetseder
// Converts Ergometer/Pulse Handles & Pulse Sensor Input to keypresses.
// configurable for Flappy Cycling or Quake 3 Arena Mod (set cfg accordingly)
// Flappy Cycling Mode:
// - presses 'x' key on every ergometer pedal cycle or 'z'/'c' keys on pulse handle touch
// Quake 3 Arena Mode:
// - presses 'x' key on every ergometer pedal cycle or 'h' key on puls sensor heart beat

// Additional Info:
// pulse sensor code from https://github.com/WorldFamousElectronics/PulseSensor_Amped_Arduino/tree/88c1548d77f43464d3719a3a83df067fdf7ebea8
// files: AllSerialHandling.ino, Interrupt.ino, Timer_Interrupt_Notes.ino
// code in this file marked with [pulsesensor.com start/end]

// config (0 = flappy, 1 = quake3)
const int cfg = 0;

// globals (pedals)
int pedalsState = 0;
boolean pedalsAreHigh = false;
// PINs (pedal)
const int pedalsPin = 2;
const int jumperPin = 4; // needed to disable keyboard functionality
const int ledPin =  13;

// globals (touch)
const int MAX_LOWER_NOISE    = 10; // ignore up until 10 to cancel out lower noise
const int MIN_UPPER_NOISE = 250; // upper noise can occur
const int MAX_L_SIGNAL = 35; // L is downpowered by voltage divider -> weaker signal
const int MIN_R_SIGNAL = 45;
// PINs (touch)
const int touchPin = 0; // for touch analysis (analog)
// timing (touch)
unsigned long touchSignalTime = 0; // for touch interval reading

// globals (heart rate)
/* pulsesensor.com START */
//  Variables
int pulsePin = 2;                 // Pulse Sensor purple wire connected to analog pin 2
int blinkPin = 13;                // pin to blink led at each beat
int fadePin = 5;                  // pin to do fancy classy fading blink at each beat
int fadeRate = 0;                 // used to fade LED on with PWM on fadePin

// Volatile Variables, used in the interrupt service routine!
volatile int BPM;                   // int that holds raw Analog in 0. updated every 2mS
volatile int Signal;                // holds the incoming raw data
volatile int IBI = 600;             // int that holds the time interval between beats! Must be seeded!
volatile boolean Pulse = false;     // "True" when User's live heartbeat is detected. "False" when not a "live beat".
volatile boolean QS = false;        // becomes true when Arduoino finds a beat.

// Regards Serial OutPut  -- Set This Up to your needs
static boolean serialVisual = false;   // Set to 'false' by Default.  Re-set to 'true' to see Arduino Serial Monitor ASCII Visual Pulse
/* pulsesensor.com END */

// globals (keys)
char keyL = 'z';
char keyR = 'c';
int keyStateL = 0;
int keyStateR = 0;
char keyHeart = 'h';

void setup()
{
  pinMode(ledPin, OUTPUT);
  pinMode(pedalsPin, INPUT);
  pinMode(jumperPin, INPUT);
  digitalWrite(jumperPin, HIGH); // enable pull up resistor on pin

  Serial.begin(115200); /* pulsesensor.com changed from 9600 to 115200 */

  /* pulsesensor.com START */
  interruptSetup();                 // sets up to read Pulse Sensor signal every 2mS
  // IF YOU ARE POWERING The Pulse Sensor AT VOLTAGE LESS THAN THE BOARD VOLTAGE,
  // UN-COMMENT THE NEXT LINE AND APPLY THAT VOLTAGE TO THE A-REF PIN
  //   analogReference(EXTERNAL);
  /* pulsesensor.com END */

  startTime(touchSignalTime);

  Keyboard.begin();

  //delay(2000); //a slight delay for system stabilization

}

void loop()
{
  // only continueif LOW (0) is read
  // (pull up resistors are inverting, so
  // if jumper plugged in, read yields LOW...)
  while (digitalRead(jumperPin) == HIGH)
  {
    // remove jumper from jumperPin to activate
    // infinite loop and keep arduino from being
    // detected as a keyboard
  }

  if (cfg < 1)
  {
     /* BIKE PULSE SENSOR TOUCH */
    handleTouch(touchPin, 50);
  }
  else
  {
    /* FINGER PULSE SENSOR */
    /* pulsesensor.com START */
    //serialOutput();

    if (QS == true)
    {     // A Heartbeat Was Found
          // BPM and IBI have been Determined
          // Quantified Self "QS" true when arduino finds a heartbeat
          Keyboard.write(104);                // press 'h'
          //digitalWrite(blinkPin,HIGH);     // Blink LED, we got a beat.
          fadeRate = 255;         // Makes the LED Fade Effect Happen
                                  // Set 'fadeRate' Variable to 255 to fade LED with pulse
          //serialOutputWhenBeatHappens();   // A Beat Happened, Output that to serial.
          QS = false;                      // reset the Quantified Self flag for next time
    }
    //delay(20);                           //  take a break (necessary?)
    /* pulsesensor.com END */
  }

  /* PEDAL RATE */
  // light onbard LED if pedals are HIGH
  pedalsState = digitalRead(pedalsPin);
  digitalWrite(ledPin, pedalsState);

  // output 'x' as keyboard on pedals HIGH status
  if (pedalsState == HIGH)
  {
    if (!pedalsAreHigh)
    {
      Keyboard.write(120);
      pedalsAreHigh = true;
    }
    //delay(300);
  }
  else
  {
    pedalsAreHigh = false;
  }

}

void handleTouch(int pin, int interVal)
{
    if (checkInterval(touchSignalTime, interVal))
    {
      int a;
      a = analogRead(pin);

      if (a >= MAX_LOWER_NOISE && a <= MAX_L_SIGNAL)
      {

        if (keyStateR > 0)
        {
          Keyboard.release(keyR);
          keyStateR = 0;
        }

        if (keyStateL < 1)
        {
          Keyboard.press(keyL);
          keyStateL = 1;
        }

      }
      else if (a >= MIN_R_SIGNAL && a <= MIN_UPPER_NOISE)
      {
        if (keyStateL > 0)
        {
          Keyboard.release(keyL);
          keyStateL = 0;
        }

        if (keyStateR < 1)
        {
          Keyboard.press(keyR);
          keyStateR = 1;
        }

      }
      else
      {
        // signal is lower or upper noise
		// ( signal < MAX_LOWER_NOISE || signal > MIN_UPPER_NOISE)
        releaseAllKeys();
      }
      startTime(touchSignalTime);
    }
}

void releaseAllKeys()
{
  if (keyStateL > 0) {
    Keyboard.release(keyL);
    keyStateL = 0;
  }
  if (keyStateR > 0) {
    Keyboard.release(keyR);
    keyStateR = 0;
  }
}

void startTime(unsigned long &timerVar)
{
  timerVar = millis();
}

bool checkInterval(unsigned long timerVar, int interval)
{
  unsigned long elapsed = getElapsedTime(timerVar);
  if (elapsed >= interval) return true;
  return false;
}

unsigned long getElapsedTime(unsigned long timerVar)
{
  unsigned long CurrentTime = millis();
  unsigned long ElapsedTime = CurrentTime - timerVar;
  return ElapsedTime;
}
