byte sensorInterrupt = 0;  // 0 = digital pin 2
#define FlowMeterPulsePerSecondPerLiter 6.9
//#define FlowMeterPulsePerSecondPerLiter 7.5
float FlowCalculationDuration =1000;


float FlowCalculationStartTime;
volatile float PulseCount;
float LPM;
int LPMdecimal;

void setup() 
  {
  PulseCount = 0;
  Serial.begin(115200);  
  LPM               = 0;
  LPMdecimal        = 2;
  attachInterrupt(sensorInterrupt, pulseCounter2, CHANGE);
  FlowCalculationStartTime = millis();
  }

void loop() 
  {

  CalculateFlow2();
 
  }


void CalculateFlow2()
  {
  if (millis()-FlowCalculationStartTime > FlowCalculationDuration)
    {
    LPM = PulseCount/(2*FlowMeterPulsePerSecondPerLiter*(FlowCalculationDuration/1000));
    DisplayLPM();
    FlowCalculationStartTime = millis();
    PulseCount=0;
    }
  }
    

void pulseCounter2()
  {
  PulseCount++;
  }
  

void DisplayLPM()
  {
  Serial.println(LPM,LPMdecimal);
  }




  
