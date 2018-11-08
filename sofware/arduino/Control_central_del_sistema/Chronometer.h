class Chronometer{
  public:
    int horas = 0;
    int minutos = 0;
    int segundos = 0;
    int decimas = 0;

    //Chronometer();
    //~Chronometer();
    //Timer
    void timer(int range){
      // Variables will change:
      long previousMillis = 0;        // will store last time LED was updated
      
      // the follow variables is a long because the time, measured in miliseconds,
      // will quickly become a bigger number than can be stored in an int.
      long interval = range;           // interval at which to blink (milliseconds)
      unsigned long currentMillis = milisegundos;

      if((currentMillis - previousMillis) > interval) {
        // save the last time you blinked the LED
        previousMillis = currentMillis;
          return false;
      }else{
          return true;
      }
    }
    void start(){
      chronometer();
    }
  private:
  void printTime()
  {
     
     Serial.println("--------Chronometer gadget-----------");
     Serial.print("Milisegundos: ");
     Serial.println(difMilisegundos);
     Serial.print("Segundos: ");
     Serial.println(segundos);
     Serial.print("Minutos: ");
     Serial.println(minutos);
     Serial.print("Horas: ");
     Serial.println(horas);
     Serial.print("Milisegundos totales");
     Serial.println(milisegundos);
     Serial.println("------End chronometer gadget---------");
  }
  protected:
  long milisegundos = 0;
  int difTiempo = 0;
  int contMilis = 0;
  int difMilisegundos;
  //Chronometer Controller
  void chronometer()
  {
    unsigned long croMilisegundos = millis();
    milisegundos = croMilisegundos;
    difMilisegundos = milisegundos - difTiempo;
    if(difMilisegundos >= 1000){
      contMilis++;
      segundos++;
      difTiempo = (contMilis*1000);
      if(segundos == 60){
        segundos = 0;
        minutos++;
        if(minutos == 60){
          minutos = 0;
          horas++;
        }
      }
    }
    //Print Time
    //printTime();
  }
};
