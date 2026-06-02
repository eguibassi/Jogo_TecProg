#include "Goblin.h"

using namespace Personagens;

Goblin::Goblin() : Inimigo(), tamanho(1){
    nivel_maldade = 3; 
    num_vidas = 3;     

   corpo.setSize(sf::Vector2f(30.f, 30.f));
    
   
    textura = Gerenciadores::Gerenciador_Grafico::getInstancia()->carregarTextura("Assets/Goblin.png");

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