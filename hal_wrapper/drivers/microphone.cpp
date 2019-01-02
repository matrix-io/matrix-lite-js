#include <nan.h>
#include "../matrix.h"
#include "microphone.h"
#include <v8.h>
#include "matrix_hal/matrixio_bus.h"
#include "matrix_hal/microphone_array.h"
#include "matrix_hal/microphone_core.h"

// Part of the microphone example includes
#include <sys/stat.h>
// Linux file control options
#include <fcntl.h>
// System calls
#include <unistd.h>
// Google gflags parser
#include <gflags/gflags.h>
// Communicating with Pi GPIO
#include <wiringPi.h>
// Input/output stream class to operate on files
#include <fstream>
// Input/output streams and functions
#include <iostream>
// Use strings
#include <string>
// Arrays for math operations
#include <valarray>

// Create MATRIX microphone object
matrix_hal::MicrophoneArray mics;

// Default settings
int gain = -1, sampling_rate = 16000;
// - Edit recording settings
NAN_METHOD(config) {
    // if object argument is not given, throw error
    if (!info[0]->IsObject()) {Nan::ThrowTypeError("Argument must be an object");return;}

    // grab microhone config properties
    v8::Local<v8::Object> configs = info[0]->ToObject();
    v8::Local<v8::String> gainProp = Nan::New("gain").ToLocalChecked();
    v8::Local<v8::String> samplingRateProp = Nan::New("sampling_rate").ToLocalChecked();

    // set new property values
    int gain = Nan::Get(configs, gainProp).ToLocalChecked()->NumberValue();
    int sampling_rate = Nan::Get(configs, samplingRateProp).ToLocalChecked()->NumberValue();

    //test
    info.GetReturnValue().Set(gain);
    // info.GetReturnValue().Set(sampling_rate);
}

// ** EXPORTED LED OBJECT ** //
NAN_METHOD(microphone) {
    // Create object
    v8::Local<v8::Object> obj = Nan::New<v8::Object>();

    // Set micropone config
    Nan::Set(obj, Nan::New("config").ToLocalChecked(),
    Nan::GetFunction(Nan::New<v8::FunctionTemplate>(config)).ToLocalChecked());

    // Return object
    info.GetReturnValue().Set(obj);
}