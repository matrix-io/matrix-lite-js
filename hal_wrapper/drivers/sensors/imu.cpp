#include <nan.h>
#include "../../matrix.h"
#include "sensors.h"
#include "matrix_hal/imu_sensor.h"
#include "matrix_hal/imu_data.h"
#include <v8.h>

// Create IMU Data object
matrix_hal::IMUData imu_data;
// Create IMU Sensor object
matrix_hal::IMUSensor imu_sensor;

NAN_METHOD(ReadIMU){
  // Overwrites imu_data with new data from IMU sensor
  imu_sensor.Read(&imu_data);

  // Create IMU data object //
  v8::Local<v8::Object> obj = Nan::New<v8::Object>();
  // Accelerometer data
  Nan::Set(obj, Nan::New("accel_x").ToLocalChecked(), Nan::New(imu_data.accel_x));
  Nan::Set(obj, Nan::New("accel_y").ToLocalChecked(), Nan::New(imu_data.accel_y));
  Nan::Set(obj, Nan::New("accel_z").ToLocalChecked(), Nan::New(imu_data.accel_z));
  // Gyroscope data
  Nan::Set(obj, Nan::New("gyro_x").ToLocalChecked(), Nan::New(imu_data.gyro_x));
  Nan::Set(obj, Nan::New("gyro_y").ToLocalChecked(), Nan::New(imu_data.gyro_y));
  Nan::Set(obj, Nan::New("gyro_z").ToLocalChecked(), Nan::New(imu_data.gyro_z));
  // Yaw, Pitch & Roll data
  Nan::Set(obj, Nan::New("yaw").ToLocalChecked(), Nan::New(imu_data.yaw));
  Nan::Set(obj, Nan::New("pitch").ToLocalChecked(), Nan::New(imu_data.pitch));
  Nan::Set(obj, Nan::New("roll").ToLocalChecked(), Nan::New(imu_data.roll));
  // Magnetometer Output
  Nan::Set(obj, Nan::New("mag_x").ToLocalChecked(), Nan::New(imu_data.mag_x));
  Nan::Set(obj, Nan::New("mag_y").ToLocalChecked(), Nan::New(imu_data.mag_y));
  Nan::Set(obj, Nan::New("mag_z").ToLocalChecked(), Nan::New(imu_data.mag_z));

  // Return object
  info.GetReturnValue().Set(obj);
}

// ** EXPORTED IMU OBJECT ** //
NAN_METHOD(imu) {
    // Set imu_sensor to use MatrixIOBus bus
    imu_sensor.Setup(&bus);

    // Create IMU object
    v8::Local<v8::Object> obj = Nan::New<v8::Object>();

    // Set Object Properties //
    // Read IMU method
    Nan::Set(obj, Nan::New("read").ToLocalChecked(),
    Nan::GetFunction(Nan::New<v8::FunctionTemplate>(ReadIMU)).ToLocalChecked());

    // Return object
    info.GetReturnValue().Set(obj);
}