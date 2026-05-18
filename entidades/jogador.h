#pragma once
#include <SFML/Graphics.hpp>

class Jogador {
private:
    sf::RectangleShape corpo;
    sf::Texture textura;
    sf::Vector2f velocidade;
    int vida;

public:
    // Construtor com posições iniciais
    Jogador(float x = 0.0f, float y = 0.0f);
    ~Jogador();

    void atualiza();
    void mover();
    
    // Como ainda não temos o Gerenciador Gráfico, passamos a janela por parâmetro
    void desenhar(sf::RenderWindow* window);

    // Getters básicos
    sf::RectangleShape getCorpo() const { return corpo; }
    int getVida() const { return vida; }
};