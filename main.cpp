#include <iostream>
#include <vector>
using namespace std;

// Declarando a função exibirSaldo para evitar erro de compilação
void exibirSaldo(float saldo);

// Model - Classes
class Cliente {
private:
    string nome;
    int cpf;
public:
//constructor que pega nome e CPF do cliente
    Cliente(string n, int c) {
        nome = n;
        cpf = c;
    }
    string getNome() {
        return nome;
    }
    int getCpf() {
        return cpf;
    }
};

class Conta {
private:
    Cliente cliente; //objeto cliente
    float saldo;
public:
    Conta(Cliente c) : cliente(c) { // Construtor da classe Conta que recebe um objeto Cliente e inicializa o saldo como zero
        saldo = 0;
    }
    void transferir(Conta &destino, float valor) {
    if (this == &destino) {
        cout << "Não é possível transferir para a mesma conta." << endl;
        return;
    }
    if (valor <= 0) {
        cout << "Valor inválido para transferência." << endl;
        return;
    }
    if (saldo >= valor) {
        saldo -= valor;
        destino.depositar(valor);
        cout << "Transferência realizada com sucesso." << endl;
    } else {
        cout << "Saldo insuficiente." << endl;
    }
}
   
    void depositar(float valor) {
        saldo += valor;
    }
    void sacar(float valor) {
    if (saldo >= valor) {
        saldo -= valor;
    } else {
        cout << "Saldo insuficiente." << endl;
    }
}
    float getSaldo() {
        return saldo;
    }
    int getCpf() {
        return cliente.getCpf();
    }
};

class Agencia {
private:
    vector<Conta> contas; //Vetor que armazena as contas da agencia
public:
    void adicionarConta(Conta c) {
        contas.push_back(c);
    }
    Conta* getConta(int cpf) { //Ponteiro para uma conta com base no CPF do dono da conta
        for (int i = 0; i < contas.size(); i++) {
            if (contas[i].getCpf() == cpf) {
                return &contas[i];
            }
        }
        return nullptr; //Valor de ponteiro nulo
    }
};

class Controller {
public:
    void adicionarConta(Agencia& agencia, Conta& conta) {
        agencia.adicionarConta(conta); //Adiciona a conta para a agencia
    }

    void depositarValor(Agencia& agencia, int cpf, float valor) {
        Conta* conta = agencia.getConta(cpf);//Adiciona o CPF para a agencia
        if (conta != nullptr) {
            conta->depositar(valor);
        }
    }

    void exibirSaldoConta(Agencia& agencia, int cpf) { 
        Conta* conta = agencia.getConta(cpf); //Exibe o saldo conforme o CPF
        if (conta != nullptr) {
            exibirSaldo(conta->getSaldo());
        }
    }
};

// View - Funções de exibição
void exibirSaldo(float saldo) {
    cout << "Saldo: " << saldo << endl;
}

// Função Main como parte do Controller
int main() {
    Cliente c1("Jacisto Pinto", 123456789);
    Cliente c2("Dolores Fuertes", 987654321);
    Cliente c3("Hypotenusa Pereira", 836512789);
    Cliente c4("Frankstefferson", 281930450);
    Cliente c5("Jacisto Pinto", 402937106);
    Cliente c6("Sebastião Salgado Doce", 763829057);

    Conta conta1(c1);
    Conta conta2(c2);
    Conta conta3(c3);
    Conta conta4(c4);
    Conta conta5(c5);
    Conta conta6(c6);

    Agencia agencia;
    Controller controller;

    controller.adicionarConta(agencia, conta1);
    controller.adicionarConta(agencia, conta2);
    controller.adicionarConta(agencia, conta3);
    controller.adicionarConta(agencia, conta4);
    controller.adicionarConta(agencia, conta5);
    controller.adicionarConta(agencia, conta6);

    controller.depositarValor(agencia, 123456789, 1000.10);
    controller.depositarValor(agencia, 987654321, 500.50);
    controller.depositarValor(agencia, 123456789, 780.25);
    controller.depositarValor(agencia, 836512789, 50);
    controller.depositarValor(agencia, 281930450, 105.25);
    controller.depositarValor(agencia, 402937106, 95.99);
    controller.depositarValor(agencia, 763829057, 2500);

    controller.exibirSaldoConta(agencia, 123456789);
    controller.exibirSaldoConta(agencia, 987654321);
    controller.exibirSaldoConta(agencia, 836512789);
    controller.exibirSaldoConta(agencia, 281930450);
    controller.exibirSaldoConta(agencia, 402937106);
    controller.exibirSaldoConta(agencia, 763829057);
  
    cout << "" <<endl;
  
    conta1.transferir(conta2, 0); //transfere da primeira conta para a segunda
    conta2.transferir(conta3, 100000);
    conta4.transferir(conta3, -0.5);
    conta5.transferir(conta5, 10);
   
    cout << "" <<endl;
  
    controller.exibirSaldoConta(agencia, 123456789);
    controller.exibirSaldoConta(agencia, 987654321);
    controller.exibirSaldoConta(agencia, 836512789);
    controller.exibirSaldoConta(agencia, 281930450);
    controller.exibirSaldoConta(agencia, 402937106);
    controller.exibirSaldoConta(agencia, 763829057);

    return 0;
}
