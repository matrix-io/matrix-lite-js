var gpio = hal.gpio();

// - Set a pin as input or output
function setMode(pin, mode){
  if(mode === 0 || mode.toString().toLowerCase() === 'input') 
    mode = 0;
  else if(mode === 1 || mode.toString().toLowerCase() === 'output') 
    mode = 1;
  else
    throw Error('Did not specify mode as "input" or "output"\n');

  gpio.setMode(pin, mode);
}

// - Set a pin as I/O or PWM
function setFunction(pin, mode){
  if(mode === 0 || mode.toString().toLowerCase() === 'digital') 
    mode = 0;
  else if(mode === 1 || mode.toString().toLowerCase() === 'pwm') 
    mode = 1;
  else 
    throw Error('Did not specify mode as "I/O" or "PWM"\n');

  gpio.setFunction(pin, mode);
}

// - Read digital pin value
function getDigital(pin){
  return gpio.getValue(pin);
}

// - Set digital pin value
function setDigital(pin, mode){
  if(mode === 0 || mode.toString().toLowerCase() === 'off') 
    mode = 0;
  else if(mode === 1 || mode.toString().toLowerCase() === 'on') 
    mode = 1;
  else 
    throw Error('Did not specify value as "on" or "off"\n');

  return gpio.setDigital(pin, mode);
}

// - Set Servo Angle
function setServoAngle(config){
  // min_pulse_ms is the minimum pulse width for a PWM wave in milliseconds
  return gpio.setServoAngle(config.angle, config.min_pulse_ms, config.pin);
}

// - Set PWM value
function setPWM(config){
  return gpio.setPWM(config.frequency, config.percentage, config.pin);
}

module.exports = {
  "setMode": function(pin, mode){
    setMode(pin, mode);
  },
  "setFunction": function(pin, mode){
    setFunction(pin, mode);
  },
  "getDigital": function(pin){
    return getDigital(pin);
  },
  "setDigital": function(pin, mode){
    return setDigital(pin, mode);
  },
  "setPWM": function(config){
    return setPWM(config);
  },
  "setServoAngle": function(config){
    return setServoAngle(config);
  }
};
