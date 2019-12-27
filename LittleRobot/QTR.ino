int qtrPins[] = {30, 31, 32, 33, 34, 35, 36, 37};

// Runs in setup
// Sets pinmode and other neceassry stuff for QTR sensor
void defineQtr()
{
  for (int i = 0; i < 8; i++)
  {
    pinMode(qtrPins[i], INPUT_PULLUP);
  }
  Serial.println("Defined QTR");
}

// Reads QTR values into qtrValues array
void readQtr()
{

  for (int i = 0; i < 8; i++)
  {
    qtrValues[i] = !digitalRead(qtrPins[i]);
  }
}

// Prints out the current value of qtrValues array
void testQtr()
{
  for (int i = 0; i < 8; i++)
  {
    Serial.print(qtrValues[i]);
  }
  Serial.println();
}

void testQtrB()
{
  for (int i = 0; i < 8; i++)
  {
    mySerial.print(qtrValues[i]);
  }
  mySerial.println();
}

bool isLineCompletelyWhite()
{
  int sum = 0;
  for (int i = 0; i < 8; i++)
  {
    sum += qtrValues[i];
  }
  return (sum == 8);
}
