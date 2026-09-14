#include "ponto.h"

ponto::ponto()
{
  varx = 0;
  vary = 0;
}

ponto::ponto(int x, int y)
{
  setxy(x, y);
}

ponto::~ponto()
{
}

void ponto::setxy(int x, int y)
{
  varx = x;
  vary = y;
}

int ponto::x()
{
  return varx;
}

int ponto::y()
{
  return vary;
}