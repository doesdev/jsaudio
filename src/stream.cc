#include "stream.h"

static inline Persistent<v8::Function> & constructor() {
  static Persistent<v8::Function> JsPaStream::constructor;
  return JsPaStream::constructor;
}

JsPaStream::JsPaStream() {
}

JsPaStream::~JsPaStream() {
}

NAN_MODULE_INIT(JsPaStream::Init) {
  // Prepare constructor template
  LocalFunctionTemplate tpl = Nan::New<FunctionTemplate>(New);
  tpl->SetClassName(Nan::New("JsPaStream").ToLocalChecked());
  tpl->InstanceTemplate()->SetInternalFieldCount(1);

  constructor.Reset(Nan::GetFunction(tpl));
  Set(target, Nan::New("JsPaStream").ToLocalChecked(), Nan::GetFunction(tpl));
}

NAN_METHOD(JsPaStream::New) {
  if (info.IsConstructCall()) {
    // Invoked as constructor: `new JsPaStream(...)`
    JsPaStream* obj = new JsPaStream();
    obj->Wrap(info.This());
    info.GetReturnValue().Set(info.This());
  } else {
    // Invoked as plain function `JsPaStream(...)`, turn into construct call.
    const int argc = 1;
    LocalValue argv[argc] = { info[0] };
    LocalFunction cons =  Nan::New<Function>(constructor);
    info.GetReturnValue().Set(cons->NewInstance(argc, argv));
  }
}
