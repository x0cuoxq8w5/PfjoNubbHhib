#include <iostream>
#include <string>
#include <utility>
#include <vector>
#include <limits>

using std::cout;
using std::cin;
using std::endl;
using std::string;
using std::vector;
class astronauta {
public:
    string nome, cpf;
    int idade, status, missao;
    astronauta(string n, string c, int i) {
    nome = std::move(n);
    cpf = std::move(c);
    idade = i;
    status = 1; // 0 = morto, 1 = vivo
    missao = -1;
    }
    astronauta() {
        nome = "default";
        cpf = "default";
        idade = -1;
        status = 1; // 0 = morto, 1 = vivo
        missao = -1;
    } //não deve ocorrer a não ser que se algo esteja errado
    astronauta(astronauta const &a) {
        nome = a.nome;
        cpf = a.cpf;
        idade = a.idade;
        status = a.status;
        missao = a.missao;
    }
};
class missao {
public:
    int codigo;
    int estagio; //0 = planejamento, 1 = voo, 2 = explodiu, 3 = pousou
    vector<int> associados; //armazena a posição dos astronautas no vetor austronauta
    missao() {
        codigo = -1;
    }
    missao(int c) {
        codigo = c;
        estagio = 0;
    }
    missao(missao const &m) {
        codigo = m.codigo;
        estagio = m.estagio;
        associados = m.associados;
    }
};
int acharCPF(vector<astronauta> &a, string &cpfCheck) {
    for (int i = 0; i < a.size(); ++i) {
        if (a[i].cpf == cpfCheck) {
            return i;
        }
    }
    return -1;
}

template <typename T> void eliminarElemento(vector<T> &v, int ind) {
    for (int i = ind; i < v.size()-1; ++i) {
        v[i] = v[i+1];
    }
    v.pop_back();
}
template <typename T> bool checarVetor (vector<T> &v) {
    if (!v.empty()) {
        return true;
    }
    else {
        //cout << "Vetor vazio! Abortando." << endl;
        return false;
    }
}

astronauta cadastrarAstronauta(vector<astronauta> &a) {
    string nome, cpf;
    int idade;
    bool flag = true;
    cout << "Nome?" << endl;
    cin >> nome;
    /*if (nome == "SAIR") {
        return {}; //faz a mesma coisa que astronauta(), do que entendi joga os parâmetros dentro de {} no construtor do valor de retorno
    }*/
    while (flag) {
        cout << "CPF?" << endl;
        cin >> cpf;
        flag = false;
        for (auto & i : a) {
            if (i.cpf == cpf) {
                flag = true;
                cout << "CPF já em uso! Tente novamente.\n" << endl;
                break;
            }
        }
        if (cpf == "default") {
            flag = true;
            cout << "CPF reservado pelo sistema! Tente novamente." << endl;
        }
    }
    flag = true;
    while(flag) {
        cout << "Idade?" << endl;
        cin >> idade;
        flag = false;
        if (idade < 0 || cin.fail()) {
            cout << "Apenas inteiros positivos!" << endl;
            flag = true;
            cin.clear();
            cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        }
    }
    cin.clear();
    astronauta temp(nome, cpf, idade);
    return temp;
}
missao cadastrarVoo(vector<missao> &v){
    int codigo;
    bool flag = true;
    while (flag) {
        cout << "Código?" << endl;
        cin >> codigo;
        flag = false;
        if (codigo < 0 || cin.fail()) {
            cout << "Apenas inteiros positivos! Tente novamente." << endl;
            flag = true;
            cin.clear();
            cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        }
        for (auto & i : v) {
            if (i.codigo == codigo) {
                flag = true;
                cout << "Código já em uso! Tente novamente." << endl;
                break;
            }
        }
    }
    missao temp(codigo);
    return temp;
}
void listarVoos(vector<missao> &m, int estagio){
    for (auto & i : m) {
        if (i.estagio == estagio) {
            cout << i.codigo << endl;
        }
    }
}
void listarAstronautas(vector<astronauta> &a, int s, int m){
    //cout << "listarast" << endl;
    for (auto & i : a) {
        if (i.status == s && i.missao == m) {
            cout << i.nome << " - " << i.cpf << endl;
        }
    }
}
void listarAssociados(vector<astronauta> &a, missao &m){
    //cout << "listarass" << endl;
    for (int associado : m.associados) {
        cout << a[associado].nome << " - " << a[associado].cpf << endl;
    }
}
void addAstronauta(vector<astronauta> &a, vector<missao> &m){
    if (!checarVetor(a) || !checarVetor(m)) {
        return;
    }
    int cod, idM, idA;
    string cpf;
    bool flag = true;
    listarVoos(m, 0);
    cout << "Escolha um voo em planejamento" << endl;
    while (flag) {
        cin >> cod;
        for (int i = 0; i < m.size(); i++) {
            if (m[i].codigo == cod) {
                flag = false;
                idM = i;
                break;
            }
        }
        if(flag) {
            cout << "Nenhum voo com esse código! Tente novamente." << endl;
        }
        if (m[idM].estagio != 0) {
            cout << "Este voo não está em planejamento! Tente novamente." << endl;
            flag = true;
        }
        if (cod < 0 || cin.fail()) {
            cout << "Codigo não inteiro! Tenten novamente" << endl;
            flag = true;
            cin.clear();
            cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        }
    }
    //cout << "finalizou while" << endl;
    flag = true;
    listarAstronautas(a,1,-1); //checar se o astronauta já está na missão
    cout << "Selecione o astronauta a ser adicionado" << endl;
    while (flag) {
        cin >> cpf;
        for (int i = 0; i < a.size(); ++i) {
            if (a[i].cpf == cpf) {
                flag = false;
                idA = i;
                break;
            }
        }
        if (flag) {
            cout << "Nenhum Astronauta com esse CPF! Tente novamente." << endl;
        }
        if (a[idA].status == 0) {
            cout << "Este astronauta está morto! Tente novamente." << endl;
            flag = true;
        }
        else if (a[idA].missao != -1) {
            flag = true;
            cout << "Este astronauta está em outro voo! Tente novamente" << endl;
        }
        for (int associado : m[idM].associados) {
            if (idA == associado) {
                flag = true;
                cout << "Este astronauta já está neste voo! Tente novamente." << endl;
                break;
            }
        }
    }
    m[idM].associados.push_back(idA);
}
void removerAstronauta(vector<astronauta> &a, vector<missao> &m){
    if (!checarVetor(a) || !checarVetor(m)) {
        return;
    }
    int cod, idM, idA;
    string cpf;
    bool flag = true;
    listarVoos(m, 0);
    cout << "Escolha um voo em planejamento" << endl;
    while (flag) {
        cin >> cod;
        for (int i = 0; i < m.size(); i++) {
            if (m[i].codigo == cod) {
                flag = false;
                idM = i;
                break;
            }
        }
        if(flag) {
            cout << "Nenhum voo com esse código! Tente novamente." << endl;
        }
        if (m[idM].estagio != 0) {
            cout << "Este voo não está em planejamento! Tente novamente." << endl;
            flag = true;
        }
        if (cod < 0 || cin.fail()) {
            cout << "Codigo não inteiro! Tente novamente" << endl;
            flag = true;
            cin.clear();
            cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        }
    }

    flag = true;
    cout << "Escolha um astronauta para remover" << endl;
    listarAssociados(a, m[idM]);
    while (flag) {
        cin >> cpf;
        for (int i = 0; i < m[idM].associados.size(); ++i) {
            if (a[m[idM].associados[i]].cpf == cpf) {
                flag = false;
                idA = i;
                break;
            }
        }
        if (flag) {
            cout << "Nenhum Astronauta nesse voo com esse CPF! Tente novamente." << endl;
        }
    }
    eliminarElemento(m[idM].associados, idA);
}
void lancarVoo(vector<astronauta> &a, vector<missao> &m){
    bool flag = true;
    int cod, idM;
    if (!checarVetor(a) || !checarVetor(m)) {
        return;
    }
    listarVoos(m, 0);
    cout << "Escolha um voo em planejamento" << endl;
    while (flag) {
        cin >> cod;
        for (int i = 0; i < m.size(); i++) {
            if (m[i].codigo == cod) {
                flag = false;
                idM = i;
                break;
            }
        }
        if(flag) {
            cout << "Nenhum voo com esse código! Tente novamente." << endl;
        }
        if (m[idM].estagio != 0) {
            cout << "Este voo não está em planejamento! Tente novamente." << endl;
            flag = true;
        }
        if (cod < 0 || cin.fail()) {
            cout << "Codigo não inteiro! Tente novamente" << endl;
            flag = true;
            cin.clear();
            cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        }
    }
    for (int i = 0; i < m[idM].associados.size(); ++i) {
        a[m[idM].associados[i]].missao = idM;
    }
    m[idM].estagio = 1;
}
void finalizarVoo(vector<astronauta> &a, vector<missao> &m, vector<missao> &c) {
    missao aux;
    bool flag = true;
    int cod, pousar;
    if (!checarVetor(a) || !checarVetor(m)) {
        return;
    }
    cout << "Missões em voo:" << endl;
    listarVoos(m, 1);
    cout << "Qual missão deseja pousar?" << endl;
    while (flag) {
        cin >> pousar;
        for (int i = 0; i < m.size(); ++i) {
            if (pousar == m[i].codigo) {
                flag = false;
                cod = i;
                break;
            }
        }
        if (flag) {
            cout << "Código de voo inválido! Tente novamente." << endl;
        }
        if (m[cod].estagio != 1) {
            flag = true;
            cout << "Missão não está em voo! Tente novamente." << endl;
        }
        if (cod < 0 || cin.fail()) {
            cout << "Codigo não inteiro! Tente novamente" << endl;
            flag = true;
            cin.clear();
            cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        }
    }
    m[cod].estagio = 3;
    for (int associado : m[cod].associados) {
        a[associado].missao = -1;
    }
    aux = m[cod];
    eliminarElemento(m, cod);
    c.push_back(aux);
}
void explodir(vector<astronauta> &a, vector<missao> &m, vector<missao> &c){
    missao aux;
    if (!checarVetor(a) || !checarVetor(m)) {
        return;
    }
    bool flag = true;
    int cod, explodir;
    cout << "Missões em voo:" << endl;
    listarVoos(m, 1);
    cout << "Qual missão deseja explodir?" << endl;
    while (flag) {
        cin >> explodir;
        for (int i = 0; i < m.size(); ++i) {
            if (explodir == m[i].codigo) {
                flag = false;
                cod = i;
                break;
            }
        }
        if (flag) {
            cout << "Código de voo inválido! Tente novamente." << endl;
        }
        if (m[cod].estagio != 1) {
            flag = true;
            cout << "Missão não está em voo! Tente novamente." << endl;
        }
        if (cod < 0 || cin.fail()) {
            cout << "Codigo não inteiro! Tente novamente" << endl;
            flag = true;
            cin.clear();
            cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        }
    }
    m[cod].estagio = 2;
    for (int associado : m[cod].associados) {
        a[associado].status = 0;
    }
    aux = m[cod];
    eliminarElemento(m, cod);
    c.push_back(aux);
}
void listarTodosVoos(vector<astronauta> &a, vector<missao> &m, vector<missao> &c) {
    if (!checarVetor(a) || !(checarVetor(m) && checarVetor(c))) {
        return;
    }
    if (!checarVetor(m)) {
        cout << "Em planejamento: " << endl;
        for (int i = 0; i < m.size(); ++i) {
            if (m[i].estagio == 0) {
                cout << m[i].codigo << endl;
                cout << "Astronautas: " << endl;
                for (int j = 0; j < m[i].associados.size(); ++j) {
                    cout << a[i].nome << " - " << a[i].cpf << endl;
                }
            }
        }
        cout << "Em voo: " << endl;
        for (int i = 0; i < m.size(); ++i) {
            if (m[i].estagio == 1) {
                cout << m[i].codigo << endl;
                cout << "Astronautas: " << endl;
                for (int j = 0; j < m[i].associados.size(); ++j) {
                    cout << a[i].nome << " - " << a[i].cpf << endl;
                }
            }
        }
    }
    if (checarVetor(c)) {
        cout << "Concluídos: " << endl;
        for (int i = 0; i < c.size(); ++i) {
            cout << c[i].codigo << endl;
            if (c[i].estagio == 2) {
                cout << "Explodiu!" << endl;
            } else cout << "Pousou!" << endl;
            cout << "Astronautas: " << endl;
            for (int j = 0; j < c[i].associados.size(); ++j) {
                cout << a[i].nome << " - " << a[i].cpf << endl;
            }
        }
    }
}
void cemiterio(vector<astronauta> &a, vector<missao> &m){
    if (!checarVetor(a) || !checarVetor(m)) {
        return;
    }
    for (int i = 0; i < a.size(); ++i) {
        if (a[i].status == 0) {
            cout << a[i].nome << " - " << a[i].cpf << endl;
            cout << "Missões Participadas: " << endl;
            for (auto & j : m) {
                for (int k = 0; k < j.associados.size(); ++k) {
                    if (j.associados[k] == i) {
                        cout << j.codigo << endl;
                    }
                }
            }
        }
    }
}
int main() {
    int seletor = 0;
    vector<astronauta> astronautas;
    vector<missao> missoes;
    vector<missao> concluidas;
    astronauta ausaux;
    missao misaux;
    cout << "Bem vindo. Escolha uma das opções." << endl;
    while (seletor != 10) {
        cout << "1) Cadastrar Astronauta\n"
                "2) Cadastrar Voo\n"
                "3) Adicionar Astrtronauta a Voo\n"
                "4) Remover Astronauta de Voo\n"
                "5) Lançar Voo\n"
                "6) Finalizar Voo com Sucesso\n"
                "7) Explodir Voo\n"
                "8) Listar Voos\n"
                "9) Ver Cemitério\n"
                "10) Sair" << endl;
        cin >> seletor;
        switch (seletor) {
            case 1:
                ausaux = cadastrarAstronauta(astronautas);
                if (ausaux.cpf!="default") {
                    astronautas.push_back(ausaux);
                }
                break;
            case 2:
                misaux = cadastrarVoo(missoes);
                if (misaux.codigo!=-1) {
                    missoes.push_back(misaux);
                }
                break;
            case 3:
                addAstronauta(astronautas, missoes);
                break;
            case 4:
                removerAstronauta(astronautas, missoes);
                break;
            case 5:
                lancarVoo(astronautas, missoes);
                break;
            case 6:
                finalizarVoo(astronautas, missoes, concluidas);
                break;
            case 7:
                explodir(astronautas, missoes, concluidas);
                break;
            case 8:
                listarTodosVoos(astronautas, missoes, concluidas);
                break;
            case 9:
                cemiterio(astronautas, concluidas);
                break;
            case 10:
                break;
            default:
                cout << "Opção inválida!" << endl;
        }
    }
    return 0;
}
