/*
  AnalogReadSerial
  Reads an analog input on pin 0, prints the result to the serial monitor.
  Attach the center pin of a potentiometer to pin A0, and the outside pins to +5V and ground.
 
 This example code is in the public domain.
 */

// the setup routine runs once when you press reset:

#define INIT -1
#define UP 0 
#define DOWN 1
#define DEBUG 0
#define INPUT_PIN 0


//numbers
float convert = 5/1024.0;
int vals_ppg[10];
int samples_ppg=10;
int state_PPG = INIT;
float voltage_PPG;
unsigned long time_ppg, period_ppg;
boolean first_ppg = true;
float p_ppg, ps_ppg, f_ppg;
float threshold = 0.800;

void setupPPG() 
{
  //na
}

// the loop routine runs over and over again forever:
float runPPG() 
{
  // read the input on analog pin 0:
  int averageVal=0;
  int sum=0;
  int i = 0;
  int temp=0;
  
  for (i = 0; i < samples_ppg; i++)
  {      
    //grab the sensor value
    int sensorValue = analogRead(INPUT_PIN);
    vals_ppg[i] = sensorValue;
  }

  for(i=0; i<samples_ppg; i++)
  {
       sum += vals_ppg[i];
  }
  
  averageVal = sum/samples_ppg;
  voltage_PPG = averageVal*convert;
    
  //output things
  // print out the value you read:
  if(DEBUG)
  {
    Serial.print(averageVal);
    Serial.print(", ");
    Serial.println(voltage_PPG);    
  } 
  
  //STATE MACHINE

  if(state_PPG == INIT)
  {
    state_PPG = DOWN;   
    if(DEBUG)
    {
      Serial.println("BEGIN PPG DETECTION!");
    }
    
  }
  else if(state_PPG == DOWN)
  {
    if(voltage_PPG > threshold)
    {
      if(DEBUG) Serial.println("PPG UP");
      
      state_PPG = UP;

      if (first_ppg)
      {
         if(DEBUG) Serial.println("disable first_ppg");
         first_ppg = false;
         time_ppg = millis();
      }
      else
      {        
        unsigned long currentTime = millis();
        period_ppg = currentTime-time_ppg;      
        time_ppg = currentTime;        
        p_ppg = (float)period_ppg;
        ps_ppg = p_ppg/1000.0;
        f_ppg = 1/ps_ppg;
        
        if(DEBUG)
        {
          Serial.println("STUFF");
          Serial.println(p_ppg);
          Serial.println(ps_ppg);          
        }

        if(DEBUG)
        {
          Serial.print("Frequency: ");
          Serial.println(f_ppg);
        }
        return f_ppg;
      }
    }     
  }
  else if (state_PPG == UP)
  {
    if(voltage_PPG < threshold)
    {
      if(DEBUG) Serial.println("PPG DOWN");     
   
      state_PPG = DOWN;
    }
  } 
  return f_ppg;
}
