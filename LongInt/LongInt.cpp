#include <iostream>
#include "LongInt.h"

using namespace std;

LongInt::LongInt()
{
  size = 0;
}


istream& operator>>(istream& is, LongInt &longInt)
{
  char c;
  
  while (cin.get(c) && c != '\n')
  {
    longInt.stackLi.push(c - '0');
    longInt.size++;
  }

  return is;
}

LongInt LongInt::operator+(LongInt &rhs)
{
  bool flag = false;
  int sum = 0, num, num1, num2, stackSize = 0;
  LongInt longSum;
  int maxLenght;

  if (size >= rhs.size)
    maxLenght= size;
  else
    maxLenght = rhs.size;

  while (!stackLi.isEmpty() || !rhs.stackLi.isEmpty())
  {
    if (stackLi.isEmpty())
    {
      num1 = 0;
    }
    else 
    {
      num1 = stackLi.topAndPop();
    }

    if (rhs.stackLi.isEmpty())
    {
      num2 = 0;
    }
    else
    {
      num2 = rhs.stackLi.topAndPop();
    } 
    
    num = num1 + num2;

    if(flag)
      num++;

    if (num > 9 && stackSize < maxLenght - 1)
    {
      longSum.stackLi.push((num % 10));
      flag = true;
    }
    else
    {
      longSum.stackLi.push(num);
      flag = false;
    }
    stackSize++;
  }
  return longSum;
}
/*
LongInt LongInt::operator+(LongInt &rhs)
{
  bool flag = false;
  int sum = 0, num;
  LongInt longSum;

  while (!stackLi.isEmpty() && !rhs.stackLi.isEmpty())
  {
    num = (stackLi.topAndPop() + rhs.stackLi.topAndPop());
    
    if (flag)
      num++;

    if (num > 9)
    {
      longSum.stackLi.push((num % 10));
//      cout << longSum.stackLi.top() << endl;
//      cout << sum << endl;
      flag = true;
    }
    else
    {
      longSum.stackLi.push(num);
//      cout << longSum.stackLi.top() << endl;
      //sum = num;
     /// cout << sum << endl;
      flag = false;
    }
    sum = 0;
  }

  while(!stackLi.isEmpty() || !rhs.stackLi.isEmpty())
  {
    if (stackLi.isEmpty())
    {
      if (flag)
      {
        longSum.stackLi.push(rhs.stackLi.topAndPop() + 1);
      }
      else
      {
        longSum.stackLi.push(rhs.stackLi.topAndPop());
      }
 //    cout << longSum.stackLi.top() << endl;
     // num = rhs.stackLi.topAndPop();
    }
    else
    {
      if (flag)
      {
        longSum.stackLi.push(stackLi.topAndPop() + 1);
      }
      else
      {
        longSum.stackLi.push(stackLi.topAndPop());
      }
    //  cout << longSum.stackLi.top() << endl;
      //num = stackLi.topAndPop();
    }
    flag = false;
      //cout << num << endl;
  }

  return longSum;
}
*/
ostream& operator<< (ostream& os, LongInt& longInt)
{
  while (!longInt.stackLi.isEmpty())
  {
    os << longInt.stackLi.topAndPop();
  }
  return os;
}

int LongInt::getSize()
{
  return size;
}

LongInt& LongInt::operator=(const LongInt &rhs)
{
  stackLi = rhs.stackLi;
  size = rhs.size;
  return *this;
}
