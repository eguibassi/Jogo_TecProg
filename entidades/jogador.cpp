#include "Jogador.h"
using namespace Personagens;
#define VEL_JOGADOR_X 5.f
#define VEL_JOGADOR_Y 12.f

Jogador::Jogador() : pontos(0), vida(5) {
    corpo.setSize(sf::Vector2f(50.f, 50.f));
    corpo.setPosition(100.f, 100.f); 
    corpo.setFillColor(sf::Color::Blue); 
    velocidade = sf::Vector2f(0.f, 0.f);
}

Jogador::~Jogador() {
}

void Jogador::mover() {
    velocidade.x = 0.f;

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
        velocidade.x = -VEL_JOGADOR_X; 
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
        velocidade.x = VEL_JOGADOR_X;  
    }

    velocidade.y += 0.5f; 

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::W) && corpo.getPosition().y >= 500.f) {
        velocidade.y = VEL_JOGADOR_Y; 
    }

    corpo.move(velocidade);

    if (corpo.getPosition().y > 500.f) {
        corpo.setPosition(corpo.getPosition().x, 500.f);
        velocidade.y = 0.f; 
    }
}


void Jogador::executar() {
    mover();
}



void Jogador::salvar() {
}

void Jogador::colidir() {
    // TODO: Implementar quando tivermos a classe GerenciadorDeColisoes e Entidade.
    // Vai tratar o que acontece quando bater num inimigo 
}


void Jogador::desenhar(sf::RenderWindow* window) {
    if (window) {
        window->draw(corpo);
    }
}