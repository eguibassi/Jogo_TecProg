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

    public:
        Pekka();
        ~Pekka();

        void executar();
        void danificar(Jogador* pJogador);
        void salvar();
    };
}

