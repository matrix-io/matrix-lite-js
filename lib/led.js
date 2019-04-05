var Color = require('color');
var led = hal.led();

// - Set each everloop LED
function set(config){
  var everloop = [];

  // If valid array, fill everloop
  if (Array.isArray(config)){

    // catch invalid array lengths
    if (config.length > led.length)
      throw Error('You set '+config.length+' LEDs when your MATRIX device only has '+led.length+'\n');
    
    // set led values & set undefined values as 'black'
    everloop = new Array(led.length);
    for (var i = 0; i < led.length; i++){
      everloop[i] = (config[i] === undefined) ? {} : readColor(config[i]);
    }

    led.set(everloop);
    return;
  }

  // Else set everloop as one color
  everloop = new Array(led.length).fill(readColor(config));
  led.set(everloop);
}

// - Return an RGB(W) value from a string or object
function readColor(color){
  var ledSetting = {red: 0, green: 0, blue: 0}

  if (color === undefined || color.constructor == Object){
    color = new Object(color);

    // If color given, set. else set as 0
    ledSetting.red   = (color.r) ? color.r : 0;
    ledSetting.green = (color.g) ? color.g : 0;
    ledSetting.blue  = (color.b) ? color.b : 0;
    ledSetting.white = (color.w) ? color.w : 0;
  }

  else if (color.constructor == String){
    // parse string into rgb format
    color = Color(color);
    ledSetting.red   = color.red();
    ledSetting.green = color.green();
    ledSetting.blue  = color.blue();
  }

  else {
    throw Error(
      'LED configuration must be an object, string, or array\n'
      +'Invalid Input: '+color+'\n'
      +'examples:\n'
      +'\tled.set(["green", "rgb(0,255,0)", "#008000", {g:250}]);\n'
      +'\tled.set("purple");\n');
  }

  return ledSetting;
}

module.exports = {
  "set": function(everloop){
    set(everloop);
  },
  "length": led.length
}