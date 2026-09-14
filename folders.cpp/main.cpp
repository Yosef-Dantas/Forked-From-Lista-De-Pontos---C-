#include <iostream>
#include <limits>
#define NOMINMAX
#include <windows.h>

using namespace std;

#include "lista.h"
#include "mensagens.h"
#include "opcoes.h"

extern int g_modo_interativo;

const int MODO_INTERATIVO = 10;

int main()
{
  SetConsoleOutputCP(CP_UTF8);
  SetConsoleCP(CP_UTF8);

  int opc;
  int erros = 0;
  lista minhaEstrutura;

  do
  {
    cout << CABECALHO_PRINCIPAL;
    cout << PROMPT_ESCOLHA;
    cin >> opc;

    if (cin.fail())
    {
      cin.clear();
      cin.ignore(numeric_limits<streamsize>::max(), '\n');
      opc = -1;
    }

    if (opc < 0 || opc > 3)
    {
      erros++;
      if (erros >= 3)
      {
        cout << MSG_ERRO_LIMITE;
        cout << MSG_DESPEDIDA;
        return 0;
      }
    }
    else
    {
      erros = 0;
    }

    switch (opc)
    {
    case FILA:
    {
      int opc_init;
      int erros_init = 0;
      cout << CABECALHO_FILA;

      do
      {
        cout << MENU_INICIALIZACAO;
        cout << PROMPT_ESCOLHA;
        cin >> opc_init;

        if (cin.fail())
        {
          cin.clear();
          cin.ignore(numeric_limits<streamsize>::max(), '\n');
          opc_init = -1;
        }

        if (opc_init < INIT_VOLTAR || opc_init > INIT_CIRCULO)
        {
          erros_init++;
          if (erros_init >= 3)
          {
            cout << MSG_ERRO_LIMITE;
            cout << MSG_DESPEDIDA;
            return 0;
          }
        }
        else
        {
          erros_init = 0;
        }

        switch (opc_init)
        {
        case INIT_VOLTAR:
          break;
        case INIT_MANUAL:
          minhaEstrutura = lista();
          break;
        case INIT_ARQ1:
          minhaEstrutura = lista((char *)"folders.txt/pontos1.txt");
          cout << MSG_SUCESSO_ARQ;
          break;
        case INIT_ARQ2:
          minhaEstrutura = lista((char *)"folders.txt/pontos2.txt");
          cout << MSG_SUCESSO_ARQ;
          break;
        case INIT_CIRCULO:
        {
          int cx, cy, np;
          float r;
          int erros_circulo = 0;
          bool sucesso_circulo = false;

          do
          {
            cout << PROMPT_CIRCULO_CX;
            cin >> cx;
            cout << PROMPT_CIRCULO_CY;
            cin >> cy;
            cout << PROMPT_CIRCULO_R;
            cin >> r;

            if (cin.fail())
            {
              cin.clear();
              cin.ignore(numeric_limits<streamsize>::max(), '\n');
              cout << MSG_ERRO_TIPO;
              erros_circulo++;
            }
            else if (r <= 0)
            {
              cout << MSG_ERRO_CIRCULO_R;
              erros_circulo++;
            }
            else
            {
              cout << PROMPT_CIRCULO_NP;
              cin >> np;

              if (cin.fail())
              {
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                cout << MSG_ERRO_TIPO;
                erros_circulo++;
              }
              else if (np <= 0)
              {
                cout << MSG_ERRO_CIRCULO_NP;
                erros_circulo++;
              }
              else
              {
                minhaEstrutura = lista(cx, cy, r, np);
                cout << MSG_SUCESSO_CIRCULO;
                sucesso_circulo = true;
              }
            }

            if (erros_circulo >= 3)
            {
              cout << MSG_ERRO_LIMITE;
              cout << MSG_DESPEDIDA;
              return 0;
            }
          } while (!sucesso_circulo);

          break;
        }
        default:
          cout << MSG_OPCAO_INVALIDA;
          break;
        }
      } while (opc_init < INIT_VOLTAR || opc_init > INIT_CIRCULO);

      if (opc_init != INIT_VOLTAR)
      {
        int opcfila;
        int erros_acao = 0;
        do
        {
          minhaEstrutura.mostrarPontos();
          cout << MENU_ACOES;
          cout << PROMPT_ESCOLHA;
          cin >> opcfila;

          if (cin.fail())
          {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            opcfila = -1;
          }

          if (opcfila < VOLTAR || opcfila > REMOVER)
          {
            erros_acao++;
            if (erros_acao >= 3)
            {
              cout << MSG_ERRO_LIMITE;
              cout << MSG_DESPEDIDA;
              return 0;
            }
          }
          else
          {
            erros_acao = 0;
          }

          switch (opcfila)
          {
          case ADICIONAR:
          {
            int x, y;
            cout << PROMPT_ADD_COORD_X;
            cin >> x;
            cout << PROMPT_ADD_COORD_Y;
            cin >> y;

            if (cin.fail())
            {
              cin.clear();
              cin.ignore(numeric_limits<streamsize>::max(), '\n');
              cout << MSG_ERRO_TIPO;
            }
            else if (minhaEstrutura.existePonto(x, y))
            {
              cout << MSG_ERRO_DUPLICADO;
            }
            else
            {
              minhaEstrutura.adicionarNoFim(x, y);
              cout << MSG_SUCESSO_ADD;
            }
          }
          break;

          case REMOVER:
          {
            minhaEstrutura.removerDoComeco();
          }
          break;

          case VOLTAR:
            break;

          default:
            cout << MSG_OPCAO_INVALIDA;
            break;
          }
        } while (opcfila != VOLTAR);
      }
    }
    break;

    case PILHA:
    {
      int opc_init;
      int erros_init = 0;
      cout << CABECALHO_PILHA;

      do
      {
        cout << MENU_INICIALIZACAO;
        cout << PROMPT_ESCOLHA;
        cin >> opc_init;

        if (cin.fail())
        {
          cin.clear();
          cin.ignore(numeric_limits<streamsize>::max(), '\n');
          opc_init = -1;
        }

        if (opc_init < INIT_VOLTAR || opc_init > INIT_CIRCULO)
        {
          erros_init++;
          if (erros_init >= 3)
          {
            cout << MSG_ERRO_LIMITE;
            cout << MSG_DESPEDIDA;
            return 0;
          }
        }
        else
        {
          erros_init = 0;
        }

        switch (opc_init)
        {
        case INIT_VOLTAR:
          break;
        case INIT_MANUAL:
          minhaEstrutura = lista();
          break;
        case INIT_ARQ1:
          minhaEstrutura = lista((char *)"folders.txt/pontos1.txt");
          cout << MSG_SUCESSO_ARQ;
          break;
        case INIT_ARQ2:
          minhaEstrutura = lista((char *)"folders.txt/pontos2.txt");
          cout << MSG_SUCESSO_ARQ;
          break;
        case INIT_CIRCULO:
        {
          int cx, cy, np;
          float r;
          int erros_circulo = 0;
          bool sucesso_circulo = false;

          do
          {
            cout << PROMPT_CIRCULO_CX;
            cin >> cx;
            cout << PROMPT_CIRCULO_CY;
            cin >> cy;
            cout << PROMPT_CIRCULO_R;
            cin >> r;

            if (cin.fail())
            {
              cin.clear();
              cin.ignore(numeric_limits<streamsize>::max(), '\n');
              cout << MSG_ERRO_TIPO;
              erros_circulo++;
            }
            else if (r <= 0)
            {
              cout << MSG_ERRO_CIRCULO_R;
              erros_circulo++;
            }
            else
            {
              cout << PROMPT_CIRCULO_NP;
              cin >> np;

              if (cin.fail())
              {
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                cout << MSG_ERRO_TIPO;
                erros_circulo++;
              }
              else if (np <= 0)
              {
                cout << MSG_ERRO_CIRCULO_NP;
                erros_circulo++;
              }
              else
              {
                minhaEstrutura = lista(cx, cy, r, np);
                cout << MSG_SUCESSO_CIRCULO;
                sucesso_circulo = true;
              }
            }

            if (erros_circulo >= 3)
            {
              cout << MSG_ERRO_LIMITE;
              cout << MSG_DESPEDIDA;
              return 0;
            }
          } while (!sucesso_circulo);

          break;
        }
        default:
          cout << MSG_OPCAO_INVALIDA;
          break;
        }
      } while (opc_init < INIT_VOLTAR || opc_init > INIT_CIRCULO);

      if (opc_init != INIT_VOLTAR)
      {
        int opcpilha;
        int erros_acao = 0;
        do
        {
          minhaEstrutura.mostrarPontos();
          cout << MENU_ACOES;
          cout << PROMPT_ESCOLHA;
          cin >> opcpilha;

          if (cin.fail())
          {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            opcpilha = -1;
          }

          if (opcpilha < VOLTAR || opcpilha > REMOVER)
          {
            erros_acao++;
            if (erros_acao >= 3)
            {
              cout << MSG_ERRO_LIMITE;
              cout << MSG_DESPEDIDA;
              return 0;
            }
          }
          else
          {
            erros_acao = 0;
          }

          switch (opcpilha)
          {
          case ADICIONAR:
          {
            int x, y;
            cout << PROMPT_ADD_COORD_X;
            cin >> x;
            cout << PROMPT_ADD_COORD_Y;
            cin >> y;

            if (cin.fail())
            {
              cin.clear();
              cin.ignore(numeric_limits<streamsize>::max(), '\n');
              cout << MSG_ERRO_TIPO;
            }
            else if (minhaEstrutura.existePonto(x, y))
            {
              cout << MSG_ERRO_DUPLICADO;
            }
            else
            {
              minhaEstrutura.adicionarNoFim(x, y);
              cout << MSG_SUCESSO_ADD;
            }
          }
          break;

          case REMOVER:
          {
            minhaEstrutura.removerDoFim();
          }
          break;

          case VOLTAR:
            break;

          default:
            cout << MSG_OPCAO_INVALIDA;
            break;
          }
        } while (opcpilha != VOLTAR);
      }
    }
    break;

    case LISTA:
    {
      int opc_init;
      int erros_init = 0;
      cout << CABECALHO_LISTA;

      do
      {
        cout << MENU_INICIALIZACAO;
        cout << PROMPT_ESCOLHA;
        cin >> opc_init;

        if (cin.fail())
        {
          cin.clear();
          cin.ignore(numeric_limits<streamsize>::max(), '\n');
          opc_init = -1;
        }

        if (opc_init < INIT_VOLTAR || opc_init > INIT_CIRCULO)
        {
          erros_init++;
          if (erros_init >= 3)
          {
            cout << MSG_ERRO_LIMITE;
            cout << MSG_DESPEDIDA;
            return 0;
          }
        }
        else
        {
          erros_init = 0;
        }

        switch (opc_init)
        {
        case INIT_VOLTAR:
          break;
        case INIT_MANUAL:
          minhaEstrutura = lista();
          break;
        case INIT_ARQ1:
          minhaEstrutura = lista((char *)"folders.txt/pontos1.txt");
          cout << MSG_SUCESSO_ARQ;
          break;
        case INIT_ARQ2:
          minhaEstrutura = lista((char *)"folders.txt/pontos2.txt");
          cout << MSG_SUCESSO_ARQ;
          break;
        case INIT_CIRCULO:
        {
          int cx, cy, np;
          float r;
          int erros_circulo = 0;
          bool sucesso_circulo = false;

          do
          {
            cout << PROMPT_CIRCULO_CX;
            cin >> cx;
            cout << PROMPT_CIRCULO_CY;
            cin >> cy;
            cout << PROMPT_CIRCULO_R;
            cin >> r;

            if (cin.fail())
            {
              cin.clear();
              cin.ignore(numeric_limits<streamsize>::max(), '\n');
              cout << MSG_ERRO_TIPO;
              erros_circulo++;
            }
            else if (r <= 0)
            {
              cout << MSG_ERRO_CIRCULO_R;
              erros_circulo++;
            }
            else
            {
              cout << PROMPT_CIRCULO_NP;
              cin >> np;

              if (cin.fail())
              {
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                cout << MSG_ERRO_TIPO;
                erros_circulo++;
              }
              else if (np <= 0)
              {
                cout << MSG_ERRO_CIRCULO_NP;
                erros_circulo++;
              }
              else
              {
                minhaEstrutura = lista(cx, cy, r, np);
                cout << MSG_SUCESSO_CIRCULO;
                sucesso_circulo = true;
              }
            }

            if (erros_circulo >= 3)
            {
              cout << MSG_ERRO_LIMITE;
              cout << MSG_DESPEDIDA;
              return 0;
            }
          } while (!sucesso_circulo);

          break;
        }
        default:
          cout << MSG_OPCAO_INVALIDA;
          break;
        }
      } while (opc_init < INIT_VOLTAR || opc_init > INIT_CIRCULO);

      if (opc_init != INIT_VOLTAR)
      {
        int opclista;
        int erros_lista = 0;
        do
        {
          minhaEstrutura.mostrarPontos();
          cout << MENU_ACOES_LISTA;
          cout << PROMPT_ESCOLHA;
          cin >> opclista;

          if (cin.fail())
          {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            opclista = -1;
          }

          if (opclista < VOLTAR_LISTA || opclista > 10)
          {
            erros_lista++;
            if (erros_lista >= 3)
            {
              cout << MSG_ERRO_LIMITE;
              cout << MSG_DESPEDIDA;
              return 0;
            }
          }
          else
          {
            erros_lista = 0;
          }

          switch (opclista)
          {
          case ADD_COMECO:
          {
            int x, y;
            cout << PROMPT_ADD_COORD_X;
            cin >> x;
            cout << PROMPT_ADD_COORD_Y;
            cin >> y;
            if (cin.fail())
            {
              cin.clear();
              cin.ignore(numeric_limits<streamsize>::max(), '\n');
              cout << MSG_ERRO_TIPO;
            }
            else if (minhaEstrutura.existePonto(x, y))
            {
              cout << MSG_ERRO_DUPLICADO;
            }
            else
            {
              minhaEstrutura.adicionarNoComeco(x, y);
              cout << MSG_SUCESSO_ADD;
            }
          }
          break;

          case ADD_FIM:
          {
            int x, y;
            cout << PROMPT_ADD_COORD_X;
            cin >> x;
            cout << PROMPT_ADD_COORD_Y;
            cin >> y;
            if (cin.fail())
            {
              cin.clear();
              cin.ignore(numeric_limits<streamsize>::max(), '\n');
              cout << MSG_ERRO_TIPO;
            }
            else if (minhaEstrutura.existePonto(x, y))
            {
              cout << MSG_ERRO_DUPLICADO;
            }
            else
            {
              minhaEstrutura.adicionarNoFim(x, y);
              cout << MSG_SUCESSO_ADD;
            }
          }
          break;

          case ADD_INDICE:
          {
            int x, y, ind;
            cout << PROMPT_ADD_COORD_X;
            cin >> x;
            cout << PROMPT_ADD_COORD_Y;
            cin >> y;
            cout << PROMPT_INDICE;
            cin >> ind;
            if (cin.fail())
            {
              cin.clear();
              cin.ignore(numeric_limits<streamsize>::max(), '\n');
              cout << MSG_ERRO_TIPO;
            }
            else if (minhaEstrutura.existePonto(x, y))
            {
              cout << MSG_ERRO_DUPLICADO;
            }
            else if (ind < 0 || ind > minhaEstrutura.tamanho())
            {
              cout << MSG_ERRO_INDICE;
            }
            else
            {
              minhaEstrutura.adicionarNoIndice(x, y, ind);
              cout << MSG_SUCESSO_ADD;
            }
          }
          break;

          case ADD_CENTROIDE:
          {
            int x, y;
            cout << PROMPT_REF_COORD_X;
            cin >> x;
            cout << PROMPT_REF_COORD_Y;
            cin >> y;
            if (cin.fail())
            {
              cin.clear();
              cin.ignore(numeric_limits<streamsize>::max(), '\n');
              cout << MSG_ERRO_TIPO;
            }
            else
            {
              minhaEstrutura.adicionarCentroideMaisProximo(x, y);
            }
          }
          break;

          case REM_COMECO:
          {
            minhaEstrutura.removerDoComeco();
          }
          break;

          case REM_FIM:
          {
            minhaEstrutura.removerDoFim();
          }
          break;

          case REM_INDICE:
          {
            int ind;
            cout << PROMPT_INDICE;
            cin >> ind;
            if (cin.fail())
            {
              cin.clear();
              cin.ignore(numeric_limits<streamsize>::max(), '\n');
              cout << MSG_ERRO_TIPO;
            }
            else if (minhaEstrutura.tamanho() == 0)
            {
              cout << MSG_ERRO_VAZIA;
            }
            else if (ind < 0 || ind >= minhaEstrutura.tamanho())
            {
              cout << MSG_ERRO_INDICE;
            }
            else
            {
              minhaEstrutura.apagarIndice(ind);
            }
          }
          break;

          case REM_PROXIMO:
          {
            int x, y;
            cout << PROMPT_REF_COORD_X;
            cin >> x;
            cout << PROMPT_REF_COORD_Y;
            cin >> y;
            if (cin.fail())
            {
              cin.clear();
              cin.ignore(numeric_limits<streamsize>::max(), '\n');
              cout << MSG_ERRO_TIPO;
            }
            else if (minhaEstrutura.tamanho() == 0)
            {
              cout << MSG_ERRO_VAZIA;
            }
            else
            {
              minhaEstrutura.apagarPontoMaisProximo(x, y);
            }
          }
          break;

          case REM_CENTROIDE:
          {
            int x, y;
            cout << PROMPT_REF_COORD_X;
            cin >> x;
            cout << PROMPT_REF_COORD_Y;
            cin >> y;
            if (cin.fail())
            {
              cin.clear();
              cin.ignore(numeric_limits<streamsize>::max(), '\n');
              cout << MSG_ERRO_TIPO;
            }
            else if (minhaEstrutura.tamanho() == 0)
            {
              cout << MSG_ERRO_VAZIA;
            }
            else
            {
              minhaEstrutura.apagarCentroideMaisProximo(x, y);
            }
          }
          break;

          case MODO_INTERATIVO: // NOVA OPÇÃO 10
          {
            int opcMouse;
            do
            {
              cout << MENU_INTERATIVO;
              cout << PROMPT_ESCOLHA;
              cin >> opcMouse;

              if (cin.fail())
              {
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                opcMouse = -1;
              }

              if (opcMouse == 1 || opcMouse == 2)
              {
                g_modo_interativo = opcMouse; // Destrava o mouse
                cout << "\n[INFO] Janela grafica reaberta. Clique na tela para modificar e feche-a para voltar.\n";
                minhaEstrutura.mostrarPontos(); // Abre a tela
                g_modo_interativo = 0;          // Trava o mouse novamente de forma segura
              }
              else if (opcMouse != 0)
              {
                cout << MSG_OPCAO_INVALIDA;
              }
            } while (opcMouse != 0);
          }
          break;

          case VOLTAR_LISTA:
            break;

          default:
            cout << MSG_OPCAO_INVALIDA;
            break;
          }
        } while (opclista != VOLTAR_LISTA);
      }
    }
    break;

    case SAIR:
      cout << MSG_DESPEDIDA;
      break;

    default:
      cout << MSG_OPCAO_INVALIDA;
      break;
    }
  } while (opc != SAIR);

  return 0;
}