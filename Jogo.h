#pragma once

#include "Gerenciadores/Gerenciador_Grafico.h"
#include "Entidades/Personagens/Jogador.h"
#include "Fases/Fase_Primeira.h"

class Menu;

class Jogo {
private:
    enum EstadoJogo {
        MENU,
        FASE1
    };

    EstadoJogo estadoAtual;

    Gerenciadores::Gerenciador_Grafico GG;
    Personagens::Jogador pJog1;
    Personagens::Jogador pJog2;

    Fases::FasePrimeira* fasePrimeira;
    Menu* menu;

public:
    Jogo();
    ~Jogo();

    void executar();

    void entrarFase1(bool segundoJogador);
};