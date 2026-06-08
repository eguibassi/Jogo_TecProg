#pragma once
#include <SFML/Graphics.hpp>
#include "../Entidade.h"
#include "../Personagens/Jogador.h"

namespace Entidades {

    class Obstaculo : public Entidade {
    protected:
    
        bool danoso;

    public:
        Obstaculo();
        virtual ~Obstaculo();

        
        void salvarDataBuffer();/*fazer*/
        

        virtual void executar() = 0;
        virtual void salvar() = 0;
        
        
        virtual void obstaculizar(Personagens::Jogador* p);
    };

} 