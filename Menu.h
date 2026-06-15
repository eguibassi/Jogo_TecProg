#pragma once

#include "Ente.h"
#include "Jogo.h"
#include <iostream>
#include <vector>
#include <string>

class Menu : public Ente {
private:
    sf::Font fonte;

    sf::Texture texturaFundo;
    sf::Sprite fundo;

    sf::Text titulo;
    std::vector<sf::Text> opcoesMenu;    // Vetor para os botões principais
    std::vector<sf::Text> textosRanking; // Vetor para a tela de Ranking
    //[0] = p1, [1] = p2
    std::vector<sf::RectangleShape> caixaJogs;
    sf::Text texto1P;
    sf::Text texto2P;

    sf::Text textoCadastroTitulo;
    sf::Text textoCadastroNome;
    sf::Text textoCadastroAjuda;


    Jogo* pJog;
    bool ativo;
    bool rankingAberto;
    bool cadastroAberto;
    bool digitandoJogador2;
    //mouseClick: bool que evita problema ao segurar o click
    bool mouseClick;

    bool segundoJogador;
    int faseSelecionada;
    std::string nomeJogador1;
    std::string nomeJogador2;

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
    void verificarCadastro();
    void executarSair();

    void abrirCadastro(const int numeroFase);
    void atualizarTextoCadastro();
    void iniciarFaseSelecionada();
    void atualizarTextosRanking();

    std::string getNomeDigitadoAtual() const;
    void setNomeDigitadoAtual(const std::string& nome);

    void esconderTextosRanking();
    void esconderTextosCadastro();

public:
    Menu();
    ~Menu();

    void setJogo(Jogo* pJogo);
    void setAtivo(const bool estado);
    bool getAtivo() const;
    void executar();

    void tratarEvento(const sf::Event& evento);
};