#include "Ferramenta.h"

Ferramenta::Ferramenta(string nome, double custoDiario) : Recurso(nome)
{
    if (custoDiario < 0)
        throw new invalid_argument ("Erro: RF Custo Negativo,");
    this->custoDiario = custoDiario;
}

Ferramenta::~Ferramenta()
{

}

double Ferramenta::getCustoDiario()
{
    return custoDiario;
}

double Ferramenta::getCusto(int dias)
{
    if (dias <= 0)
        throw new invalid_argument ("Erro: RF Quantidade de dias <= 0.");

    custo = dias * custoDiario;
    return custo;
}

void Ferramenta::imprimir()
{
    cout << "Ferramenta: ";
    cout << nome;
    cout << " - R$";
    cout << custoDiario;
    cout << " por dia";
}


