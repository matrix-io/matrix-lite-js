#include <nan.h>
#include "../matrix.h"
#include "microphone.h"
#include <iostream>
#include <v8.h>
#include "matrix_hal/matrixio_bus.h"
#include "matrix_hal/microphone_core.h"

// - Create & set microphones to use MatrixIOBus bus
NAN_METHOD(setupMicCore) {        
    matrix_hal::MicrophoneCore microphone_core(microphone_array);
    microphone_core.Setup(&bus);
}

// ** EXPORTED MICROPHONE ARRAY OBJECT ** //
NAN_METHOD(microphoneCore) {
    // Create object
    v8::Local<v8::Object> obj = Nan::New<v8::Object>();

    // Set micropone configs
    Nan::Set(obj, Nan::New("setup").ToLocalChecked(),
    Nan::GetFunction(Nan::New<v8::FunctionTemplate>(setupMicCore)).ToLocalChecked());

    // Return object
    info.GetReturnValue().Set(obj);
}