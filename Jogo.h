#pragma once
#include "Gerenciadores/Gerenciador_Grafico.h"
#include "Gerenciadores/Gerenciador_Colisoes.h"
#include "Entidades/Personagens/Jogador.h"
#include "Entidades/Personagens/Inimigo.h"
#include "Entidades/Obstaculos/Plataforma.h"
#include "Entidades/Obstaculos/ObstaculoDano.h"
#include "Entidades/Obstaculos/ObstaculoLento.h"

    
class Hog : public Personagens::Inimigo {
public:
    Hog() {}
    void executar() override { mover(); }
    void danificar(Personagens::Jogador* p) override {}
    void salva() override {}
    void salvar() override {}
};

class Jogo {
private: 

    enum EstadoJogo { MENU = 0, FASE_TESTE };
    EstadoJogo estadoAtual;

    
    Gerenciadores::Gerenciador_Grafico GG; 
    Personagens::Jogador pJog1;

    
    Hog inimigoTeste;
    Entidades::Plataforma chao;
    Entidades::ObstaculoDano espinho;
    Entidades::ObstaculoLento lama;
    Gerenciadores::Gerenciador_Colisoes gerenciadorColisoes;

public:
    Jogo();
    ~Jogo();
    void executar();
};