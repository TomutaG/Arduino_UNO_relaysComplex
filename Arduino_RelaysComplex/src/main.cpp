#define     DIO_PINS_ON_USE           12u
#define     ALL_DIO_PINS_TO_ACTUATE   0xFFu

int         LedBuiltInReadVal   = 0;     // variable to store the read value
int         DioPins[12]         = {2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13};

void SetupDioPins()
{
  char idx;

  for (idx = 0; idx < DIO_PINS_ON_USE; idx++)
  {
    pinMode(DioPins[idx], OUTPUT);
  }
}

char InputIsValid(char inputToCheck)
{
  char retVal = false;
  char idx;
  char requestedPin;

  requestedPin = inputToCheck & 0x7Fu;
  for (idx = 0; ((idx < DIO_PINS_ON_USE) && (retVal == false)); idx++)
  {
    if (requestedPin == DioPins[idx])
    {
      retVal = true;
    }
  }
  if (requestedPin == ALL_DIO_PINS_TO_ACTUATE)
  {
    retVal = ALL_DIO_PINS_TO_ACTUATE;
  }
}

// actuate all LEDs in the same time.
void AllLedsONOFF(char operation)
{
  char idx;

  if (true == operation)
  {
    for (idx = 0; idx < DIO_PINS_ON_USE; idx++)
    {
      digitalWrite(DioPins[idx], HIGH);  // turn the LED on (HIGH is the voltage level)
    }
  }
  else
  {
    for (idx = 0; idx < DIO_PINS_ON_USE; idx++)
    {
      digitalWrite(DioPins[idx], LOW);  // turn the LED on (HIGH is the voltage level)
    }
  }
}

// the setup function runs once when you press reset or power the board
void setup() {
  // initialize digital pin LED_BUILTIN as an output.
  SetupDioPins();
  Serial.begin(9600);
}

// the loop function runs over and over again forever
void loop()
{
  if (Serial.available() > 0)
  {
    char inputSerialChar;
    char requestedState;
    char requestedPin;

    inputSerialChar = Serial.read();

    if (true == InputIsValid(inputSerialChar))
    {
      requestedPin = inputSerialChar & 0x7Fu;
      requestedState = inputSerialChar & 80u;
      if (1 == requestedState)
      {
        digitalWrite(requestedPin, HIGH);  // turn the LED on (HIGH is the voltage level)
        Serial.println("### Pin ON");
      }
      else
      {
        digitalWrite(requestedPin, LOW);  // turn the LED off by making the voltage LOW
        Serial.println("### Pin OFF");
      }
    }
    else if (ALL_DIO_PINS_TO_ACTUATE == requestedPin)
    {
      AllLedsONOFF(true);
    }
    else
    {
      Serial.println("*** Invalid command requested");

      /* Signal the error visually via the build in LED. */

      digitalWrite(LED_BUILTIN, HIGH);    // turn the LED on (HIGH is the voltage level)
      delay(100);                         // wait for a little time
      digitalWrite(LED_BUILTIN, LOW);     // turn the LED off by making the voltage LOW
      delay(100);                         // wait for a little time

      digitalWrite(LED_BUILTIN, HIGH);    // turn the LED on (HIGH is the voltage level)
      delay(100);                         // wait for a little time
      digitalWrite(LED_BUILTIN, LOW);     // turn the LED off by making the voltage LOW
      delay(100);                         // wait for a little time

      digitalWrite(LED_BUILTIN, HIGH);    // turn the LED on (HIGH is the voltage level)
      delay(100);                         // wait for a little time
      digitalWrite(LED_BUILTIN, LOW);     // turn the LED off by making the voltage LOW
      delay(100);                         // wait for a little time
    }
  }

  delay(100);                       // wait for a little time
}
