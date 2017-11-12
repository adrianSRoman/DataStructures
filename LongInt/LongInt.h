#ifndef LONGINT_H
#define LONGINT_H

#include <iostream>
#include "StackLi.h"

using namespace std;

class LongInt
{
  StackLi<int> stackLi;
  int size;
public:
  LongInt();
  int getSize();
  friend istream& operator>>(istream &is, LongInt &longInt);
  friend ostream& operator<<(ostream &os, LongInt &longInt);
  LongInt operator + (LongInt &rhs);
  LongInt& operator= (const LongInt &rhs);
};

#endif // LONGINT
