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
            ~Hog();

            Entidades::Projetil* arremessar();
            void executar();
            void danificar(Jogador* p);
            void salvar();
    };

}
