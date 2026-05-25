#include "Jogador.h"
#include <iostream>

#include "../../Gerenciadores/Gerenciador_Grafico.h" 

#define VELOCIDADE_X_JOGADOR 5.0f
#define FORCA_PULO -12.0f
#define GRAVIDADE 0.5f

namespace Personagens {

    Jogador::Jogador() : pontos(0), lento(false) {
        num_vidas = 5; 
        x = 100; 
        y = 100; 
        
        corpo.setSize(sf::Vector2f(50.f, 50.f)); 
        corpo.setPosition((float)x, (float)y); 
        corpo.setFillColor(sf::Color::Transparent); 
        
       
       // === CAMINHO ATUALIZADO ===
        textura = Gerenciadores::Gerenciador_Grafico::getInstancia()->carregarTextura("imagens/Rei Azul.png");
        
        if (textura != nullptr) {
            sprite.setTexture(*textura);
            // Ajustando a escala de 1254 para aprox 128 pixels (128 / 1254 = ~0.102)
            sprite.setScale(0.102f, 0.102f); 
            sprite.setPosition((float)x, (float)y);
        }
    }

    Jogador::~Jogador() {
    }

    void Jogador::mover() {
        velocidade.x = 0.f;

        float velAtualX = VELOCIDADE_X_JOGADOR;
        if (lento) velAtualX = VELOCIDADE_X_JOGADOR * 0.3f; 

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) velocidade.x = -velAtualX; 
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) velocidade.x = velAtualX;  

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::W) && velocidade.y == 0.f) {
            velocidade.y = FORCA_PULO; 
        }

        velocidade.y += GRAVIDADE; 

        corpo.move(velocidade);

        x = static_cast<int>(corpo.getPosition().x);
        y = static_cast<int>(corpo.getPosition().y);

       
        sprite.setPosition((float)x, (float)y);

        lento = false;
    }

    void Jogador::executar() {
        mover();
    }

    void Jogador::salvar() {}
    void Jogador::colidir() {}
    
    void Jogador::tomarDano(int dano) {
        num_vidas -= dano;
        std::cout << "Ai! O Jogador pisou no espinho! Vidas restantes: " << num_vidas << std::endl;
    }

  
    void Jogador::desenhar(sf::RenderWindow* window) {
        if (textura != nullptr) {
            Gerenciadores::Gerenciador_Grafico::getInstancia()->desenharElemento(sprite);
        } else {
            // Se falhar ao carregar a imagem desenha o corpo normal para não sumir do jogo
            corpo.setFillColor(sf::Color::Blue);
            Gerenciadores::Gerenciador_Grafico::getInstancia()->desenharElemento(corpo);
        }
    }

} //