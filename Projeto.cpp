#include "Projeto.h"
#include <cmath>
#include <iostream>

using namespace std;

Projeto::Projeto(string nome) : nome (nome) {
    quantidadeDeAtividades = 0;
    quantidadeDeRecursos = 0;
}

Projeto::~Projeto()
{
    vector<Atividade*>::iterator j = atividades->begin();
    for (int i = 0; i < quantidadeDeAtividades; i++){
        atividades->erase(j);
        j++;
    }
    list<Recurso*>::iterator k = recursos->begin();
    for (int i = 0; i < quantidadeDeRecursos; i++){
        recursos->erase(k);
        k++;
    }
}

string Projeto::getNome() {
    return nome;
}

void Projeto::adicionar (Atividade* a) {
    if (atividades->size() == MAXIMO_ATIVIDADES)
        throw new overflow_error("Erro: PR Limite de atividades atingido");
    bool indHa = false;
    for (unsigned int i = 0; i < atividades->size(); i++) {
        if (atividades->begin()[i] == a)
            indHa = true;
    }
    if (!indHa && atividades->size() < MAXIMO_ATIVIDADES)
        atividades->push_back(a);
    else if (indHa)
        throw new invalid_argument ("Erro: PR Atividade ja adicionada");
    else
        throw new invalid_argument ("Erro: PR Locacao maxima de atividades");
}

void Projeto::adicionar (Recurso *r) {
    if (recursos->size() == MAXIMO_RECURSOS)
        throw new overflow_error ("Erro: PR Limite de recursos atingido");

    bool indHa = false;
    list<Recurso*>::iterator j = recursos->begin();
    for (unsigned int i = 0; i < recursos->size(); i++) {
        if (*j == r)
            indHa = true;
        j++;
    }
    if (recursos->size() < MAXIMO_RECURSOS && !indHa) {
        recursos->push_back(r);
    }
    else if (indHa)
        throw new invalid_argument ("Erro: PR Recurso ja adicionado");
    else
        throw new invalid_argument ("Erro: PR Locacao maxima de recursos");
}

int Projeto::getDuracao () {
    /*double somaDuracao = 0;
    vector<Atividade*>::iterator j = atividades->begin();
    for (unsigned int i = 0; i < atividades->size(); i++) {
        somaDuracao = somaDuracao + (*j)->getDuracao() ;
    }
    return somaDuracao;*/
    return (getDuracao(1)+getDuracao(0));
}

int Projeto::getDuracao(bool terminadas)
{
    double somaDuracao = 0;
    vector<Atividade*>::iterator j = atividades->begin();
    if (terminadas) {
        for (unsigned int i = 0; i < atividades->size(); i++) {
            if ((*j)->estaTerminada())
                somaDuracao = somaDuracao + (*j)->getDuracao();
            j++;
        }
        return somaDuracao;
    }
    else {
        for (unsigned int i = 0; i < atividades->size(); i++) {
            if (!(*j)->estaTerminada())
                somaDuracao = somaDuracao + (*j)->getDuracao();
            j++;
        }
        return somaDuracao;
    }
}

double Projeto::getCusto () {
    double somaCusto = 0;
    vector<Atividade*>::iterator j = atividades->begin();
    for (unsigned int i = 0; i < atividades->size(); i++) {
        somaCusto = somaCusto + (*j)->getCusto();
        j++;
    }
    custo = somaCusto;
    return custo;

}

void Projeto::imprimir () {
    cout << getNome();
    cout << " - ";
    cout << "R$" << getCusto() << endl;
    cout << "Duracao:" << endl;

    cout << " - ";
    cout << "Feito ";
    cout << getDuracao(1);
    cout << " dias" << endl;

    cout << " - ";
    cout << "Falta ";
    cout << getDuracao(0);
    cout << " dias" << endl;

    cout << " - ";
    cout << "Total ";
    cout << getDuracao();
    cout << " dias" << endl;

    cout << "----" << endl;
    vector<Atividade*>::iterator j = atividades->begin();
    for (unsigned int i = 0; i < atividades->size(); i++) {
        (*j)->imprimir();
        j++;
        cout << endl;
    }
}

vector<Atividade*>* Projeto::getAtividades(){
    return atividades;
}

list<Recurso*>* Projeto::getRecursos() {
    return recursos;
}
