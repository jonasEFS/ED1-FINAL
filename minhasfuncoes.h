#ifndef MINHASFUNCOES_H
#define MINHASFUNCOES_H

#include "biblioteca.h"
#include <cstdlib>
#include <cstring>
#include <ctype.h>

void listar_pilha(T_Lista *pilhaExpressao) {
  T_No *aux = pilhaExpressao->ultimo;

  while (aux != NULL) {
    if (aux->item.flagZeroIntUmChar == 0) {
      printf("%d ", aux->item.campo);
    } else {
      printf("%c ", aux->item.campo);
    }
    aux = aux->prox;
  }
  printf("\n");
}

int meuDesempilhar(T_Lista *pilha) {
  if (checkListaVazia(pilha))
    return 0;

  int aDesempilhar = pilha->ultimo->item.campo;

  T_No *noLocalizado = pilha->ultimo;
  pilha->ultimo = noLocalizado->prox;
  free(noLocalizado);
  pilha->qtdeAtual--;

  return aDesempilhar;
}

void calcular_resultado(T_Lista *pilhaExpressao, T_Lista *pilhaResultado) {
  T_No *aux = pilhaExpressao->ultimo;

  while (aux != NULL) {
    T_Item *aSerTestado = &(aux->item);

    if (aSerTestado->flagZeroIntUmChar == 0) {
      int value = aSerTestado->campo;
      T_Item item;
      item.campo = value;
      inserir(pilhaResultado, item);
    } else {
      int operador1 = meuDesempilhar(pilhaResultado);
      int operador2 = meuDesempilhar(pilhaResultado);
      int resultado;

      switch (aSerTestado->campo) {
      case '+':
        resultado = operador2 + operador1;
        break;
      case '-':
        resultado = operador2 - operador1;
        break;
      case '*':
        resultado = operador2 * operador1;
        break;
      case '/':
        resultado = operador2 / operador1;
        break;
      }

      T_Item resultadoItem;
      resultadoItem.campo = resultado;
      inserir(pilhaResultado, resultadoItem);
    }

    aux = aux->prox;
  }
}

void meuGerarPosfixa(T_Lista *plOutput, char exp[], int capacidade) {
  T_Lista plOperadores;
  T_Lista plTemp;
  iniciarLista(&plOperadores);
  iniciarLista(&plTemp);

  T_Item item;

  int i = 0;
  while (exp[i] != '\0') {
    if (isdigit(exp[i])) {
      int num = 0;
      while (isdigit(exp[i])) {
        num = num * 10 + (exp[i] - '0');
        i++;
      }

      item.campo = num;
      item.flagZeroIntUmChar = 0;
      inserir(&plTemp, item);
    } else if (strchr("+-*/", exp[i]) != NULL) {
      item.campo = exp[i];
      item.flagZeroIntUmChar = 1;

      while (!checkListaVazia(&plOperadores) &&
             plOperadores.ultimo->item.campo != '(') {
        inserir(&plTemp, plOperadores.ultimo->item);
        excluirFinal(&plOperadores);
      }

      inserir(&plOperadores, item);
      i++;
    } else if (exp[i] == '(') {
      item.campo = '(';
      item.flagZeroIntUmChar = 1;
      inserir(&plOperadores, item);
      i++;
    } else if (exp[i] == ')') {
      while (!checkListaVazia(&plOperadores) &&
             plOperadores.ultimo->item.campo != '(') {
        inserir(&plTemp, plOperadores.ultimo->item);
        excluirFinal(&plOperadores);
      }

      excluirFinal(&plOperadores);
      i++;
    } else {
      i++;
    }
  }

  while (!checkListaVazia(&plOperadores)) {
    inserir(&plTemp, plOperadores.ultimo->item);
    excluirFinal(&plOperadores);
  }

  while (!checkListaVazia(&plTemp)) {
    inserir(plOutput, plTemp.ultimo->item);
    excluirFinal(&plTemp);
  }
}
const int max = 99;
#endif
