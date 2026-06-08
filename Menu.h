#pragma once

#include "Ente.h"
#include "Jogo.h"
#include <iostream>
#include <vector>

class Menu : public Ente {
private:
    sf::Font fonte;

    sf::Texture texturaFundo;
    sf::Sprite fundo;

    sf::Text titulo;
    std::vector<sf::Text> opcoesMenu;    // Vetor para os botões principais
    std::vector<sf::Text> textosRanking; // Vetor para a tela de Ranking

    sf::RectangleShape caixa1P;
    sf::RectangleShape caixa2P;

    sf::Text texto1P;
    sf::Text texto2P;

    Jogo* pJog;
    bool ativo;
    bool rankingAberto;
    //mouseClick: bool que evita problema ao segurar o click
    bool mouseClick;

    bool segundoJogador;

private:
    //Carrega a fonte dos textos
    void inicializarFonte();
    //Carrega o fundo do menu
    void inicializarFundo();
    
    //Configura o texto na página do menu
    void inicializarTextos();
    bool mouseEmCima(const sf::Text& texto) const;
    bool mCaixa(const sf::RectangleShape& caixa) const;

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