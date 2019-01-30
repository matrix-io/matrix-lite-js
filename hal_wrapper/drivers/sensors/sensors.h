#ifndef SENSORS_SENSOR_H
#define SENSORS_SENSOR_H

#include <nan.h>

NAN_METHOD(pressure);
NAN_METHOD(humidity);
NAN_METHOD(uv);
NAN_METHOD(imu);

#endif