var Color = require('color');
var led = matrixLite.led();

// - Set each everloop LED
function set(config){
  var everloop;

  // Array Input
  if (Array.isArray(config)){
    //if (config.length === matrixLite.led.length){
    everloop = config.map(x => readColor(x));
    led.set(everloop);
    //}
  }

  // String Input
  else if (typeof config === 'string'){
    everloop = new Array(led.length).fill(readColor(config));
    led.set(everloop);
  }

  // Invalid Input
  else {
    console.log("could not read input");
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