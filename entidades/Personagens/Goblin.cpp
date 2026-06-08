#include "Goblin.h"

using namespace Personagens;


Goblin::Goblin() : Inimigo(), raio(15.0f){
    nivel_maldade = 1; 
    num_vidas = 3;     

    
    corpo.setSize(sf::Vector2f(raio * 2.0f, raio * 2.0f));
    /*carregar a imagem do goblin, e transforma o png em texture*/
    textura = Gerenciadores::Gerenciador_Grafico::getInstancia()->carregarTextura("Assets/Goblin.png");
    /*textura vai guardar o endereco de memoria onde a imagem do goblin ficou armazenada*/
    if (textura != nullptr)
    {
        sprite.setTexture(*textura);
        sprite.setPosition(corpo.getPosition());
        sprite.setScale(0.1f, 0.1f);
    }
}

Goblin::~Goblin(){}

void Goblin::executar(){
    mover(); 

    if (sprite.getTexture() != nullptr)
    {
        sprite.setPosition(corpo.getPosition());
    }
}

void Goblin::danificar(Jogador* pJogador){
    if (pJogador != nullptr)
    {
        pJogador->tomarDano(nivel_maldade); 
    }
}

void Goblin::salvar(){}