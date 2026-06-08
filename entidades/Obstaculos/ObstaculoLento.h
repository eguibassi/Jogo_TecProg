#pragma once
#include <SFML/Graphics.hpp>
#include "Obstaculo.h"
#include "../Personagens/Jogador.h"

namespace Entidades {

    class ObstaculoLento : public Obstaculo {
    private:
        
        float largura;

    public:
        ObstaculoLento();
        ~ObstaculoLento();

        void executar();
        void obstaculizar(Personagens::Jogador* p);
        void salvar() ; /*fazer*/
  
    };

} 