#include "Jogador.h"

Jogador::Jogador(float x, float y) : vida(5) {
    // Tamanho provisório do jogador
    corpo.setSize(sf::Vector2f(50.f, 50.f));
    corpo.setPosition(x, y);
    
    // Como ainda não temos as artes do Clash Royale, vamos usar uma cor para testar
    corpo.setFillColor(sf::Color::Blue); 
    
    velocidade = sf::Vector2f(0.f, 0.f);
}

Jogador::~Jogador() {
}

void Jogador::mover() {
    // Movimentação horizontal
    velocidade.x = 0.f;

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
        velocidade.x = -5.f; // Esquerda
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
        velocidade.x = 5.f;  // Direita
    }

    // Pulo (só pula se estiver no "chão" falso que criaremos abaixo)
    // No futuro, isso será controlado pelo Gerenciador de Colisões
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::W) && corpo.getPosition().y >= 500.f) {
        velocidade.y = -12.f; 
    }

    // Efeito da gravidade constante puxando para baixo
    velocidade.y += 0.5f; 

    // Chão falso para podermos testar sem cair infinitamente
    if (corpo.getPosition().y >= 500.f) {
        corpo.setPosition(corpo.getPosition().x, 500.f);
        velocidade.y = 0.f; // Zera a velocidade y ao tocar no chão
    }

    // Aplica a velocidade na posição do corpo
    corpo.move(velocidade);
}

void Jogador::atualiza() {
    mover();
}

void Jogador::desenhar(sf::RenderWindow* window) {
    if (window) {
        window->draw(corpo);
    }
}