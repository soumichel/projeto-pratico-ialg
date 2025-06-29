/*
===================================================
╦ ╦╔═╗╦  ╔═╗                          
║ ║╠╣ ║  ╠═╣  
╚═╝╚  ╩═╝╩ ╩                        
                                              __
Autores:                                      ||       
Lucas Gabriel Pereira Moreira.          ______||
Matrícula: 202110677.                  / ____ o|
                                      | / ;; \ |
Michel Alexandrino de Souza.          | ______ |
Matrícula: 202111084.                 ||______||
                                      || IALG ||
Turma 14A - Sistemas de Informação.   ||______||
                                      |'\[--]/'|
Trabalho prático de IALG 2021/1.      |  ¨''¨  |
                                      |  ''''  |
Trabalho Final.                       |        |
                                      |        |
Tema: Telefones e Smartphones.        |________|
                                     
===================================================
*/
#include <iostream>
#include <iomanip>
#include <string>
#include <fstream>
#include <ctime>

using namespace std;

struct itens {
    int ident;
    string nomeCod;
    string fabricante;
    int anoCriacao;
    string descricao;
};
itens celulares[100];
int cadastros = 0;

void cadastrar();
void interface();
void campos();
void pesquisa();
void altera();
void exclui();
void grava();

int digitos(int n) {
    int count = 0;
    while (n != 0) {
        n = n / 10;
        ++count;
    }
    return count;
}

void ordena(itens *lista) {
    for(int i = 1; i < cadastros; i++) {
        itens item = lista[i];
        int j = i;
        while(j > 0 and lista[j-1].anoCriacao > item.anoCriacao) {
            lista[j] = lista[j-1];
            j--;
        } 
        lista[j] = item; 
    }
}

void menu();

int busca_sequencial(itens lista[], string campo, string valor) {
    for(int i = 0; i < cadastros; i++) {
        itens celular=lista[i];
        if (campo == "nome") {
            if (celular.nomeCod==valor) {
                return i;
            }
        } else if(campo == "fab") {
            if(celular.fabricante==valor) {
                return i;
            }
        } else if(campo == "desc") {
            if(celular.descricao==valor){
                return i;
            }
        }
    }
    return -1;
}


int busca_binaria(itens lista[], int inicio, int fim, int ano){
    int i = (inicio + fim) / 2;
    if (inicio > fim) {
        return -1;
    }
    if (lista[i].anoCriacao == ano) {
        return i;
    }
    if (lista[i].anoCriacao < ano) {
        return busca_binaria(lista, i + 1, fim, ano);
    } else { 
        return busca_binaria(lista, inicio, i - 1, ano);
    }
}

void mudaNome(int i, string nome) {celulares[i].nomeCod=nome;}
void mudaFab(int i, string fabricante) {celulares[i].fabricante=fabricante;}
void mudaAno(int i,int ano) {celulares[i].anoCriacao=ano;}
void mudaDesc(int i, string desc) {celulares[i].descricao=desc;}

void listar_item(int i) {
    if (celulares[i].descricao != "apagado" and celulares[i].fabricante != "apagado" and celulares[i].nomeCod != "apagado" and celulares[i].anoCriacao != -999) {
        cout
        << setw(3)<<celulares[i].ident<<"|"<<setw(20) <<celulares[i].nomeCod <<"|"<< setw(20) << celulares[i].fabricante << "|"<< setw(4) << celulares[i].anoCriacao << endl
        << "--------------------------------------------------\n"
        << "DESCRICAO:"<< celulares[i].descricao << endl
        << "--------------------------------------------------\n";
    }
}

void listar(int inicio, int fim){
    cout 
    << "#################### LISTAGEM ####################\n"
    << "ID.|      NOME OU CODIGO|          FABRICANTE| ANO\n"
    << "==================================================\n";
    for(int i=inicio;i<fim;i++){   
        listar_item(i);
    }
    system("pause");
    menu();
}


void pesquisa () {
    campos();
    int op;
    bool ok=true;
    cout << "Selecione o campo a ser pesquisado (1-5): ";
    cin >> op;
    while(ok) {
        cout << "Conteudo da pesquisa: ";
        if(op==1) {
            string valor;
            cin.ignore();
            getline(cin, valor);
            int indice = busca_sequencial(celulares, "nome", valor);
            if(indice!=-1){
                listar(indice, indice+1);
                    ok=false;
            } else {
                cout << "Celular nao encontrado, tente novamente\a\n";
            }
        }
        if(op==2){
            string valor;
            cin.ignore();
            getline(cin, valor);
            int indice=busca_sequencial(celulares, "fab", valor);
            if(indice!=-1) {
                listar(indice, indice+1);
                ok=false;
            } else {
                cout << "Celular nao encontrado, tente novamente\a\n";
            }   
        }
        if(op==3) {
            int ano;
            cin >> ano;
            int indice=busca_binaria(celulares, 0, cadastros-1, ano);
            if(indice!=-1) {
                listar(indice, indice+1);
                ok=false;
            } else {
                cout << "Celular nao encontrado, tente novamente\a\n";
            }
            system("pause");
        }
        if(op==4) {
            string valor;
            cin.ignore();
            getline(cin, valor);
            int indice=busca_sequencial(celulares, "desc", valor);
            if(indice!=-1){
                listar(indice, indice+1);
                ok=false;
            } else {
                cout << "Celular nao encontrado, tente novamente\a\n";
            }
        } else {
            menu();
        }
    }
}

void altera () {
    campos();
    int op;
    bool ok=true;
    cout << "Campo que ira ser alterado (1-5): ";
    cin >> op;
    while(ok) {
        cout << "Digite o valor atual do campo que deseja alterar: ";
        if(op==1) {
            string valor;
            cin.ignore();
            getline(cin, valor);
            int indice=busca_sequencial(celulares, "nome", valor);
            if(indice!=-1){
                cout << "Novo valor para o campo: ";
                getline(cin, valor);
                mudaNome(indice,valor);
                ok=false;
                cout << "O item foi alterado!" << endl;
            } else {
                cout << "Celular nao encontrado, tente novamente\a\n";
            }
        }
        if(op==2){
            string valor;
            cin.ignore();
            getline(cin, valor);
            int indice=busca_sequencial(celulares, "fab", valor);
            if(indice!=-1){
                cout << "Novo valor para o campo: ";
                getline(cin, valor);
                mudaFab(indice, valor);
                ok=false;
                cout << "O item foi alterado!" << endl;
            } else {
                cout << "Celular nao encontrado, tente novamente\a\n";
            }
        }
        if(op==3){
            int ano;
            cin >> ano;
            int indice=busca_binaria(celulares, 0, cadastros-1, ano);
            if(indice!=-1){
                cout << "Novo valor para o campo: ";
                cin >> ano;
                mudaAno(indice, ano);
                ok=false;
                cout << "O item foi alterado!" << endl;
            } else {
                cout << "Celular nao encontrado, tente novamente\a\n";
            }
        }
        if(op==4){
            string valor;
            cin.ignore();
            getline(cin, valor);
            int indice=busca_sequencial(celulares, "desc", valor);
            if(indice!=-1) {
                cout << "Novo valor para o campo: ";
                getline(cin, valor);
                mudaDesc(indice, valor);
                ok=false;
                cout << "O item foi alterado!" << endl;
            } else {
                cout << "Celular nao encontrado, tente novamente\a\n";
            }
        } else {
            cout << endl;
            system("pause");
            menu();
        }
    }
}

void exclui () {
    string item;
    int op, retornoDelete;
    system("cls");
    cout << "Para excluir um item do banco, pesquise a partir de uma das seguintes opcoes: \n"
    << "\n##########################################\n"
    "# [1]NOME # [2]FABRICANTE # [3]DESCRICAO #\n"
    "##########################################\n";
    cin >> op;
    if (op==1) {
        cout << "Qual o nome ou codigo do produto a ser excluido? ";
        getline(cin >> ws, item);
        retornoDelete = busca_sequencial(celulares, "nome", item);
    } else if (op==2) {
        cout << "Qual o fabricante do produto a ser excluido? ";
        getline(cin >> ws, item);
        retornoDelete = busca_sequencial(celulares, "fab", item);
    } else if (op==3) {
        cout << "Qual a descricao do produto a ser excluido? ";
        getline(cin >> ws, item);
        retornoDelete = busca_sequencial(celulares, "desc", item);
    }
    if (retornoDelete < 0) {
        cout << "Dado nao encontrado!" << endl;
        system("pause");
        menu();
    } else {
        char opcao;
        cout <<
        "\n| IDENTIFICADOR: " << celulares[retornoDelete].ident << endl
        << "| NOME/CODIGO:" << celulares[retornoDelete].nomeCod << endl
        << "| FABRICANTE: " << celulares[retornoDelete].fabricante << endl
        << "| ANO DE CRIACAO: " << celulares[retornoDelete].anoCriacao << endl
        << "| DESCRICAO: " << celulares[retornoDelete].descricao  << endl << endl;
        cout << "Deseja mesmo excluir o item acima? (S/N) \a";
        cin >> opcao;
        if (opcao == 'S' or opcao == 's') {
            celulares[retornoDelete].nomeCod = "apagado";
            celulares[retornoDelete].fabricante = "apagado";
            celulares[retornoDelete].descricao = "apagado";
            celulares[retornoDelete].anoCriacao = -999;
            cout << "O ITEM FOI REMOVIDO DO SISTEMA!\n";
            system("pause");
            menu();
        } else {
            menu();
        }
    }
}

void grava () {
    //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    // declaring argument of time()
    time_t my_time = time(NULL);
    //
    // ctime() used to give the present time
    //cout << ctime(&my_time);
    ////// trecho de código do website GeeksForGeeks. Disponivel em: www.geeksforgeeks.org/print-system-time-c-3-different-ways/
    
    char op;
    cout << "DESEJA GRAVAR OS DADOS NA MEMORIA SECUNDARIA? (S/N)" << endl;
    cin >> op;
    if (op == 'S' or op == 's') {
        ordena(celulares);
        string nomeArq;
        cout << "\nEscreva APENAS O NOME que voce quer dar ao arquivo de dados. \nEle sera salvo na mesma pasta que este codigo-fonte.\n"
        "Se o arquivo ja existir os dados serao adicionados ao antigo, caso contrario um novo sera criado." 
        << endl;
        getline(cin >> ws, nomeArq);
        nomeArq += ".txt";
        ofstream saida (nomeArq.c_str(), fstream::app);
        if (saida) {
            saida << "GRAVADO EM: "<< ctime(&my_time)
            << "==================================================\n"
            << "#################### LISTAGEM ####################\n"
            << "ID.|      NOME OU CODIGO|          FABRICANTE| ANO\n"
            << "==================================================\n";
            for(int i=0;i<cadastros;i++){   
                saida << setw(3)<<celulares[i].ident<<"|"<<setw(20) <<celulares[i].nomeCod <<"|"<< setw(20) << celulares[i].fabricante << "|"<< setw(4) << celulares[i].anoCriacao << endl
                << "--------------------------------------------------\n"
                << "DESCRICAO:"<< celulares[i].descricao << endl
                << "--------------------------------------------------\n";
            }
            saida << "\n\n\n";
        }
        
    }
    system("pause");
    menu();
}

void menu () {
    system("cls");
    int opcao;
    itens celular[100];
    cout << "Veja abaixo o menu principal  deste  banco \nde dados. Para  prosseguir escolha um numero dentre\nas alternativas abaixo:" << endl << endl;
    interface();
    cout << "O que deseja fazer? ";
    bool check = true;
    while (check == true) {
        cin >> opcao;
        if (opcao > 0 and opcao < 7) {
            switch (opcao) {
                case 1: 
                    cadastrar();
                    break;
                case 2:
                    if (cadastros == 0) {
                        cout 
                        << "\n[==========================================================]"
                        << "\n|            NENHUM ITEM ARMAZENADO NA MEMORIA             |"
                        << "\n[==========================================================]\a" 
                        << endl;
                        listar(0, cadastros);
                    }
                    listar(0, cadastros);
                    break;
                case 3:
                    pesquisa();   
                    break;
                case 4:
                    altera();
                    break;
                case 5:
                    exclui();
                    break;
                case 6:
                    grava();
                    break;
            }
        } else if (opcao==7) {
            cout << "FALHA AO SAIR TENTE NOVAMENTE" << endl; 
            check = false;
        }
    }
}


void cadastrar () {
    if(cadastros==100) {
        cout 
        << "\n[========================================================================================]"
        << "\n| Nao e possivel realizar mais cadastros, a quantidade de dados na memoria foi excedida. |"
        << "\n[========================================================================================]\a"
        << endl;
        system("pause");
        menu();
    } else if(cadastros==99) {
        cout 
        << "\n[=========================================================]"
        << "\n| O proximo cadastro sera o ultimo disponivel na memoria! |"
        << "\n[=========================================================]\a" 
        << endl;
    }
    string testar;
    itens celular;
    celular.ident=cadastros+1;
    bool tudoOK = true;   
    while (tudoOK == true) {
        cout << "\nDigite agora o nome ou o codigo do aparelho (ate 20 caracteres): ";
        getline(cin >> ws, celular.nomeCod);
        testar = celular.nomeCod;
        if (testar.size() <= 20) {
            tudoOK = false;
            cout << "\nDado cadastrado com sucesso!\n" << endl;
        } else if (testar.size() > 20) {
            cout << "\nDado nao cadastrado, o numero de caracteres\nmaximo permitido foi excedido. Tente novamente\n";
        }
    }
    tudoOK = true;
    while (tudoOK == true) {
        cout << "\nDigite agora o fabricante do aparelho (ate 20 caracteres): ";
        getline(cin >> ws, celular.fabricante);
        testar = celular.fabricante;
        if (testar.size() <= 20) {
            tudoOK = false;
            cout << "\nDado cadastrado com sucesso!\n" << endl;
        } else if (testar.size() > 20) {
            cout << "\nDado nao cadastrado, o numero de caracteres\nmaximo permitido foi excedido. Tente novamente\a\n";
        }
    }
    tudoOK = true;
    while (tudoOK == true) {
        cout << "Digite agora o ano de criacao do aparelho (AAAA): ";
        cin >> celular.anoCriacao;
        if (digitos(celular.anoCriacao)<=4) {
            tudoOK = false;
            cout << "\nDado cadastrado com sucesso!\n" << endl;
        }
        if (!cin) {
            cout << "\nExiste um caractere nao numerico na sua entrada. \a\n";
        }
        if (tudoOK == true) {
            cout << "Tente novamente\a" << endl;
        }
    }
    tudoOK = true;
    while (tudoOK == true) {
        cout << "Digite agora a descricao do aparelho (ate 40 caracteres): ";
        getline(cin >> ws, celular.descricao);
        testar = celular.descricao;
        if (testar.size() <= 40) {
            tudoOK = false;
            cout << "\nDado cadastrado com sucesso!\n" << endl;
        } else if (testar.size() > 40) {
            cout << "\nDado nao cadastrado, o numero de caracteres\nmaximo permitido foi excedido. Tente novamente\a\n";
        }
    }
    celulares[cadastros]=celular;
    cadastros++;
    ordena(celulares);
    cout << "Todos os dados estao corretos, telefone cadastrado com sucesso!" << endl;
    cout << "Deseja cadastrar outro telefone? (S/N) ";
    char opcao;
    cin >> opcao;
    if(opcao=='s' or opcao=='S'){
        cadastrar();
    }
    system("pause");
    cin.ignore();
    menu();
}

int main () {
    string nome;
    cout << "Para iniciar digite seu primeiro nome: ";
    cin >> nome;
    cout << "\nOla, " << nome << ", bem vindo(a). Este programa ira lhe auxiliar\na organizar sua lista de smartphones e telefones.\n";
    cout << "\nPara navegar entre os menus basta utilizar o teclado numerico\nou as teclas \"S/s\" para SIM ou \"N/n\" para NAO, quando requisitado.\n\n";
    system("pause");
    menu();
    return 0;
}

void interface () {
    cout 
    << "       _________________________________   \n"
    << "      |#################################|  \n" 
    << "     |############## MENU ###############| \n"
    << "     |###################################| \n"
    << "     |#                                 #| \n"
    << "     |#                                 #| \n"
    << "     |#                                 #| \n"
    << "     |#  [1] cadastrar    [2] listar    #| \n"
    << "     |#                                 #| \n"
    << "     |#                                 #| \n"
    << "     |#  [3] procurar     [4] alterar   #| \n"
    << "     |#                                 #| \n"
    << "     |#                                 #| \n"
    << "     |#  [5] excluir      [6] gravar    #| \n"
    << "     |#                                 #| \n"
    << "     |#                                 #| \n"
    << "     |#                                 #| \n"
    << "     |###################################| \n"
    << "     |############ [7] sair #############| \n"
    << "      |#################################|  \n"
    << endl;
    }

void campos() {
    cout 
    << "       _________________________________   \n"
    << "      |#################################|  \n" 
    << "     |############## MENU ###############| \n"
    << "     |###################################| \n"
    << "     |#                                 #| \n"
    << "     |#                                 #| \n"
    << "     |#                                 #| \n"
    << "     |#  [1] Nome       [2] Fabricante  #| \n"
    << "     |#                                 #| \n"
    << "     |#                                 #| \n"
    << "     |#  [3] Criacao    [4] Descricao   #| \n"
    << "     |#                                 #| \n"
    << "     |#                                 #| \n"
    << "     |#                                 #| \n"
    << "     |###################################| \n"
    << "     |############ [5] sair #############| \n"
    << "      |#################################|  \n"
    << endl;
}
