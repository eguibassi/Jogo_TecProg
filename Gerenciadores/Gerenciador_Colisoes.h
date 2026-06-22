#pragma once

#include <list>
#include <set>

#include "../Entidades/Entidade.h"
#include "../Entidades/Personagens/Jogador.h"
#include "../Entidades/Personagens/Inimigo.h"
#include "../Entidades/Obstaculos/Obstaculo.h"
#include "../Entidades/Projetil.h" 
#include "../Entidades/Obstaculos/Pilha.h"

namespace Gerenciadores {

    class Gerenciador_Colisoes {
    private:
        Personagens::Jogador* pJog1;
        Personagens::Jogador* pJog2;

        std::list<Personagens::Inimigo*> LIs;
        std::list<Entidades::Obstaculo*> LOs;
        std::set<Entidades::Projetil*> Lps;

        sf::RectangleShape* chaoFase;

        static const float LARGURA_TELA;
        static const float ALTURA_TELA;

    private:
        bool verificarColisao(Entidades::Entidade* pe1, Entidades::Entidade* pe2) const;

        void tratarColisoesJogsObstacs();
        void tratarColisoesInimigsObstacs();
        void tratarColisoesJogsInimgs();
        void tratarColisoesJogsProjeteis();
        void tratarColisoesChao();
        //Limitar inimigo e jogador tela foi condensada em uma pois ambos são personagens e servem o mesmo propósito
        void tratarColisaoBorda();

    public:
        Gerenciador_Colisoes();
        ~Gerenciador_Colisoes();

        void setJogador(Personagens::Jogador* pJog);
        void setJogador2(Personagens::Jogador* pJog);

        void incluirProjetil(Entidades::Projetil* pj);
        void incluirInimigo(Personagens::Inimigo* pi);
        void incluirObstaculo(Entidades::Obstaculo* po);
        void setChao(sf::RectangleShape* chao);

        void executar();
    };

}