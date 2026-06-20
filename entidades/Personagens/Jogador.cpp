#include "Jogador.h"
#include <iostream>

#include "../../Gerenciadores/Gerenciador_Grafico.h" 

#define VELOCIDADE_X_JOGADOR 5.0f
#define FORCA_PULO -12.0f
#define GRAVIDADE 0.5f

namespace Personagens {

    Jogador::Jogador(bool jog2) : pontos(0), lento(false), tonto(false), durrTont(0.0f), jogador2(jog2)
     {/*lento só é true quando estiver em contato com o Pilha*/
        num_vidas = 7; 
        corpo.setSize(sf::Vector2f(25.f, 50.f)); 
        corpo.setFillColor(sf::Color::Transparent);
        if(!jogador2){ 
            x = 100; /*posicoes iniciais*/
            y = 100;    
            textura = Gerenciadores::Gerenciador_Grafico::getInstancia()->carregarTextura("Assets/Rei Azul.png");
        }
        else{
            x = 200; /*posicoes iniciais*/
            y = 100; 
        textura = Gerenciadores::Gerenciador_Grafico::getInstancia()->carregarTextura("Assets/Rei Vermelho.png");
        }
        corpo.setPosition((float)x, (float)y);     
        if (textura != nullptr) {
                sprite.setTexture(*textura);
                sprite.setScale(0.1f, 0.1f); 
                sprite.setOrigin(0.0f,-75.0f);
                sprite.setPosition((float)x, (float)y);

            }
    }
    Jogador::Jogador(
        bool jog2,
        const std::string& nome,
        int pontos,
        int vidas,
        bool ativo,
        int x,
        int y,
        float vx,
        float vy,
        bool lento,
        bool tonto
    ) : Jogador(jog2)
    {
        this->nome = nome;
        this->pontos = pontos;
        num_vidas = vidas;
        this->ativo = ativo;
        velocidade.x = vx;
        velocidade.y = vy;
        this->lento = lento;
        this->tonto = tonto;

        setPosicao(x, y);
    }
    Jogador::~Jogador() {}
   
    void Jogador::setTonto(bool estado, float duracao) {
        tonto = estado;
        durrTont = duracao;
        if (estado) relogioTontura.restart();
    }

    /* sempre adiciono a gravidade ao jogador para que fique puxando ele pra baixo, se a velocidadeY for zero(está pisando em algo) pula no W adicionando um impulso negativo (pra cima)*/
    void Jogador::mover() {
        velocidade.x = 0.f;

        // reseta tonto apos durrTont segundos
        if (tonto && relogioTontura.getElapsedTime().asSeconds() >= durrTont)
            tonto = false;

        float velAtualX = VELOCIDADE_X_JOGADOR;
        if (lento) velAtualX = VELOCIDADE_X_JOGADOR * 0.3f;

        if (!jogador2) {
            if (!tonto) {
                if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) velocidade.x = -velAtualX;
                if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) velocidade.x =  velAtualX;
            } else {
                // teclas invertidas
                if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) velocidade.x =  velAtualX;
                if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) velocidade.x = -velAtualX;
            }
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::W) && velocidade.y == 0.f)
                velocidade.y = FORCA_PULO;
        } else {
            if (!tonto) {
                if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))  velocidade.x = -velAtualX;
                if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) velocidade.x =  velAtualX;
            } else {
                // teclas invertidas
                if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))  velocidade.x =  velAtualX;
                if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) velocidade.x = -velAtualX;
            }
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up) && velocidade.y == 0.f)
                velocidade.y = FORCA_PULO;
        }

        velocidade.y += GRAVIDADE;
        corpo.move(velocidade);

        x = static_cast<int>(corpo.getPosition().x);
        y = static_cast<int>(corpo.getPosition().y);

        sprite.setPosition((float)x, (float)y);

        lento = false;
    }   
    void Jogador::setNome(const std::string& n) {nome = n;}

    const std::string& Jogador::getNome() const {return nome;}

    void Jogador::operator++() {pontos++;}
    
    void Jogador::operator--() {
        if (pontos > 0) pontos--;
    }
    
    void Jogador::executar() {
        if (!ativo) return;
        mover();
    }

    void Jogador::salvar() 
{
    std::ofstream arquivo("save_jogo.txt", std::ios::app);

    if (!arquivo.is_open()){return;}

    salvarDataBuffer();

    arquivo << "JOGADOR "
            << jogador2 << " "
            << std::quoted(nome) << " "
            << pontos << " "
            << buffer.str()
            << lento << " "
            << tonto
            << std::endl;

    arquivo.close();
}
}