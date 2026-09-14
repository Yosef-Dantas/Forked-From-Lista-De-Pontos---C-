#include "lista.h"
#include <stdlib.h>
#include <stdio.h>
#include <cmath>
#include "mensagens.h"
#include <opencv2/opencv.hpp>
using namespace cv;

using namespace std;

int g_modo_interativo = 0;
float g_escala = 2.0f;
int g_centerX = 400;
int g_centerY = 400;
lista *g_listaAtual = nullptr;

void onMouseClick(int event, int x, int y, int flags, void *userdata)
{
  if (g_listaAtual == nullptr || g_modo_interativo == 0)
    return;

  if (event == EVENT_LBUTTONDOWN)
  {
    int cartX = (int)std::round((x - g_centerX) / g_escala);
    int cartY = (int)std::round((g_centerY - y) / g_escala);

    if (g_modo_interativo == 1)
    {
      if (!g_listaAtual->existePonto(cartX, cartY))
      {
        g_listaAtual->adicionarNoFim(cartX, cartY);
        cout << "\n[+] Ponto (" << cartX << ", " << cartY << ") adicionado pelo mouse!" << endl;
      }
      else
      {
        cout << MSG_ERRO_DUPLICADO;
      }
    }
    else if (g_modo_interativo == 2)
    {
      if (g_listaAtual->tamanho() == 0)
      {
        cout << MSG_ERRO_VAZIA;
      }
      else
      {
        if (g_listaAtual->existePonto(cartX, cartY))
        {
          g_listaAtual->apagarPontoMaisProximo(cartX, cartY);
        }
        else
        {
          cout << "\n[!] Erro: Nenhum ponto na coordenada (" << cartX << ", " << cartY << "). Clique exatamente em cima de um ponto para exclui-lo!\n";
        }
      }
    }
  }
}

lista::lista()
{
}

lista::lista(int x, int y)
{
  ponto p(x, y);
  list.push_back(p);
}

lista::lista(int cx, int cy, float raio, int numero_pontos)
{
  double ang = (2.0 * CV_PI) / (double)numero_pontos;
  int pontos_reais = 0;

  for (int i = 0; i < numero_pontos; i++)
  {
    double temp = i * ang;
    int x = cx + (int)std::round(std::cos(temp) * (double)raio);
    int y = cy + (int)std::round(std::sin(temp) * (double)raio);

    if (!existePonto(x, y))
    {
      ponto p(x, y);
      list.push_back(p);
      pontos_reais++;
    }
  }

  if (pontos_reais != numero_pontos)
  {
    cout << "\n[INFO] Nota Matematica: Voce pediu " << numero_pontos << " pontos, mas devido ao raio estreito, apenas " << pontos_reais << " pontos espaciais unicos couberam." << endl;
  }
}

lista::lista(char *fileName)
{
  FILE *fp;
  fp = fopen(fileName, "r");

  if (fp == NULL)
  {
    cout << "\n[!] Erro: Nao foi possivel abrir o arquivo: " << fileName << endl;
    return;
  }

  char linha[256];
  while (fgets(linha, sizeof(linha), fp))
  {
    int vx, vy;
    if (sscanf(linha, "%d - %d", &vx, &vy) == 2)
    {
      list.push_back(ponto(vx, vy));
    }
    else if (sscanf(linha, "%d %d", &vx, &vy) == 2)
    {
      list.push_back(ponto(vx, vy));
    }
    else if (sscanf(linha, "%d,%d", &vx, &vy) == 2)
    {
      list.push_back(ponto(vx, vy));
    }
  }
  fclose(fp);
}

lista::~lista()
{
}

void lista::adicionarNoFim(int x, int y)
{
  ponto p(x, y);
  list.push_back(p);
}

void lista::adicionarNoComeco(int x, int y)
{
  ponto p(x, y);
  list.insert(list.begin(), p);
}

void lista::removerDoFim()
{
  if (list.size() != 0)
  {
    list.pop_back();
  }
  else
  {
    cout << MSG_ERRO_VAZIA;
  }
}

void lista::removerDoComeco()
{
  if (list.size() != 0)
  {
    list.erase(list.begin());
  }
  else
  {
    cout << MSG_ERRO_VAZIA;
  }
}

void lista::adicionarNoIndice(int x, int y, int ind)
{
  ponto p(x, y);
  list.insert(list.begin() + ind, p);
}

void lista::apagarIndice(int ind)
{
  if (ind >= 0 && ind < list.size())
  {
    list.erase(list.begin() + ind);
  }
}

void lista::apagarPontoMaisProximo(int x, int y)
{
  if (list.empty())
    return;

  int indexMaisProximo = 0;
  float menorDistancia = sqrt(pow(list[0].x() - x, 2) + pow(list[0].y() - y, 2));

  for (int i = 1; i < list.size(); i++)
  {
    float dist = sqrt(pow(list[i].x() - x, 2) + pow(list[i].y() - y, 2));
    if (dist < menorDistancia)
    {
      menorDistancia = dist;
      indexMaisProximo = i;
    }
  }

  cout << "\n[INFO] O ponto (" << list[indexMaisProximo].x() << ", " << list[indexMaisProximo].y() << ") era o mais proximo e foi APAGADO!" << endl;
  list.erase(list.begin() + indexMaisProximo);
}

void lista::adicionarCentroideMaisProximo(int x, int y)
{
  if (list.size() < 2)
  {
    cout << "\n[!] Erro: Precisa de pelo menos 2 pontos diferentes para calcular o centroide!\n";
    return;
  }

  int idx1 = -1, idx2 = -1;
  float dist1 = 9999999.0, dist2 = 9999999.0;

  for (int i = 0; i < list.size(); i++)
  {
    float dist = sqrt(pow(list[i].x() - x, 2) + pow(list[i].y() - y, 2));
    if (dist < dist1)
    {
      dist1 = dist;
      idx1 = i;
    }
  }

  for (int i = 0; i < list.size(); i++)
  {
    if (list[i].x() == list[idx1].x() && list[i].y() == list[idx1].y())
      continue;

    float dist = sqrt(pow(list[i].x() - x, 2) + pow(list[i].y() - y, 2));
    if (dist < dist2)
    {
      dist2 = dist;
      idx2 = i;
    }
  }

  if (idx2 == -1)
  {
    cout << "\n[!] Erro: Nao existem 2 pontos espaciais diferentes na estrutura para calcular o centroide!\n";
    return;
  }

  int centroideX = (list[idx1].x() + list[idx2].x()) / 2;
  int centroideY = (list[idx1].y() + list[idx2].y()) / 2;

  if (existePonto(centroideX, centroideY))
  {
    cout << MSG_ERRO_DUPLICADO;
    return;
  }

  ponto p(centroideX, centroideY);

  int posInsercao = (idx1 < idx2) ? idx1 + 1 : idx2 + 1;
  list.insert(list.begin() + posInsercao, p);

  cout << "\n[INFO] Referencia digitada: (" << x << ", " << y << ")" << endl;
  cout << "[INFO] Os 2 pontos mais proximos sao: ("
       << list[idx1].x() << ", " << list[idx1].y() << ") e ("
       << list[idx2].x() << ", " << list[idx2].y() << ")." << endl;
  cout << MSG_SUCESSO_ADD;
  cout << "[+] Coordenada do Centroide Adicionado entre eles: (" << centroideX << ", " << centroideY << ")\n"
       << endl;
}

void lista::apagarCentroideMaisProximo(int x, int y)
{
  if (list.size() == 0)
    return;
  if (list.size() == 1)
  {
    cout << "\n[INFO] O ponto (" << list[0].x() << ", " << list[0].y() << ") foi apagado!\n"
         << endl;
    list.pop_back();
    return;
  }

  int idx1 = -1, idx2 = -1;
  float dist1 = 9999999.0, dist2 = 9999999.0;

  for (int i = 0; i < list.size(); i++)
  {
    float dist = sqrt(pow(list[i].x() - x, 2) + pow(list[i].y() - y, 2));
    if (dist < dist1)
    {
      dist1 = dist;
      idx1 = i;
    }
  }

  for (int i = 0; i < list.size(); i++)
  {
    if (list[i].x() == list[idx1].x() && list[i].y() == list[idx1].y())
      continue;

    float dist = sqrt(pow(list[i].x() - x, 2) + pow(list[i].y() - y, 2));
    if (dist < dist2)
    {
      dist2 = dist;
      idx2 = i;
    }
  }

  if (idx2 == -1)
  {
    cout << "\n[!] Erro: Nao existem 2 pontos espaciais diferentes na estrutura para gerar um centroide e apagar o vizinho!\n"
         << endl;
    return;
  }

  int cx = (list[idx1].x() + list[idx2].x()) / 2;
  int cy = (list[idx1].y() + list[idx2].y()) / 2;

  int idxRemover = 0;
  float menorDist = 9999999.0;

  for (int i = 0; i < list.size(); i++)
  {
    float d = sqrt(pow(list[i].x() - cx, 2) + pow(list[i].y() - cy, 2));
    if (d < menorDist)
    {
      menorDist = d;
      idxRemover = i;
    }
  }

  cout << "\n[INFO] O centroide calculado foi (" << cx << ", " << cy << ")." << endl;
  cout << "[INFO] O ponto mais proximo dele na lista era (" << list[idxRemover].x() << ", " << list[idxRemover].y() << "), que foi APAGADO!\n"
       << endl;
  list.erase(list.begin() + idxRemover);
}

bool lista::existePonto(int x, int y)
{
  for (int i = 0; i < list.size(); i++)
  {
    if (list.at(i).x() == x && list.at(i).y() == y)
    {
      return true;
    }
  }
  return false;
}

void lista::mostrarPontos()
{
  g_listaAtual = this;

  if (list.size() > 0)
  {
    cout << "\nPontos atuais no sistema:" << endl;
    for (int i = 0; i < list.size(); i++)
    {
      cout << "(" << list[i].x() << ", " << list[i].y() << ")" << endl;
    }
  }
  else
  {
    cout << MSG_INFO_VAZIA;
  }

  namedWindow("Plano Cartesiano");
  setMouseCallback("Plano Cartesiano", onMouseClick, NULL);

  while (getWindowProperty("Plano Cartesiano", WND_PROP_VISIBLE) >= 1)
  {
    int maxCoord = 10;

    for (int i = 0; i < list.size(); i++)
    {
      if (abs(list.at(i).x()) > maxCoord)
        maxCoord = abs(list.at(i).x());
      if (abs(list.at(i).y()) > maxCoord)
        maxCoord = abs(list.at(i).y());
    }

    Mat image(800, 800, CV_8UC3, Scalar(255, 255, 255));

    g_centerX = 400;
    g_centerY = 400;
    g_escala = 360.0f / (float)maxCoord;

    int espacoNumeros = 5;
    if (maxCoord > 25)
      espacoNumeros = 10;
    if (maxCoord > 60)
      espacoNumeros = 20;
    if (maxCoord > 150)
      espacoNumeros = 50;
    if (maxCoord > 300)
      espacoNumeros = 100;
    if (maxCoord > 700)
      espacoNumeros = 200;
    if (maxCoord > 2000)
      espacoNumeros = 500;

    int maxUnidades = maxCoord + espacoNumeros;

    for (int i = -maxUnidades; i <= maxUnidades; i++)
    {
      if (i % (espacoNumeros / 2 > 0 ? espacoNumeros / 2 : 1) == 0)
      {
        int pX = g_centerX + (int)(i * g_escala);
        int pY = g_centerY + (int)(i * g_escala);
        line(image, Point(pX, 0), Point(pX, 800), Scalar(240, 240, 240), 1);
        line(image, Point(0, pY), Point(800, pY), Scalar(240, 240, 240), 1);
      }
    }

    line(image, Point(0, g_centerY), Point(800, g_centerY), Scalar(0, 0, 0), 2);
    line(image, Point(g_centerX, 0), Point(g_centerX, 800), Scalar(0, 0, 0), 2);

    line(image, Point(785, g_centerY - 5), Point(800, g_centerY), Scalar(0, 0, 0), 2);
    line(image, Point(785, g_centerY + 5), Point(800, g_centerY), Scalar(0, 0, 0), 2);
    putText(image, "X", Point(775, g_centerY + 25), FONT_HERSHEY_SIMPLEX, 0.6, Scalar(0, 0, 0), 2);

    line(image, Point(g_centerX - 5, 15), Point(g_centerX, 0), Scalar(0, 0, 0), 2);
    line(image, Point(g_centerX + 5, 15), Point(g_centerX, 0), Scalar(0, 0, 0), 2);
    putText(image, "y", Point(g_centerX - 25, 25), FONT_HERSHEY_SIMPLEX, 0.6, Scalar(0, 0, 0), 2);

    for (int i = -maxUnidades; i <= maxUnidades; i++)
    {
      if (i == 0)
        continue;

      if (i % espacoNumeros == 0)
      {
        int pX = g_centerX + (int)(i * g_escala);
        int pY = g_centerY - (int)(i * g_escala);

        line(image, Point(pX, g_centerY - 4), Point(pX, g_centerY + 4), Scalar(0, 0, 0), 2);
        putText(image, to_string(i), Point(pX - 10, g_centerY + 20), FONT_HERSHEY_SIMPLEX, 0.4, Scalar(0, 0, 0), 1);

        line(image, Point(g_centerX - 4, pY), Point(g_centerX + 4, pY), Scalar(0, 0, 0), 2);
        putText(image, to_string(i), Point(g_centerX - 28, pY + 5), FONT_HERSHEY_SIMPLEX, 0.4, Scalar(0, 0, 0), 1);
      }
    }

    putText(image, "0", Point(g_centerX - 12, g_centerY + 12), FONT_HERSHEY_SIMPLEX, 0.4, Scalar(0, 0, 0), 1);

    for (int i = 0; i < list.size(); i++)
    {
      int x1 = g_centerX + (int)(list[i].x() * g_escala);
      int y1 = g_centerY - (int)(list[i].y() * g_escala);

      int nextIndex = (i == list.size() - 1) ? 0 : i + 1;
      int x2 = g_centerX + (int)(list[nextIndex].x() * g_escala);
      int y2 = g_centerY - (int)(list[nextIndex].y() * g_escala);

      line(image, Point(x1, y1), Point(x2, y2), Scalar(150, 100, 50), 2);

      cv::circle(image, Point(x1, y1), 4, Scalar(0, 0, 255), -1);

      if (list.size() <= 20)
      {
        string texto = "(" + to_string(list[i].x()) + ", " + to_string(list[i].y()) + ")";
        putText(image, texto, Point(x1 + 10, y1 - 10), FONT_HERSHEY_SIMPLEX, 0.4, Scalar(150, 0, 0), 1);
      }
    }

    imshow("Plano Cartesiano", image);

    if (waitKey(50) >= 0)
      break;
  }

  destroyAllWindows();
  waitKey(1);

  if (g_modo_interativo != 0)
  {
    cout << "\n============================================" << endl;
    cout << "[INFO] Janela fechada. Lista definitiva de pontos:" << endl;
    if (list.size() > 0)
    {
      for (int i = 0; i < list.size(); i++)
      {
        cout << "(" << list.at(i).x() << ", " << list.at(i).y() << ")" << endl;
      }
    }
    else
    {
      cout << "A estrutura esta vazia." << endl;
    }
    cout << "============================================\n"
         << endl;
  }
}

int lista::tamanho()
{
  return list.size();
}

void lista::circle(const int &cx, const int &cy, const int &r, const int &np)
{
  list.clear();
  double ang = (2.0 * CV_PI) / (double)np;
  int pontos_reais = 0;

  for (int i = 0; i < np; i++)
  {
    double temp = i * ang;
    int x = cx + (int)std::round(std::cos(temp) * (double)r);
    int y = cy + (int)std::round(std::sin(temp) * (double)r);

    if (!existePonto(x, y))
    {
      ponto p(x, y);
      list.push_back(p);
      pontos_reais++;
    }
  }

  if (pontos_reais == np)
  {
    cout << "\n[INFO] Circulo gerado com sucesso! Pontos: " << np << " | Raio: " << r << "\n"
         << endl;
  }
  else
  {
    cout << "\n[INFO] Nota Matematica: Voce pediu " << np << " pontos, mas devido ao raio estreito, apenas " << pontos_reais << " pontos espaciais unicos couberam.\n"
         << endl;
  }
}