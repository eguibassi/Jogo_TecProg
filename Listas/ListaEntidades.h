#pragma once
#include "Lista.h"
#include "../Entidades/Entidade.h"
#include "../Entidades/Personagens/Inimigo.h"
#include <SFML/Graphics.hpp>

namespace Listas {

    class ListaEntidades {
    private:
        Listas::Lista<Entidades::Entidade> LEs;

    public:
        ListaEntidades();
        ~ListaEntidades();

        //Inclui uma entidade na lista
        void incluir(Entidades::Entidade* pE);
        //Percorre a lista de entidades
        void percorrer();
        
        //Chama o desenhar das entidades da lista
        void desenhar();

        bool InimsDerr() const;
    };

}