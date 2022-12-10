#include <iostream>
#include "./FuncoesMain.cpp"


using namespace std;

int main() {
    int idLinhas = 1;
    int opcao;

    encadeada::Lista linhas;
    encadeada::CriaListaVazia(&linhas);
    preencheAutomatico(&linhas, &idLinhas);
    
    string senhaAdm = "NosDeTotalPfv";
    string senha;
    

    while(opcao != 3) {
        cout << "1. Procurar Linha de Onibus" << endl;
        cout << "2. Manutencao do Programa" << endl;
        cout << "3. Sair" << endl;
        cout << "Digite sua escolha: ";
        cin >> opcao;

        if(opcao == 1) {
            procuraLinhaOnibus(&linhas);
        } else if(opcao == 2) {
            cout << "Digite a senha de adminitrador: ";
            cin >> senha;
            if(senha == senhaAdm) {
                manutencaoDoPrograma(&linhas, &idLinhas);
            } else {
                cout << "Senha incorreta" << endl;
            }
        }
        system("pause");
        system("cls");  
    }

    return 0;
}