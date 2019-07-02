#include "PersistenciaDeProjeto.h"
#include <fstream>
#include "Projeto.h"
#include "Atividade.h"
#include "AtividadeDeEsforcoFixo.h"
#include "AtividadeDePrazoFixo.h"
#include "Recurso.h"
#include "Ferramenta.h"
#include "Pessoa.h"

PersistenciaDeProjeto::PersistenciaDeProjeto()
{
    //ctor
}

PersistenciaDeProjeto::~PersistenciaDeProjeto()
{
    //dtor
}

Projeto* PersistenciaDeProjeto::carregar(string arquivo)
{
    ifstream input;
    input.open (arquivo);

    if (input.fail())
        throw new ErroDeArquivo ("Erro: PP Arquivo nao encontrado");

    string nomeProjeto;
    input >> nomeProjeto;

    Projeto *p = new Projeto (nomeProjeto);

    int numeroDeRecursos;
    input >> numeroDeRecursos;

    string tipoDeRecurso;
    for (int i = 0; i < numeroDeRecursos; i++) {
        input >> tipoDeRecurso;

        if (tipoDeRecurso == "P"){
            string nomeDaPessoa;
            input >> nomeDaPessoa;

            bool recebeHoras = false;
            double valorPorHora;
            input >> valorPorHora;

            if (valorPorHora == -1)
                recebeHoras = true;

            int horasDiarias;
            input >> horasDiarias;
            Pessoa *pessoa;
            if (!recebeHoras)
                pessoa = new Pessoa
                    (nomeDaPessoa,valorPorHora,horasDiarias);
            else
                pessoa = new Pessoa
                    (nomeDaPessoa, horasDiarias);

            p->adicionar(pessoa);
        }
        else if (tipoDeRecurso == "F"){
            string nomeDaFerramenta;
            input >> nomeDaFerramenta;

            double custoDiario;
            input >> custoDiario;

            Ferramenta *f = new Ferramenta(nomeDaFerramenta, custoDiario);
            p->adicionar(f);
        }
    }

    int numeroDeAtividades;
    input >> numeroDeAtividades;

    for (int i = 0; i < numeroDeAtividades; i++) {
        string tipoDeAtividade;
        input >> tipoDeAtividade;

        string nomeDaAtividade;
        if (tipoDeAtividade == "E"){
            input >> nomeDaAtividade;

            int horasNecessarias;
            input >> horasNecessarias;

            bool estaTermindada = NULL;
            string terminada;
            input >> terminada;
            if (terminada == "T")
                estaTermindada = true;
            else if (terminada == "N")
                estaTermindada = false;

            AtividadeDeEsforcoFixo *aE;
            if (estaTermindada) {
                int duracao;
                input >> duracao;
                aE = new AtividadeDeEsforcoFixo (nomeDaAtividade,horasNecessarias);
                aE->terminar(duracao);
                p->adicionar(aE);
            }
            else {
                aE = new AtividadeDeEsforcoFixo
                    (nomeDaAtividade,horasNecessarias);
                p->adicionar(aE);
            }
            int numeroDeRecursosAtividade;
            input >> numeroDeRecursosAtividade;
            for (int i = 0; i < numeroDeRecursosAtividade; i++) {
                string nomeDoRecurso;
                input >> nomeDoRecurso;
                list<Recurso*>::iterator j2 = p->getRecursos()->begin();
                for (unsigned int i2 = 0; i2 < p->getRecursos()->size(); i2++){
                    if (nomeDoRecurso == (*j2)->getNome())
                        aE->adicionar((*j2));
                    j2++;
                }
            }
        }

        else if (tipoDeAtividade == "P"){
            input >> nomeDaAtividade;

            int prazo;
            input >> prazo;

            bool estaTerminada = NULL;
            string terminada;
            input >> terminada;
            if (terminada == "T")
                estaTerminada = true;
            else if (terminada == "N")
                estaTerminada = false;
            AtividadeDePrazoFixo *aP;
            if (estaTerminada){
                int duracao;
                input >> duracao;
                aP = new AtividadeDePrazoFixo
                    (nomeDaAtividade,prazo);
                aP->terminar(duracao);
                p->adicionar(aP);
            }
            else {
                aP = new AtividadeDePrazoFixo
                    (nomeDaAtividade, prazo);
                p->adicionar(aP);
            }
            int numeroDeRecursosAtividade;
            input >> numeroDeRecursosAtividade;
            for (int i = 0; i < numeroDeRecursosAtividade; i++) {
                string nomeDoRecurso;
                input >> nomeDoRecurso;
                list<Recurso*>::iterator j2 = p->getRecursos()->begin();
                for (unsigned int i2 = 0; i2 < p->getRecursos()->size(); i2++){
                    if (nomeDoRecurso == (*j2)->getNome())
                        aP->adicionar((*j2));
                    j2++;
                }
            }
        }
    }
    input.close();
    return p;
}

void PersistenciaDeProjeto::salvar(Projeto* p, string arquivo)
{

    ofstream output;
    output.open (arquivo);

    if (output.fail())
        throw new ErroDeArquivo ("Erro: PP Arquivo nao pode ser escrito");

    output << p->getNome() << endl;
    output << p->getRecursos()->size() << endl;
    list<Recurso*>::iterator j = p->getRecursos()->begin();
    Ferramenta *recursoBool = new Ferramenta("null",1);
    for (unsigned int i = 0; i < p->getRecursos()->size(); i++){
        recursoBool = dynamic_cast<Ferramenta*>((*j));

        if (recursoBool == NULL) {//Pessoa
            Pessoa *recursoPessoa = dynamic_cast<Pessoa*>((*j));

            output << "P";
            output << " ";
            output << recursoPessoa->getNome();
            output << " ";
            if (recursoPessoa->recebeValorPadrao())
                output << -1 << " ";
            else
                output << recursoPessoa->getValorPorHora() << " ";

            output << recursoPessoa->getHorasDiarias();
            output << endl;
        }
        else {//Ferramenta
            Ferramenta *recursoFerramenta = dynamic_cast<Ferramenta*>((*j));

            output << "F";
            output << " ";
            output << recursoFerramenta->getNome();
            output << " ";
            output << recursoFerramenta->getCustoDiario();
            output << endl;
        }

        j++;
    }
    delete recursoBool;
    output << p->getAtividades()->size() << endl;
    vector<Atividade*>::iterator k = p->getAtividades()->begin();
    AtividadeDePrazoFixo *atividadeBool = new AtividadeDePrazoFixo("bool",1);
    for (unsigned int i = 0; i < p->getAtividades()->size(); i++){
        atividadeBool = dynamic_cast<AtividadeDePrazoFixo*>((*k));

        if (atividadeBool == NULL){// Atividade de Esforco Fixo
            AtividadeDeEsforcoFixo *atividadeEF = dynamic_cast<AtividadeDeEsforcoFixo*>((*k));

            output << "E ";
            output << atividadeEF->getNome() << " ";
            output << atividadeEF->getHorasNecessarias() << " ";
            if (atividadeEF->estaTerminada()) {
                output << "T ";
                output << atividadeEF->getDuracao() << endl;
            }
            else
                output << "N " << endl;

            output << atividadeEF->getQuantidadeDeRecursos() << endl;

            for (int i2 = 0; i2 < atividadeEF->getQuantidadeDeRecursos(); i2++){
                output << atividadeEF->getRecursos()[i2]->getNome() << " ";
            }
            output << endl;
        }

        else{ // Atividade de Prazo fixo
            AtividadeDePrazoFixo *atividadePF = dynamic_cast<AtividadeDePrazoFixo*>((*k));

            output << "P ";
            output << atividadePF->getNome() << " ";
            output << atividadePF->getPrazo() << " ";
            if (atividadePF->estaTerminada()) {
                output << "T ";
                output << atividadePF->getDuracao() << endl;
            }
            else
                output << "N " << endl;

            output << atividadePF->getQuantidadeDeRecursos() << endl;

            for (int i2 = 0; i2 < atividadePF->getQuantidadeDeRecursos(); i2++){
                output << atividadePF->getRecursos()[i2]->getNome() << " ";
            }
            output << endl;
        }
        k++;
    }
    output << endl;
    output.close();
}
