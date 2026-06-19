#include <iostream>
#include "Inimigo.h"
#include "../Projetil.h"
#include "../../Gerenciadores/Gerenciador_Grafico.h"

namespace Personagens{
    class Hog : public Inimigo{    
        private:
            short int forca;
        public:
            Hog();
            Hog(
        bool ativo,
        int x,
        int y,
        int vidas,
        int nivel,
        float vx,
        float vy,
        int direcao,
        int forca
    );
            ~Hog();

            Entidades::Projetil* arremessar();
            void executar();
            void danificar(Jogador* p);
            void salvar();

            
    };

}
