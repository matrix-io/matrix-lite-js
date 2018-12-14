#include <nan.h>
#include "matrix.h"
#include <string>
#include <cmath>
#include <unistd.h>// System calls
#include <iostream>// Input/output streams and functions
#include "matrix_hal/everloop.h"
#include "matrix_hal/everloop_image.h"
#include "matrix_hal/matrixio_bus.h"

// using namespace Nan;
using namespace std;

// EXPORTED FUNCTION //
NAN_METHOD(Led){
  //led colors
  int red;
  int green;
  int blue;
  int white;

  // If param 1 is object
  if (!info[0]->IsObject()){
    // Throw error
    Nan::ThrowTypeError("argument must be an Object!");return;
  }

  v8::Local<v8::Object> jsonObj = info[0]->ToObject();
  v8::Local<v8::String> redProp = Nan::New("red").ToLocalChecked();
  v8::Local<v8::String> greenProp = Nan::New("green").ToLocalChecked();
  v8::Local<v8::String> blueProp = Nan::New("blue").ToLocalChecked();
  v8::Local<v8::String> whiteProp = Nan::New("white").ToLocalChecked();

  red = Nan::Get(jsonObj, redProp).ToLocalChecked()->NumberValue();
  green = Nan::Get(jsonObj, greenProp).ToLocalChecked()->NumberValue();
  blue = Nan::Get(jsonObj, blueProp).ToLocalChecked()->NumberValue();
  white = Nan::Get(jsonObj, whiteProp).ToLocalChecked()->NumberValue();

/// 11111
  // Create new object
  //  v8::Local<v8::Object> obj = info[0]->ToObject();
  //  v8::Local<v8::String> red = Nan::New<String>("red").ToLocalChecked();
  //  v8::Local<v8::String> green = Nan::New<String>("green").ToLocalChecked();
  //  v8::Local<v8::String> blue = Nan::New<String>("blue").ToLocalChecked();
  //  v8::Local<v8::String> white = Nan::New<String>("white").ToLocalChecked();

  // red = Nan::Get(obj, red).ToLocalChecked()->NumberValue();
  // green y1 = Nan::Get(obj, green).ToLocalChecked()->NumberValue();
  // blue y1 = Nan::Get(obj, blue).ToLocalChecked()->NumberValue();
  // white y1 = Nan::Get(obj, white).ToLocalChecked()->NumberValue();

///// 2222222
  // // Extract values
  // v8::Local<v8::Object> obj = info[0]->ToObject();
  // v8::Local<v8::Array> props = obj->GetPropertyNames();
  // // For each property
  // for (unsigned int j = 0; j < props->Length(); j++) {
  //   int value = *v8::Integer::New(obj->Get(props->Get(j))->ToString());

  //   if ( "red" == *v8::String::Utf8Value(props->Get(j)->ToString()) ){
  //     red = value;
  //   }
  //   else if ( "green" == *v8::String::Utf8Value(props->Get(j)->ToString()) ){
  //     green = value;
  //   }
  //   else if ( "blue" == *v8::String::Utf8Value(props->Get(j)->ToString()) ){
  //     blue = value;
  //   }
  //   else if ( "white" == *v8::String::Utf8Value(props->Get(j)->ToString()) ){
  //     white = value;
  //   }

  //   cout << value << endl;
    // printf("%s: %s",
    //   *v8::String::Utf8Value(props->Get(j)->ToString()),
    //   *v8::String::Utf8Value(obj->Get(props->Get(j))->ToString())
    // );
  // }








  ///////////////////////
  // MATRIX LED STUFF //
  // Create MatrixIOBus object for hardware communication
  matrix_hal::MatrixIOBus bus;
  // Initialize bus and exit program if error occurs
  if (!bus.Init()) {
    Nan::ThrowTypeError("Error Initializing Bus");
    return;
  }

  // Holds the number of LEDs on MATRIX device
  int ledCount = bus.MatrixLeds();
  // Create EverloopImage object, with size of ledCount
  matrix_hal::EverloopImage everloop_image(ledCount);
  // Create Everloop object
  matrix_hal::Everloop everloop;
  // Set everloop to use MatrixIOBus bus
  everloop.Setup(&bus);

  // For each led in everloop_image.leds, set led value
  for (matrix_hal::LedValue &led : everloop_image.leds) {
    led.red = red;
    led.green = green;
    led.blue = blue;
    led.white = white;
  }

  // Updates the Everloop on the MATRIX device
  everloop.Write(&everloop_image);

  // MATRIX LED STUFF //
 //////////////////////


  ////////////////
  // NAN STUFF //
  //info.GetReturnValue().Set(New<v8::Integer>(2));
  //info.GetReturnValue().Set(To<v8::Object>(info[0]).ToLocalChecked());
  //v8::Local<v8::Object> obj = info[0].internal_fields_;
  
  
  //cout << info[0] << endl;

  //int number = (int) info[0]->NumberValue();
};