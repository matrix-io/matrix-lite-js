const matrix = require('./build/Release/addon');

// Returns & logs a string (test function)
// console.log(matrix);

/////////////////
// LED EXAMPLE \\
var everloop = matrix.led() // get LED object (everloop is the ring of LEDs)
var leds = []; // array representing each LED

// For each LED
for (i = 0; i < matrix.led().length; i++){
  // Push new color configuration
  leds.push({
    red: 0,
    green: 0,
    blue: 1,
    white: 0
  })
}

// Write configuration to everloop
everloop.set(leds);

/////////////////
// IMU EXAMPLE \\
var imu = matrix.imu(); // get IMU object

// get & refresh sensors
setInterval(function(){
  console.log(imu.read());
},50)