#include <nan.h>
#include "matrix.h"
#include "drivers/everloop.h"
#include "drivers/sensors/imu.h"

// Declare bus for MATRIX hardware communication
matrix_hal::MatrixIOBus bus;
// Initialize MATRIX bus
bool busReady = bus.Init();

// NAN_METHOD is a Nan macro enabling convenient way of creating native node functions.
NAN_METHOD(Hello) { 
    // Create an instance of V8's String type
    auto message = Nan::New("HELLO WORLD! ):^D").ToLocalChecked();
    //auto message = Nan::New(halNumber);
    // 'info' is a macro's "implicit" parameter - it's a bridge object between C++ and JavaScript runtimes
    // You would use info to both extract the parameters passed to a function as well as set the return value.
    info.GetReturnValue().Set(message);
}

// Module initialization logic
NAN_MODULE_INIT(Initialize) {
  // Initialize MATRIX BUS
  if (!bus.Init()) return Nan::ThrowError(Nan::New("MATRIX HAL BUS: NOT INITIALIZED!").ToLocalChecked());

    // Export function that returns "hello world"
    NAN_EXPORT(target, Hello);
    // Export function that returns LED object
    NAN_EXPORT(target, led);
    // Export function that returns Sensor objects
    NAN_EXPORT(target, imu);
}

// Create the module called "addon" and initialize it with `Initialize` function (created with NAN_MODULE_INIT macro)
NODE_MODULE(addon, Initialize);