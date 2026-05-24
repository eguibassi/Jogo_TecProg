#include <SFML/Graphics.hpp>
#include "Entidades/Personagens/Jogador.h"
#include "Entidades/Personagens/Inimigo.h" 
#include "Entidades/Obstaculos/Plataforma.h" 
#include "Entidades/Obstaculos/ObstaculoDano.h" 
#include "Entidades/Obstaculos/ObstaculoLento.h" 
#include "Gerenciadores/Gerenciador_Colisoes.h"

using namespace Personagens;
using namespace Entidades;
using namespace Gerenciadores; 

class Hog : public Inimigo {
public:
    Hog() {}
    void executar()  { mover(); }
    void danificar(Jogador* p) {}
    void salva()  {}
    void salvar() {}
};

int main() {
    sf::RenderWindow window(sf::VideoMode(800, 600), "Teste Nível Completo - Clash++");
    window.setFramerateLimit(60);

    Jogador jogador;
    Hog inimigoTeste;
    inimigoTeste.setJogador(&jogador);
    
    Plataforma chao;
    ObstaculoDano espinho;
    ObstaculoLento lama; 

   
    Gerenciador_Colisoes gerenciador;
    
    
    gerenciador.setJogador(&jogador);
    gerenciador.incluirInimigo(&inimigoTeste);
    gerenciador.incluirObstaculo(&chao);
    gerenciador.incluirObstaculo(&espinho);
    gerenciador.incluirObstaculo(&lama);
    

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
        }
        
        jogador.executar();
        inimigoTeste.executar(); 
        chao.executar(); 
        espinho.executar(); 
        lama.executar();

    
        gerenciador.executar();

        window.clear(sf::Color::Black);
        
        chao.desenhar(&window);
        lama.desenhar(&window);
        espinho.desenhar(&window);
        
        jogador.desenhar(&window);
        inimigoTeste.desenhar(&window);
        
        window.display();
    }

    return 0;
}