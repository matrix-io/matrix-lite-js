#include <nan.h>
#include "everloop.h"
#include "../matrix.h"
#include "matrix_hal/everloop.h"
#include "matrix_hal/everloop_image.h"

#include <v8.h>

// - Number of LEDs on MATRIX device
int ledCount = bus.MatrixLeds();

// create empty everloop image with size of ledCount
matrix_hal::EverloopImage everloop_image(ledCount);
// create Everloop object
matrix_hal::Everloop everloop;

// - Set LED states (WORK IN PROGRESS)
NAN_METHOD(Set){
    // if array argument is not given, throw error
    if (!info[0]->IsArray()) {Nan::ThrowTypeError("Argument is not an array");return;}
    
    // grab array of LED RGBW states
    v8::Local<v8::Array> leds = v8::Local<v8::Array>::Cast(info[0]);
    // if LED array != LEDs on MATRIX device, throw error
    if (leds->Length() != ledCount) {Nan::ThrowTypeError("Argument array size != LEDs on MATRIX device");return;}

    // MATRIX EVERLOOP LOGIC //
    // for each LED
    int red, green, blue, white;
    for (int i = 0; i < leds->Length(); i++) {
        // grab LED object properties
        v8::Local<v8::Object> newLed = leds->Get(i)->ToObject();
        v8::Local<v8::String> redProp = Nan::New("red").ToLocalChecked();
        v8::Local<v8::String> greenProp = Nan::New("green").ToLocalChecked();
        v8::Local<v8::String> blueProp = Nan::New("blue").ToLocalChecked();
        v8::Local<v8::String> whiteProp = Nan::New("white").ToLocalChecked();
        // grab RGBW values
        red = Nan::Get(newLed, redProp).ToLocalChecked()->NumberValue();
        green = Nan::Get(newLed, greenProp).ToLocalChecked()->NumberValue();
        blue = Nan::Get(newLed, blueProp).ToLocalChecked()->NumberValue();
        white = Nan::Get(newLed, whiteProp).ToLocalChecked()->NumberValue();
        // set new LED state
        everloop_image.leds[i].red = red;
        everloop_image.leds[i].green = green;
        everloop_image.leds[i].blue = blue;
        everloop_image.leds[i].white = white;
    }

    // Updates the Everloop on the MATRIX device
    everloop.Write(&everloop_image);
}

// ** EXPORTED LED OBJECT ** //
NAN_METHOD(led) {
    // set everloop to use MatrixIOBus bus
    everloop.Setup(&bus);

    // Create object
    v8::Local<v8::Object> obj = Nan::New<v8::Object>();

    // Set Object parameters //
    // # of MATRIX LEDs
    Nan::Set(obj, Nan::New("length").ToLocalChecked(), Nan::New(ledCount));

    // LED set method
    Nan::Set(obj, Nan::New("set").ToLocalChecked(),
    Nan::GetFunction(Nan::New<v8::FunctionTemplate>(Set)).ToLocalChecked());

    // Return object
    info.GetReturnValue().Set(obj);
}