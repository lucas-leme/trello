#include "AtividadeDePrazoFixo.h"

AtividadeDePrazoFixo::AtividadeDePrazoFixo(string nome, int dias) :
    Atividade (nome)
{
    if (dias <= 0)
        throw new invalid_argument ("Erro: *APF* Dias <= 0.");

    this->dias = dias;
}

AtividadeDePrazoFixo::~AtividadeDePrazoFixo()
{
    //dtor
}

int AtividadeDePrazoFixo::getPrazo () {
    return dias;
}

int AtividadeDePrazoFixo::getDuracao()
{
    if (estaTerminada()){
        return duracao;
    }
    else
        return getPrazo();
}
