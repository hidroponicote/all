class Thermometer{
  public:
    int thermpin;
    int stateTemp;   
    int t0;      
    float vf0; 
    //actual temperature
    float temp;
    int  highTemp;
    int  idealTemp;
    int  lowTemp;
    //minimum temperature
    int minTemp;
    
    char message = "";
    Thermometer(int pin, int tempIn, int valFin, int minTempe){
      thermpin = pin;                         // Assign analog input at thermometer pin                  
      t0 = tempIn;                            //actual temperature
      vf0 = valFin;
      minTemp = minTempe;
    }
    void configure(int temAlta, int temIdeal, int temBaja){
      // initialize analogic pin thermometer as an pullup.
      pinMode(thermpin, INPUT_PULLUP);
      highTemp = temAlta;
      idealTemp = temIdeal;
      lowTemp = temBaja;
    }
    void start(){
      action();
    }
    void setTemp(){
      return temp;
    }
  protected:
  private:
  void calTemp(){
    float dtemp, dtemp_avg;
      dtemp_avg = 0;
      for (int i = 0; i < 1024; i++) {
        float vf = analogRead(thermpin) * (4976.30 / 1023.000);
        //Serial.println(vf);
        dtemp = (vf - vf0) * 0.4545454;
        dtemp_avg = dtemp_avg + dtemp;
      }
      //Save data to termometer
      temp = (t0 - dtemp_avg / 1024);
  }
  void printTemp(){
    

    if(stateTemp == 4){
      //Serial.println("Sensor desconectado");
    }else{
      if(stateTemp == 0){
        Serial.print("temperatura ALTA ( grados centigrados)   = ");
      }else if(stateTemp == 1){
        Serial.print("temperatura IDEAL ( grados centigrados)   = ");
      }else if(stateTemp == 2){
        Serial.print("temperatura PERFECTA ( grados centigrados)   = ");
      }else if(stateTemp == 3){
        Serial.print("temperatura BAJA ( grados centigrados)   = ");
      };
      Serial.println(temp);
    }
  }
  
  void action(){
    //calculate time
    calTemp();
    
    if( temp > highTemp ){
      stateTemp = 0;
    }else if( temp > lowTemp && temp < highTemp ){
      stateTemp = 1;
    if( temp == idealTemp){
      stateTemp = 2;
    }
    }else if( temp < lowTemp && temp > (minTemp-1)){
      stateTemp = 3;
    }else if( temp < minTemp){
      stateTemp = 4;
    }
    printTemp();
  }
};
