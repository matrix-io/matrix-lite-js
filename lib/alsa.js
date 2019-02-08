var mic = require('mic');// Requires matrix kernel module to work
var loudness = require('loudness');

// exported object
var alsa = {
  'setVolume': loudness.setVolume,
  'getVolume': loudness.getVolume,
  'mute':      loudness.setMuted,
  ///*not working*/ 'isMuted': loudness.getMuted
};

// mic initialization function
  alsa.mic = function(config={}){
    // If kernel modules are not installed
    if(!hal.info.isDirectBus){
      throw Error('\nCannot use Alsa mic without MATRIX Kernel Modules!\n'
      +'You can install them with:\n\n'
      +'sudo apt install matrixio-kernel-modules'
      +'sudo reboot\n');
    }

    config = {
      // Set default values for any missing configs
      rate:          config.rate !== undefined ? config.rate : 16000,
      debug:         config.debug !== undefined ? config.debug : true,
      endian:        config.endian !== undefined ? config.endian : 'little',
      bitwidth:      config.bitwidth !== undefined ? config.bitwidth : 16,
      exitOnSilence: config.exitOnSilence !== undefined ? config.exitOnSilence : 0,
      device:        config.exitOnSilence !== undefined ? config.exitOnSilence : 'hw:2,0',
      channels:      config.channels !== undefined ? config.channels : 1,// 8 channels total
    }

    return mic(config);
}

module.exports = alsa;