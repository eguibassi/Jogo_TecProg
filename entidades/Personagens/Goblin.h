#pragma once

#include "Inimigo.h"
#include "../../Gerenciadores/Gerenciador_Grafico.h"
#include <SFML/Graphics.hpp>
#include <iostream>

//inimigo fácil/médio
namespace Personagens{
    class Goblin: public Inimigo{
    private:
        float raio; 

    public:
        Goblin();
        Goblin(
        bool ativo,
        int x,
        int y,
        int vidas,
        int nivel,
        float vx,
        float vy,
        int direcao,
        float raio
        );
        ~Goblin();

        void executar();
        void danificar(Jogador* pJogador);
        
        void salvar(); 

        
    };
}