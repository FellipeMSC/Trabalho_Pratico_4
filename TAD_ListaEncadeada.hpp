#ifndef LISTA_H
#define LISTA_H

#include "TAD_CircularDuplamenteEncadeada.cpp"

namespace encadeada {

    struct Item {
        int id;
        string nomeLinha;
        string companhia;

        int idParada = 1;
        
        circularDuplamenteEncadeada::Lista paradas;
    };

    typedef struct Elemento* Apontador;

    struct Elemento{
        Item item;
        Elemento *prox;
    };

    struct Lista {
        Apontador primeiro;
        Apontador ultimo;
        int tamanho = 0;
    };

    void CriaListaVazia(Lista *lista);
    bool VerificaListaVazia(Lista *lista);
    int TamanhoLista(Lista *lista);
    void AtualizaUltimo(Lista *lista);

    void InsereListaPrimeiro(Lista *lista, Item *item);
    void InsereListaAposElemento(Lista *lista, Item *item, int id);
    void InsereListaUltimo(Lista *lista, Item *item);

    void ImprimeLista(Lista lista);
    Apontador PesquisaItem(Lista *lista, int id);
    void ImprimeItemRecebido(Item item);
    void ImprimeItemRecebidoComProjetos(Item item);
    void ImprimeContraCheque(Item item);

    void RemoveListaPrimeiro(Lista *lista);
    void RemoveListaUltimo(Lista *lista);
    void RemoveItemPorId(Lista *lista, int id);
    int RemoveItemsSemProjetos(Lista *lista);
    void DesalocaLista(Lista *lista);
}

#endif