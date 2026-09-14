#ifndef ponto_h
#define ponto_h

#include <iostream>
#include <stdio.h>
#include <stdlib.h>
using namespace std;

class ponto
{
public:
  ponto();
  ponto(int x, int y);
  ~ponto();
  void setxy(int x, int y);
  int x();
  int y();

private:
  int varx;
  int vary;
};

#endif