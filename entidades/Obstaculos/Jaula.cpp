#include "Jaula.h"
#include "../../Gerenciadores/Gerenciador_Grafico.h" 

namespace Entidades {

    Jaula::Jaula() {
        danosidade = 1; // Tira 1 ponto de vida
        danoso = true;  

     
        x = 400; 
        y = 550; 
        yBase = y;
        
      
        corpo.setSize(sf::Vector2f(20.f, 20.f)); 
        corpo.setPosition((float)x, (float)y);
        
     textura = Gerenciadores::Gerenciador_Grafico::getInstancia()->carregarTextura("Assets/Jaula de goblin.png");
        
        if (textura != nullptr) {
            sprite.setTexture(*textura);
            sprite.setScale(0.1f, 0.1f); 
            sprite.setOrigin(0.f, -200.f);/*fazendo ele parar de flutuar*/
            sprite.setPosition((float)x, (float)y);
        }
        
    }
    Jaula::Jaula(
    bool ativo,
    int x,
    int y,
    bool danoso,
    int yBase,
    float velocidadeY,
    int danosidade
) : Jaula()
{
    this->ativo = ativo;
    this->danoso = danoso;
    this->yBase = yBase;
    this->velocidadeY = velocidadeY;
    this->danosidade = danosidade;

    setPosicao(x, y);
}
    Jaula::~Jaula() {
    }

    void Jaula::executar() {
        aplicarGravidade();
        sprite.setPosition((float)x, (float)y);
    }

    void Jaula::salvar() {
        std::ofstream arquivo("save_jogo.txt", std::ios::app);

        if (!arquivo.is_open()) {return;}

        salvarDataBuffer();

        arquivo << "JAULA "
            << buffer.str()
            << danosidade
            << std::endl;

        arquivo.close();
}

    void Jaula::setPosicao(int novoX, int novoY) {
        x = novoX;
        y = novoY;
        yBase = novoY;
        velocidadeY = 0.f;

        corpo.setPosition((float)x, (float)y);
        sprite.setPosition((float)x, (float)y);
    }

    void Jaula::obstaculizar(Personagens::Jogador* p) {
        if (p != nullptr) {
            
            
            p->tomarDano(danosidade);/*chama o metodo do jogador para diminuir a vida*/

            
            sf::Vector2f velKnockback = p->getVelocidade();/*velocidade do jogador*/
            velKnockback.y = -10.0f; /*joga ele pra cima*/
            
           
            if (p->getPosicao().x < this->x) { /*se o jogador estiver a esquerda joga ele mais pra esquerda*/
                velKnockback.x = -10.0f; 
            } else {
                velKnockback.x = 10.0f;  /* se estiver para direita joga ele mais para direita*/
            }
            
            
            p->setVelocidade(velKnockback); /*aplica a nova velocidade no jogador*/
        }
    }


} 
