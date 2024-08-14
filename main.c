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
  int altura;
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

int alturaDoNo(NoArvore *no) { return (no == NULL) ? -1 : no->altura; }

int calcularAlturaNo(NoArvore *no) {
  if (no == NULL)
    return 0;

  int alturaEsquerda = calcularAlturaNo(no->esquerdo);
  int alturaDireita = calcularAlturaNo(no->direito);

  return (alturaEsquerda > alturaDireita) ? alturaEsquerda + 1
                                          : alturaDireita + 1;
}

int calcularFatorDeBalaciamento(NoArvore *no) {
  int fatorDeBalaciamento = alturaDoNo(no->esquerdo) - alturaDoNo(no->direito);
  return fatorDeBalaciamento;
}

void calcularTodosOsFatoresDeBalanceamento(Arvore *arvore) {
  if (arvore == NULL)
    return;

  if (*arvore != NULL) {
    (*arvore)->fatorBalanciamento = calcularFatorDeBalaciamento(*arvore);
    calcularTodosOsFatoresDeBalanceamento(&(*arvore)->esquerdo);
    calcularTodosOsFatoresDeBalanceamento(&(*arvore)->direito);
  }
}

int maior(int x, int y) { return (x > y) ? x : y; }

void giroSimplesDireita(Arvore *no) {
  NoArvore *auxiliar = (*no)->esquerdo;
  (*no)->esquerdo = auxiliar->direito;
  auxiliar->direito = *no;
  (*no)->altura =
      maior(alturaDoNo((*no)->esquerdo), alturaDoNo((*no)->direito)) + 1;
  auxiliar->altura = maior(alturaDoNo(auxiliar->esquerdo), (*no)->altura) + 1;
  *no = auxiliar;
}

void giroSimplesEsquerda(Arvore *no) {
  NoArvore *auxiliar = (*no)->direito;
  (*no)->direito = auxiliar->esquerdo;
  auxiliar->esquerdo = (*no);
  (*no)->altura =
      maior(alturaDoNo((*no)->esquerdo), alturaDoNo((*no)->direito)) + 1;
  auxiliar->altura = maior(alturaDoNo(auxiliar->direito), (*no)->altura) + 1;
  (*no) = auxiliar;
}

void giroDuploEsquerdaDireita(Arvore *no) {
  giroSimplesEsquerda(&(*no)->esquerdo);
  giroSimplesDireita(no);
}

void giroDuploDireitaEsquerda(Arvore *no) {
  giroSimplesDireita(&(*no)->direito);
  giroSimplesEsquerda(no);
}

int inserirNaArvore(Arvore *arvore, int novoValor) {
  int status;
  if (*arvore == NULL) {
    NoArvore *novoNo;
    novoNo = (NoArvore *)malloc(sizeof(NoArvore));

    if (novoNo == NULL)
      return 0;

    novoNo->valor = novoValor;
    novoNo->altura = 0;
    novoNo->esquerdo = NULL;
    novoNo->direito = NULL;
    *arvore = novoNo;
    return 1;
  }

  NoArvore *atual = *arvore;
  if (novoValor < atual->valor) {
    if ((status = inserirNaArvore(&(atual->esquerdo), novoValor)) == 1) {
      if (labs(calcularFatorDeBalaciamento(atual)) >= 2) {
        if (novoValor < (*arvore)->esquerdo->valor) {
          giroSimplesDireita(arvore);
        } else {
          giroDuploEsquerdaDireita(arvore); // LR
        }
      }
    }
  } else {
    if ((status = inserirNaArvore(&(atual->direito), novoValor)) == 1) {
      if (labs(calcularFatorDeBalaciamento(atual)) >= 2) {
        if ((*arvore)->direito->valor < novoValor) {
          giroSimplesEsquerda(arvore);
        } else {
          giroDuploDireitaEsquerda(arvore);
        }
      }
    }
  }
  calcularTodosOsFatoresDeBalanceamento(arvore);
  atual->altura =
      maior(alturaDoNo(atual->esquerdo), alturaDoNo(atual->direito)) + 1;

  return status;
}

int removerDaArvore(Arvore *arvore, int valorAExcluir) {
  if (*arvore == NULL) {
    printf("Valor %i Não Encontrado\n", valorAExcluir);
    return 0;
  }

  int status;
  if (valorAExcluir < (*arvore)->valor) {
    if ((status = removerDaArvore(&(*arvore)->esquerdo, valorAExcluir)) == 1) {
      if (calcularFatorDeBalaciamento(*arvore) >= 2) {
        if (alturaDoNo((*arvore)->direito->esquerdo) <=
            alturaDoNo((*arvore)->direito->direito))
          giroSimplesEsquerda(arvore);
        else
          giroDuploDireitaEsquerda(arvore);
      }
    }
  }

  if ((*arvore)->valor < valorAExcluir) {
    if ((status = removerDaArvore(&(*arvore)->direito, valorAExcluir)) == 1) {
      if (calcularFatorDeBalaciamento(*arvore) >= 2) {
        if (alturaDoNo((*arvore)->esquerdo->direito) <=
            alturaDoNo((*arvore)->esquerdo->esquerdo))
          giroSimplesDireita(arvore);
        else
          giroDuploEsquerdaDireita(arvore);
      }
    }
  }

  if ((*arvore)->valor == valorAExcluir) {
    if (((*arvore)->esquerdo == NULL || (*arvore)->direito == NULL)) {
      NoArvore *NoAExluir = *arvore;
      if ((*arvore)->esquerdo != NULL)
        *arvore = (*arvore)->esquerdo;
      else
        *arvore = (*arvore)->direito;
      free(NoAExluir);
    } else {
      NoArvore *no1 = (*arvore)->direito;
      NoArvore *no2 = (*arvore)->direito->esquerdo;
      while (no2 != NULL) {
        no1 = no2;
        no2 = no2->esquerdo;
      }
      NoArvore *temp = no1;

      (*arvore)->valor = temp->valor;
      removerDaArvore(&(*arvore)->direito, (*arvore)->valor);
      if (calcularFatorDeBalaciamento(*arvore) >= 2) {
        if (alturaDoNo((*arvore)->esquerdo->direito) <=
            alturaDoNo((*arvore)->esquerdo->esquerdo))
          giroSimplesDireita(arvore);
        else
          giroDuploEsquerdaDireita(arvore);
      }
    }

    if (*arvore != NULL)
      (*arvore)->altura = maior(alturaDoNo((*arvore)->esquerdo),
                                alturaDoNo((*arvore)->direito)) +
                          1;
    return 1;
  }

  (*arvore)->altura =
      maior(alturaDoNo((*arvore)->esquerdo), alturaDoNo((*arvore)->direito)) +
      1;

  return status;
}

void exibirInOrdem(Arvore *arvore) {
  if (arvore == NULL)
    return;

  if (*arvore != NULL) {
    exibirInOrdem(&(*arvore)->esquerdo);
    printf("{ v: %i, ", (*arvore)->valor);
    printf("fbc: %i - fbs: %i }\n", calcularFatorDeBalaciamento(*arvore),
           (*arvore)->fatorBalanciamento);
    exibirInOrdem(&(*arvore)->direito);
  }
}

void mostrarFilhos(Arvore *arvore, int noPai) {
  if (arvore == NULL)
    return;

  if (*arvore == NULL) {
    printf("Sem elementos\n");
  } else {
    NoArvore *atual = *arvore;
    while (atual->valor != noPai) {
      if (noPai < atual->valor) {
        atual = atual->esquerdo;
      } else if (noPai > atual->valor) {
        atual = atual->direito;
      }

      if (atual == NULL) {
        printf("Elemento não presente na Arvore\n\n");
        return;
      }
    }

    printf("No Pai: { Valor: %d,\n", noPai);
    printf("\t  Fator de Balanciamento: %d,\n", atual->fatorBalanciamento);

    if (atual->esquerdo == NULL)
      printf("\n\t  No Esquerdo: { NULL },\n");
    else {
      printf("\n\t  No Esquerdo: { Valor: %d,\n", atual->esquerdo->valor);
      printf("\t\t\t Fator de Balanciamento: %d\n\t  }\n",
             atual->esquerdo->fatorBalanciamento);
    }

    if (atual->direito == NULL)
      printf("\n\t  No Direito:  { NULL },\n");
    else {
      printf("\n\t  No Direito:  { Valor: %d,\n", atual->direito->valor);
      printf("\t\t\t Fator de Balanciamento: %d\n\t  }\n}\n",
             atual->direito->fatorBalanciamento);
    }
  }
}

int main() {
  // Vetores e não listas para testar a arvore
  int itemsParaInserir[] = {1,  64, 12, 18, 66, 38, 95, 58,
                            59, 70, 68, 39, 62, 7,  60};
  int itemsParaRemover[] = {43, 16, 67, 34, 35};

  Lista *lista = criarLista();
  inserirValoresDoVetorNaLista(lista, itemsParaInserir);
  exibirLista(lista);
  // Passou

  // Teste de Inserção Arvore e Balaceio
  Arvore *arvore = criarArvore();
  inserirNaArvore(arvore, itemsParaInserir[0]);
  inserirNaArvore(arvore, itemsParaInserir[1]);
  inserirNaArvore(arvore, itemsParaInserir[2]);
  inserirNaArvore(arvore, itemsParaInserir[3]);
  inserirNaArvore(arvore, itemsParaInserir[4]);
  inserirNaArvore(arvore, itemsParaInserir[5]);
  inserirNaArvore(arvore, itemsParaInserir[6]);
  inserirNaArvore(arvore, itemsParaInserir[7]);
  inserirNaArvore(arvore, itemsParaInserir[8]);
  inserirNaArvore(arvore, itemsParaInserir[9]);
  inserirNaArvore(arvore, itemsParaInserir[10]);
  inserirNaArvore(arvore, itemsParaInserir[11]);
  inserirNaArvore(arvore, itemsParaInserir[12]);
  inserirNaArvore(arvore, itemsParaInserir[13]);
  inserirNaArvore(arvore, itemsParaInserir[14]);

  removerDaArvore(arvore, itemsParaRemover[0]);
  removerDaArvore(arvore, itemsParaRemover[1]);
  removerDaArvore(arvore, itemsParaRemover[2]);
  removerDaArvore(arvore, itemsParaRemover[3]);
  removerDaArvore(arvore, itemsParaRemover[4]);

  exibirInOrdem(arvore);

  printf("\n\nDigite um numero da Arvore para obter seus filhos>> ");
  int pai;
  scanf("%d", &pai);
  mostrarFilhos(arvore, pai);
  return 0;
  // Passou

  exibirInOrdem(arvore);

  return 0;
}
