#include <iostream>
#include "TAD_ListaEncadeada.hpp"

void encadeada::CriaListaVazia(Lista *lista)
{
        lista->primeiro = new Elemento;
        lista->ultimo = lista->primeiro;
        lista->ultimo->prox = NULL;
}

bool encadeada::VerificaListaVazia(Lista *lista)
{
    return (lista->primeiro == lista->ultimo);
}

int encadeada::TamanhoLista(Lista *lista)
{
    return lista->tamanho;
}

void encadeada::AtualizaUltimo(Lista *lista)
{
    Apontador aux;
    aux = lista->primeiro;
    while (aux->prox != NULL)
    {
        aux = aux->prox;
    }
    lista->ultimo = aux;
}

void encadeada::InsereListaPrimeiro(Lista *lista, Item *item)
{
    Apontador aux;
    aux = lista->primeiro->prox;
    lista->primeiro->prox = new Elemento;
    lista->primeiro->prox->prox = aux;
    lista->primeiro->prox->item = *item;
    lista->tamanho++;
    AtualizaUltimo(lista);
}

void encadeada::InsereListaUltimo(Lista *lista, Item *item)
{
    lista->ultimo->prox = new Elemento;
    lista->ultimo = lista->ultimo->prox;
    lista->ultimo->prox = NULL;
    lista->ultimo->item = *item;
    lista->tamanho++;
}

void encadeada::InsereListaAposElemento(Lista *lista, Item *item, int id)
{
    Apontador aux, pAux, x;
    bool find = false;
    pAux = lista->primeiro->prox;
    while (pAux != NULL)
    {
        if (pAux->item.id == id)
        {
            find = true;
            x = pAux;
            aux = x->prox;
            x->prox = new Elemento;
            x->prox->prox = aux;
            x->prox->item = *item;
            break;
        }
        pAux = pAux->prox; /* próxima célula */
    }
    if (find)
    {
        cout << "Item inserido com sucesso!";
        AtualizaUltimo(lista);
        lista->tamanho++;
    }
    else
    {
        cout << "Elemento anterior não encontrado na lista.";
    }
}

void encadeada::ImprimeLista(Lista lista)
{
    if (VerificaListaVazia(&lista))
    {
        cout << "Lista vazia!\n";
        return;
    }
    Apontador aux;
    aux = lista.primeiro->prox;
    while (aux != NULL)
    {
        ImprimeItemRecebido(aux->item);
    }
    system("pause");
}

encadeada::Apontador encadeada::PesquisaItem(Lista *lista, int id)
{
    Apontador aux;
    aux = lista->primeiro->prox;
    while (aux != NULL)
    {
        if (aux->item.id == id)
        {
            return aux;
        }
        aux = aux->prox;
    }
    return aux;
}

void encadeada::ImprimeItemRecebido(Item item) {
    cout << "Codigo: " << item.id << item.nomeLinha << endl;
    cout << "Companhia: " << item.companhia << endl;
}

void encadeada::RemoveListaPrimeiro(Lista *lista)
{
    if (VerificaListaVazia(lista))
    {
        return;
    }
    Apontador aux;
    aux = lista->primeiro->prox;
    lista->primeiro->prox = aux->prox;
    delete aux;
    lista->tamanho--;
}

void encadeada::RemoveListaUltimo(Lista *lista)
{
    if (VerificaListaVazia(lista))
    {
        return;
    }
    Apontador aux, atual;
    atual = lista->primeiro->prox;
    aux = lista->ultimo;
    while (atual->prox != lista->ultimo)
    {
        atual = atual->prox;
    }
    atual->prox = NULL;
    lista->ultimo = atual;
    delete aux;
    lista->tamanho--;
}

void encadeada::RemoveItemPorId(Lista *lista, int id)
{
    if (VerificaListaVazia(lista))
    {
        return;
    }

    Apontador aux, anterior, x;

    x = lista->primeiro;

    while (x != NULL)
    {
        if (x->prox->item.id == id)
        {
            anterior = x;
            break;
        }
        x = x->prox;
    }
    aux = anterior->prox;
    anterior->prox = aux->prox;
    delete aux;
    lista->tamanho--;
    AtualizaUltimo(lista);
}

void encadeada::DesalocaLista(Lista *lista) {
    Apontador aux, excluido;
    aux = lista->primeiro->prox;
    while(aux != NULL) {
        excluido = aux;
        aux = aux->prox;
        delete excluido;
    }
    delete aux;
}