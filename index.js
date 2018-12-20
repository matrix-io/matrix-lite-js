const matrix = require('./build/Release/addon');

// Returns & logs a string (test function)
// console.log(matrix);

/////////////////
// LED EXAMPLE \\
var everloop = matrix.led() // get LED object (everloop is the ring of LEDs)
var leds = []; // array representing each LED

// For each LED
for (i = 0; i < everloop.length; i++){
  // Push new color configuration (0-255)
  leds.push({
    red: 0,
    green: 0,
    blue: 1,
    white: 0
  })
}
// Write configuration to everloop
everloop.set(leds);

//////////////////
// GPIO EXAMPLE \\
var gpio = matrix.gpio(); // get GPIO object
// Set pin 4 mode (0=INPUT or 1=OUTPUT)
gpio.setPinMode(4,1);

// Toggle pin value ON/OFF
gpio.setPinValue(4,1)// set initial value
var counter = 0;
// toggle value every second
setInterval(function(){
  if (counter%2 === 0) {gpio.setPinValue(4,0);}
  else if (counter%2 === 1) {gpio.setPinValue(4,1);}
  counter++;
},1000);

// Log pin state
setInterval(function(){
  if(gpio.readPinValue(4)){console.log("PIN 4 is ON");}
  else {console.log("PIN 4 is OFF");}
},50)

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

////////////////
// UV EXAMPLE \\
// var uv = matrix.uv(); // get UV object

// // get & refresh sensor data
// setInterval(function(){
//   console.log(uv.read());
// },50)
