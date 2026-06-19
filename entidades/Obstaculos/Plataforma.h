#pragma once
#include <SFML/Graphics.hpp>
#include "Obstaculo.h"
#include "../Personagens/Jogador.h"

namespace Entidades {

    class Plataforma : public Obstaculo {
    private:
        int altura;        /*posicao original*/
        int offset;        /*quanto ja desceu*/
        bool pisadaFrame;

    public:
        Plataforma();
        Plataforma(
            bool ativo,
            int x,
            int y,
            bool danoso,
            int yBase,
            float velocidadeY,
            int altura,
            int offset,
            bool pisadaFrame
        );
        ~Plataforma();
             
        void executar();
        void obstaculizar(Personagens::Jogador* p);
        void salvar(); 
        void setPosicao(int novoX, int novoY);
        void setPisada();
    protected:
        
        void aplicarGravidade();


    };

}