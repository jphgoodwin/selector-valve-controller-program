
// ArduinoAutosamplerControl.cpp : Defines the entry point for the console application.
//

//variables to hold pin numbers
int stepPin = 12;
int homePin = 8;
int relayPin1 = 7;
int relayPin2 = 4;
//variables to hold run parameters
int maxSampleRuns = 3;
int maxNumberSamples = 3;
int maxCaliRuns = 3;
int blankNumber = 1;
//initiate step and home pins for output, and relayPin1 for input
void setup()
{
  pinMode(stepPin, OUTPUT);
  pinMode(homePin, OUTPUT);
  pinMode(relayPin1, INPUT);
  digitalWrite(stepPin, LOW);
  digitalWrite(homePin, LOW):
}
//function to return selector valve to home position
void returnHome()
{
  digitalWrite(homePin, HIGH);
  delay(1000);
  digitalWrite(homePin, LOW);
}
//function to step through selector valve ports
void stepThrough(int numberOfSteps)
{
  for (int step = 0; step < numberOfSteps; ++step)
  {
    digitalWrite(stepPin, HIGH);
    delay(500);
    digitalWrite(stepPin, LOW);
    delay(500);
  }
}
//function to run move valve input to calibration port,
//and carry out user defined number of runs
void calibrate()
{
  returnHome();

  for (int caliNumber = 0; caliNumber < maxCaliRuns; ++caliNumber)
  {
    while (digitalRead(relayPin1) == LOW)
    {
    }

    delay(1000);
  }
}
//function to position valve on blank port,
//in order to minimise gas waste
void blank()
{
  returnHome();
  stepThrough(blankNumber);
}
//function to run sample user defined number of times
void runSample()
{
  for (int runNumber = 0; runNumber < maxSampleRuns; ++runNumber)
  {
    while (digitalRead(relayPin1) == LOW)
    {
    }

    delay(1000);
  }
}
//continuous loop runs in arduino once power is connected
void loop()
{
  //reset the selector valve to home position
  returnHome();
  //loop until signal is received from relay
  while (digitalRead(relayPin1) == LOW)
  {
  }
  //step through to first sample
  stepThrough(2); //change this if blankNumber is altered
  //perform calibration cycle
  calibrate();
  //run a user defined number of samples
  for (int sampleNumber = 0; sampleNumber < maxNumberSamples; ++sampleNumber) 
  {
    //run the sample
    runSample();
    //re-calibrate
    calibrate();
    //move on to the next sample (from home position)
    stepThrough(sampleNumber + 2); //change this if blankNumber is altered

  }
  //set selector valve to blank port,
  //in order to conserve gas
  blank();
  //stop arduino repeating until reset
  while (true)
  { 
  }
}


