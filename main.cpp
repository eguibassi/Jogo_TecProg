#include "Gerenciadores/Gerenciador_Grafico.h"
#include "Gerenciadores/Gerenciador_Colisoes.h"
#include "Entidades/Personagens/Jogador.h"
#include "Entidades/Personagens/Inimigo.h" 
#include "Entidades/Obstaculos/Plataforma.h" 
#include "Entidades/Obstaculos/ObstaculoDano.h" 
#include "Entidades/Obstaculos/ObstaculoLento.h" 

using namespace Personagens;
using namespace Entidades;
using namespace Gerenciadores;

class Hog : public Inimigo {
public:
    Hog() {}
    void executar()  { mover(); }
    void danificar(Jogador* p) {}
    void salva()  {}
    void salvar() {}
};

int main() {
    // === O GERENCIADOR GRÁFICO ASSUME O CONTROLE DA JANELA ===
    Gerenciador_Grafico* pGrafico = Gerenciador_Grafico::getInstancia();

    Jogador jogador;
    Hog inimigoTeste;
    inimigoTeste.setJogador(&jogador);
    
    Plataforma chao;
    ObstaculoDano espinho;
    ObstaculoLento lama; 

    Gerenciador_Colisoes gerenciador;
    
    gerenciador.setJogador(&jogador);
    gerenciador.incluirInimigo(&inimigoTeste);
    gerenciador.incluirObstaculo(&chao);
    gerenciador.incluirObstaculo(&espinho);
    gerenciador.incluirObstaculo(&lama);

    // O loop agora pergunta para o Gerenciador Gráfico se a janela está aberta
    while (pGrafico->verificaJanelaAberta()) {
        sf::Event event;
        // Pega os eventos através do ponteiro da janela do Gerenciador
        while (pGrafico->getWindow()->pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                pGrafico->fecharJanela();
        }

        jogador.executar();
        inimigoTeste.executar(); 
        chao.executar(); 
        espinho.executar(); 
        lama.executar();

        gerenciador.executar();

        // === LIMPANDO E DESENHANDO USANDO O GERENCIADOR ===
        pGrafico->limparJanela();
        
        chao.desenhar(pGrafico->getWindow());
        lama.desenhar(pGrafico->getWindow());
        espinho.desenhar(pGrafico->getWindow());
        
        jogador.desenhar(pGrafico->getWindow());
        inimigoTeste.desenhar(pGrafico->getWindow());
        
        pGrafico->mostrarElementos();
    }

    return 0;
}