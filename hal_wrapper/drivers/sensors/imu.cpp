#include <nan.h>
#include "../../matrix.h"
#include "imu.h"
#include "matrix_hal/imu_sensor.h"
#include "matrix_hal/imu_data.h"
#include <v8.h>

// Create IMUData object
matrix_hal::IMUData imu_data;
// Create IMUSensor object
matrix_hal::IMUSensor imu_sensor;

// ** EXPORTED LED OBJECT ** //
NAN_METHOD(imu) {
    // Set imu_sensor to use MatrixIOBus bus
    imu_sensor.Setup(&bus);

    // Overwrites imu_data with new data from IMU sensor
    imu_sensor.Read(&imu_data);

    // Create IMU object
    v8::Local<v8::Object> obj = Nan::New<v8::Object>();

    // Set Object parameters //
    // # of MATRIX LEDs
    Nan::Set(obj, Nan::New("accel_x").ToLocalChecked(), Nan::New(imu_data.accel_x));

    // Return object
    info.GetReturnValue().Set(obj);
}