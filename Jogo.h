#pragma once

#include <fstream>
#include <cstdlib>
#include <string>
#include <vector>
#include <sstream>
#include <iomanip>
#include <queue>
#include <iostream>
#include <stdexcept>
#include <cstdio>

#include "Gerenciadores/Gerenciador_Grafico.h"
#include "Entidades/Personagens/Jogador.h"
#include "Fases/Fase_Primeira.h"
#include "Fases/Fase_Segunda.h"
#include "RegistroRanking.h"

class Menu;
class MenuPausa;

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
    MenuPausa* menuPausa;

    std::vector<RegistroRanking> ranking;
    std::priority_queue<RegistroRanking> filaRanking;

    bool pausado;

private:
    void trocarFase2();
    void voltarMenu();
    void salvarRanking();
    bool jogsDerr() const;
    void carregarJogador();
    void carregarInimigo(int faseSalva);
    void carregarObstaculo(int faseSalva);
    void carregarProjetil();
public:
    Jogo();
    ~Jogo();

    void executar();

    void entrarFase(
        int nFase,
        bool Jog2,
        const std::string& nomeJ1 = "",
        const std::string& nomeJ2 = ""
    );

    const std::vector<RegistroRanking>& getRanking() const;
    void salvarJogo();
    void carregarJogo();
};