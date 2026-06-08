#pragma once
#include <SFML/Graphics.hpp>
#include "Obstaculo.h"
#include "../Personagens/Jogador.h"

namespace Entidades {

    // HerdandoObstaculo
    class ObstaculoDano : public Obstaculo {
    private:
        
        short int danosidade;
        
    public:
        ObstaculoDano();
        ~ObstaculoDano();
        
        
        void salvarDataBuffer();/*fazer*/
        void executar();
        void obstaculizar(Personagens::Jogador* p);
        
      
        void salvar();/*fazer*/
      
    };

} 