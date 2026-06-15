#pragma once
#include <fstream>
#include <algorithm>
//std::atoi, converte strings para ints https://stackoverflow.com/questions/7663709/how-can-i-convert-a-stdstring-to-int
#include <cstdlib>
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
    const int TELA_MENU = 0;
    const int TELA_FASE1 = 1;
    const int TELA_FASE2 = 2;

    int estadoAtual; 

    Gerenciadores::Gerenciador_Grafico GG;
    Personagens::Jogador* pJog1;
    Personagens::Jogador* pJog2;

    Fases::FasePrimeira* fasePrimeira;
    Fases::FaseSegunda* faseSegunda;

    Menu* menu;

    std::vector<RegistroRanking> ranking;

private:
    void trocarFase2();
    void voltarMenu();
    void salvarRanking();
    bool jogsDerr() const;

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