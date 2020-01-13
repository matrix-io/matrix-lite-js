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
    if(hal.info.isDirectBus){
      throw Error('Cannot use Alsa mic without MATRIX Kernel Modules!\n'
      +'\x1b[35mYou can install them with:\x1b[0m\n'
      +'\x1b[33msudo apt install matrixio-kernel-modules\x1b[0m\n'
      +'\x1b[33msudo reboot\x1b[0m\n');
    }

    config = {
      // Set default values for any missing configs
      rate:          config.rate !== undefined ? config.rate : 16000,
      debug:         config.debug !== undefined ? config.debug : false,
      endian:        config.endian !== undefined ? config.endian : 'little',
      bitwidth:      config.bitwidth !== undefined ? config.bitwidth : 16,
      exitOnSilence: config.exitOnSilence !== undefined ? config.exitOnSilence : 0,
      device:        config.device !== undefined ? config.device : 'hw:2,0',
      channels:      config.channels !== undefined ? config.channels : 1,// 8 channels total
    }

    return mic(config);
}

module.exports = alsa;
