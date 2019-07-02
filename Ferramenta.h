#ifndef FERRAMENTA_H
#define FERRAMENTA_H
#include "Recurso.h"
#include <stdexcept>
#include <string>
using namespace std;

class Ferramenta : public Recurso
{
    public:
        Ferramenta(string nome, double custoDiario);
        virtual ~Ferramenta();

        double getCusto (int dias);
        virtual double getCustoDiario ();
        void imprimir();

    protected:
        double custoDiario;

    private:
};

#endif // FERRAMENTA_H
