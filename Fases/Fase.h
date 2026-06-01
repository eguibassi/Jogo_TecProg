#pragma once
#include "../Listas/ListaEntidades.h"
#include "../Gerenciadores/Gerenciador_Colisoes.h"
#include "../Gerenciadores/Gerenciador_Grafico.h"


#include "../Entidades/Personagens/Jogador.h"
#include "../Entidades/Personagens/Inimigo.h"
#include "../Entidades/Obstaculos/Plataforma.h"
#include "../Entidades/Obstaculos/ObstaculoDano.h"
#include "../Entidades/Obstaculos/ObstaculoLento.h"

namespace Fases {

    class Fase {
    protected:
        Listas::ListaEntidades lista_ents;
        Gerenciadores::Gerenciador_Colisoes GC;
        

        Personagens::Jogador* pJogador;
        Personagens::Jogador* pJogador2; 

    public:
        Fase();
        virtual ~Fase();
        
        virtual void executar();

    protected:
    
        virtual void criarInimigos() = 0;
        virtual void criarObstaculo() = 0;
        virtual void criarFundo() = 0;
        virtual void desenharFundo() = 0;
        
        
        void criarInimFaceis();
        void criarPlataformas();
        void criarCenario();
    };

}