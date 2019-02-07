#include <nan.h>
#include "../matrix.h"
#include "info.h"
#include <v8.h>

// - Detect if using bus or kernel modules
NAN_METHOD(isDirectBus){
  if(!bus.IsDirectBus())
    info.GetReturnValue().Set(false);
  else
    info.GetReturnValue().Set(true);
}

///////////////////////////////////////
// ** EXPORTED DEVICE INFO OBJECT ** //
NAN_METHOD(info) {
    // Create object
    v8::Local<v8::Object> obj = Nan::New<v8::Object>();

    // Set Object Properties //
    Nan::Set(obj, Nan::New("isDirectBus").ToLocalChecked(),
    Nan::GetFunction(Nan::New<v8::FunctionTemplate>(isDirectBus)).ToLocalChecked());

    // Return object
    info.GetReturnValue().Set(obj);
}