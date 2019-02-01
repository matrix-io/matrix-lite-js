matrixLite = require('./build/Release/addon');
var led = require('./lib/led.js');
var gpio = require('./lib/gpio.js');

// - final module exports
function exported(){
  var drivers = {
    "led":      led,
    "gpio":     gpio,
    "imu":      matrixLite.imu(),
    "humidity": matrixLite.humidity(),
    "pressure": matrixLite.pressure(),
    "uv":       matrixLite.uv()
  }

  return drivers;
}

module.exports = exported();