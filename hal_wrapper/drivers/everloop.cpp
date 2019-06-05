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

// - Set LED states
// Paramters: Array of size ledCount with objects that have RGBW values.
NAN_METHOD(Set){
    // if array argument is not given, throw error
    if (!info[0]->IsArray()) {Nan::ThrowTypeError("Argument must be an array");return;}
    
    // grab array of LEDs objects
    v8::Local<v8::Array> leds = v8::Local<v8::Array>::Cast(info[0]);

    // read RGBW properties of each LED
    int red, green, blue, white;
    for (uint i = 0; i < leds->Length(); i++) {
        // grab LED object properties
        v8::Local<v8::Value> readLed = Nan::Get(leds, i).ToLocalChecked();
        v8::Local<v8::Object> newLed = Nan::To<v8::Object>(readLed).ToLocalChecked();

        v8::Local<v8::String> redProp = Nan::New("red").ToLocalChecked();
        v8::Local<v8::String> greenProp = Nan::New("green").ToLocalChecked();
        v8::Local<v8::String> blueProp = Nan::New("blue").ToLocalChecked();
        v8::Local<v8::String> whiteProp = Nan::New("white").ToLocalChecked();

        // grab RGBW values
        red   = Nan::To<int>(Nan::Get(newLed, redProp).ToLocalChecked()).FromJust();
        green = Nan::To<int>(Nan::Get(newLed, greenProp).ToLocalChecked()).FromJust();
        blue  = Nan::To<int>(Nan::Get(newLed, blueProp).ToLocalChecked()).FromJust();
        white = Nan::To<int>(Nan::Get(newLed, whiteProp).ToLocalChecked()).FromJust();

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
    // Set everloop to use MatrixIOBus bus
    everloop.Setup(&bus);

    // Create object
    v8::Local<v8::Object> obj = Nan::New<v8::Object>();

    // Set Object Properties //
    // # of MATRIX LEDs
    Nan::Set(obj, Nan::New("length").ToLocalChecked(), Nan::New(ledCount));

    // LED set method
    Nan::Set(obj, Nan::New("set").ToLocalChecked(),
    Nan::GetFunction(Nan::New<v8::FunctionTemplate>(Set)).ToLocalChecked());

    // Return object
    info.GetReturnValue().Set(obj);
}