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
        
        
        void salvarDataBuffer();
        void executar();
        void obstaculizar(Personagens::Jogador* p);
        
        // Função que era virtual = 0 no pai e precisa de corpo aqui
        void salvar(); 
    };

} // namespace Entidades