#include "Gerenciador_Colisoes.h"
#include "../Entidades/Obstaculos/Plataforma.h" 
#include <cmath> 

/*O método das colisões foi extraído majoritariamente do exemplo do monitor Giovanni
https://github.com/Giovanenero/JogoPlataforma2D-Jungle/blob/main/Jungle%2B%2B/src/Gerenciador/GerenciadorColisao.cpp */



namespace Gerenciadores {

    Gerenciador_Colisoes::Gerenciador_Colisoes() : pJog1(nullptr), pJog2(nullptr),chaoFase(nullptr){}

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

        if (pJog1 != nullptr && pJog1->getAtivo()) {
            for (auto it = LOs.begin(); it != LOs.end(); ++it) {
                Entidades::Obstaculo* obs = *it;

                if (obs == nullptr) {
                    continue;
                }

                if (verificarColisao(pJog1, obs)) {
                    if (dynamic_cast<Entidades::ObstaculoLento*>(obs) != nullptr) {
                        obs->obstaculizar(pJog1);
                            continue;
                    }
                    sf::FloatRect rectJogador = pJog1->getCorpo().getGlobalBounds();/*pega hitbox*/
                    sf::FloatRect rectObs = obs->getCorpo().getGlobalBounds();

                    float centroJogX = rectJogador.left + rectJogador.width / 2.0f; /*calacula o cenntro*/
                    float centroJogY = rectJogador.top + rectJogador.height / 2.0f;
                    float centroObsX = rectObs.left + rectObs.width / 2.0f;
                    float centroObsY = rectObs.top + rectObs.height / 2.0f;

                    float distX = centroJogX - centroObsX; /*distancia entre os centros*/
                    float distY = centroJogY - centroObsY;

                    float minDistX = (rectJogador.width / 2.0f) + (rectObs.width / 2.0f); /*distancia pra eles nao se sobreporem*/
                    float minDistY = (rectJogador.height / 2.0f) + (rectObs.height / 2.0f);

                    float intersectX = std::abs(distX) - minDistX; /*vendo se um entrou no outro*/
                    float intersectY = std::abs(distY) - minDistY;

                    if (intersectX < 0.0f && intersectY < 0.0f) { /*se for negativo entrou*/
                        sf::Vector2f velJog = pJog1->getVelocidade();
                        sf::Vector2f posJog = pJog1->getPosicao();
                        /*empurrando ele pra fora*/
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

        if (pJog2 != nullptr && pJog2->getAtivo()) {
            for (auto it = LOs.begin(); it != LOs.end(); ++it) {
                Entidades::Obstaculo* obs = *it;

                if (obs == nullptr) {
                    continue;
                }

                if (verificarColisao(pJog2, obs)) {
                    if (dynamic_cast<Entidades::ObstaculoLento*>(obs) != nullptr) {
                        obs->obstaculizar(pJog2);
                        continue;}
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

           
            if (pJog1 != nullptr && pJog1->getAtivo() && verificarColisao(pJog1, ini)) {
                
                ini->danificar(pJog1);

                sf::FloatRect rectJog = pJog1->getCorpo().getGlobalBounds();
                sf::FloatRect rectIni = ini->getCorpo().getGlobalBounds();

                float centroJogX = rectJog.left + rectJog.width / 2.0f;
                float centroIniX = rectIni.left + rectIni.width / 2.0f;

                sf::Vector2f posJog = pJog1->getPosicao();
                sf::Vector2f velJog = pJog1->getVelocidade();

                // Se o jogador estiver à esquerda do Inimigo, é empurrado para a esquerda
                if (centroJogX < centroIniX) {
                    posJog.x -= 25.0f; 
                    velJog.x = -5.0f;  
                } 
                // Se estiver à direita, é empurrado para a direita
                else {
                    posJog.x += 25.0f; 
                    velJog.x = 5.0f;
                }

                velJog.y = -3.0f; 

                pJog1->setPosicao(posJog.x, posJog.y);
                pJog1->setVelocidade(velJog);
            }

           
            if (pJog2 != nullptr && pJog2->getAtivo() && verificarColisao(pJog2, ini)) {
                
                ini->danificar(pJog2);

                sf::FloatRect rectJog = pJog2->getCorpo().getGlobalBounds();
                sf::FloatRect rectIni = ini->getCorpo().getGlobalBounds();

                float centroJogX = rectJog.left + rectJog.width / 2.0f;
                float centroIniX = rectIni.left + rectIni.width / 2.0f;

                sf::Vector2f posJog = pJog2->getPosicao();
                sf::Vector2f velJog = pJog2->getVelocidade();

                if (centroJogX < centroIniX) {
                    posJog.x -= 25.0f; 
                    velJog.x = -5.0f;
                } else {
                    posJog.x += 25.0f; 
                    velJog.x = 5.0f;
                }

                velJog.y = -3.0f; 

                pJog2->setPosicao(posJog.x, posJog.y);
                pJog2->setVelocidade(velJog);
            }
        }
    }

    void Gerenciador_Colisoes::tratarColisoesJogsProjeteis() {
        std::set<Entidades::Projetil*>::iterator itProj;

        for (itProj = Lps.begin(); itProj != Lps.end(); ++itProj) {
            Entidades::Projetil* proj = *itProj;

            if (proj == nullptr || !proj->getAtivo()) {
                continue;
            }

            // Colisão do projétil com inimigo:
            // causa dano no inimigo e desativa o projétil
            std::list<Personagens::Inimigo*>::iterator itIni;

            for (itIni = LIs.begin(); itIni != LIs.end(); ++itIni) {
                Personagens::Inimigo* ini = *itIni;

                if (ini == nullptr || !ini->getAtivo()) {
                    continue;
                }

                if (verificarColisao(proj, ini)) {
                    ini->tomarDano(proj->getDano());
                    proj->setAtivo(false);
                    break;
                }
        }

        // Se o projétil já bateu no inimigo, não precisa testar plataforma
        if (!proj->getAtivo()) {
            continue;
        }

        // Colisão do projétil com plataforma:
        // apenas desativa o projétil
        std::list<Entidades::Obstaculo*>::iterator itObs;

        
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
    
    void Gerenciador_Colisoes::setChao(sf::RectangleShape* chao) {
        chaoFase = chao;
    }

    void Gerenciador_Colisoes::tratarColisoesChao() {
        if (!chaoFase) return;

        sf::FloatRect boundsChao = chaoFase->getGlobalBounds();

        if (pJog1 && pJog1->getAtivo()) {
            sf::FloatRect boundsJog = pJog1->getCorpo().getGlobalBounds();
            if (boundsJog.intersects(boundsChao)) {
                sf::Vector2f pos = pJog1->getPosicao();
                pos.y = boundsChao.top - boundsJog.height; // Coloca exatamente em cima do chão
                pJog1->setPosicao(pos.x, pos.y);
                
                sf::Vector2f vel = pJog1->getVelocidade();
                vel.y = 0.0f; 
                pJog1->setVelocidade(vel);
            }
        }
 
        if (pJog2 && pJog2->getAtivo()) {
            sf::FloatRect boundsJog2 = pJog2->getCorpo().getGlobalBounds();
            if (boundsJog2.intersects(boundsChao)) {
                sf::Vector2f pos = pJog2->getPosicao();
                pos.y = boundsChao.top - boundsJog2.height; // Coloca em cima do chão
                pJog2->setPosicao(pos.x, pos.y);
                
                sf::Vector2f vel = pJog2->getVelocidade();
                vel.y = 0.0f; 
                pJog2->setVelocidade(vel);
            }
        }

        for (auto it = LIs.begin(); it != LIs.end(); ++it) {
            Personagens::Inimigo* ini = *it; // Pega o inimigo apontado pelo iterador
            
            if (ini) {
                sf::FloatRect boundsIni = ini->getCorpo().getGlobalBounds();
                if (boundsIni.intersects(boundsChao)) {
                    sf::Vector2f pos = ini->getPosicao();
                    pos.y = boundsChao.top - boundsIni.height;
                    ini->setPosicao(pos.x, pos.y);
                    
                    sf::Vector2f vel = ini->getVelocidade();
                    vel.y = 0.0f; 
                    ini->setVelocidade(vel);
                }
            }
        }
    }

        void Gerenciador_Colisoes::tratarColisaoBorda() {
        std::list<Personagens::Personagem*> personagens;

        if (pJog1 != nullptr && pJog1->getAtivo()) {
            personagens.push_back(pJog1);
        }

        if (pJog2 != nullptr && pJog2->getAtivo()) {
            personagens.push_back(pJog2);
        }

        for (std::list<Personagens::Inimigo*>::iterator it = LIs.begin(); it != LIs.end(); ++it) {
            if (*it != nullptr) {
                personagens.push_back(*it);
            }
        }

        for (std::list<Personagens::Personagem*>::iterator it = personagens.begin(); it != personagens.end(); ++it) {
            Personagens::Personagem* pPers = *it;

            sf::FloatRect bounds = pPers->getCorpo().getGlobalBounds();
            sf::Vector2f pos = pPers->getPosicao();
            sf::Vector2f vel = pPers->getVelocidade();

            if (bounds.left < 0.0f) {
                pos.x -= bounds.left;
                vel.x = 0.0f;
            }

            if (bounds.left + bounds.width > LARGURA_TELA) {
                pos.x -= (bounds.left + bounds.width) - LARGURA_TELA;
                vel.x = 0.0f;
            }

            if (bounds.top < 0.0f) {
                pos.y -= bounds.top;
                vel.y = 0.0f;
            }

            pPers->setPosicao(
                static_cast<int>(pos.x),
                static_cast<int>(pos.y)
            );

            pPers->setVelocidade(vel);
        }
    }

    void Gerenciador_Colisoes::executar() {
        tratarColisoesChao(); 
        tratarColisaoBorda();
        tratarColisoesJogsObstacs();     
        tratarColisoesInimigsObstacs(); 
        tratarColisoesJogsInimgs();      
        tratarColisoesJogsProjeteis();
        tratarColisaoBorda();
    }

}