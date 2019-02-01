var gpio = matrixLite.gpio();

// - Set a pin as input or output
function setMode(pin, mode){
  if(mode === 'input') 
    mode = 0;
  else if(mode === 'output') 
    mode = 1;
  else 
    throw Error('Did not specify mode as "input" or "output"\n');

  gpio.setMode(pin, mode);
}

// - Set a pin as I/O or PWM
function setFunction(pin, mode){
  if(mode === 'I/O') 
    mode = 0;
  else if(mode === 'PWM') 
    mode = 1;
  else 
    throw Error('Did not specify mode as "I/O" or "PWM"\n');

  gpio.setFunction(pin, mode);
}

// - Read digital pin value
function readDigital(pin){
  return gpio.readDigital(pin);
}

// console.log(gpio);// CC REMOVE
module.exports = {
  "setMode": function(pin, mode){
    setMode(pin, mode);
  },
  "setFunction": function(pin, mode){
    setFunction(pin, mode);
  },
  "readDigital": function(pin){
    return readDigital(pin);
  }
};