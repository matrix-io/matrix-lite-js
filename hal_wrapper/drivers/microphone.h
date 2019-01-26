#ifndef MICROPHONE_H  // Prevent duplicate declarations
#define MICROPHONE_H

#include <nan.h>
#include "matrix_hal/microphone_array.h"

NAN_METHOD(microphoneArray);
NAN_METHOD(microphoneCore);

void getMicrophoneArray();

#endif