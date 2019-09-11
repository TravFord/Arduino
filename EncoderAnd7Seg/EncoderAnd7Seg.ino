#define outputA 2
#define outputB 3

int aState;
int aLastState;
float radioMin = 108.0;
float radioMax = 117.95;
float increment = 0.05;
float radioCurrent = 108.0;
int detente = 0;


void setup() 
{
  pinMode (outputA, INPUT) ;
  pinMode (outputB, INPUT) ;

  Serial.begin(9600) ;

  aLastState = digitalRead(outputA);
}

void loop() 
{
  // 
  aState = digitalRead(outputA);
  
  if(aState != aLastState)
  {
    if(Debounce(aState))
    {
      aLastState = aState;
      
      if(detente == 0)
      {
        detente = 1;
        if(digitalRead(outputB) == aState)
        {
          radioCurrent-= increment;  
        }
        else
        {
          radioCurrent+= increment;  
        }
        
        if(radioCurrent < radioMin)
          {
            radioCurrent = radioMax;  
          }
    
          else if (radioCurrent > radioMax)
          {
            radioCurrent = radioMin;  
          }
    
          Serial.println(radioCurrent);   
       }
       else
       {
         detente = 0;  
       }
    }
  }

  else if (aState != aLastState && detente != 0)
  {
    detente = 0;  
  }
}

bool Debounce(int newState)
{
  for(int i = 1; i <= 10; i++)
  {
    if(digitalRead(outputA) != newState)
    {return false;}  
  }  

  return true;
}
