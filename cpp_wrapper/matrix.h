#ifndef MATRIX_H  // To make sure you don't declare the function more than once by including the header multiple times.
#define MATRIX_H 

NAN_METHOD(Led);

#endif





////////////
// Nan Note Book!!!

// - Reading user input //
// if (info[i]->IsBoolean()) {
//             printf("boolean = %s", info[i]->BooleanValue() ? "true" : "false");
//         } else if (info[i]->IsInt32()) {
//             printf("int32 = %ld", info[i]->IntegerValue());
//         } else if (info[i]->IsNumber()) {
//             printf("number = %f", info[i]->NumberValue());
//         } else if (info[i]->IsString()) {
//             printf("string = %s", *v8::String::Utf8Value(info[i]->ToString()));
//         } else if (info[i]->IsObject()) {
//             printf("[object]");
//             v8::Local<v8::Object> obj = info[i]->ToObject();
//             v8::Local<v8::Array> props = obj->GetPropertyNames();
//             for (unsigned int j = 0; j < props->Length(); j++) {
//                 printf("%s: %s",
//                        *v8::String::Utf8Value(props->Get(j)->ToString()),
//                        *v8::String::Utf8Value(obj->Get(props->Get(j))->ToString())
//                       );
//             }
//         } else if (info[i]->IsUndefined()) {
//             printf("[undefined]");
//         } else if (info[i]->IsNull()) {
//             printf("[null]");
//         }
//         i += 1;
//   }