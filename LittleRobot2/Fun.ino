void rcMode() {
  int leftSpeed = 0;
  int rightSpeed = 0;
  int increment = 30;
  char serialInput;
  while (remoteMode)
  {
    if (mySerial.available())
    {
      serialInput = mySerial.read();
      if (serialInput == 'a')
      {
        if (leftSpeed < 55)
        {
          leftSpeed += increment;
        }
        if (rightSpeed < 85)
        {
          rightSpeed += increment;
        }
      }
      else if (serialInput == 'r')
      {
        if (leftSpeed < 55)
        {
          leftSpeed += increment;
        }
        if (rightSpeed > -170)
        {
          rightSpeed -= increment;
        }
      }
      else if (serialInput == 'l')
      {
        if (rightSpeed < 85)
        {
          rightSpeed += increment;
        }
        if (leftSpeed > -200)
        {
          leftSpeed -= increment;
        }
      }
      else if (serialInput == 'b')
      {
        if (leftSpeed > -200)
        {
          leftSpeed -= increment;
        }
        if (rightSpeed > -170)
        {
          rightSpeed -= increment;
        }
      }
      else if (serialInput == 'r')
      {
        remoteMode = false;
      }
      setMotors(200 + leftSpeed, 170 + rightSpeed);
    }
  }
}
