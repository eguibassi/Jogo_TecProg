#pragma once

#include "Inimigo.h"
#include "../../Gerenciadores/Gerenciador_Grafico.h"
#include <SFML/Graphics.hpp>
#include <iostream>

//inimigo médio
namespace Personagens{
    class Pekka: public Inimigo{
    private:
        int tamanho;
        int aumentaVida; 

    public:
        Pekka();
        Pekka(
        bool ativo,
        int x,
        int y,
        int vidas,
        int nivel,
        float vx,
        float vy,
        int direcao,
        int tamanho,
        int aumentaVida
    );
        ~Pekka();

        void executar();
        void danificar(Jogador* pJogador);
        void salvar(); 

       
    };
}