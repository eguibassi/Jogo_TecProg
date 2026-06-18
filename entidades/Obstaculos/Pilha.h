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
        ~Pilha();

        void executar();
        void obstaculizar(Personagens::Jogador* p);
        void setPosicao(int novoX, int novoY);
        void salvar() ;
  
    };

} 