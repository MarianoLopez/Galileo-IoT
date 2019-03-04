const mraa = require('mraa');
console.log('MRAA Version: ' + mraa.getVersion());

exports.TemperatureSensor = function TemperatureSensor(_pin){
  const B = 4275;
  const R0 = 100000;
  const pin = new mraa.Aio(_pin);

  this.getValue = function(){
    var rawValue = pin.read(); //read the value of the analog pin
    var R = 4095.0/rawValue-1.0;//get the resistance of the sensor - Thermal Dissipation;
    R = R0*R;
    return 1.0/(Math.log(R/R0)/B+1/298.15)-273.15; // convert to temperature via datasheet
  }
}

exports.Led = function Led(_pin){
  const pin = new mraa.Gpio(4);
  pin.dir(mraa.DIR_OUT);
  this.setValue = function(value){
      pin.write(parseInt(value));
  }
}
