#include "AtividadeDeEsforcoFixo.h"

AtividadeDeEsforcoFixo::AtividadeDeEsforcoFixo(string nome, int horasNecessarias) :
    Atividade(nome)
{
    if (horasNecessarias <= 0)
        throw new invalid_argument ("Erro: AEF Horas <= 0.");

    this->horasNecessarias = horasNecessarias;
}

AtividadeDeEsforcoFixo::~AtividadeDeEsforcoFixo()
{
    //dtor
}

int AtividadeDeEsforcoFixo::getHorasNecessarias () {
    return horasNecessarias;
}

int AtividadeDeEsforcoFixo::getDuracao()
{
    if (estaTerminada()){
        return duracao;
    }
    int somaDuracaoDiaria = 0;
    bool naoTemRecursos = false;
    for (int i = 0; i < getQuantidadeDeRecursos(); i++){
        Ferramenta *recursoBool = new Ferramenta ("bool",1);
        recursoBool = dynamic_cast<Ferramenta*>(getRecursos()[i]);
        if (recursoBool == NULL){
            naoTemRecursos = true;
            Pessoa *recursoPessoa = dynamic_cast<Pessoa*>(getRecursos()[i]);
            somaDuracaoDiaria =+ recursoPessoa->getHorasDiarias();
        }
    }
    if (naoTemRecursos == false)
        throw new logic_error ("Erro: AFF Nao ha recursos");
    if (ceil(horasNecessarias/somaDuracaoDiaria) == 0)
        return 1;
    return ceil(horasNecessarias/somaDuracaoDiaria);
}
