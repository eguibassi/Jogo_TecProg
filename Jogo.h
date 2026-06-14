#pragma once

#include "Gerenciadores/Gerenciador_Grafico.h"
#include "Entidades/Personagens/Jogador.h"
#include "Fases/Fase_Primeira.h"
#include "Fases/Fase_Segunda.h"

class Menu;

class Jogo {
private:
    enum EstadoJogo {
        MENU,
        FASE1,
        FASE2
    };

    EstadoJogo estadoAtual;

    Gerenciadores::Gerenciador_Grafico GG;
    Personagens::Jogador* pJog1;
    Personagens::Jogador* pJog2;

    Fases::FasePrimeira* fasePrimeira;
    Fases::FaseSegunda* faseSegunda;

    Menu* menu;
private:
    void trocarFase2();
    bool jogadoresDerrotados() const;
    void voltarMenu();
    

public:
    Jogo();
    ~Jogo();

    void executar();
    void entrarFase(int numeroFase, bool segundoJogador);
};