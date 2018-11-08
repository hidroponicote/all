#include <SoftwareSerial.h>
SoftwareSerial BT(4,2);
class Bluetooth{
  public:
    //Config bluetooth pin

    long currentCommand;

    /* Bluetooth(int rx, int tx){
      SoftwareSerial BT(rx,tx);
    } */
    void startBluetooth(int baudios)
    {
     configBluetooth(baudios);
     
    }
    void lisentBluetooth(){
       if (BT.available()) {
          Serial.write(BT.read());
          
        }
        if (Serial.available()) {
          BT.write(Serial.read());
        }
    }
  protected:
  
  private:
  void configBluetooth(int baudios){
    BT.begin(baudios);
  }
};
