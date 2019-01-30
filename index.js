matrixLite = require('./build/Release/addon');
led = require('./lib/led.js');

// - final module exports
function exported(){
  var drivers = {
    "led":      led,
    "gpio":     matrixLite.gpio(),
    "imu":      matrixLite.imu(),
    "humidity": matrixLite.humidity(),
    "pressure": matrixLite.pressure(),
    "uv":       matrixLite.uv()
  }

  return drivers;
}

module.exports = exported();