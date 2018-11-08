class Lights{
  public:
  unsigned long previousMillis = 0;
  bool state;
  int cont = 0;
  Lights(int pin){
    lightPin = pin;
  }
  void configure(){
    // initialize digital pin pump as an output.
    pinMode(lightPin, OUTPUT);
  }
  void start(){
    lSwitch(true);
    Serial.println("Luz encendida");
  }
  void finalize(){
    lSwitch(false);
    Serial.println("Luz apagada");
  }
  //Timer
  void timer(int OffTime, int OnTime){
    if(cont == 0){
      start();
      cont++;
    };
    unsigned long currentMillis = millis();
    if((lightState == HIGH) && (currentMillis - previousMillis >= OnTime))
    {
      lightState = LOW;  // Turn it off
      previousMillis = currentMillis;  // Remember the time
      start();
    }
    else if ((lightState == LOW) && (currentMillis - previousMillis >= OffTime))
    {
      lightState = HIGH;  // turn it on
      previousMillis = currentMillis;   // Remember the time
      finalize();
    }
  }
  //Restart timer
  void resetTimer(){
    previousMillis = 0;
  }
  protected:
  private:
  
  int lightState = LOW;             // lightState used to set the Pump
  int lightPin;      // the number of the watter pin
  
  //This function is for functioning of the water's bomba
  void lSwitch(bool stateIn){
    if(stateIn)
    {
      lightState = LOW;
    }else
    {
      lightState = HIGH;
    }
    state = stateIn;
    digitalWrite(lightPin, lightState);
  }
};
