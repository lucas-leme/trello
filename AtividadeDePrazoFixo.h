#ifndef ATIVIDADEDEPRAZOFIXO_H
#define ATIVIDADEDEPRAZOFIXO_H
#include "Atividade.h"
#include <string>
#include <stdexcept>

using namespace std;

class AtividadeDePrazoFixo : public Atividade
{
    public:
        AtividadeDePrazoFixo(string nome, int dias);
        virtual ~AtividadeDePrazoFixo();

        virtual int getPrazo ();

        virtual int getDuracao();
        //virtual double getCusto();

    protected:

    private:
        string nome;
        int dias;
};

#endif // ATIVIDADEDEPRAZOFIXO_H
