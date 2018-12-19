const matrix = require('./build/Release/addon');

// Returns & logs a string
// console.log(matrix.Hello());

// Returns & logs the led object
var leds = [];
for (i = 0; i < matrix.led().length; i++){
  leds.push({
    red: 1,
    green: 0,
    blue: 1,
    white: 0
  })}

matrix.led().set(leds);
