class Pumps{
  public:
  unsigned long previousMillis = 0;
  bool state;
  int cont = 0;
  Pumps(int pin){
    pumpPin = pin;
  }
  void configure(){
    // initialize digital pin pump as an output.
    pinMode(pumpPin, OUTPUT);
  }
  void start(){
    lSwitch(true);
    Serial.println("Bomba de agua iniciada");
  }
  void finalize(){
    lSwitch(false);
    Serial.println("Bomba de agua apagada");
  }
  //Timer
  void timer(int OffTime, int OnTime){
    on = OnTime;
    off = OffTime;
    if(cont == 0){
      start();
      cont++;
    };
    unsigned long currentMillis = millis();
    if((pumpState == HIGH) && (currentMillis - previousMillis >= on))
    {
      pumpState = LOW;  // Turn it off
      previousMillis = currentMillis;  // Remember the time
      start();
    }
    else if ((pumpState == LOW) && (currentMillis - previousMillis >= off))
    {
      pumpState = HIGH;  // turn it on
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

  int on;
  int off;
  
  int pumpState = LOW;             // pumpState used to set the Pump
  int pumpPin;      // the number of the watter pin
  
  //This function is for functioning of the water's bomba
  void lSwitch(bool stateIn){
    if(stateIn)
    {
      pumpState = LOW;
    }else
    {
      pumpState = HIGH;
    }
    state = stateIn;
    digitalWrite(pumpPin, pumpState);
  }
};
