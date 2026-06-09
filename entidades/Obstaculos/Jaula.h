#pragma once
#include <SFML/Graphics.hpp>
#include "Obstaculo.h"
#include "../Personagens/Jogador.h"

namespace Entidades {

    // HerdandoObstaculo
    class Jaula : public Obstaculo {
    private:
        
        short int danosidade;
        
    public:
        Jaula();
        ~Jaula();
        
        
        void salvarDataBuffer();/*fazer*/
        void executar();
        void obstaculizar(Personagens::Jogador* p);
        
      
        void salvar();/*fazer*/
      
    };

} 