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
    // 1. Movimentação horizontal
    velocidade.x = 0.f;

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
        velocidade.x = -5.f; // Esquerda
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
        velocidade.x = 5.f;  // Direita
    }

    // 2. Gravidade puxando para baixo
    velocidade.y += 0.5f; 

    // 3. Pulo (só pula se estiver exatamente no chão falso)
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::W) && corpo.getPosition().y >= 500.f) {
        velocidade.y = -12.f; 
    }

    // 4. Aplica a velocidade na posição do corpo PRIMEIRO
    corpo.move(velocidade);

    // 5. DEPOIS verifica a colisão com o chão para não cair infinitamente
    if (corpo.getPosition().y > 500.f) {
        corpo.setPosition(corpo.getPosition().x, 500.f);
        velocidade.y = 0.f; // Zera a velocidade ao bater no chão
    }
}

void Jogador::atualiza() {
    mover();
}

void Jogador::desenhar(sf::RenderWindow* window) {
    if (window) {
        window->draw(corpo);
    }
}