#include <nan.h>
#include "../../matrix.h"
#include "sensors.h"
#include "matrix_hal/humidity_sensor.h"
#include "matrix_hal/humidity_data.h"
#include <v8.h>

// Create humidity Data object
matrix_hal::HumidityData humidity_data;
// Create humidity Sensor object
matrix_hal::HumiditySensor humidity_sensor;

NAN_METHOD(ReadHumidity){
  // Overwrites humidity_data with new data from humidity sensor
  humidity_sensor.Read(&humidity_data);

  // Create Humidity data object //
  v8::Local<v8::Object> obj = Nan::New<v8::Object>();
  // Get/Set object properties
  Nan::Set(obj, Nan::New("humidity").ToLocalChecked(), Nan::New(humidity_data.humidity));// Humidity represented in %
  Nan::Set(obj, Nan::New("temperature").ToLocalChecked(), Nan::New(humidity_data.temperature));// Temperature represented in °C

  // Return object
  info.GetReturnValue().Set(obj);
}

// ** EXPORTED HUMIDITY OBJECT ** //
NAN_METHOD(humidity) {
    // Set humidity_sensor to use MatrixIOBus bus
    humidity_sensor.Setup(&bus);

    // Create Humidity object
    v8::Local<v8::Object> obj = Nan::New<v8::Object>();

    // Set Object Properties //
    // Read humidity method
    Nan::Set(obj, Nan::New("read").ToLocalChecked(),
    Nan::GetFunction(Nan::New<v8::FunctionTemplate>(ReadHumidity)).ToLocalChecked());

    // Return object
    info.GetReturnValue().Set(obj);
}