#include "Personagem.h"
#include "../../Gerenciadores/Gerenciador_Grafico.h"

namespace Personagens {

    Personagem::Personagem() : num_vidas(1), maxVidas(0) {
        // Inicializa a velocidade zerada 
        velocidade = sf::Vector2f(0.f, 0.f);
    }

    Personagem::~Personagem() {
    }

    void Personagem::tomarDano(int dano) {
        if (!ativo) return; // Se já está morto/inativo, ignora o dano

        num_vidas -= dano;
        std::cout << "Vidas restantes: " << num_vidas << std::endl;

        if (num_vidas <= 0) {
            ativo = false; // Desativa a entidade
            setPosicao(-9999, -9999); // Joga para fora da tela
            std::cout << "Personagem eliminado!" << std::endl;
        }
    }

    void Personagem::desenhar() {
        Entidade::desenhar(); // desenha sprite/corpo e textos normalmente

        if (!ativo) return;

        // auto-inicializa maxVidas na primeira chamada, pois subclasses
        // sobrescrevem num_vidas apos o construtor de Personagem rodar
        if (maxVidas == 0) maxVidas = num_vidas;
        if (maxVidas <= 0) return;

        Gerenciadores::Gerenciador_Grafico* pGraf = Gerenciadores::Gerenciador_Grafico::getInstancia();
        if (pGraf == nullptr) return;

        float largura = corpo.getSize().x;
        float altura = 5.0f;
        sf::Vector2f posBase = corpo.getPosition();
        sf::Vector2f posBarra(posBase.x + 10.0f, posBase.y - 10.0f);

        float proporcao = (float)num_vidas / (float)maxVidas;
        if (proporcao < 0.0f) proporcao = 0.0f;
        if (proporcao > 1.0f) proporcao = 1.0f;

        sf::RectangleShape fundoBarra;
        fundoBarra.setSize(sf::Vector2f(largura, altura));
        fundoBarra.setPosition(posBarra);
        fundoBarra.setFillColor(sf::Color(60, 60, 60));
        pGraf->desenharForma(fundoBarra);

        sf::RectangleShape vidaBarra;
        vidaBarra.setSize(sf::Vector2f(largura * proporcao, altura));
        vidaBarra.setPosition(posBarra);
        vidaBarra.setFillColor(proporcao < 0.3f ? sf::Color::Red : sf::Color::Green);
        pGraf->desenharForma(vidaBarra);
    }
   void Personagem::salvarDataBuffer() {
    Entidade::salvarDataBuffer();

    buffer << num_vidas << " "
           << velocidade.x << " "
           << velocidade.y << " ";
} 

}