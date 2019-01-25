#include <nan.h>
#include "../matrix.h"
#include "microphone.h"
#include <v8.h>
#include "matrix_hal/matrixio_bus.h"
#include "matrix_hal/microphone_array.h"
#include "matrix_hal/microphone_core.h"

// Create MATRIX microphone array object
matrix_hal::MicrophoneArray microphone_array;

// - Setup MATRIX array mics
NAN_METHOD(setup) {
    microphone_array.Setup(&bus);
}

// - Get gain
NAN_METHOD(getGain) {
    if(microphone_array.GetGain()){
        uint32_t gain = microphone_array.Gain();
        info.GetReturnValue().Set(Nan::New(gain));
    }
    else
        Nan::ThrowTypeError("Could not get gain");
}

// - Set gain
NAN_METHOD(setGain) {
    // if number argument is not given, throw error
    if (!info[0]->IsNumber()) {Nan::ThrowTypeError("Argument must be a valid number");return;}
    
    // read & set gain
    int gain = info[0]->NumberValue();
    if(gain > 0)
        microphone_array.SetGain(gain);
}

// - Get sampling rate
NAN_METHOD(getSamplingRate) {
    if(microphone_array.GetSamplingRate()){
        uint32_t samplingRate = microphone_array.SamplingRate();
        info.GetReturnValue().Set(Nan::New(samplingRate));
    }
    else
        Nan::ThrowTypeError("Could not get sampling rate");
}

// - Set sampling rate
NAN_METHOD(setSamplingRate) {
    // if number argument is not given, throw error
    if (!info[0]->IsNumber()) {Nan::ThrowTypeError("Argument must be a valid number");return;}
    
    // read & set sampling rate
    int samplingRate = info[0]->NumberValue();
    microphone_array.SetSamplingRate(samplingRate);
}

// ** EXPORTED MICROPHONE ARRAY OBJECT ** //
NAN_METHOD(microphoneArray) {
    // Create object
    v8::Local<v8::Object> obj = Nan::New<v8::Object>();

    // Set micropone configs
    Nan::Set(obj, Nan::New("setup").ToLocalChecked(),
    Nan::GetFunction(Nan::New<v8::FunctionTemplate>(setup)).ToLocalChecked());

    Nan::Set(obj, Nan::New("setGain").ToLocalChecked(),
    Nan::GetFunction(Nan::New<v8::FunctionTemplate>(setGain)).ToLocalChecked());
    Nan::Set(obj, Nan::New("getGain").ToLocalChecked(),
    Nan::GetFunction(Nan::New<v8::FunctionTemplate>(getGain)).ToLocalChecked());

    Nan::Set(obj, Nan::New("setSamplingRate").ToLocalChecked(),
    Nan::GetFunction(Nan::New<v8::FunctionTemplate>(setSamplingRate)).ToLocalChecked());
    Nan::Set(obj, Nan::New("getSamplingRate").ToLocalChecked(),
    Nan::GetFunction(Nan::New<v8::FunctionTemplate>(getSamplingRate)).ToLocalChecked());

    // Return object
    info.GetReturnValue().Set(obj);
}