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
#include "Menus/Menu.h"
namespace Menus{
class Menu;
class MenuPausa;
}

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

    Menus::Menu* menu;
    Menus::MenuPausa* menuPausa;

    std::vector<Menus::Menu::RegistroRanking> ranking;
    std::priority_queue<Menus::Menu::RegistroRanking> filaRanking;

    bool pausado;

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
        int nFase,
        bool Jog2,
        const std::string& nomeJ1 = "",
        const std::string& nomeJ2 = ""
    );

    const std::vector<Menus::Menu::RegistroRanking>& getRanking() const;
    void salvarJogo();
    void carregarJogo();
};