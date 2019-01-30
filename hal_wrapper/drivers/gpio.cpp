#include <nan.h>
#include "../matrix.h"
#include "gpio.h"
#include "matrix_hal/gpio_control.h"
#include <v8.h>

// Create GPIOControl object
matrix_hal::GPIOControl gpio_control;

////////////////////////
// PIN CONFIG METHODS//

// - Set GPIO Pin state (digital)
// Paramters: int pin (0-15), int mode (0=INPUT or 1=OUTPUT)
NAN_METHOD(SetMode){
    // if argument 1 & 2 are not a number, throw error
    if (!info[0]->IsNumber() && !info[1]->IsNumber()) {Nan::ThrowTypeError("Arguments 1 & 2 must be a number");return;}
    // get user arguments
    int pin = info[0]->NumberValue();
    int mode = info[1]->NumberValue();

    // if argument 2 is not 0 (INPUT) or 1 (OUTPUT), throw error
    if (mode != 1 && mode != 0){Nan::ThrowTypeError("Argument 2 must be 0 or 1");return;}
    // set pin to desired INPUT/OUTPUT mode
    gpio_control.SetMode(pin, mode);
}

// - Set GPIO Pin function
// Parameters: int pin (0-15), int function (0=DIGITAL or 1=PWM)
NAN_METHOD(SetFunction){
    // if argument 1 & 2 are not a number, throw error
    if (!info[0]->IsNumber() && !info[1]->IsNumber()) {Nan::ThrowTypeError("Arguments 1 & 2 must be a number");return;}

    // get user arguments
    int pin = info[0]->NumberValue();
    int pinFunction = info[1]->NumberValue();

    // if argument 2 is not 0 (DIGITAL) or 1 (PWM), throw error
    if (pinFunction != 1 && pinFunction != 0){Nan::ThrowTypeError("Argument 2 must be 0 or 1");return;}

    gpio_control.SetFunction(pin, pinFunction);
}

//////////////////////////
// PWM GET/SET METHODS //

// - Set GPIO Pin PWM
// Parameters: float frequency, float percentage, int pin (0-15)
NAN_METHOD(SetPWM){
    // for each required argument
    int args = 3;
    for(int i = 0; i < args; i++){
        // if argument is not a number, throw error
        if (!info[i]->IsNumber()){Nan::ThrowTypeError("Arguments 1 & 2 must be a number");return;}
    }  

    // get user arguments
    int frequency = info[0]->NumberValue();
    int percentage = info[1]->NumberValue();
    int pin = info[2]->NumberValue();

    // set PWM output
    gpio_control.SetPWM(frequency, percentage, pin);
}

// - Set A Servo Angle from PWM
// Parameters: float angle, float min_pulse_ms, int pin (0-15)
NAN_METHOD(SetServoAngle){
    // for each required argument
    int args = 3;
    for(int i = 0; i < args; i++){
        // if argument is not a number, throw error
        if (!info[i]->IsNumber()){Nan::ThrowTypeError("Arguments 1, 2, & 3 must be a number");return;}
    }

    // get user arguments
    int angle = info[0]->NumberValue();
    int min_pulse_ms = info[1]->NumberValue();
    int pin = info[2]->NumberValue();

    // set servo angle
    gpio_control.SetServoAngle(angle, min_pulse_ms, pin);
}

//////////////////////////////
// DIGITAL GET/SET METHODS //

// - Read GPIO Pin state (digital)
NAN_METHOD(ReadDigital){
    // if first argument is not a number, throw error
    if (!info[0]->IsNumber()) {Nan::ThrowTypeError("Argument must be a number");return;}
    // get user arguments
    bool pinValue = gpio_control.GetGPIOValue(info[0]->NumberValue());
    // return desired pin's value
    info.GetReturnValue().Set(pinValue);
}

// - Set GPIO Pin state (digital)
// Paramters: int pin (0-15), int PinState (0-1)
NAN_METHOD(SetDigital){
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

/////////////////////////////////
// ** EXPORTED GPIO OBJECT ** //
NAN_METHOD(gpio) {
    // Set gpio to use MatrixIOBus bus
    gpio_control.Setup(&bus);
    // Create object
    v8::Local<v8::Object> obj = Nan::New<v8::Object>();

    // Set Object Properties //
    // GPIO set mode method
    Nan::Set(obj, Nan::New("setMode").ToLocalChecked(),
    Nan::GetFunction(Nan::New<v8::FunctionTemplate>(SetMode)).ToLocalChecked());
    // GPIO set function method
    Nan::Set(obj, Nan::New("setFunction").ToLocalChecked(),
    Nan::GetFunction(Nan::New<v8::FunctionTemplate>(SetFunction)).ToLocalChecked());
    
    // Digital read method
    Nan::Set(obj, Nan::New("readDigital").ToLocalChecked(),
    Nan::GetFunction(Nan::New<v8::FunctionTemplate>(ReadDigital)).ToLocalChecked());
    // Digital set method
    Nan::Set(obj, Nan::New("setDigital").ToLocalChecked(),
    Nan::GetFunction(Nan::New<v8::FunctionTemplate>(SetDigital)).ToLocalChecked());

    // PWM set servo angle method
    Nan::Set(obj, Nan::New("setServoAngle").ToLocalChecked(),
    Nan::GetFunction(Nan::New<v8::FunctionTemplate>(SetServoAngle)).ToLocalChecked());
    // PWM set output method
    Nan::Set(obj, Nan::New("setPWM").ToLocalChecked(),
    Nan::GetFunction(Nan::New<v8::FunctionTemplate>(SetPWM)).ToLocalChecked());

    // Return object
    info.GetReturnValue().Set(obj);
}