// testing exposed c++
const matrix = require('./build/Release/addon');

// Returns & logs a string (test function)
// console.log(matrix);

/////////////////
// LED EXAMPLE \\
var everloop = matrix.led() // get LED object (everloop is the ring of LEDs)
var leds = []; // array representing each LED

// For each LED
for (i = 0; i < everloop.length; i++){
  // Push new color configuration (0-255)
  leds.push({
    red: 1,
    blue: 1
  });
}
// Write configuration to everloop
everloop.set(leds);


////////////////////////
// MICROPHONE EXAMPLE \\
// setup mics
var mics = matrix.microphoneArray();
var micsCore = matrix.microphoneCore();

mics.setup();
micsCore.setup();

// set config
mics.setSamplingRate(16000);// Set sampling rate must come before set gain!
mics.setGain(1);
mics.showConfiguration();

// beamforming delays
mics.calculateDelays({
  "azimutal_angle": 0,
  "polar_angle": 0,
  "radial_distance_mm": 1000,
  "sound_speed_mmseg": 320 * 1000
});

console.log("\n\n************\n");
console.log(buffer);
console.log("Channels: "+mics.channels());
console.log("Sampling Rate: "+mics.getSamplingRate());
console.log("Number Of Samples: "+mics.numberOfSamples());
console.log("\n************\n");

var buffer = [
  [mics.channels() + 1],
  [mics.getSamplingRate() + mics.numberOfSamples()]
];

// RECORD MICROPHONES
// initial vars
var audioData = "";
seconds_to_record = 2;
var samples = 0;
console.log("Recording Starting");

//open file
var fs = require('fs');
var wstream = fs.createWriteStream('mics.txt');

// record
for (let s = 0; s < seconds_to_record; s++) {
  while(true){
    mics.read();
    // For number of samples
    for (let s = 0; s < mics.numberOfSamples(); s++) {
      // For each microphone
      for (let c = 0; c < 1; c++) {
        // Send microphone data to buffer
        // buffer[c][samples] = mics.at(s, c);
        audioData += mics.at(s, c) + "\n";
        console.log( mics.at(s, c));
        // console.log(mics.at(s, c));
      }
      // Increment samples for buffer write
      samples++;
    }

    if (samples >= mics.getSamplingRate()) {
      // Set samples to zero for loop to fill buffer
      samples = 0;
      break;
    }
  }
}

wstream.write(audioData);
console.log("done");
// end stream
wstream.end(function(){
  console.log("Recording Finished!");
  process.exit();
});


// while (true){
  // // Record audio
  // if (mics.read()) {
  //   // Read 1 microphone data
  //   for(s = 0; s < mics.numberOfSamples(); s++){
  //     buffer[1][s] = mics.at(s, 1);
  //     console.log(buffer[1][s]);
  //     // console.log(Date.now());
  //     audioData += buffer[1][s] + "\n";
  //   };
  // }
// }

///////////////////////////////////
// GPIO DIGITAL SET/READ EXAMPLE \\
// var gpio = matrix.gpio(); // get GPIO object
// // Set pin 4 mode (0=INPUT or 1=OUTPUT)
// gpio.setMode(4,1);

// // Toggle pin value ON/OFF
// gpio.setDigital(4,1)// set initial value
// var counter = 0;
// // toggle value every second
// setInterval(function(){
//   if (counter%2 === 0) {gpio.setDigital(4,0);}
//   else if (counter%2 === 1) {gpio.setDigital(4,1);}
//   counter++;
// },1000);

// // Log pin state
// setInterval(function(){
//   if(gpio.readDigital(4)){console.log("PIN 4 is ON");}
//   else {console.log("PIN 4 is OFF");}
// },50)

////////////////////////////
// GPIO PWM SERVO ANGLE EXAMPLE \\
// var gpio = matrix.gpio(); // get GPIO object
// gpio.setMode(4,1);// set pin 0 to output
// gpio.setFunction(4, 1);// set pin 0 to PWM

// var percentage = 0.8;
// gpio.setServoAngle(179,percentage,4)
// setTimeout(function(){
//   gpio.setServoAngle(1,percentage,4)
// },2000);
// float angle, float min_pulse_ms, int pin (0-15)
// var angle = 0;
// setInterval(function(){
//   if(angle < 180){
//     console.log(angle);
//     gpio.setServoAngle(angle,0.5,0)// set servo angle
//     angle ++;
//   }
// },100);


//////////////////////
// GPIO PWM EXAMPLE \\
// var gpio = matrix.gpio(); // get GPIO object
// gpio.setMode(0, 1);// set pin 0 to output
// gpio.setFunction(0, 1);// set pin 0 to PWM
// var percentage = 0;
// setInterval(function(){
//   console.log(percentage);
//   // Parameters: float frequency, float percentage, int pin (0-15)
//   gpio.setPWM(50, percentage, 0)// set pwm for pin 0
//   percentage += 0.2;
// },500);

/////////////////
// IMU EXAMPLE \\
// var imu = matrix.imu(); // get IMU object

// // get & refresh sensor data
// setInterval(function(){
//   console.log(imu.read());
// },50)

//////////////////////
// HUMIDITY EXAMPLE \\
// var humidity = matrix.humidity(); // get Humidity object

// // get & refresh sensor data
// setInterval(function(){
//   console.log(humidity.read());
// },50)

//////////////////////
// PRESSURE EXAMPLE \\
// var pressure = matrix.pressure(); // get Pressure object

// // get & refresh sensor data
// setInterval(function(){
//   console.log(pressure.read());
// },50)

////////////////
// UV EXAMPLE \\
// var uv = matrix.uv(); // get UV object

// // get & refresh sensor data
// setInterval(function(){
//   console.log(uv.read());
// },50)
