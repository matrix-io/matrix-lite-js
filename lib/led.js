var Color = require('color');
var led = hal.led();

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
    // grab array values
    everloop = config.map(x => readColor(x));

    // set remaining LEDs to black
    everloop = everloop.concat(new Array(led.length-config.length).fill(0));

    led.set(everloop);
  }

  // Invalid Input
  else {
    try{
      if (config.length >= led.length)
        throw Error('LEDs set exceed amount on MATRIX device ('+led.length+')\n');
    }
    catch(e){
      throw Error(
      'LED configuration must be an int, string, or array\n'
      +'examples:\n'
      +'\tled.set(["green", "rgb(0,255,0)", "#008000"]);\n'
      +'\tled.set("purple");\n');
    }
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