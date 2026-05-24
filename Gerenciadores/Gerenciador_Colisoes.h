#pragma once
#include <vector>
#include <list>
#include <set>
#include <SFML/Graphics.hpp>

#include "../Entidades/Personagens/Jogador.h"
#include "../Entidades/Personagens/Inimigo.h"
#include "../Entidades/Obstaculos/Obstaculo.h"


class Projetil;

namespace Gerenciadores {

    class Gerenciador_Colisoes {
    private:
        
        std::vector<Personagens::Inimigo*> LIs;
        std::list<Entidades::Obstaculo*> LOs;
        std::set<Projetil*> Lps; 
        Personagens::Jogador* pJog1;

    private:
        bool verificarColisao(Entidades::Entidade* pe1, Entidades::Entidade* pe2) const;
        void tratarColisoesJogsObstacs();
        void tratarColisoesJogsInimgs();
        void tratarColisoesJogsProjeteis();

    public:
        Gerenciador_Colisoes();
        ~Gerenciador_Colisoes();

        void setJogador(Personagens::Jogador* pJog);

    
        void incluirInimigo(Personagens::Inimigo* pi);
        void incluirObstaculo(Entidades::Obstaculo* po);
        void incluirProjetil(Projetil* pj);
        void executar();
    };

} 