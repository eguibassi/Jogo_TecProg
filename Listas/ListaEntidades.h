#pragma once

#include "Lista.h"
#include "../Entidades/Entidade.h"
namespace Listas{
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
}