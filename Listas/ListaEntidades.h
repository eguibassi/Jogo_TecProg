#pragma once

#include "Lista.h"
#include "../entidades/Entidade.h"

class ListaEntidades
{
private:
    Listas::Lista<Entidades::Entidade> LEs;

public:
    ListaEntidades();
    ~ListaEntidades();

    void incluir(Entidades::Entidade* pE);
    void percorrer();
};