#include "Gerenciador_Colisoes.h"
#include "../Entidades/Obstaculos/Plataforma.h" 
#include <cmath> 
/*O método das colisões foi extraído majoritariamente do exemplo do monitor Giovannihttps://github.com/Giovanenero/JogoPlataforma2D-Jungle/blob/main/Jungle%2B%2B/src/Gerenciador/GerenciadorColisao.cpp */
/*implemenar singleton
/*sem funcoes locais*/
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
                sf::FloatRect rectJogador = pJog1->getCorpo().getGlobalBounds(); /*dimensao e posicao do jogador*/
                sf::FloatRect rectObs = obs->getCorpo().getGlobalBounds();/*dimensao e posicao do obstaculo*/

                float centroJogX = rectJogador.left + rectJogador.width / 2.0f;
                float centroJogY = rectJogador.top + rectJogador.height / 2.0f;
                float centroObsX = rectObs.left + rectObs.width / 2.0f;
                float centroObsY = rectObs.top + rectObs.height / 2.0f;

                float distX = centroJogX - centroObsX;/*distancia entre os dois centros*/
                float distY = centroJogY - centroObsY;

                float minDistX = (rectJogador.width / 2.0f) + (rectObs.width / 2.0f);/*// Calcula a distância mínima que deveriam ter para estar apenas encostados (metade da largura/altura de cada)*/
                float minDistY = (rectJogador.height / 2.0f) + (rectObs.height / 2.0f);

                float intersectX = std::abs(distX) - minDistX;/*// Subtrai a distância real da distância mínima (usando módulo para não ter número negativo) para ver o quanto invadiu*/
                float intersectY = std::abs(distY) - minDistY;

                if (intersectX < 0.0f && intersectY < 0.0f) { /*Se ambos são menores que zero, há intersecção*/
                    sf::Vector2f velJog = pJog1->getVelocidade();
                    sf::Vector2f posJog = pJog1->getPosicao();

                    if (intersectX > intersectY) { /*// Se a invasão no eixo X for maior que a do eixo Y (ou seja, foi colisão vertical)*/
                        if (distX > 0.0f) posJog.x -= intersectX; /*Se bateu pela direita, empurra pra direita*/
                        else posJog.x += intersectX;  /*Se bateu pela esquerda empurra pela esquerda*/
                        velJog.x = 0.0f; 
                    } 
                    else {
                        if (distY > 0.0f) posJog.y -= intersectY;  /*Se bateu vindo de baixo, empurra pra baixo*/
                        else posJog.y += intersectY; 
                        velJog.y = 0.0f; 
                    }

                    pJog1->setPosicao(static_cast<int>(posJog.x), static_cast<int>(posJog.y)); /*aplica a nova posicao*/
                    pJog1->setVelocidade(velJog);
                }

                obs->obstaculizar(pJog1);
            }
        }
    }

    

    void Gerenciador_Colisoes::tratarColisoesInimigsObstacs() {
        for (size_t i = 0; i < LIs.size(); i++) {
            Personagens::Inimigo* ini = LIs[i];
            if (ini == nullptr) continue;

            for (auto it = LOs.begin(); it != LOs.end(); ++it) {
                Entidades::Obstaculo* obs = *it;

                
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
                            if (distX > 0.0f) posIni.x -= intersectX; 
                            else posIni.x += intersectX; 
                            velIni.x = 0.0f; 
                        } 
                        else {
                            if (distY > 0.0f) posIni.y -= intersectY; 
                            else posIni.y += intersectY; 
                            velIni.y = 0.0f; 
                        }

                        ini->setPosicao(static_cast<int>(posIni.x), static_cast<int>(posIni.y));
                        ini->setVelocidade(velIni);
                    }
                }
            }
        }
    }

    void Gerenciador_Colisoes::tratarColisoesJogsInimgs() {
        if (pJog1 == nullptr) return;
        for (size_t i = 0; i < LIs.size(); i++) {
            if (verificarColisao(pJog1, LIs[i])) {
                
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

    void Gerenciador_Colisoes::incluirProjetil(Entidades::Projetil* pj) {
        if (pj) Lps.insert(pj);
    }

    void Gerenciador_Colisoes::executar() {
        tratarColisoesJogsObstacs();     
        tratarColisoesInimigsObstacs(); 
        tratarColisoesJogsInimgs();      
        tratarColisoesJogsProjeteis();
    }

}