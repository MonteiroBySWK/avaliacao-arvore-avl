#include <stdio.h>
#include <stdlib.h>

// Funções de Lista

typedef struct noLista {
  int valor;
  struct noLista *proximo;
} NoLista;

typedef struct noLista *Lista;

Lista *criarLista() {
  Lista *lista = (Lista *)malloc(sizeof(Lista));
  if (lista != NULL) {
    *lista = NULL;
  }
  return lista;
}

void inserirNaLista(Lista *lista, int valor) {
  if (lista == NULL)
    return;

  NoLista *novoNo = (NoLista *)malloc(sizeof(NoLista));

  if (novoNo == NULL)
    return;

  novoNo->valor = valor;
  novoNo->proximo = NULL;

  if (*lista == NULL) {
    *lista = novoNo;
  } else {
    NoLista *atual = *lista;
    while (atual->proximo != NULL) {
      atual = atual->proximo;
    }

    atual->proximo = novoNo;
  }
}

void inserirValoresDoVetorNaLista(Lista *lista, int *v) {
  if (lista == NULL)
    return;

  for (int i = 0; i < 15; i++) {
    inserirNaLista(lista, v[i]);
  }
}

void exibirLista(Lista *lista) {
  if (lista == NULL)
    return;

  NoLista *atual = *lista;
  while (atual != NULL) {
    printf("%i - ", atual->valor);
    atual = atual->proximo;
  }
  printf("\n");
}

// Funções da Arvore
typedef struct noArvore {
  int valor;
  int fatorBalanciamento;
  struct noArvore *esquerdo;
  struct noArvore *direito;
} NoArvore;

typedef struct noArvore *Arvore;

Arvore *criarArvore() {
  Arvore *arvore = (Arvore *)malloc(sizeof(Arvore));
  if (arvore != NULL) {
    *arvore = NULL;
  }
  return arvore;
}

int alturaNo(NoArvore *no) {
  if (no == NULL)
    return 0;

  if (no->direito == NULL && no->esquerdo == NULL)
    return 0;

  int alturaEsquerda = alturaNo(no->esquerdo);
  int alturaDireita = alturaNo(no->direito);
  if (alturaEsquerda > alturaDireita)
    return alturaEsquerda + 1;
  else
    return alturaDireita + 1;
}

int calcularFatorDeBalaciamento(NoArvore *no) {
  return alturaNo(no->esquerdo) - alturaNo(no->direito);
}

void calcularTodosOsFatoresDeBalanceamento(Arvore *arvore) {
  if (arvore == NULL)
    return;

  if (*arvore != NULL) {
    calcularTodosOsFatoresDeBalanceamento(&(*arvore)->esquerdo);
    calcularTodosOsFatoresDeBalanceamento(&(*arvore)->direito);
    (*arvore)->fatorBalanciamento = calcularFatorDeBalaciamento(*arvore);
  }
}

void giroSimples(Arvore *arvore) {}

void giroDuplo(Arvore *arvore) {}

int inserirNaArvore(Arvore *arvore, int valorNovo) {
  if (arvore == NULL)
    return 0;

  NoArvore *novoNo = (NoArvore *)malloc(sizeof(NoArvore));
  if (novoNo == NULL)
    return 0;

  novoNo->esquerdo = NULL;
  novoNo->direito = NULL;
  novoNo->valor = valorNovo;
  novoNo->fatorBalanciamento = 0;

  if (*arvore == NULL) {
    *arvore = novoNo;
    novoNo->fatorBalanciamento = 0;
  } else {
    NoArvore *atual = *arvore;
    NoArvore *anterior = NULL;
    while (atual != NULL) {
      anterior = atual;
      if (novoNo->valor < atual->valor)
        atual = atual->esquerdo;
      else
        atual = atual->direito;
    }
    if (novoNo->valor < anterior->valor)
      anterior->esquerdo = novoNo;
    else
      anterior->direito = novoNo;
  }

  calcularTodosOsFatoresDeBalanceamento(arvore);
  return 0;
}

void inserirListaNaArvore(Lista *lista, Arvore *arvore) {
  NoLista *atual = *lista;
  while (atual != NULL) {
    inserirNaArvore(arvore, atual->valor);
    atual = atual->proximo;
  }
}

void exibirInOrdem(Arvore *arvore) {
  if (arvore == NULL)
    return;

  if (*arvore != NULL) {
    exibirInOrdem(&(*arvore)->esquerdo);
    printf("v: %i - \n", (*arvore)->valor);
    printf("fb: %i - \n", (*arvore)->fatorBalanciamento);
    exibirInOrdem(&(*arvore)->direito);
  }
}

int removerDaArvore(Arvore *arvore, int valorExclusao) { return 0; }

int main() {
  // Vetores e não listas para testar a arvore
  int itemsParaInserir[] = {1,  64, 12, 18, 66, 38, 95, 58,
                            59, 70, 68, 39, 62, 7,  60};
  int itemsParaRemover[] = {43, 16, 67, 34, 35};

  // Teste Lista
  Lista *lista = criarLista();
  inserirValoresDoVetorNaLista(lista, itemsParaInserir);
  exibirLista(lista);
  // Passou

  // Teste de Inserção Arvore
  Arvore *arvore = criarArvore();
  inserirListaNaArvore(lista, arvore);
  exibirInOrdem(arvore);
  // Passou
  return 0;
}
