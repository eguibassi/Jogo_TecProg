#pragma once
#include <SFML/Graphics.hpp>
#include "Obstaculo.h"
#include "../Personagens/Jogador.h"

namespace Entidades {

    class Plataforma : public Obstaculo {
    private:
        
        int altura;

    public:
        Plataforma();
        ~Plataforma();
        
     
        void executar() override;
        void obstaculizar(Personagens::Jogador* p) override;

   
        void salvar() override; 
    };

} 