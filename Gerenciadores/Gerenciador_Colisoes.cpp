#include "Gerenciador_Colisoes.h"
#include <cmath> // Para usar std::abs()

namespace Gerenciadores {

    Gerenciador_Colisoes::Gerenciador_Colisoes() : pJog1(nullptr) {
    }

    Gerenciador_Colisoes::~Gerenciador_Colisoes() {
    }

    void Gerenciador_Colisoes::setJogador(Personagens::Jogador* pJog) {
        pJog1 = pJog;
    }

    bool Gerenciador_Colisoes::verificarColisao(Entidades::Entidade* pe1, Entidades::Entidade* pe2) const {
        if (pe1 == nullptr || pe2 == nullptr) return false;
        
        
        return pe1->getCorpo().getGlobalBounds().intersects(pe2->getCorpo().getGlobalBounds());
    }

    void Gerenciador_Colisoes::tratarColisoesJogsObstacs() {
        if (pJog1 == nullptr) return;

        for (auto it = LOs.begin(); it != LOs.end(); ++it) {
            Entidades::Obstaculo* obs = *it;

            
            if (verificarColisao(pJog1, obs)) {
                
               
                sf::FloatRect rectJogador = pJog1->getCorpo().getGlobalBounds();
                sf::FloatRect rectObs = obs->getCorpo().getGlobalBounds();

                float centroJogX = rectJogador.left + rectJogador.width / 2.0f;
                float centroJogY = rectJogador.top + rectJogador.height / 2.0f;
                float centroObsX = rectObs.left + rectObs.width / 2.0f;
                float centroObsY = rectObs.top + rectObs.height / 2.0f;

                float distX = centroJogX - centroObsX;
                float distY = centroJogY - centroObsY;

                float minDistX = (rectJogador.width / 2.0f) + (rectObs.width / 2.0f);
                float minDistY = (rectJogador.height / 2.0f) + (rectObs.height / 2.0f);

                float intersectX = std::abs(distX) - minDistX;
                float intersectY = std::abs(distY) - minDistY;

              
                if (intersectX < 0.0f && intersectY < 0.0f) {
                    
                    sf::Vector2f velJog = pJog1->getVelocidade();
                    sf::Vector2f posJog = pJog1->getPosicao();

                    if (intersectX > intersectY) {
                        
                        if (distX > 0.0f) posJog.x -= intersectX; 
                        else posJog.x += intersectX; 
                        velJog.x = 0.0f; 
                    } 
                    else {
                        
                        if (distY > 0.0f) posJog.y -= intersectY; 
                        else posJog.y += intersectY; 
                        velJog.y = 0.0f; 
                    }

                    
                    pJog1->setPosicao(static_cast<int>(posJog.x), static_cast<int>(posJog.y));
                    pJog1->setVelocidade(velJog);
                }

                
                obs->obstaculizar(pJog1);
            }
        }
    }

    void Gerenciador_Colisoes::tratarColisoesJogsInimgs() {
        if (pJog1 == nullptr) return;

        for (size_t i = 0; i < LIs.size(); i++) {
            if (verificarColisao(pJog1, LIs[i])) {
                // Futuramente resolvemos com o inimigo
            }
        }
    }

    void Gerenciador_Colisoes::tratarColisoesJogsProjeteis() {
        if (pJog1 == nullptr) return;
    }

    void Gerenciador_Colisoes::incluirInimigo(Personagens::Inimigo* pi) {
        if (pi) LIs.push_back(pi);
    }

    void Gerenciador_Colisoes::incluirObstaculo(Entidades::Obstaculo* po) {
        if (po) LOs.push_back(po);
    }

    void Gerenciador_Colisoes::incluirProjetil(Projetil* pj) {
        if (pj) Lps.insert(pj);
    }

    void Gerenciador_Colisoes::executar() {
        tratarColisoesJogsObstacs();
        tratarColisoesJogsInimgs();
        tratarColisoesJogsProjeteis();
    }

} 