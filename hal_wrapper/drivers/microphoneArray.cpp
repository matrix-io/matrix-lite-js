#include <nan.h>
#include "../matrix.h"
#include "microphone.h"
#include <iostream> // being used for cout CC REMOVE LATER
#include <v8.h>
#include "matrix_hal/matrixio_bus.h"
#include "matrix_hal/microphone_array.h"

// Create MATRIX microphone array object
matrix_hal::MicrophoneArray microphone_array;

// - Set microphones to use MatrixIOBus bus
NAN_METHOD(setupMicArray) {
    microphone_array.Setup(&bus);
}

// - Calculate delays
NAN_METHOD(calculateDelays) {
    // if object argument is not given, throw error
    if (!info[0]->IsObject()) {Nan::ThrowTypeError("Argument must be an object");return;}

    // grab microhone config properties
    v8::Local<v8::Object> configs = info[0]->ToObject();
    v8::Local<v8::String> azimutal_angle_prop = Nan::New("azimutal_angle").ToLocalChecked();
    v8::Local<v8::String> polar_angle_prop = Nan::New("polar_angle").ToLocalChecked();
    v8::Local<v8::String> radial_distance_mm_prop = Nan::New("radial_distance_mm").ToLocalChecked();
    v8::Local<v8::String> sound_speed_mmseg_prop = Nan::New("sound_speed_mmseg").ToLocalChecked();

    // set new property values
    float azimutal_angle = Nan::Get(configs, azimutal_angle_prop).ToLocalChecked()->NumberValue();
    float polar_angle = Nan::Get(configs, polar_angle_prop).ToLocalChecked()->NumberValue();
    float radial_distance_mm = Nan::Get(configs, radial_distance_mm_prop).ToLocalChecked()->NumberValue();
    float sound_speed_mmseg = Nan::Get(configs, sound_speed_mmseg_prop).ToLocalChecked()->NumberValue();

    microphone_array.CalculateDelays(azimutal_angle, polar_angle, radial_distance_mm, sound_speed_mmseg);  // These are default values
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
    microphone_array.SetGain(gain);
}

// - Get sampling rate
NAN_METHOD(getSamplingRate) {
    // if(microphone_array.GetSamplingRate()){
    if(true){
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

// - Print the gain & sampling rate
NAN_METHOD(showConfiguration){
    microphone_array.ShowConfiguration();
}

// - Return the number of microphone channels from MATRIX device
NAN_METHOD(channels){
    int channels = microphone_array.Channels();
    info.GetReturnValue().Set(Nan::New(channels));
}

// - Return the current number of samples
NAN_METHOD(numberOfSamples){
    int numberOfSamples = microphone_array.NumberOfSamples();
    info.GetReturnValue().Set(Nan::New(numberOfSamples));
}

// ** EXPORTED MICROPHONE ARRAY OBJECT ** //
NAN_METHOD(microphoneArray) {
    // Create object
    v8::Local<v8::Object> obj = Nan::New<v8::Object>();

    // microphone methods //
    Nan::Set(obj, Nan::New("setup").ToLocalChecked(),
    Nan::GetFunction(Nan::New<v8::FunctionTemplate>(setupMicArray)).ToLocalChecked());

    Nan::Set(obj, Nan::New("numberOfSamples").ToLocalChecked(),
    Nan::GetFunction(Nan::New<v8::FunctionTemplate>(numberOfSamples)).ToLocalChecked());

    Nan::Set(obj, Nan::New("channels").ToLocalChecked(),
    Nan::GetFunction(Nan::New<v8::FunctionTemplate>(channels)).ToLocalChecked());

    Nan::Set(obj, Nan::New("calculateDelays").ToLocalChecked(),
    Nan::GetFunction(Nan::New<v8::FunctionTemplate>(calculateDelays)).ToLocalChecked());

    Nan::Set(obj, Nan::New("showConfiguration").ToLocalChecked(),
    Nan::GetFunction(Nan::New<v8::FunctionTemplate>(showConfiguration)).ToLocalChecked());

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