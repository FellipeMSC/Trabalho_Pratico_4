#include "./FuncoesMain.hpp"

using namespace circularDuplamenteEncadeada;

// Preenche algumas linhas automaticamente
void preencheAutomatico(encadeada::Lista* linhas, int* id) {
    encadeada::Item linha;
    linha.id = *id;
    *id += 1;

    linha.nomeLinha = "SJE-BH";
    linha.companhia = "Sanitur";

    criaListaVazia(&linha.paradas);

    Item parada;

    parada.id = linha.idParada;
    linha.idParada++;
    parada.horarioChegada = "00:10";
    parada.horarioSaida = "00:25";
    parada.nomeCidade = "SJE";
    parada.preco = 0;
    insereItemUltimo(&linha.paradas, parada);


    parada.id = linha.idParada;
    linha.idParada++;
    parada.horarioChegada = "00:45";
    parada.horarioSaida = "01:00";
    parada.nomeCidade = "GNH";
    parada.preco = 16;
    insereItemUltimo(&linha.paradas, parada);

    parada.id = linha.idParada;
    linha.idParada++;
    parada.horarioChegada = "04:00";
    parada.horarioSaida = "04:15";
    parada.nomeCidade = "ITA";
    parada.preco = 16;
    insereItemUltimo(&linha.paradas, parada);

    parada.id = linha.idParada;
    linha.idParada++;
    parada.horarioChegada = "05:15";
    parada.horarioSaida = "05:30";
    parada.nomeCidade = "BH";
    parada.preco = 16;
    insereItemUltimo(&linha.paradas, parada);

    encadeada::InsereListaUltimo(linhas, &linha);
}

// A opção 1 do menu principal, procura linhas de onibus por meio de um ID ou por meio das cidades de origem e destino
void procuraLinhaOnibus(encadeada::Lista* linhas) {
    system("cls");  
    int opcao;

    while(opcao != 1 && opcao != 2 && opcao != 3) {
        cout << "|----------------------------------------|" << endl;
        cout << "|   1. Procurar por cidade               |" << endl;
        cout << "|----------------------------------------|" << endl;
        cout << "|   2. Procurar por codigo               |" << endl;
        cout << "|----------------------------------------|" << endl;
        cout << "|   3. Sair                              |" << endl;
        cout << "|----------------------------------------|" << endl;
        cin >> opcao;
    }

    if(opcao == 3) {
        cout << "Voltando ao menu principal" << endl;
        return;
    }

    system("cls");
    
    // Encontrar linha de onibus por cidades
    if(opcao == 1) {
        int rotas = 0; // Usada como orientação de erro caso não encontre nenhuma linha.

        float preco = 0; // Armazena o valor total da passagem

        bool encontrouOrigem = false; // Usada como orientação de erro, caso não encontre a origem nenhuma vez no sistema
        bool encontrouDestino = false; // Usada como orientação de erro, caso não encontre o destino nenhuma vez no sistema

        string origem; // Armazena a cidade de origem desejada
        string destino; // Armazena a cidade de destino desejada

        encadeada::Apontador linha = linhas->primeiro->prox;

        Apontador aDestino;
        Apontador aOrigem;

        cout << "Digite a cidade de origem: ";
        cin >> origem;
        cout << "Digite a cidade de destino: ";
        cin >> destino;

        // Percorre todas a linhas
        while(linha != NULL) {

            aDestino = linha->item.paradas.primeiro->prox;

            // Percorre todas as paradas
            while(aDestino != linha->item.paradas.primeiro) {
                
                // Encontra a cidade de destino
                if(aDestino->item.nomeCidade == destino) {
                    encontrouDestino = true;
                    aOrigem = aDestino;
                    preco = 0;

                    // A partir da cidade de destino, procura a cidade de origem
                    while(aOrigem != linha->item.paradas.primeiro) {

                        // Encontra a cidade de origem
                        if(aOrigem->item.nomeCidade == origem) {
                            rotas++;
                            encontrouOrigem = true;

                            encadeada::ImprimeItemRecebido(linha->item);
                            cout << "Horario de saida: " << aOrigem->item.horarioSaida << endl;
                            cout << "Horario de chegada: " << aDestino->item.horarioChegada << endl;
                            cout << "Preco da passagem: " << preco << endl;
                            cout << "----------------------------" << endl;
                            
                        }
                        preco += aOrigem->item.preco;
                        aOrigem = aOrigem->ante;
                    }

                }

                aDestino = aDestino->prox;
            }

            linha = linha->prox;
        }

        // Mensagens de orientação de erro
        if(!encontrouOrigem) {
            cout << "A cidade de origem não está cadastrada no sistema" << endl;
        }
        if(!encontrouDestino) {
            cout << "A cidade de destino não está cadastrada no sistema" << endl;
        }
        if(rotas == 0 && !encontrouDestino && !encontrouOrigem) {
            cout << "Nenhuma linha encontrada com as cidades desejadas" << endl;
        }
        return;
    }

    // Encontrar linha de onibus por ID
    cout << "Digite o ID da linha desejada: ";
    cin >> opcao;

    encadeada::Apontador aux;
    aux = encadeada::PesquisaItem(linhas, opcao);

    if(aux == NULL) {
        cout << "Linha nao encontrada!";
        return;
    }

    // Imprime a linha inteira
    encadeada::ImprimeItemRecebido(aux->item);
    cout << endl << "---Cidades que a linha passa---" << endl << endl;
    imprimeLista(&aux->item.paradas);
}

// Imprime o menu da manutenção
void imprimeMenuManutencao() {
    cout << "|------------------------------------|" << endl;
    cout << "|         Menu De Manutencao         |" << endl;
    cout << "|------------------------------------|" << endl;
    cout << "|   1. Incluir Nova Linha            |" << endl;
    cout << "|------------------------------------|" << endl;
    cout << "|   2. Incluir Nova Parada na Linha  |" << endl;
    cout << "|------------------------------------|" << endl;
    cout << "|   3. Alterar uma Parada            |" << endl;
    cout << "|------------------------------------|" << endl;
    cout << "|   4. Eliminar uma Parada           |" << endl;
    cout << "|------------------------------------|" << endl;
    cout << "|   5. Eliminar uma linha            |" << endl;
    cout << "|------------------------------------|" << endl;
    cout << "|   6. Imprimir todas as linhas      |" << endl;
    cout << "|------------------------------------|" << endl;
    cout << "|   7. Sair                          |" << endl;
    cout << "|------------------------------------|" << endl;
}

// Inclui uma nova linha no sistema
void incluirNovaLinha(encadeada::Lista* linhas, int* id) {
    encadeada::Item novaLinha;
    novaLinha.id = *id;
    
    cout << "Digite a companhia da linha: ";
    cin >> novaLinha.companhia;

    cout << "Digite o nome da linha: ";
    cin >> novaLinha.nomeLinha;
    criaListaVazia(&novaLinha.paradas);

    encadeada::InsereListaUltimo(linhas, &novaLinha);

    system("cls");
    encadeada::ImprimeItemRecebido(novaLinha);
    cout << endl << "Linha inserida com sucesso" << endl;
    *id += 1;
}

// Inclui uma nova parada em uma linha especifica
void incluirNovaParada(encadeada::Lista* linhas) {
    int id;

    cout << "Digite o ID da linha na qual deseja incluir uma nova parada: ";
    cin >> id;

    encadeada::Apontador linha = encadeada::PesquisaItem(linhas, id);
    if(linha == NULL) {
        cout << "O ID digitado nao corresponde a nenhuma linha cadastrada" << endl;
        return;
    }

    Item parada;
    parada.id = linha->item.idParada;
    linha->item.idParada++;

    cout << "Digite o nome da cidade: ";
    cin >> parada.nomeCidade;
    cout << "Digite o horario de chegada do onibus na cidade: ";
    cin >> parada.horarioChegada;
    cout << "Digite o horario de saida do onibus da cidade: ";
    cin >> parada.horarioSaida;
    cout << "Digite o preco da passagem: ";
    cin >> parada.preco;

    system("cls");
    if(listaVazia(&linha->item.paradas)) {
        cout << "Essa linha nao possui paradas" << endl;
        cout << "Parada inserida" << endl;
        insereItemUltimo(&linha->item.paradas, parada);
        return;
    }

    imprimeLista(&linha->item.paradas);
    cout << "Digite o ID da parada na qual deseja inserir a nova parada" << endl;
    cout << "(Digite 0 para incluir no começo)" << endl;
    cin >> id;

    if(id == 0) {
        insereItemPrimeiro(&linha->item.paradas, parada);
        cout << "Parada inserida" << endl;
        return;
    }

    insereItemAposElemento(&linha->item.paradas, parada, id);
}
    
// Altera uma parada de uma linha especifica
void alterarParada(encadeada::Lista* linhas) {
    int id;

    cout << "Digite o ID da linha na qual deseja alterar uma parada: ";
    cin >> id;

    encadeada::Apontador linha = encadeada::PesquisaItem(linhas, id);
    if(linha == NULL) {
        cout << "O ID digitado nao corresponde a nenhuma linha cadastrada" << endl;
        return;
    }

    if(listaVazia(&linha->item.paradas)) {
        cout << "Essa linha nao possui paradas" << endl;
        return;
    }

    imprimeLista(&linha->item.paradas);
    cout << "Digite o ID da parada que deseja alterar: ";
    cin >> id;

    Apontador parada = localizaItemPorId(&linha->item.paradas, id);
    if(parada == NULL) {
        cout << "O ID digitado nao corresponde a nenhuma parada cadastrada" << endl;
    }

    imprimeItem(parada->item);

    cout << "Digite o novo nome da cidade: ";
    cin >> parada->item.nomeCidade;
    cout << "Digite o novo horario de chegada do onibus na cidade: ";
    cin >> parada->item.horarioChegada;
    cout << "Digite o novo horario de saida do onibus da cidade: ";
    cin >> parada->item.horarioSaida;
    cout << "Digite o novo preco da passagem: ";
    cin >> parada->item.preco;

    cout << endl << "Parada alterada com sucesso" << endl;
}

// Exclui uma parada da linha desejada
void eliminarParada(encadeada::Lista* linhas) {
    int id;

    cout << "Digite o ID da linha na qual deseja eliminar uma parada: ";
    cin >> id;

    encadeada::Apontador linha = encadeada::PesquisaItem(linhas, id);
    if(linha == NULL) {
        cout << "O ID digitado nao corresponde a nenhuma linha cadastrada" << endl;
        return;
    }

    if(listaVazia(&linha->item.paradas)) {
        cout << "Essa linha nao possui paradas" << endl;
        return;
    }

    imprimeLista(&linha->item.paradas);
    cout << "Digite o ID da parada que deseja eliminar: ";
    cin >> id;

    Apontador parada = localizaItemPorId(&linha->item.paradas, id);
    if(parada == NULL) {
        cout << "O ID digitado nao corresponde a nenhuma parada cadastrada" << endl;
        return;
    }
    retiraItemPorId(&linha->item.paradas, id);
    cout << "Parada removida com sucesso" << endl;
}

// Exclui uma linha de onibus
void eliminarLinha(encadeada::Lista* linhas) {
    int id;

    cout << "Digite o ID da linha que deseja eliminar: ";
    cin >> id;

    encadeada::Apontador linha = encadeada::PesquisaItem(linhas, id);
    if(linha == NULL) {
        cout << "O ID digitado nao corresponde a nenhuma linha cadastrada" << endl;
        return;
    }
    encadeada::ImprimeItemRecebido(linha->item);
    encadeada::RemoveItemPorId(linhas, id);
    cout << endl << "Linha removida com sucesso" << endl;
}

// Menu de manutenção do programa, chama as funções necessarias para tal
void manutencaoDoPrograma(encadeada::Lista* linhas, int* id) {
    system("cls");
    int opcao;

    while(opcao != 7) {
        
        imprimeMenuManutencao();
        cin >> opcao;
        system("cls");
        switch(opcao) {
            case 1:
                incluirNovaLinha(linhas, id);
            break;

            case 2:
                incluirNovaParada(linhas);
            break;

            case 3:
                alterarParada(linhas);
            break;

            case 4:
                eliminarParada(linhas);
            break;

            case 5:
                eliminarLinha(linhas);
            break;

            case 6:
                encadeada::ImprimeLista(*linhas);
            break;
        }
        system("pause");
        system("cls");
    }
    cout << "Voltando ao menu principal" << endl;

}