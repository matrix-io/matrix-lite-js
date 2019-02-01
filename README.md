# MATRIX-Lite-JS
 MATRIX Lite JS is an NPM package that allows users to interface with MATRIX HAL, without having to code in C++.

# Roadmap
This roadmap is for achieving a basic implementation of the checklist below. **As this module develops, the api will improve and may change.**
- [x] Leds
- [x] Sensors
  - [x] IMU
  - [x] Humidity
  - [x] Pressure
  - [x] UV
- [ ] GPIO
- [ ] Microphones

# Dependancies
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

# Usage
## Everloop
```js
var matrix = require("matrix-lite");

// A string sets all LEDs
// Below are different ways of expressing a color
matrix.led.set('blue');
matrix.led.set("rgb(0,0,255)");
matrix.led.set("#0000ff");

// An array sets individual LEDs
matrix.led.set(["red", "gold", "purple", "#0000ff", "#6F41C1", "blue"]);
```

## Sensors
```js
var matrix = require("matrix-lite");

var imu = matrix.imu.read();
var uv = matrix.uv.read();
var humidity = matrix.humidity.read();
var pressure = matrix.pressure.read();

console.log(imu,uv,humidity, pressure);
```
 
