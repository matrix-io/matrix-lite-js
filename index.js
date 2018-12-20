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
    blue: 0,
    white: 0
  })
}

// Write configuration to everloop
everloop.set(leds);

/////////////////
// IMU EXAMPLE \\
// var imu = matrix.imu(); // get IMU object

// // get & refresh sensor data
// setInterval(function(){
//   console.log(imu.read());
// },50)

//////////////////////
// HUMIDITY EXAMPLE \\
// var humidity = matrix.humidity(); // get Humidity object

// // get & refresh sensor data
// setInterval(function(){
//   console.log(humidity.read());
// },50)

//////////////////////
// PRESSURE EXAMPLE \\
// var pressure = matrix.pressure(); // get Pressure object

// // get & refresh sensor data
// setInterval(function(){
//   console.log(pressure.read());
// },50)

//////////////////////
// UV EXAMPLE \\
var uv = matrix.uv(); // get UV object

// get & refresh sensor data
setInterval(function(){
  console.log(uv.read());
},50)
