# MATRIX-Lite-JS
MATRIX Lite JS is an [npm package](https://www.npmjs.com/package/@matrix-io/matrix-lite) that allows users of varying skill levels to easily program their MATRIX Device. This is achieved by creating a Node.js addon for [MATRIX HAL](https://matrix-io.github.io/matrix-documentation/matrix-hal/overview/) which lets you call C++ functions with JavaScript.

# Roadmap
This roadmap is for achieving a basic implementation of the checklist below. **As this package develops, the API will improve and may change.**
- [x] Leds
- [x] Sensors
  - [x] IMU
  - [x] Humidity
  - [x] Pressure
  - [x] UV
- [ ] GPIO
- [ ] Microphones

# Dependencies
Ensure you have a Raspberry Pi, attached with a MATRIX device, that's flashed with [Raspbian Stretch](https://www.raspberrypi.org/blog/raspbian-stretch/).

## 1. Install MATRIX HAL
https://matrix-io.github.io/matrix-documentation/matrix-hal/getting-started/installation-package/

## 2. Install Node.js & Create A Project
**Downloads and installs the latest version of Node.js, using [nvm](https://github.com/creationix/nvm) (Node Version Manager)**
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

# Usage (may change during development)
## Everloop
```js
var matrix = require('@matrix-io/matrix-lite');

// A string sets all LEDs
// Below are different ways of expressing a color
matrix.led.set('blue');
matrix.led.set('rgb(0,0,255)');
matrix.led.set('#0000ff');

// LEDs off
matrix.led.set('black');

// An array sets individual LEDs
matrix.led.set(['red', 'gold', 'purple', '#0000ff', '#6F41C1', 'blue']);

// Get LED count
console.log("This device has " + matrix.led.length + ' LEDs');
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
 
# Building Locally For Development
Below are the steps to building MATRIX-Lite locally. Each step should take place on your raspberry pi

Download the matrix-lite-js repository
```bash
git clone https://github.com/matrix-io/matrix-lite-js
```

Install Node.js
```bash
curl -o- https://raw.githubusercontent.com/creationix/nvm/v0.33.11/install.sh | bash
. ~/.bashrc
nvm install node
```

Install Node.js dependencies
```bash
npm install
```

If you need to edit any C++ files in the `hal-wrapper` folder, use the following to compile your changes.
```bash
npm run build
```