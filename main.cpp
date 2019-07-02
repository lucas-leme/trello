#include "Recurso.h"
#include "Pessoa.h"
#include "Ferramenta.h"
#include "Projeto.h"
#include "Atividade.h"
#include "AtividadeDeEsforcoFixo.h"
#include "AtividadeDePrazoFixo.h"
#include "PersistenciaDeProjeto.h"
#include "ErroDeArquivo.h"

#include <iostream>

using namespace std;

void telaPrincipal ();

void opcaoUm (Projeto *p);

void opcaoDois (Projeto *p);
void adicionarRecurso (Projeto *p, Atividade *a);

void opcaoTres (Projeto *p);


int main () {

    string sOuN;
    PersistenciaDeProjeto *pP = new PersistenciaDeProjeto();
    while (1) {
        cout << "Deseja carregar um novo projeto (s/n)?";
        cin >> sOuN;
        if (sOuN == "s" || sOuN == "n")
            break;
    }
    Projeto *projeto;
    if (sOuN == "s"){
        try {
            string arquivo;
            cout << "Digite o nome do arquivo: ";
            cin >> arquivo;
            projeto = pP->carregar(arquivo);
        } catch (ErroDeArquivo *e){
            cout << e->what() << endl;
            return 0;
        }
    }
    else if (sOuN == "n"){
        string nomeDoProjeto;
        cout << "Digite o nome do projeto: ";
        cin >> nomeDoProjeto;
        projeto = new Projeto(nomeDoProjeto);
    }
    if (sOuN == "s" || sOuN == "n") {
        while (1) {
            int opcao;
            telaPrincipal();
            cin >> opcao;

            if (opcao == 1)
                opcaoUm(projeto);

            if (opcao == 2)
                opcaoDois(projeto);

            if (opcao == 3)
                opcaoTres(projeto);

            if (opcao == 4) {
                try {
                    projeto->imprimir();
                } catch (invalid_argument *e){
                    cout << e->what() << endl;
                } catch (logic_error *e) {
                    cout << e->what() << endl;
                }
            }
            if (opcao == 5) {
                try {
                    cout << "Valor atual: ";
                    cout << "R$";
                    cout << Pessoa::getValorPorHoraPadrao();
                    cout << " por hora" << endl;

                    cout << "Novo valor: ";
                    double valorPorHoraPadrao;
                    cin >> valorPorHoraPadrao;
                    Pessoa::setValorPorHoraPadrao(valorPorHoraPadrao);
                } catch (invalid_argument *e) {
                    cout << e->what() << endl;
                } catch (overflow_error *e) {
                    cout << e->what() << endl;
                } catch (logic_error *e) {
                    cout << e->what() << endl;
                }
            }

            if (opcao == 6) {
                string nomeArquivo;
                cout << "Nome do arquivo: ";
                cin >> nomeArquivo;

                pP->salvar(projeto, nomeArquivo);
            }

            if (opcao == 0)
                break;
        }
    }
    return 0;
}

void telaPrincipal() {
    cout << "1 - Adicionar recurso" << endl;
    cout << "2 - Adicionar atividade" << endl;
    cout << "3 - Terminar atividade" << endl;
    cout << "4 - Imprimir projeto" << endl;
    cout << "5 - Definir valor por hora padrao" << endl;
    cout << "6 - Salvar" << endl;
    cout << "0 - Sair" << endl;
    cout << "Escolha a opcao: " ;
}

void opcaoUm(Projeto *p) {
    try {
        string fOuP;
        while (fOuP != "f" && fOuP != "p") {
            cout << "Ferramenta (f) ou Pessoa (p): ";
            cin >> fOuP;
        }

        if (fOuP == "f") {
            string nomeDaFerramenta;
            cout << "Nome: ";
            cin >> nomeDaFerramenta;

            double custoDiario;
            cout << "Custo diario: ";
            cin >> custoDiario;

            Ferramenta *f = new Ferramenta(nomeDaFerramenta, custoDiario);
            p->adicionar(f);
        }
        else if (fOuP == "p") {
            string nomeDaPessoa;
            cout << "Nome: ";
            cin >> nomeDaPessoa;

            int horasDiarias;
            cout << "Horas diarias: ";
            cin >> horasDiarias;

            while (1) {
                string sOuN;
                cout << "Valor por horas padrao (s/n)? ";
                cin >> sOuN;

                if (sOuN == "n") {
                    double valorPorHora;
                    cout << "Valor por horas (em R$): ";
                    cin >> valorPorHora;
                    Pessoa *pessoa = new Pessoa
                        (nomeDaPessoa, valorPorHora, horasDiarias);
                    p->adicionar(pessoa);
                    break;
                }
                else if (sOuN == "s") {
                    Pessoa *pessoa = new Pessoa(nomeDaPessoa, horasDiarias);
                    p->adicionar(pessoa);
                    break;
                }
            }

        }
    } catch (invalid_argument *e) {
        cout << e->what() << endl;
    } catch (overflow_error *e) {
        cout << e->what() << endl;
    }
}

void opcaoDois(Projeto *p) {
    try {
        string nomeDaAtividade;
        cout << "Nome: ";
        cin >> nomeDaAtividade;

        string pOuT = "a";
        while (pOuT != "p" && pOuT != "t") {
            cout << "Prazo fixo (p) ou trabalho fixo (t)? ";
            cin >>pOuT;
        }

        if (pOuT == "p") {
            int diasNecessarios;
            cout << "Dias necessarios: ";
            cin >> diasNecessarios;
            AtividadeDePrazoFixo *aF = new AtividadeDePrazoFixo
                (nomeDaAtividade, diasNecessarios);
            p->adicionar(aF);
            adicionarRecurso(p, aF);
        }
        else if (pOuT == "t") {
            int horasNecessarias;
            cout << "Horas necessarias: ";
            cin >> horasNecessarias;
            AtividadeDeEsforcoFixo *aE = new AtividadeDeEsforcoFixo
                (nomeDaAtividade, horasNecessarias);
            p->adicionar(aE);
            adicionarRecurso(p, aE);

        }
    } catch (invalid_argument *e) {
        cout << e->what() << endl;
    } catch (overflow_error *e) {
        cout << e->what() << endl;
    }

}

void adicionarRecurso (Projeto *p, Atividade *a) {
        try {
            string sOuN;
            bool indSim = false;
            while (sOuN != "s" && sOuN != "n"){
                cout << "Deseja adicionar um recurso (s/n)? ";
                cin >> sOuN;
                if (sOuN == "s")
                    indSim = true;
            }

            int escolha;
            while (indSim) {
                Ferramenta *recuroBool = new Ferramenta("null",1);
                list<Recurso*>::iterator j = p->getRecursos()->begin();
                for (unsigned int i = 0; i < p->getRecursos()->size(); i++){
                    cout << i + 1;
                    cout << " - ";
                    recuroBool = dynamic_cast<Ferramenta*>((*j));
                    if (recuroBool == NULL){//Pessoa
                        Pessoa *recursoPessoa = dynamic_cast<Pessoa*>((*j));
                        cout << "Pessoa: ";
                        cout << recursoPessoa->getNome();
                        cout << " - ";
                        cout << "R$";
                        cout << recursoPessoa->getValorPorHora();
                        cout << " - ";
                        cout << recursoPessoa->getHorasDiarias();
                        cout << " por dia";
                        cout << endl;
                    }
                    else {// Ferramenta
                        Ferramenta *recursoFerramenta = dynamic_cast<Ferramenta*>((*j));
                        cout << "Ferramenta: ";
                        cout << recursoFerramenta->getNome();
                        cout << " - ";
                        cout << recursoFerramenta->getCustoDiario();
                        cout << " por dia";
                        cout << endl;
                    }
                    j++;
                }
                cout << "Escolha um recurso ou 0 para cancelar: ";
                cin >> escolha;
                if (escolha == 0)
                    break;
                j = p->getRecursos()->begin();
                for (int i = 0; i < escolha - 1; i++)
                    j++;
                a->adicionar((*j));
            }
        } catch (invalid_argument *e) {
            cout << e->what() << endl;
            adicionarRecurso(p,a);
        }
}

void opcaoTres (Projeto *p) {
    try {
        for (unsigned int i = 0; i < p->getAtividades()->size(); i++) {
            cout << i + 1;
            cout << " - ";
            cout << p->getAtividades()->begin()[i]->getNome();
            cout << endl;
        }
        int escolha;
        cout << "Escolha uma atividade ou 0 para cancelar: ";
        cin >> escolha;

        if(escolha != 0){
            if (p->getAtividades()->begin()[escolha-1]->estaTerminada())
                 cout << "Atividade ja terminada" << endl;
            else{
                int duracaoReal;
                cout << "Duracao real: ";
                cin >> duracaoReal;
                p->getAtividades()->begin()[escolha-1]->terminar(duracaoReal);
            }
        }
    } catch (invalid_argument *e) {
        cout << e->what() << endl;
    } catch (overflow_error *e) {
        cout << e->what() << endl;
    }
}
