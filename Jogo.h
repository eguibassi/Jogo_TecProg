#pragma once

#include "Gerenciadores/Gerenciador_Grafico.h"
#include "Entidades/Personagens/Jogador.h"
#include "Fases/Fase_Primeira.h"
#include "Fases/Fase_Segunda.h"
#include <string>
#include <vector>

class Menu;

struct RegistroRanking {
    std::string nome;
    int pontos;
};

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
    std::vector<RegistroRanking> ranking;

private:
    void trocarFase2();
    bool jogadoresDerrotados() const;
    void voltarMenu();

    void salvarRanking();

public:
    Jogo();
    ~Jogo();

    void executar();

    void entrarFase(
        int numeroFase,
        bool segundoJogador,
        const std::string& nomeJogador1 = "",
        const std::string& nomeJogador2 = ""
    );

    const std::vector<RegistroRanking>& getRanking() const;
};