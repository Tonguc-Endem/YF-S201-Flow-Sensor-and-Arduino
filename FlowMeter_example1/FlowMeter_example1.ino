byte sensorInterrupt = 0;  // 0 = digital pin 2
#define FlowMeterPulsePerSecondPerLiter 6.9
//#define FlowMeterPulsePerSecondPerLiter 7.5

volatile float PreviousPulseTime;
volatile float PulseDuration;
float LPM;
float averageLPM;
float CumulativeLPM;
float averageCount;
int LPMdecimal;

void setup() 
  {
  Serial.begin(115200);  
  PreviousPulseTime = 0;
  PulseDuration     = 0;
  LPM               = 0;
  averageLPM        = 0;
  averageCount      = 0;
  CumulativeLPM     = 0;
  LPMdecimal        = 2;
  attachInterrupt(sensorInterrupt, pulseCounter, CHANGE);
  }

void loop() 
  {

  CalculateFlow1();

  }

void CalculateFlow1()
  {
  CumulativeLPM = CumulativeLPM + (500/(PulseDuration*FlowMeterPulsePerSecondPerLiter)); 
  averageCount ++; averageLPM = CumulativeLPM/averageCount;
  if (averageCount >10000) 
    { 
    LPM = averageLPM;
    Serial.println(LPM,LPMdecimal);
    averageCount=0;   CumulativeLPM = 0; 
    }  
  }
  
void pulseCounter()
  {
  PulseDuration = millis() - PreviousPulseTime;
  PreviousPulseTime = millis(); 
  }





  
