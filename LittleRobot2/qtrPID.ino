// 100 300 200
// 1600 300 100
// 6400 600 100
double qtrKp = 64, qtrKd = 6, qtrKi = 1;

const int qtrMults[] = {7, 5, 3, 1, -1, -3, -5, -7};
double qtrInput;
double lastQtrInput;
double qtrOutput;
double qtrSetpoint = 0;

PID qtrPID(&qtrInput, &qtrOutput, &qtrSetpoint, qtrKp, qtrKi, qtrKd, DIRECT);

void initQtrPid()
{
  qtrPID.SetMode(AUTOMATIC);
  qtrPID.SetOutputLimits(-200, 200);
}

void computeQtrInput()
{
  lastQtrInput = qtrInput;
  qtrInput = 0;
  int qtrReadCounter = 0;
  for (int i = 0; i < 8; i++)
  {
    if (qtrValues[i] == 1)
    {
      qtrReadCounter++;
    }
    qtrInput += qtrValues[i] * qtrMults[i];
  }
  if (qtrReadCounter == 0) // If qtr has stopped seeing the line, increase the qtrInput value in the last direction until the line can be see again.
  {
    if (lastQtrInput > 0)
    {
      qtrInput = lastQtrInput + 1;
    }
    else if (lastQtrInput < 0)
    {
      qtrInput = lastQtrInput - 1;
    }
  }
  else
  {
    qtrInput /= qtrReadCounter;
  }
//  mySerial.print("QTR Read Count: ");
//  mySerial.println(qtrReadCounter);
//  mySerial.print("QTR Input: ");
//  mySerial.println(qtrInput);
//  mySerial.print("Last QTR Input: ");
//  mySerial.println(lastQtrInput);
}

void printQtrPidValues()
{
  mySerial.print("QTR Input: ");
  mySerial.print(qtrInput);
  mySerial.print(" | Output: ");
  mySerial.println(qtrOutput);
}

void executeQtrPid()
{
  computeQtrInput();
  qtrPID.Compute();
  //printQtrPidValues();
  setMotors(leftBaseSpeed + qtrOutput, rightBaseSpeed - qtrOutput);
}

void readQtrConstantsFromSerial()
{
  if (mySerial.available())
  {
    char serialInput;
    char serialInputNumber[5] = {0, 0, 0, 0, 0};
    int len = 0;
    serialInput = mySerial.read();
    //Serial.println(serialInput);
    if (serialInput == 'p')
    {
      while (!mySerial.available())
      {}
      len = mySerial.readBytes(serialInputNumber, 5);
      serialInputNumber[len] = 0;
      qtrKp = atoi(serialInputNumber);
      mySerial.print("Set Kp: ");
      mySerial.println(qtrKp);
      qtrPID.SetTunings(qtrKp, qtrKi, qtrKd);
    }
    else if (serialInput == 'i')
    {
      while (!mySerial.available())
      {}
      len = mySerial.readBytes(serialInputNumber, 5);
      serialInputNumber[len] = 0;
      qtrKi = atoi(serialInputNumber);
      mySerial.print("Set Ki: ");
      mySerial.println(qtrKi);
      qtrPID.SetTunings(qtrKp, qtrKi, qtrKd);
    }
    else if (serialInput == 'd')
    {
      while (!mySerial.available())
      {}
      len = mySerial.readBytes(serialInputNumber, 5);
      serialInputNumber[len] = 0;
      qtrKd = atoi(serialInputNumber);
      mySerial.print("Set Kd: ");
      mySerial.println(qtrKd);
      qtrPID.SetTunings(qtrKp, qtrKi, qtrKd);
    }
    else if (serialInput == 's')
    {
      stopMotors();
      stopped = true;
      mySerial.println("Stopped.");
    }
    else if (serialInput == 'c')
    {
      stopped = false;
      mySerial.println("Continued.");
    }
    else if (serialInput == 'r')
    {
      stopMotors();
      remoteMode = true;
      mySerial.println("Remote mode");
      rcMode();
    }
  }
}
