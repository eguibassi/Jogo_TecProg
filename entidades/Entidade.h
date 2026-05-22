#pragma once
#include <SFML/Graphics.hpp>
#include <string>

namespace Entidades {

class Entidade {
protected:
    sf::Texture textura;
    sf::Sprite sprite;

    sf::Vector2f posicao;
    sf::Vector2f velocidade;

    bool ativo;

public:
    //Construtora para entidades não prontas
    Entidade();
    //Inicializadora das derivadas
    Entidade(const std::string& caminhoTextura, sf::Vector2f posicaoInicial);

    virtual ~Entidade();

    virtual void executar() = 0;

    //Desenha o sprite(pixel art) da entidade
    virtual void desenhar(sf::RenderWindow* window);

    //Carrega a imagem e envia ao sprite a imagem
    bool carregarTextura(const std::string& caminhoTextura);

    void setPosicao(float x, float y);
    void setPosicao(sf::Vector2f novaPosicao);

    sf::Vector2f getPosicao() const;

    void setVelocidade(float x, float y);
    sf::Vector2f getVelocidade() const;

    sf::FloatRect getBounds() const;

    void setAtivo(bool estado);
    bool getAtivo() const;

    sf::Sprite& getSprite();
    const sf::Sprite& getSprite() const;
};

}

