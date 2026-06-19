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
        Jaula(
            bool ativo,
            int x,
            int y,
            bool danoso,
            int yBase,
            float velocidadeY,
            int danosidade
        );
        ~Jaula();
        
        
        void executar();
        void obstaculizar(Personagens::Jogador* p);
        void salvar();

        
        void setPosicao(int novoX, int novoY);
      
    };

} 