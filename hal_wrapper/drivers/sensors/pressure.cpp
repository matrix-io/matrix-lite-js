#include <nan.h>
#include "../../matrix.h"
#include "sensors.h"
#include "matrix_hal/pressure_sensor.h"
#include "matrix_hal/pressure_data.h"
#include <v8.h>

// Create pressure Data object
matrix_hal::PressureData pressure_data;
// Create pressure Sensor object
matrix_hal::PressureSensor pressure_sensor;

NAN_METHOD(ReadPressure){
  // Overwrites pressure_data with new data from pressure sensor
  pressure_sensor.Read(&pressure_data);

  // Create Pressure data object //
  v8::Local<v8::Object> obj = Nan::New<v8::Object>();
  // Get/Set object properties 
  Nan::Set(obj, Nan::New("altitude").ToLocalChecked(), Nan::New(pressure_data.altitude));// Altitude represented in meters
  Nan::Set(obj, Nan::New("pressure").ToLocalChecked(), Nan::New(pressure_data.pressure));// Pressure represented in kPa
  Nan::Set(obj, Nan::New("temperature").ToLocalChecked(), Nan::New(pressure_data.temperature));// Temperature represented in °C

  // Return object
  info.GetReturnValue().Set(obj);
}

// ** EXPORTED PRESSURE OBJECT ** //
NAN_METHOD(pressure) {
    // Set pressure_sensor to use MatrixIOBus bus
    pressure_sensor.Setup(&bus);

    // Create Pressure object
    v8::Local<v8::Object> obj = Nan::New<v8::Object>();

    // Set Object Properties //
    // Read pressure method
    Nan::Set(obj, Nan::New("read").ToLocalChecked(),
    Nan::GetFunction(Nan::New<v8::FunctionTemplate>(ReadPressure)).ToLocalChecked());

    // Return object
    info.GetReturnValue().Set(obj);
}