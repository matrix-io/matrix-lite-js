# MATRIX-Lite-JS
MATRIX Lite JS is an [npm package](https://www.npmjs.com/package/@matrix-io/matrix-lite) that allows users of varying skill levels to easily program their MATRIX Device.

 <!-- This is mainly done by creating a Node.js addon for [MATRIX HAL](https://matrix-io.github.io/matrix-documentation/matrix-hal/overview/) which lets you call C++ functions with JavaScript. -->

# Roadmap
- [x] Leds
- [x] Sensors
  - [x] IMU
  - [x] Humidity
  - [x] Pressure
  - [x] UV
- [x] GPIO
- [x] Device Info
- [ ] Microphones
  - [ ] Hal Mics
  - [x] Alsa Mics
- [x] [NFC](https://github.com/matrix-io/matrix-lite-nfc-js) (separate library)

# Installation
Ensure you have a Raspberry Pi, attached with a MATRIX device, that's flashed with [Raspbian](https://www.raspberrypi.org/blog/raspbian-stretch/).

## 1. Install MATRIX HAL
https://matrix-io.github.io/matrix-documentation/matrix-hal/getting-started/installation-package/

## 2. Install Node.js & Create A Project
**Download and install the latest version of Node.js, using [nvm](https://github.com/creationix/nvm) (Node Version Manager)**
```bash
curl -o- https://raw.githubusercontent.com/creationix/nvm/v0.33.11/install.sh | bash
. ~/.bashrc
nvm install node

mkdir myApp
cd myApp
npm init -y
```
## 3. Install matrix-lite-js
```
npm install @matrix-io/matrix-lite --save
```

# Usage
## Everloop
```js
var matrix = require("@matrix-io/matrix-lite");

// Get LED count
console.log("This device has " + matrix.led.length + ' LEDs');

// A single string or object sets all LEDs
// Below are different ways of expressing a color (number values are from 0-255)
matrix.led.set('blue');
matrix.led.set('rgb(0,0,255)');
matrix.led.set('#0000ff');
matrix.led.set({r:0, g:0, b:255, w:0}); // objects can set white

// LEDs off
matrix.led.set('black');
matrix.led.set([]);
matrix.led.set();
matrix.led.set({});

// Arrays set individual LEDs
matrix.led.set(['red', 'gold', 'purple', {}, 'black', '#6F41C1', 'blue', {g:255}]);

// Arrays can simulate motion
everloop = new Array(matrix.led.length).fill({});
everloop[0] = {b:100};

setInterval(function(){
  var lastColor = everloop.shift();
  everloop.push(lastColor);
  matrix.led.set(everloop);
},50);
```

## Sensors
```js
var matrix = require('@matrix-io/matrix-lite');

// Sensors will update with each .read() call
var imu, uv, humidity, pressure;
setInterval(function(){
  imu = matrix.imu.read();
  uv = matrix.uv.read();
  humidity = matrix.humidity.read();
  pressure = matrix.pressure.read();
  
  console.log(imu, uv, humidity, pressure);
},50);
```

## GPIO
```js
var matrix = require('@matrix-io/matrix-lite');

// Read GPIO pin 0 (digital)
matrix.gpio.setFunction(0, 'DIGITAL');
matrix.gpio.setMode(0, 'input');
console.log(matrix.gpio.getDigital(0));

// Set GPIO pin 1 (digital)
matrix.gpio.setFunction(1, 'DIGITAL');
matrix.gpio.setMode(1, 'output');
matrix.gpio.setDigital(1, 'ON')

// Set GPIO pin 2 (PWM)
matrix.gpio.setFunction(2, 'PWM');
matrix.gpio.setMode(2, 'output');
matrix.gpio.setPWM({
  pin: 2,
  percentage: 25,
  frequency: 50 // min 36
});

// Set Servo Angle pin 3
matrix.gpio.setFunction(3, 'PWM');
matrix.gpio.setMode(3, 'output');
matrix.gpio.setServoAngle({
  pin: 3,
  angle: 90,
  // minimum pulse width for a PWM wave (in milliseconds)
  min_pulse_ms: 0.8
});
```

## Info
```js
var matrix = require("@matrix-io/matrix-lite");

// A string of the MATRIX device currently attached
console.log("The " + matrix.info.deviceType + " is attached to the pi");

// A boolean that's true, if the kernel modules are not installed
console.log("Are the Kernel Modules installed? " + matrix.info.isDirectBus);
```

## Alsa
### Microphone
[npm mic](https://www.npmjs.com/package/mic) is used grab our microphone data from alsa.
```js
// Record mic input to file
var matrix = require("@matrix-io/matrix-lite");
var fs = require('fs');

var mic = matrix.alsa.mic();// use default settings
var mic = matrix.alsa.mic({ // or configure settings
  rate: '16000',
  debug: true,
  exitOnSilence: 6,
  // up to 8 channels
  channels: '1'
});

// Pipe mic data to file
var micStream = mic.getAudioStream();
var file = fs.WriteStream('output.raw');
micStream.pipe(file);

micStream.on('startComplete', function() {
  setTimeout(mic.stop, 5000);
});

mic.start();
```

# Building Locally For Development
If you want to contribute to matrix-lite-js, below are the steps to build locally. Each step should take place on your Raspberry Pi.

Have MATRIX HAL installed

https://matrix-io.github.io/matrix-documentation/matrix-hal/getting-started/installation-package/

Download the matrix-lite-js repository
```bash
git clone https://github.com/matrix-io/matrix-lite-js
```

Install Node.js
```bash
curl -o- https://raw.githubusercontent.com/creationix/nvm/v0.33.11/install.sh | bash
. ~/.bashrc
nvm install 11.0.0
```

Install Node.js dependencies
```bash
npm install
```

From this point, you can treat the repository as a normal module. Any Node.js script can include it.
```js
var matrix = require('PATH_TO_FOLDER/matrix-lite-js')
```

If you need to edit any C++ files in the `hal-wrapper` folder, use the following to compile your changes.
```bash
npm run build
```
