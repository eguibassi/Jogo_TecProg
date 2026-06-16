#pragma once

#include "Ente.h"
#include "Jogo.h"
#include <iostream>
#include <vector>
#include <string>
#include "RegistroRanking.h"

class Menu : public Ente {
protected:
    sf::Font fonte;

    std::vector<sf::Text> opcoesMenu;

    //mouseClick: bool que evita problema ao segurar o click
    bool mouseClick;

protected:
    //Carrega a fonte dos textos
    void inicializarFonte();

    sf::Text criarTexto(
        const std::string& conteudo,
        const unsigned int tamanho,
        const sf::Color& cor,
        const sf::Vector2f& posicao
    );

    template <typename T>
    bool mouseEmCima(const T& objeto) const {
        if (pGG == nullptr || pGG->getWindow() == nullptr)
        {
            return false;
        }

        sf::Vector2i posPixel = sf::Mouse::getPosition(*pGG->getWindow());
        sf::Vector2f posMouse = pGG->getWindow()->mapPixelToCoords(posPixel);

        return objeto.getGlobalBounds().contains(posMouse);
    }

private:
    sf::Texture texturaFundo;
    sf::Sprite fundo;

    sf::Text titulo;

    std::vector<sf::Text> textosRanking;

    //[0] = p1, [1] = p2
    std::vector<sf::RectangleShape> caixaJogs;
    std::vector<sf::Text> textosJogs;

    //[0] = titulo, [1] = nome, [2] = ajuda
    std::vector<sf::Text> textosCadastro;

    //[0] = nome jogador 1, [1] = nome jogador 2
    std::vector<std::string> nomesJogadores;

    Jogo* pJog;

    bool ativo;
    bool rankingAberto;
    bool cadastroAberto;

    bool segundoJogador;
    bool menuPrincipalInicializado;

    int faseSelecionada;
    int indiceNomeAtual;

private:
    //Carrega o fundo do menu
    void inicializarFundo();

    //Configura o texto na página do menu
    void inicializarTextos();

    void setVisibilidade(std::vector<sf::Text>& textos, const sf::Color& cor);

    //Atualiza cor do mouse se em cima para amarelo
    void atualizarMouse();

    void verificarClique();
    void verificarTelaAberta();
    void executarSair();

    void abrirCadastro(const int numeroFase);
    void atualizarTextoCadastro();
    void iniciarFaseSelecionada();
    void atualizarTextosRanking();

public:
    Menu();
    virtual ~Menu();

    void setMenuPrincipal();

    void setJogo(Jogo* pJogo);
    void setAtivo(const bool estado);
    bool getAtivo() const;

    void executar();

    void tratarEvento(const sf::Event& evento);
};