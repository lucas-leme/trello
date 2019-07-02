#include "Pessoa.h"

#include <iostream>

using namespace std;

double Pessoa::valorPorHoraPadrao = 10;

void Pessoa::setValorPorHoraPadrao(double valor) {

    if (valor <= 0)
        throw new invalid_argument ("Erro: RP Valor <= 0.");

    Pessoa::valorPorHoraPadrao = valor;
}

double Pessoa::getValorPorHoraPadrao()
{
    return Pessoa::valorPorHoraPadrao;
}

Pessoa::Pessoa(string nome, double valorPorHora, int horasDiarias) :
    Recurso(nome){
        if (valorPorHora < 0)
            throw new invalid_argument ("Erro: RP Valor por hora negativo.");
        if (horasDiarias < 0)
            throw new invalid_argument ("Erro: RP Horas diarias negativa.");

        this->valorPorHora = valorPorHora;
        this->horasDiarias = horasDiarias;

        recebeuValorPadrao = false;
}

Pessoa::Pessoa(string nome, int horasDiarias) :
     Recurso (nome), horasDiarias (horasDiarias) {
        valorPorHora = getValorPorHoraPadrao();
        recebeuValorPadrao = true;
}

Pessoa::~Pessoa() {}

bool Pessoa::recebeValorPadrao()
{
    return recebeuValorPadrao;
}


double Pessoa::getValorPorHora() {
    return valorPorHora;
}

int Pessoa::getHorasDiarias() {
    return horasDiarias;
}

double Pessoa::getCusto(int dias) {

    if (dias <= 0)
        throw new invalid_argument ("Erro: RP Quantidade de dias <= 0.");

    if (recebeValorPadrao()) {
        custo = dias * getValorPorHoraPadrao() * horasDiarias;
        return custo;
    }
    else {
        custo = dias * getValorPorHora() * getHorasDiarias();
        return custo;
    }
}

void Pessoa::imprimir() {
    cout << nome;
    cout << " - ";
    cout << "R$";
    cout << valorPorHora;
    cout << " - ";
    cout << horasDiarias;
    cout << " ";
    cout << "por dia";
}
