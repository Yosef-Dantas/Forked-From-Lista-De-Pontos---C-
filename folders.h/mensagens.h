#ifndef MENSAGENS_H
#define MENSAGENS_H

#include <iostream>
#include <string>
using namespace std;

const string CABECALHO_PRINCIPAL = "\n ===MENU===\nEscolha uma opção: \n1. Fila \n2. Pilha \n3. Lista \n0. Sair \n";
const string CABECALHO_FILA = "\n===Você escolheu a opção Fila===\n";
const string CABECALHO_PILHA = "\n===Você escolheu a opção Pilha===\n";
const string CABECALHO_LISTA = "\n===Você escolheu a opção Lista===\n";

const string MENU_INICIALIZACAO = "\nComo deseja inicializar a estrutura?\n1. Adição manual.\n2. Lê o Arquivo 1.\n3. Lê o Arquivo 2.\n4. Gerar um Círculo.\n0. Voltar ao menu inicial.\n";
const string MENU_ACOES = "\n1. Adicionar novo ponto.\n2. Remover ponto.\n0. Voltar ao menu inicial.\n";

const string MENU_ACOES_LISTA = "\n1. Adicionar no começo\n2. Adicionar no fim\n3. Adicionar em índice específico\n4. Adicionar centróide entre mais próximos\n5. Remover do começo\n6. Remover do fim\n7. Remover em índice específico\n8. Remover ponto mais próximo\n9. Remover centróide mais próximo\n10. Modo Interativo (Mouse)\n0. Voltar ao menu inicial\n";
const string MENU_INTERATIVO = "\n=== MODO MOUSE ===\n1. Adicionar pontos (Clicar na tela)\n2. Remover pontos (Clicar no ponto)\n0. Cancelar\n";

const string PROMPT_ESCOLHA = "=> ";
const string PROMPT_ADD_COORD_X = "Qual o valor da coordenada X: ";
const string PROMPT_ADD_COORD_Y = "Qual o valor da coordenada Y: ";
const string PROMPT_REF_COORD_X = "Qual o valor da coordenada X de referência: ";
const string PROMPT_REF_COORD_Y = "Qual o valor da coordenada Y de referência: ";
const string PROMPT_INDICE = "Qual o índice desejado: ";

const string PROMPT_CIRCULO_CX = "Digite a coordenada X do centro do círculo: ";
const string PROMPT_CIRCULO_CY = "Digite a coordenada Y do centro do círculo: ";
const string PROMPT_CIRCULO_R = "Digite o raio do círculo: ";
const string PROMPT_CIRCULO_NP = "Digite a quantidade de pontos do círculo: ";

const string MSG_INFO_VAZIA = "\n[INFO] A estrutura está vazia no momento.\n";

const string MSG_SUCESSO_ADD = "\n[+] Novo ponto registrado com sucesso no sistema!\n";
const string MSG_SUCESSO_ARQ = "\n[+] Arquivo carregado com sucesso!\n";
const string MSG_SUCESSO_CIRCULO = "\n[+] Círculo gerado com sucesso!\n";

const string MSG_ERRO_VAZIA = "\n[!] A lista de pontos está vazia, não há o que remover!\n\n";
const string MSG_OPCAO_INVALIDA = "\n[!] Opção inválida! Tente novamente.\n\n";
const string MSG_ERRO_PONTO = "\n[!] Erro: Coordenadas são inválidas e não podem ser adicionadas.\n\n";
const string MSG_ERRO_DUPLICADO = "\n[!] Erro: Esse ponto já existe no sistema.\n\n";
const string MSG_ERRO_TIPO = "\n[!] Erro: Entrada inválida. Digite apenas números.\n\n";
const string MSG_ERRO_LIMITE = "\n[!] Limite de tentativas excedido.\n";
const string MSG_ERRO_INDICE = "\n[!] Erro: Índice inexistente ou fora dos limites.\n\n";
const string MSG_ERRO_CIRCULO_R = "\n[!] Erro: O raio do círculo deve ser maior que zero!\n\n";
const string MSG_ERRO_CIRCULO_NP = "\n[!] Erro: A quantidade de pontos deve ser maior que zero!\n\n";

const string MSG_DESPEDIDA = "\nAté a próxima!\n";

#endif