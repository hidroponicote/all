#include <SoftwareSerial.h>


/*
  intelligent hydroponic system for micro pro

  This system is to automate the hydroponic culture for any type of component that our hydroponic system has.
  This program aims to be as minimized and efficient as possible.
  It is recommended to use switching for the management of the relays.
  
  Author: Cristian Niño  
*/

#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
SoftwareSerial BT(4,2); // RX, TX

#define OLED_RESET 4
Adafruit_SSD1306 display(OLED_RESET);

#define NUMFLAKES 10
#define XPOS 0
#define YPOS 1
#define DELTAY 2

bool startStatus = false;

#import "Thermometer.h";
#import "Pumps.h";

//End Import List

//class declaration



//substrate thermometer
Thermometer substrateThermometer(A0, 21, 372, -20);  //pinIn, initial temperature, Final value(calibration)


//Water Pump
Pumps waterPump(13);

//main light
//Lights mainLight(12);

//End class declaration

int baudios = 9600;

int susTemp = 22;
bool watterPumpStatus = false;


// the setup function runs once when you press reset or power the board
void setup() {

  
  Serial.begin(baudios);
  
  // set the data rate for the SoftwareSerial port
  BT.begin(baudios);

  // by default, we'll generate the high voltage from the 3.3v line internally! (neat!)
  display.begin(SSD1306_SWITCHCAPVCC, 0x3C);  // initialize with the I2C addr 0x3C (for the 128x32)

  
  //setting the substrate thermometer
  substrateThermometer.configure(16, 18, 23);   //low temperature, ok temperature, high temperature
  //water pump configuration
  waterPump.configure();

  //Main light configuration
  //mainLight.configure();

}

// the loop function runs over and over again forever
void loop() {
  
  
  //Run thermometer
  substrateThermometer.start();
  
  //Start Bluetooth
  if (BT.available()) {
    Serial.println(BT.read());
    
  }
  if (Serial.available()) {
    BT.write(Serial.read());
  }

  
  if(!startStatus){
    // Clear the buffer.
    display.clearDisplay();
  
    // text display tests
    display.setTextSize(1);
    display.setTextColor(WHITE);
    display.setCursor(0,0);
    display.println("HOPE SYSTEM");
    display.setTextColor(BLACK, WHITE); // 'inverted' text
    display.println(1.0);
    display.setTextSize(2);
    display.setTextColor(WHITE);
    display.print("Iniciando");
    startStatus = true;
    delay(2000);
  }else{
    display.clearDisplay();
  
    // text display tests
    display.setTextSize(1);
    display.setTextColor(WHITE);
    display.setCursor(0,0);
    if(substrateThermometer.stateTemp == 4){
      display.println("Sensor desconectado");
    }else{
      if(substrateThermometer.stateTemp == 0){
        display.print("temp ALTA: ");
      }else if(substrateThermometer.stateTemp == 1){
        display.print("temp IDEAL: ");
      }else if(substrateThermometer.stateTemp == 2){
        display.print("temp PERFECTA: ");
      }else if(substrateThermometer.stateTemp == 3){
        display.print("temp BAJA: ");
      };
      display.println(substrateThermometer.temp);
    }
    display.print("Temp sust:");
    display.println(substrateThermometer.temp);
    display.print("Bomba de agua:");
    if(waterPump.state){
      display.println("on");
    }else{  
      display.println("off");
    }
    display.print("Luz principal:");
//    if(mainLight.state){
//      display.println("on");
//    }else{  
//      display.println("off");
//    }
    
  }
  //Start lights time run/stop
  //mainLight.timer(2000, 1000);
  
  //Pumps water time   run/stop
  waterPump.timer(10000, 20000);
  if((substrateThermometer.stateTemp == 0)){
    if(waterPump.state == false){
      waterPump.start();
      watterPumpStatus = true;
    }else{
      Serial.println("----ALERTA: bomba de agua encendia por altas temperaturas-------");
      }
    }else if( (substrateThermometer.stateTemp == 1) || (substrateThermometer.stateTemp == 2)){
    waterPump.finalize();
    waterPump.resetTimer();
  };

  //commans
//    if(bluetooth.currentCommand == 87){
//      //W
//      watterPumpStatus = false;
//      waterPump.finalize();
//      waterPump.resetTimer();
//    }else if(bluetooth.currentCommand == 119){
//      //w
//      waterPump.start();
//      watterPumpStatus = true;
//    }else if(bluetooth.currentCommand == 76){
//      //l
//      mainLight.start();
//    }else if(bluetooth.currentCommand == 108){
//      //L
//      mainLight.finalize();
//      mainLight.resetTimer();
//    }else{
//      //Serial.println("comando no reconocido");
//    }
    
  display.display();
}
