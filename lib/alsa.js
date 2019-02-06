// Requires matrix kernel module to work
var mic = require('mic');
var loudness = require('loudness');

// exported object
var alsa = {
  'setVolume': loudness.setVolume,
  'getVolume': loudness.getVolume,
  'mute':      loudness.setMuted,
  ///*not working*/ 'isMuted': loudness.getMuted
};

// Grab Mics(0-7) & Beamforming(8) channels
for(var i = 0; i < 9; i++){
  alsa['mic'+i] = {
    // default recording settings
    rate:          16000,
    debug:         false,
    endian:        'little',
    bitwidth:      16,
    exitOnSilence: 0,

    // create mic instance
    setup: function(){
      return mic({
        rate:     this.rate,
        debug:    this.debug,
        endian:   this.endian,
        bitwidth: this.bitwidth,
        device:   'hw:2,0',
        channels: i
      });
    }
  }
}

module.exports = alsa;