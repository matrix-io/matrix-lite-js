#include <nan.h>
#include "../../matrix.h"
#include "sensors.h"
#include "matrix_hal/uv_sensor.h"
#include "matrix_hal/uv_data.h"
#include <v8.h>

// Create UV Data object
matrix_hal::UVData uv_data;
// Create UV Sensor object
matrix_hal::UVSensor uv_sensor;

NAN_METHOD(ReadUV){
  // Overwrites uv_data with new data from uv sensor
  uv_sensor.Read(&uv_data);

  // Create UV data object //
  v8::Local<v8::Object> obj = Nan::New<v8::Object>();
  // Get/Set object properties
  Nan::Set(obj, Nan::New("uv").ToLocalChecked(), Nan::New(uv_data.uv));// UV represented in UV Index

  // Return object
  info.GetReturnValue().Set(obj);
}

// ** EXPORTED UV OBJECT ** //
NAN_METHOD(uv) {
    // Set uv_sensor to use MatrixIOBus bus
    uv_sensor.Setup(&bus);

    // Create UV object
    v8::Local<v8::Object> obj = Nan::New<v8::Object>();

    // Set Object Properties //
    // Read UV method
    Nan::Set(obj, Nan::New("read").ToLocalChecked(),
    Nan::GetFunction(Nan::New<v8::FunctionTemplate>(ReadUV)).ToLocalChecked());

    // Return object
    info.GetReturnValue().Set(obj);
}