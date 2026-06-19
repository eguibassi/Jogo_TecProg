#pragma once
#include <SFML/Graphics.hpp>
#include "Obstaculo.h"
#include "../Personagens/Jogador.h"

namespace Entidades {

    class Pilha : public Obstaculo {
    private:
        
        float largura;

    public:
        Pilha();
        Pilha(
            bool ativo,
            int x,
            int y,
            bool danoso,
            int yBase,
            float velocidadeY,
            float largura
        );
        ~Pilha();

        void executar();
        void obstaculizar(Personagens::Jogador* p);
        void setPosicao(int novoX, int novoY);
        void salvar() ;
  
    };

} 