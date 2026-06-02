#pragma once

#include "Ente.h"
#include "Jogo.h"
#include <iostream>

class Menu : public Ente {
private:
    sf::Font fonte;

    sf::Texture texturaFundo;
    sf::Sprite fundo;

    sf::Text titulo;
    sf::Text opcaoFase1;
    sf::Text opcaoFase2;

    sf::Text opcaoRanking;
    sf::Text opcaoSalvar;
    sf::Text opcaoRecuperar;
    sf::Text opcaoSair;
    sf::Text textoRanking;
    sf::Text textoVoltar;

    Jogo* pJog;
    bool ativo;
    bool rankingAberto;
    //mouseClick:bool que evita problema ao segurar o click
    bool mouseClick;

private:
    //Carrega a fonte dos textos
    void inicializarFonte();
    //Carrega o fundo do menu
    void inicializarFundo();
    //Configura o texto na página do menu
    void inicializarTextos();
    bool mouseEmCima(const sf::Text& texto) const;
    //Atualiza cor do mouse se em cima para amarelo
    void atualizarMouse();
    void verificarClique();

    void verificarRanking();




    void executarSair();

public:
    Menu();
    Menu(Jogo* pJogo);
    ~Menu();

    void setJogo(Jogo* pJogo);
    void setAtivo(const bool estado);
    bool getAtivo() const;
    void executar();
};