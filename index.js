hal = require('./build/Release/addon');
var led = require('./lib/led.js');
var gpio = require('./lib/gpio.js');

// - final module exports
function exported(){
  var matrixLite = {
    "led":      led,
    "gpio":     gpio,
    "imu":      hal.imu(),
    "humidity": hal.humidity(),
    "pressure": hal.pressure(),
    "uv":       hal.uv()
  }

  return matrixLite;
}

module.exports = exported();