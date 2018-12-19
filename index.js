const matrix = require('./build/Release/addon');

// Returns & logs a string
console.log(matrix.Hello());

// Returns & logs the led object
var leds = [];
for (i = 0; i < matrix.led().length; i++){
  leds.push({
    red: 10,
    green: 20,
    blue: 30,
    white: 40
  })}

console.log( matrix.led().set(leds) );
