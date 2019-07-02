#ifndef PESSOA_H
#define PESSOA_H
#include "Recurso.h"
#include <stdexcept>
#include <iostream>

using namespace std;

class Pessoa : public Recurso
{
    public:
        Pessoa (string nome, double valorPorHora, int horasDiarias);
        Pessoa (string nome, int horasDiarias);
        virtual ~Pessoa ();

        virtual double getValorPorHora();
        virtual int getHorasDiarias ();
        virtual bool recebeValorPadrao ();

        static void setValorPorHoraPadrao (double valor);
        static double getValorPorHoraPadrao ();

        double getCusto(int dias);
        void imprimir();

        static double valorPorHoraPadrao;

    protected:

    private:
        bool recebeuValorPadrao;
        double valorPorHora;
        int horasDiarias;
        double custo;

};

#endif // PESSOA_H
