#ifndef lista_h
#define lista_h

#include "ponto.h"
#include <vector>
#include <stdlib.h>
#include <stdio.h>
#include <iostream>
#include <math.h>

class lista
{
public:
  lista();
  lista(int x, int y);
  lista(int x, int y, float raio, int numero_pontos);
  lista(char *fileName);
  int tamanho();
  ~lista();

  void adicionarNoFim(int x, int y);
  void adicionarNoComeco(int x, int y);
  void adicionarNoIndice(int x, int y, int ind);
  bool existePonto(int x, int y);
  void mostrarPontos();

  void apagarPontoMaisProximo(int x, int y);
  void apagarIndice(int ind);
  void removerDoComeco();
  void removerDoFim();

  void adicionarCentroideMaisProximo(int x, int y);
  void apagarCentroideMaisProximo(int x, int y);

  void circle(const int &cx, const int &cy, const int &r, const int &np);

private:
  std::vector<ponto> list;
};
#endif