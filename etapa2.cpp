#include "minhasfuncoes.h"
#include "biblioteca.h"
#include <stdio.h>

int main(void) {
  char expressao[max];
  scanf("%s", expressao);

  T_Lista pilhaExpressao;
  iniciarLista(&pilhaExpressao);

  meuGerarPosfixa(&pilhaExpressao, expressao, max);
  listar_pilha(&pilhaExpressao);

  T_Lista pilhaResultado;
  iniciarLista(&pilhaResultado);
  calcular_resultado(&pilhaExpressao, &pilhaResultado);

  printf("%d ", pilhaResultado.ultimo->item.campo);
  printf("\n");

  liberarUltimoLista(&pilhaExpressao);
  liberarUltimoLista(&pilhaResultado);

  return 0;
}

