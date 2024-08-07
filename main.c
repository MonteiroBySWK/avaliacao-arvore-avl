#include <stdlib.h>

typedef struct no {
  int valor;
  int fatorBalanciamento;
  struct no *esquerdo;
  struct no *direito;
} No;

typedef struct no *Arvore;

Arvore *criarArvore() {
  Arvore *arvore = (Arvore *)malloc(sizeof(Arvore));
  if (arvore != NULL) {
    *arvore = NULL;
  }
  return arvore;
}

int inserirNaArvore(Arvore *arvore, int valorNovo) { return 0; }

int removerDaArvore(Arvore *arvore, int valorExclusao) { return 0; }

int main() {
  // Vetores e não listas para testar a arvore
  int itemsParaInserir[] = {1,  64, 12, 18, 66, 38, 95, 58,
                            59, 70, 68, 39, 62, 7,  60};
  int itemsParaRemover[] = {43, 16, 67, 34, 35};

  return 0;
}
