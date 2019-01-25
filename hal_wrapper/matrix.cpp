#include <nan.h>
#include "matrix.h"
#include "drivers/everloop.h"
#include "drivers/gpio.h"
#include "drivers/microphone.h"
#include "drivers/sensors/imu.h"
#include "drivers/sensors/humidity.h"
#include "drivers/sensors/pressure.h"
#include "drivers/sensors/uv.h"

// Declare bus for MATRIX hardware communication
matrix_hal::MatrixIOBus bus;
// Initialize MATRIX bus
bool busReady = bus.Init();

// Module initialization logic
NAN_MODULE_INIT(Initialize) {
  // Initialize MATRIX BUS
  if (!bus.Init()) return Nan::ThrowError(Nan::New("MATRIX HAL BUS: NOT INITIALIZED!").ToLocalChecked());
    // Export function that returns LED object
    NAN_EXPORT(target, led);
    // Export function that returns GPIO object
    NAN_EXPORT(target, gpio);
    // Export function that returns Microphone objects
    NAN_EXPORT(target, microphoneArray);
    // NAN_EXPORT(target, microphoneCore);
    // Export function that returns Sensor objects
    NAN_EXPORT(target, imu);
    NAN_EXPORT(target, humidity);
    NAN_EXPORT(target, pressure);
    NAN_EXPORT(target, uv);
}

// Create the module called "addon" and initialize it with `Initialize` function (created with NAN_MODULE_INIT macro)
NODE_MODULE(addon, Initialize);