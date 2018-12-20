#include <nan.h>
#include "../matrix.h"
#include "gpio.h"
#include "matrix_hal/gpio_control.h"
#include <v8.h>

// Create GPIOControl object
matrix_hal::GPIOControl gpio_control;

// - Read GPIO Pin state (digital)
// Paramters: int pin 0-15, int mode (0=INPUT or 1=OUTPUT)
NAN_METHOD(SetPinMode){
    // if argument 1 & 2 are not a number, throw error
    if (!info[0]->IsNumber() && !info[1]->IsNumber()) {Nan::ThrowTypeError("Argument 1 & 2 must be a number");return;}
    // get user arguments
    int pin = info[0]->NumberValue();
    int mode = info[1]->NumberValue();

    // if argument 2 is not 0 (INPUT) or 1 (OUTPUT), throw error
    if (mode != 1 && mode != 0){Nan::ThrowTypeError("Argument 2 must be 0 or 1");return;}
    // set pin to desired INPUT/OUTPUT mode
    gpio_control.SetMode(pin, mode);
}

// - Read GPIO Pin state (digital)
NAN_METHOD(ReadPinValue){
    // if first argument is not a number, throw error
    if (!info[0]->IsNumber()) {Nan::ThrowTypeError("Argument must be a number");return;}
    // get user arguments
    bool pinValue = gpio_control.GetGPIOValue(info[0]->NumberValue());
    // return desired pin's value
    info.GetReturnValue().Set(pinValue);
}

// - Set GPIO Pin state (digital)
// Paramters: int pin 0-15, int PinState 0-1
NAN_METHOD(SetPinValue){
    // if argument 1 & 2 are not a number, throw error
    if (!info[0]->IsNumber() && !info[1]->IsNumber()) {Nan::ThrowTypeError("Argument 1 & 2 must be a number");return;}
    // get user arguments
    int pin = info[0]->NumberValue();
    int digitalState = info[1]->NumberValue();

    // if argument 2 is not 0 (OFF) or 1 (ON), throw error
    if (digitalState != 1 && digitalState != 0){Nan::ThrowTypeError("Argument 2 must be 0 or 1");return;}
    // set pin to desired value
    gpio_control.SetGPIOValue(pin, digitalState);
}

// ** EXPORTED GPIO OBJECT ** //
NAN_METHOD(gpio) {
    // Set gpio to use MatrixIOBus bus
    gpio_control.Setup(&bus);

    // Create object
    v8::Local<v8::Object> obj = Nan::New<v8::Object>();

    // Set Object Properties //
    // GPIO digital read method
    Nan::Set(obj, Nan::New("readPinValue").ToLocalChecked(),
    Nan::GetFunction(Nan::New<v8::FunctionTemplate>(ReadPinValue)).ToLocalChecked());
    // GPIO digital set method
    Nan::Set(obj, Nan::New("setPinValue").ToLocalChecked(),
    Nan::GetFunction(Nan::New<v8::FunctionTemplate>(SetPinValue)).ToLocalChecked());
    // GPIO digital set mode method
    Nan::Set(obj, Nan::New("setPinMode").ToLocalChecked(),
    Nan::GetFunction(Nan::New<v8::FunctionTemplate>(SetPinMode)).ToLocalChecked());

    // Return object
    info.GetReturnValue().Set(obj);
}