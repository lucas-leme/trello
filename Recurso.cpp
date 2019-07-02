#include "Recurso.h"

Recurso::Recurso(string nome) : nome (nome){}


Recurso::~Recurso()
{

}

string Recurso::getNome()
{
    return nome;
}
