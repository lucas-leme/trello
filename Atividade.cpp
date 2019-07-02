#include "Atividade.h"
#include <cmath>

using namespace std;


Atividade::Atividade (string nome) : nome (nome) {
    quantidadeDeRecursos = 0;
    duracao = 0;
    custo = 0;
    duracaoReal = 0;
    estaTerminadaa = false;
}

Atividade::~Atividade()
{
    for (int i = 0; i < quantidadeDeRecursos - 1; i++)
        delete recursos[i];
    delete[] recursos;
}

string Atividade::getNome() {
    return nome;
}

void Atividade::adicionar(Recurso* r) {
    if (quantidadeDeRecursos >= MAX_RECURSOS)
        throw new overflow_error ("Erro: *A* Recursos maximo atingido.");
    else {

        for (int i = 0; i < quantidadeDeRecursos; i++) {
            if (getRecursos()[i] == r)
                throw new invalid_argument ("Erro: *A* Recurso ja adicionado.");
        }

        recursos[quantidadeDeRecursos] = r;
        quantidadeDeRecursos = quantidadeDeRecursos + 1;
    }

}

Recurso** Atividade::getRecursos() {
    return recursos;
}

int Atividade::getQuantidadeDeRecursos() {
    return quantidadeDeRecursos;
}

double Atividade::getCusto() {
    double somaCusto = 0;
    if (quantidadeDeRecursos == 0)
        return -1;
    for (int i = 0; i < quantidadeDeRecursos; i++) {
        somaCusto = somaCusto + recursos[i]->getCusto(getDuracao());
    }
    custo = somaCusto;

    return custo;

}

void Atividade::imprimir () {
    cout << getNome();
    cout << " - ";
    cout << getDuracao();
    cout << " dias - R$";
    cout << getCusto();
}

void Atividade::terminar(int duracaoReal)
{
    if (duracaoReal <= 0)
        throw new invalid_argument ("Erro: A Duracao invalida.");

    this->duracaoReal = duracaoReal;
    duracao = duracaoReal;
    estaTerminadaa = true;
}

bool Atividade::estaTerminada()
{
    return estaTerminadaa;
}
