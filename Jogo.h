#pragma once
#include "Gerenciadores/Gerenciador_Grafico.h"
#include "Entidades/Personagens/Jogador.h"
#include "Fases/Fase_Primeira.h" 

class Jogo {
private: 
    enum EstadoJogo { MENU = 0, FASE_TESTE };
    EstadoJogo estadoAtual;

    Gerenciadores::Gerenciador_Grafico GG; 
    Personagens::Jogador pJog1;

    
    Fases::FasePrimeira* fasePrimeira;

public:
    Jogo();
    ~Jogo();
    void executar();
};