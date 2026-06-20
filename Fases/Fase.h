#pragma once

#include <vector>
#include <stdexcept>
#include <string>
#include "../Ente.h" 
#include "../Listas/ListaEntidades.h"
#include "../Gerenciadores/Gerenciador_Colisoes.h"
#include "../Gerenciadores/Gerenciador_Grafico.h"

#include "../Entidades/Personagens/Jogador.h"
#include "../Entidades/Personagens/Inimigo.h"
#include "../Entidades/Obstaculos/Plataforma.h"
#include "../Entidades/Obstaculos/Jaula.h"
#include "../Entidades/Obstaculos/Pilha.h"

namespace Fases {

    class Fase : public Ente {
    protected:
        Listas::ListaEntidades lista_ents;
        Gerenciadores::Gerenciador_Colisoes GC;

        Personagens::Jogador* pJogador;
        Personagens::Jogador* pJogador2; 
        sf::RectangleShape chaoFase;

        //por uml
        std::vector<sf::Vector2f> posicoesPlataformas;
        std::vector<bool> plataformaJaCriada;

    private:
        const int maxGoblins;
        const int maxPlat;

    public:
        Fase();
        virtual ~Fase();
        
        void executar();
        void pausaFase();
        void salvar();

        void incEntCar(Entidades::Entidade* ent);
        void incInimGC(Personagens::Inimigo* inim);
        void incObsGC(Entidades::Obstaculo* obs);
        void incProjGC(Entidades::Projetil* proj);
        const Listas::ListaEntidades& getLisEnt() const;

    protected:
        virtual void criarInimigos() = 0;
        virtual void criarObstaculo() = 0;
        virtual void criarFundo() = 0;
        virtual void desenharFundo() = 0;
        
        void criarGoblins();
        void criarPlataformas();
        void criarCenario();
    };

}