#include <nan.h>
#include "matrix.h"
#include "drivers/everloop.h"
#include "drivers/gpio.h"
#include "drivers/info.h"
#include "drivers/sensors/sensors.h"

// Initialize bus for MATRIX hardware communication
matrix_hal::MatrixIOBus bus;
bool busReady = bus.Init();

// Node addon entry point
NAN_MODULE_INIT(Initialize){
  // Throw error if MATRIX bus is not setup
  if (!busReady) return Nan::ThrowError(Nan::New("matrixio_bus not initialized!\nIs MATRIX HAL installed?").ToLocalChecked());
  
  // Export functions that return JS objects
  NAN_EXPORT(target, led);
  NAN_EXPORT(target, gpio);
  NAN_EXPORT(target, imu);
  NAN_EXPORT(target, humidity);
  NAN_EXPORT(target, pressure);
  NAN_EXPORT(target, uv);
  NAN_EXPORT(target, info);
}

// Create a Node module called "addon" and pass the entry point function.
NODE_MODULE(addon, Initialize);