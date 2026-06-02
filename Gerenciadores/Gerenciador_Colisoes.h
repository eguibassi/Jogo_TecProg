#pragma once
#include <vector>
#include <list>
#include <set>
#include "../Entidades/Personagens/Jogador.h"
#include "../Entidades/Personagens/Inimigo.h"
#include "../Entidades/Obstaculos/Obstaculo.h"
#include "../Entidades/Projetil.h" 
/*remover a seta em cima e deixar so a linha sem seta*/
namespace Gerenciadores {

    class Gerenciador_Colisoes {
    private:
        Personagens::Jogador* pJog1;
        std::vector<Personagens::Inimigo*> LIs;
        std::list<Entidades::Obstaculo*> LOs;

        std::set<Entidades::Projetil*> Lps; 
    private:
        bool verificarColisao(Entidades::Entidade* pe1, Entidades::Entidade* pe2) const;
        void tratarColisoesJogsObstacs();
        void tratarColisoesInimigsObstacs(); // Movida junto por coerência arquitetural
        void tratarColisoesJogsInimgs();
        void tratarColisoesJogsProjeteis();

    public:
        Gerenciador_Colisoes();
        ~Gerenciador_Colisoes();

        void setJogador(Personagens::Jogador* pJog);
        
        
        void incluirProjetil(Entidades::Projetil* pj); 

        void incluirInimigo(Personagens::Inimigo* pi);
        void incluirObstaculo(Entidades::Obstaculo* po);

        void executar();
    };

}