#ifndef PROJETO_H
#define PROJETO_H
#define MAXIMO_ATIVIDADES 10
#define MAXIMO_RECURSOS 10
#include "Ferramenta.h"
#include "Pessoa.h"
#include "Atividade.h"
#include <string>
#include <iostream>
#include <vector>
#include <list>

using namespace std;

class Projeto
{
    public:
        Projeto(string nome);
        virtual ~Projeto();
        virtual string getNome();

        virtual void adicionar (Atividade* a);
        virtual vector<Atividade*>* getAtividades();
        virtual void adicionar (Recurso *r);
        virtual list<Recurso*>* getRecursos();

        virtual int getDuracao ();
        virtual int getDuracao(bool terminadas);
        virtual double getCusto ();
        virtual void imprimir ();

    protected:

    private:
        string nome;
        int quantidadeDeAtividades;
        int quantidadeDeRecursos;
        int duracao;
        double custo;
        vector <Atividade*> *atividades = new vector <Atividade*>;
        list <Recurso*> *recursos = new list <Recurso*>;
};

#endif // PROJETO_H

