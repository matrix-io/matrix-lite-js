#include <nan.h>
#include "../matrix.h"
#include "info.h"
#include <v8.h>

// Detect if using bus or kernel modules
bool isDirectBus = bus.IsDirectBus() ? true : false;

// Get the name of the MATRIX device being used
std::string getDeviceType() {
  if (bus.MatrixName() == matrix_hal::kMatrixCreator)
    return "MATRIX Creator";
  else if (bus.MatrixName() == matrix_hal::kMatrixVoice)
    return "MATRIX Voice";
  else
    return "DEVICE NOT RECOGNIZED";
}

std::string deviceType = getDeviceType();

///////////////////////////////////////
// ** EXPORTED DEVICE INFO OBJECT ** //
NAN_METHOD(info) {
    // Create object
    v8::Local<v8::Object> obj = Nan::New<v8::Object>();

    // Set Object Properties //
    Nan::Set(obj, Nan::New("isDirectBus").ToLocalChecked(), Nan::New(isDirectBus));
    Nan::Set(obj, Nan::New("deviceType").ToLocalChecked(), Nan::New(deviceType).ToLocalChecked());

    // Return object
    info.GetReturnValue().Set(obj);
}
