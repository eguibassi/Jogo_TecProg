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
        
     
        void executar() ;
        void obstaculizar(Personagens::Jogador* p) ;/*fazer*/

   
        void salvar() ;/*fazer*/
    };

} 