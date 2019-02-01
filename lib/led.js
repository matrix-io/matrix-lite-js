var Color = require('color');
var led = matrixLite.led();

// - Set each everloop LED
function set(config){
  var everloop = [];

  // String Input
  if (typeof config === 'string'){
    everloop = new Array(led.length).fill(readColor(config));
    led.set(everloop);
  }

  // Array Input && Array is a valid size
  else if (Array.isArray(config) && config.length <= led.length){
    everloop = config.map(x => readColor(x));
    led.set(everloop);
  }

  // No input
  else if (config === undefined){
    led.set([]);
  } 

  // Invalid Input
  else {
    if (config.length >= led.length)
      throw Error('LEDs set exceed amount on MATRIX device ('+led.length+')\n');
    else
      throw Error('LED configuration must be an int, string, or array\n'
      +'example: ["green", "rgb(0,255,0)", "#008000"]\n');
  }

}

// - Return an RGB value from a string
function readColor(color){
  var color = Color(color);
  return{
    red   : color.red(),
    green : color.green(),
    blue  : color.blue()
  }
}

module.exports = {
  "set": function(everloop){
    set(everloop);
  },
  "length": led.length
}