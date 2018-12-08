//MASTER 

#define DEBUG 0

//PPG = A0
//GSR = A1
//Respiration = A2

unsigned long gsr = 0;
float respirationFrequency = 0;
float ppgFrequency = 0;

float newPPG, newR;

void setup()
{
  
 // pinMode(A0, INPUT);
  pinMode(A1, INPUT);
//  pinMode(A2, INPUT);
  
  Serial.begin(9600);
  //Serial.println("AWAKENING");
  setupGSR();
  //Serial.println("1");
 // setupPPG();
  //Serial.println("2");
 // setupRespiration();
  //Serial.println("3");
}

void loop()
{
  
  if(DEBUG) Serial.println("4");
  delay(500);
  gsr = runGSR();
  Serial.println("GSR here");
  if ( gsr >= 400 && gsr <=1023){
  Serial.println("red");
    setupLIGHT();

  }
  else if ( gsr >= 250 && gsr <=399){
    Serial.println("green");
    setupLIGHT();
}
    else if ( gsr >= 90 && gsr <=249){
    Serial.println("blue");
    setupLIGHT();
}
    else if ( gsr <=89){
    Serial.println("NO Light");
    setupLIGHT();
    }
  
  if(DEBUG) Serial.println("5");
  
//  newR = runRespiration();
  
  if(DEBUG) Serial.println("6");
  
//  newPPG = runPPG();
  
  //PPG sanitizing
  if(ppgFrequency == 0 && newPPG != 0)
  {
    ppgFrequency = newPPG;
  }
  else if ( abs(newPPG-ppgFrequency)>0.5*ppgFrequency )
  {
   //do nothing 
  } 
  else
  {
    ppgFrequency = newPPG;    
  }
  
  //respiration sanitizing (none)
  respirationFrequency = newR;    
  
  
  
  
  
  if(DEBUG) Serial.println("7");
  
  if(DEBUG)
  {  
    Serial.print("GSR: ");
    Serial.println(gsr);
    
//    Serial.print("Respiration: ");
//    Serial.println(respirationFrequency);
//    
//    Serial.print("PPG: ");
//    Serial.println(ppgFrequency);
  }
  
//  Serial.print(ppgFrequency);
//  Serial.print(",");
//  Serial.print(respirationFrequency);
//  Serial.print(",");
  Serial.println(gsr);
  
  delay(100);
    
}
