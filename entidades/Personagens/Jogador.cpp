#include "Jogador.h"
#include <iostream>

#include "../../Gerenciadores/Gerenciador_Grafico.h" 

#define VELOCIDADE_X_JOGADOR 5.0f
#define FORCA_PULO -12.0f
#define GRAVIDADE 0.5f

namespace Personagens {

    Jogador::Jogador() : pontos(0), lento(false), pProjetil(nullptr), podeAtirar(true) {/*lento só é true quando estiver em contato com o ObstaculoLento*/
        num_vidas = 5; 
        x = 100; /*posicoes iniciais*/
        y = 100; 

        corpo.setSize(sf::Vector2f(50.f, 50.f)); 
        corpo.setPosition((float)x, (float)y); 
        corpo.setFillColor(sf::Color::Transparent); 

        textura = Gerenciadores::Gerenciador_Grafico::getInstancia()->carregarTextura("Assets/Rei Azul.png");

        if (textura != nullptr) {
            sprite.setTexture(*textura);
            // Ajustando a escala de 1254 para aprox 128 pixels (128 / 1254 = ~0.102)
            sprite.setScale(0.102f, 0.102f); 
            sprite.setPosition((float)x, (float)y);
        }
    }

    Jogador::~Jogador() {
        if (pProjetil != nullptr) {
            delete pProjetil;
            pProjetil = nullptr;
        }
    }

    /* sempre adiciono a gravidade ao jogador para que fique puxando ele pra baixo, se a velocidadeY for zero(está pisando em algo) pula no W adicionando um impulso negativo (pra cima)*/
    void Jogador::mover() {
        velocidade.x = 0.f;

        float velAtualX = VELOCIDADE_X_JOGADOR;
        if (lento) velAtualX = VELOCIDADE_X_JOGADOR * 0.3f; /*se tiver no obstaculo lento vai devagar*/

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) velocidade.x = -velAtualX; /*esquerda*/
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) velocidade.x = velAtualX;  /*direita*/

        /* aqui o que comentei em cima da classe*/
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::W) && velocidade.y == 0.f) {
            velocidade.y = FORCA_PULO; 
        }

        velocidade.y += GRAVIDADE; /*sempre atualizando Vy para puxar ele*/

        corpo.move(velocidade);/*move ele com base nas velocidades*/

        x = static_cast<int>(corpo.getPosition().x);   /*pegam as novas posicoes e salvam*/
        y = static_cast<int>(corpo.getPosition().y);

        sprite.setPosition((float)x, (float)y); /*atualiza posiçao da imagem*/

        lento = false;
    }

    Entidades::Projetil* Jogador::atirar() {
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Z)) {
        if (podeAtirar) {
            // Criamos o projétil
            Entidades::Projetil* novoProjetil = new Entidades::Projetil();

            sf::Vector2f posJogador = getPosicao();
            // Posiciona na frente do jogador
            novoProjetil->setPosicao((int)(posJogador.x + 50.0f), (int)(posJogador.y + 20.0f));
            novoProjetil->setAtivo(true);

            podeAtirar = false;
            
            // Retorna o projétil criado para a Fase poder adotá-lo!
            return novoProjetil; 
        }
    }
    else {
        podeAtirar = true;
    }
    
    // Se não apertou Z ou não podia atirar, retorna nada
    return nullptr; 
}
    Entidades::Projetil* Jogador::getProjetil() const {
        return pProjetil;
    }

    void Jogador::executar() {
        mover();
        atirar();

        if (pProjetil != nullptr && pProjetil->getAtivo()) {
            pProjetil->executar();
        }
    }

    void Jogador::salvar() {}

    void Jogador::colidir() {}

    void Jogador::tomarDano(int dano) {
        num_vidas -= dano;
        std::cout << "Tomou dano ! Vidas restantes: " << num_vidas << std::endl;
    }


} 