# Forked-From-Lista-De-Pontos---C-

A C++ project showcasing dynamic geometric visualization by integrating OpenCV rendering directly into the data structure's display function (`mostrarPontos()`).

## ⚙️ Tecnologias e Ambiente

- **Linguagem:** C++
- **Biblioteca Gráfica:** OpenCV 4 (gerenciado via `vcpkg`)
- **Compilador:** MSVC (`cl.exe` - Windows)
- **Contexto:** Engenharia de Mecatrônica - IFCE

## 🛠️ Estrutura do Projeto

O projeto foi organizado para separar a lógica de declaração e a implementação gráfica, mantendo a pasta raiz limpa de arquivos temporários de compilação:

- `folders.h`: Cabeçalhos das classes (Ponto, Lista).
- `folders.cpp`: Implementação das estruturas e inicialização do OpenCV.

## 🚀 Como Compilar (Terminal Windows)

Este projeto foi configurado para ser compilado diretamente pelo terminal do Windows utilizando as ferramentas de desenvolvedor da Microsoft, sem depender de IDEs complexas.

1. Abra o **Developer PowerShell** ou o terminal com o ambiente C++ carregado (`vcvars64.bat`).
2. Navegue até a raiz do projeto e execute o comando de build ligando as bibliotecas do OpenCV:

```cmd
cl.exe /Zi /EHsc /nologo /Fe:programa.exe folders.cpp\*.cpp /I folders.h /I C:\vcpkg\installed\x64-windows\include /I C:\vcpkg\installed\x64-windows\include\opencv4 /link /LIBPATH:C:\vcpkg\installed\x64-windows\lib opencv_core4.lib opencv_imgproc4.lib opencv_highgui4.lib
```
