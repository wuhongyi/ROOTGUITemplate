// rqobject.cc --- 
// 
// Description: 
// Author: Hongyi Wu(吴鸿毅)
// Email: wuhongyi@qq.com 
// Created: 一 11月 14 20:04:30 2016 (+0800)
// Last-Updated: 一 11月 14 20:05:52 2016 (+0800)
//           By: Hongyi Wu(吴鸿毅)
//     Update #: 1
// URL: http://wuhongyi.cn 


// Macro is used to delegate TQObject methods to other classes

#include "RQ_OBJECT.h"

class A {
  RQ_OBJECT("A")
  
private:
  Int_t fValue;
  
public:
  A() : fValue(0) { }
  ~A() { }

  void  SetValue(Int_t value);
  void  PrintValue() const { printf("value=%d\n", fValue); }
  Int_t GetValue() const { return fValue; }
};

void A::SetValue(Int_t value)
{
  // Sets new value

  // to prevent infinite looping in the case
  // of cyclic connections
  if (value != fValue) {
    fValue = value;
    Emit("SetValue(Int_t)", fValue);
  }
}

// Load this class into root session and try the folllowing:
//
// a = new A();
// b = new A();
//
// Here is one way to connect two of these objects together:
//
// a->Connect("SetValue(Int_t)", "A", b, "SetValue(Int_t)");
//
// Calling a->SetValue(79) will make a emit a signal, which b
// will receive, i.e. b->SetValue(79) is invoked. b will in
// turn emit the same signal, which nobody receives, since no
// slot has been connected to it, so it disappears into hyperspace.


// 
// rqobject.cc ends here
