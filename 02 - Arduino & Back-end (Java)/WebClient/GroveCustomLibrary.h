class GroveSensor{ //base class
  protected:
    int pin;
  public:
    GroveSensor(int sensor_pin){
      pin = sensor_pin;
      pinMode(pin,INPUT);
    }
    virtual float getValue() = 0;
};

/*
http://wiki.seeedstudio.com/Grove-Temperature_Sensor_V1.2/
http://www.mouser.com/catalog/specsheets/Seeed_101020015.pdf
*/
class GroveTemperature: public GroveSensor{ //derivated class
  private:
    int B = 4275;// B value of the thermistor
    int R0 = 100000;// R0 = 100k
  public:
    GroveTemperature(int sensor_pin):GroveSensor(sensor_pin){}
  
    float getValue(){
      int a = analogRead(pin);
      float R = 1023.0/a-1.0;//get the resistance of the sensor - Thermal Dissipation;
      R = R0*R;
      return 1.0/(log(R/R0)/B+1/298.15)-273.15; // convert to temperature via datasheet
    }
};


/*
http://wiki.seeedstudio.com/Grove-Light_Sensor/
map(value, fromLow, fromHigh, toLow, toHigh)
value: the number to map
fromLow: the lower bound of the value’s current range
fromHigh: the upper bound of the value’s current range
toLow: the lower bound of the value’s target range
toHigh: the upper bound of the value’s target range
*/

class GroveLight: public GroveSensor{ //derivated class
  public:
    GroveLight(int sensor_pin): GroveSensor(sensor_pin){}
  
    float getValue(){
      int value = analogRead(pin);
      return map(value, 0, 800, 0, 100);
    }
};

class GroveSound: public GroveSensor{ //derivated class
  public:
    GroveSound(int sensor_pin):GroveSensor(sensor_pin){ }

    float getValue(){
      float sum = 0;
      for(int i=0; i<32; i++){
          sum += analogRead(pin);
      }
      return sum;
    }
};
