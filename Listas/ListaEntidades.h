#pragma once

#include "Lista.h"

class Entidade;

class ListaEntidades
{
private:
    Listas::Lista<Entidade> LEs;

public:
    ListaEntidades();
    ~ListaEntidades();

    void incluir(Entidade* pE);
    void percorrer();
};