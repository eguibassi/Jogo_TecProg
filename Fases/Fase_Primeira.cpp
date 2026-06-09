#include "Fase_Primeira.h"
#include <cstdlib> 
#include <ctime>   



namespace Fases {


    FasePrimeira::FasePrimeira(bool Jog2) : Fase(), maxInimMedios(3),maxInimFaceis(5) {
        
        srand(time(NULL)); 

        //Vinculamos o Jogador recebido do Jogo
        pJogador = new Personagens::Jogador(false);
        lista_ents.incluir(pJogador);
        GC.setJogador(pJogador);
        if(Jog2){
            pJogador2 = new Personagens::Jogador(true);
            lista_ents.incluir(pJogador2);
            GC.setJogador2(pJogador2);
        }

        // Criamos o cenário
        criarCenario(); 
    }

    FasePrimeira::~FasePrimeira() {}

    void FasePrimeira::criarFundo(){
        if(!texturaFundo.loadFromFile("Assets/Fundo fase 1.png"))
            return;
        spriteFundo.setTexture(texturaFundo);
        spriteFundo.setPosition(0.f, 0.f);
        sf::Vector2u tam = texturaFundo.getSize();
        if (tam.x > 0 && tam.y > 0){
            //Dimensiona a imagem para o tamanho desejado
            spriteFundo.setScale(800.f / tam.x, 600.f / tam.y);
        }
    }

    void FasePrimeira::desenharFundo(){
        Gerenciadores::Gerenciador_Grafico* pGraf = Gerenciadores::Gerenciador_Grafico::getInstancia();

        if (pGraf != nullptr && pGraf->getWindow() != nullptr)
            pGraf->getWindow()->draw(spriteFundo);
    }

    void FasePrimeira::criarObstaculo() {
    
        criarPlataformas();
        criarObstLento();
    }

    void FasePrimeira::criarInimigos() {
        criarInimMedios();
        criarInimFaceis();
    }

    void FasePrimeira::criarInimFaceis() {
        
        int quantidade = (rand() % 3) + 2; 

        for (int i = 0; i < quantidade; i++) {
            
            Personagens::Goblin* goblin = new Personagens::Goblin();
            goblin->setPosicao(100.0f + (i * 200.0f), 400.0f);
            goblin->setJogador(pJogador);
            lista_ents.incluir(goblin);
            GC.incluirInimigo(goblin);
        }
    }

    void FasePrimeira::criarInimMedios() {
        int quantidade = (rand() % maxInimMedios) + 1; 

        for (int i = 0; i < quantidade; i++) {
            
            Personagens::Pekka* pekka = new Personagens::Pekka();

            //Posição deve ser alterada quando colocarmos as plataformas
            //e implementarmos a logística do nível
            pekka->setPosicao(150.0f +(i*150.0f), 400.0f);
            pekka->setJogador(pJogador);
            lista_ents.incluir(pekka);
            GC.incluirInimigo(pekka);
        }

    }

    void FasePrimeira::criarObstLento() {
    
        for (int i = 0; i < 3; i++) {
        
            Entidades::ObstaculoLento* lama = new Entidades::ObstaculoLento();

            if (i == 0) {
                lama->setPosicao(120, 395); /*obstaculo lento na primeira plataforma*/
            }
            else {
                lama->setPosicao(250 + (i * 350), 500);
            }

            lista_ents.incluir(lama);
            GC.incluirObstaculo(lama);
        
        }
    }

   void FasePrimeira::criarPlataformas() {
        
  
        float alturaPrimeiroAndar = 430.0f; 
        
        
        float posicoesFixasX[3] = {87.0f, 325.0f, 563.0f};

        for (int i = 0; i < 3; i++) {
            Entidades::Plataforma* platFixa = new Entidades::Plataforma();
            platFixa->setPosicao(posicoesFixasX[i], alturaPrimeiroAndar);
            
            lista_ents.incluir(platFixa);
            GC.incluirObstaculo(platFixa);
        }


        float alturaSegundoAndar = 300.0f;

        
        std::vector<float> posicoesAleatoriasX = {
            1.0f,   
            206.0f,  
            444.0f,  
            635.0f   
        };

        for (size_t i = 0; i < posicoesAleatoriasX.size(); i++) {
            
            int chance = rand() % 100;

         
            if (chance < 65) {
                Entidades::Plataforma* platAleatoria = new Entidades::Plataforma();
                platAleatoria->setPosicao(posicoesAleatoriasX[i], alturaSegundoAndar);
                
                lista_ents.incluir(platAleatoria);
                GC.incluirObstaculo(platAleatoria);
            }
        }
    }

}