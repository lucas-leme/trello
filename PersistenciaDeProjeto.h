#ifndef PERSISTENCIADEPROJETO_H
#define PERSISTENCIADEPROJETO_H
#include "Projeto.h"
#include "Atividade.h"
#include "Recurso.h"
#include <string>
#include <fstream>
#include "Ferramenta.h"
#include "Pessoa.h"
#include "AtividadeDeEsforcoFixo.h"
#include "AtividadeDePrazoFixo.h"
#include "ErroDeArquivo.h"

using namespace std;


class PersistenciaDeProjeto
{
    public:
        PersistenciaDeProjeto();
        virtual ~PersistenciaDeProjeto();

        Projeto* carregar  (string arquivo);
        void salvar (Projeto* p, string arquivo);

    protected:

    private:
        string arquivo;
};

#endif // PERSISTENCIADEPROJETO_H
