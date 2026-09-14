#ifndef OPCOES_H
#define OPCOES_H

enum MenuPrincipal
{
  SAIR = 0,
  FILA = 1,
  PILHA = 2,
  LISTA = 3
};
enum MenuInicializacao
{
  INIT_VOLTAR = 0,
  INIT_MANUAL = 1,
  INIT_ARQ1 = 2,
  INIT_ARQ2 = 3,
  INIT_CIRCULO = 4
};
enum MenuAcao
{
  VOLTAR = 0,
  ADICIONAR = 1,
  REMOVER = 2
};
enum MenuLista
{
  VOLTAR_LISTA = 0,
  ADD_COMECO = 1,
  ADD_FIM = 2,
  ADD_INDICE = 3,
  ADD_CENTROIDE = 4,
  REM_COMECO = 5,
  REM_FIM = 6,
  REM_INDICE = 7,
  REM_PROXIMO = 8,
  REM_CENTROIDE = 9
};

#endif