#pragma once

#include "Ente.h"
#include "Jogo.h"
#include <iostream>

class Menu : public Ente {
private:
    sf::Font fonte;
    sf::Text titulo;
    sf::Text opcaoJogar;
    sf::Text opcaoRanking;
    sf::Text opcaoSalvar;
    sf::Text opcaoRecuperar;
    sf::Text opcaoSair;

    Jogo* pJog;
    bool ativo;
    bool mouseClick;

private:
    void inicializarFonte();
    void inicializarTextos();

    void atualizarMouse();
    void verificarClique();

    bool mouseEmCima(const sf::Text& texto) const;

    void executarJogar();
    void executarRanking();
    void executarSalvar();
    void executarRecuperar();
    void executarSair();

public:
    Menu();
    Menu(Jogo* pJogo);
    ~Menu();

    void setJogo(Jogo* pJogo);

    void executar();

    void setAtivo(const bool estado);
    bool getAtivo() const;
};