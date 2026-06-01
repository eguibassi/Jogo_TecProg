#include "Gerenciador_Colisoes.h"
#include "../Entidades/Obstaculos/Plataforma.h" 
#include <cmath> 

/*O método das colisões foi extraído majoritariamente do exemplo do monitor Giovanni
https://github.com/Giovanenero/JogoPlataforma2D-Jungle/blob/main/Jungle%2B%2B/src/Gerenciador/GerenciadorColisao.cpp */

/*implementar singleton*/

namespace Gerenciadores {

    Gerenciador_Colisoes::Gerenciador_Colisoes() : pJog1(nullptr), pJog2(nullptr){}

    Gerenciador_Colisoes::~Gerenciador_Colisoes() {}

    void Gerenciador_Colisoes::setJogador(Personagens::Jogador* pJog) {pJog1 = pJog;}

    void Gerenciador_Colisoes::setJogador2(Personagens::Jogador* pJog) {pJog2 = pJog;}

    bool Gerenciador_Colisoes::verificarColisao(Entidades::Entidade* pe1, Entidades::Entidade* pe2) const {
        if (pe1 == nullptr || pe2 == nullptr) {
            return false;
        }

        return pe1->getCorpo().getGlobalBounds().intersects(
            pe2->getCorpo().getGlobalBounds()
        );
    }

    void Gerenciador_Colisoes::tratarColisoesJogsObstacs() {

        if (pJog1 != nullptr) {
            for (auto it = LOs.begin(); it != LOs.end(); ++it) {
                Entidades::Obstaculo* obs = *it;

                if (obs == nullptr) {
                    continue;
                }

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
                            if (distX > 0.0f) {
                                posJog.x -= intersectX;
                            }
                            else {
                                posJog.x += intersectX;
                            }

                            velJog.x = 0.0f;
                        } 
                        else {
                            if (distY > 0.0f) {
                                posJog.y -= intersectY;
                            }
                            else {
                                posJog.y += intersectY;
                            }

                            velJog.y = 0.0f;
                        }

                        pJog1->setPosicao(
                            static_cast<int>(posJog.x),
                            static_cast<int>(posJog.y)
                        );

                        pJog1->setVelocidade(velJog);
                    }

                    obs->obstaculizar(pJog1);
                }
            }
        }

        if (pJog2 != nullptr) {
            for (auto it = LOs.begin(); it != LOs.end(); ++it) {
                Entidades::Obstaculo* obs = *it;

                if (obs == nullptr) {
                    continue;
                }

                if (verificarColisao(pJog2, obs)) {
                    sf::FloatRect rectJogador = pJog2->getCorpo().getGlobalBounds();
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
                        sf::Vector2f velJog = pJog2->getVelocidade();
                        sf::Vector2f posJog = pJog2->getPosicao();

                        if (intersectX > intersectY) {
                            if (distX > 0.0f) {
                                posJog.x -= intersectX;
                            }
                            else {
                                posJog.x += intersectX;
                            }

                            velJog.x = 0.0f;
                        } 
                        else {
                            if (distY > 0.0f) {
                                posJog.y -= intersectY;
                            }
                            else {
                                posJog.y += intersectY;
                            }

                            velJog.y = 0.0f;
                        }

                        pJog2->setPosicao(
                            static_cast<int>(posJog.x),
                            static_cast<int>(posJog.y)
                        );

                        pJog2->setVelocidade(velJog);
                    }

                    obs->obstaculizar(pJog2);
                }
            }
        }
    }

    void Gerenciador_Colisoes::tratarColisoesInimigsObstacs() {
        for (auto itIni = LIs.begin(); itIni != LIs.end(); ++itIni) {
            Personagens::Inimigo* ini = *itIni;

            if (ini == nullptr) {
                continue;
            }

            for (auto it = LOs.begin(); it != LOs.end(); ++it) {
                Entidades::Obstaculo* obs = *it;

                if (obs == nullptr) {
                    continue;
                }

                Entidades::Plataforma* plat = dynamic_cast<Entidades::Plataforma*>(obs);

                if (plat == nullptr) {
                    continue; 
                }

                if (verificarColisao(ini, obs)) {
                    sf::FloatRect rectIni = ini->getCorpo().getGlobalBounds();
                    sf::FloatRect rectObs = obs->getCorpo().getGlobalBounds();

                    float centroIniX = rectIni.left + rectIni.width / 2.0f;
                    float centroIniY = rectIni.top + rectIni.height / 2.0f;
                    float centroObsX = rectObs.left + rectObs.width / 2.0f;
                    float centroObsY = rectObs.top + rectObs.height / 2.0f;

                    float distX = centroIniX - centroObsX;
                    float distY = centroIniY - centroObsY;

                    float minDistX = (rectIni.width / 2.0f) + (rectObs.width / 2.0f);
                    float minDistY = (rectIni.height / 2.0f) + (rectObs.height / 2.0f);

                    float intersectX = std::abs(distX) - minDistX;
                    float intersectY = std::abs(distY) - minDistY;

                    if (intersectX < 0.0f && intersectY < 0.0f) {
                        sf::Vector2f velIni = ini->getVelocidade();
                        sf::Vector2f posIni = ini->getPosicao();

                        if (intersectX > intersectY) {
                            if (distX > 0.0f) {
                                posIni.x -= intersectX;
                            }
                            else {
                                posIni.x += intersectX;
                            }

                            velIni.x = 0.0f;
                        } 
                        else {
                            if (distY > 0.0f) {
                                posIni.y -= intersectY;
                            }
                            else {
                                posIni.y += intersectY;
                            }

                            velIni.y = 0.0f;
                        }

                        ini->setPosicao(
                            static_cast<int>(posIni.x),
                            static_cast<int>(posIni.y)
                        );

                        ini->setVelocidade(velIni);
                    }
                }
            }
        }
    }

    void Gerenciador_Colisoes::tratarColisoesJogsInimgs() {
        for (auto itIni = LIs.begin(); itIni != LIs.end(); ++itIni) {
            Personagens::Inimigo* ini = *itIni;

            if (ini == nullptr) {
                continue;
            }

            if (pJog1 != nullptr && verificarColisao(pJog1, ini)) {
                
            }

            if (pJog2 != nullptr && verificarColisao(pJog2, ini)) {
                
            }
        }
    }

    void Gerenciador_Colisoes::tratarColisoesJogsProjeteis() {
        if (pJog1 == nullptr && pJog2 == nullptr) {
            return;
        }
    }

    void Gerenciador_Colisoes::incluirInimigo(Personagens::Inimigo* pi) {
        if (pi) {
            LIs.push_back(pi);
        }
    }

    void Gerenciador_Colisoes::incluirObstaculo(Entidades::Obstaculo* po) {
        if (po) {
            LOs.push_back(po);
        }
    }

    void Gerenciador_Colisoes::incluirProjetil(Entidades::Projetil* pj) {
        if (pj) {
            Lps.insert(pj);
        }
    }

    void Gerenciador_Colisoes::executar() {
        tratarColisoesJogsObstacs();     
        tratarColisoesInimigsObstacs(); 
        tratarColisoesJogsInimgs();      
        tratarColisoesJogsProjeteis();
    }

}