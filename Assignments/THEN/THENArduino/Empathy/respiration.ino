/*
  AnalogReadSerial
  Reads an analog input on pin 0, prints the result to the serial monitor.
  Attach the center pin of a potentiometer to pin A0, and the outside pins to +5V and ground.
 
 This example code is in the public domain.
 */

// the setup routine runs once when you press reset:

#define INIT -1
#define BREATH_IN 0 
#define BREATH_OUT 1
#define DEBUG 0
#define INPUT_PIN 2

//numbers
int vals[10];
int samples=10;
int state = INIT;
int baseline = 0;
int temp;
float voltage;
double thermistor;
unsigned long time, period_respiration, frequency=0;
boolean first = true;
float p, ps, f;

int sensorToTemp(int sensorVal)
{
  //calculate stuff
  voltage = convert*sensorVal;
  thermistor = (voltage*15000/(5.0-voltage))/1000.0;
  float k1 = 0.00022468;
  float k0 = 0.00102119;
  float k2 = 0.000000133342;
  float ln1KR = log(1000.0*thermistor);
  float temperature = pow( ( k0 + k1*ln1KR + k2*pow(ln1KR,3) ),-1) - 273.15;
  temperature = 9.0/5.0*temperature+32.0;  
  temp = temperature;
  return temp; 
}


void setupRespiration() {
  // initialize serial communication at 9600 bits per second:
  //Serial.begin(9600);  
}

// the loop routine runs over and over again forever:
float runRespiration() 
{
  // read the input on analog pin 0:
  int averageVal=0;
  int sum=0;
  int i = 0;
  int temp=0;
  
  for (i = 0; i < samples; i++)
  {      
    //grab the sensor value
    int sensorValue = analogRead(INPUT_PIN);
    vals[i] = sensorValue;
  }

  for(i=0; i<samples; i++)
  {
       sum += vals[i];
  }
  
  averageVal = sum/samples;
   
  //calculate stuff
  temp = sensorToTemp(averageVal);
  
  //output things
  // print out the value you read:
  if(DEBUG)
  {
    Serial.print(averageVal);
    Serial.print(", ");
    Serial.print(voltage);
    Serial.print(", ");
    Serial.print(thermistor);
    Serial.print(", ");
    Serial.println(temp);
  } 
  
  //STATE MACHINE

  if(state == INIT)
  {
    
    baseline = temp;    
    state = BREATH_IN;
    
    if(DEBUG)
    {
      Serial.println("BEGIN BREATH DETECTION!");
      Serial.print("baseline: ");
      Serial.println(baseline);
    }
    
  }
  else if(state == BREATH_IN)
  {
    if(temp > baseline+5)
    {
      if(DEBUG) Serial.println("BREATH!");
      
      state = BREATH_OUT;
      if (first)
      {
         if(DEBUG) Serial.println("disable first");
         first = false;
         time = millis();
      }
      else
      {        
        unsigned long currentTime = millis();
        period_respiration = currentTime-time;      
        time = currentTime;        
        p = (float)period_respiration;
        ps = p/1000.0;
        f = 1/ps;
        
        if(DEBUG)
        {
          Serial.println("STUFF");
          Serial.println(p);
          Serial.println(ps);          
        }

        if(DEBUG)
        {
          Serial.print("Frequency: ");
          Serial.println(f);
        }
        return f;
      }
    }     
  }
  else if (state == BREATH_OUT)
  {
    if(temp < baseline+5)
    {
      if(DEBUG) Serial.println("breath over");     
   
      state = BREATH_IN;
    }
  } 
  return f;
}
