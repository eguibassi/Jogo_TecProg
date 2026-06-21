CXX = g++
TARGET = main.exe
LIBS = -lsfml-graphics -lsfml-window -lsfml-system
INCLUDES = -IMenus

SRCS = main.cpp \
       Jogo.cpp \
       Menus/Menu.cpp \
       Menus/MenuPausa.cpp \
       Ente.cpp \
       Fases/Fase.cpp \
       Fases/Fase_Primeira.cpp \
       Fases/Fase_Segunda.cpp \
       Listas/ListaEntidades.cpp \
       Entidades/Entidade.cpp \
       Entidades/Projetil.cpp \
       Entidades/Personagens/personagem.cpp \
       Entidades/Personagens/Jogador.cpp \
       Entidades/Personagens/Inimigo.cpp \
       Entidades/Personagens/Goblin.cpp \
       Entidades/Personagens/Pekka.cpp \
       Entidades/Personagens/Hog.cpp \
       Entidades/Obstaculos/Obstaculo.cpp \
       Entidades/Obstaculos/Plataforma.cpp \
       Entidades/Obstaculos/Jaula.cpp \
       Entidades/Obstaculos/Pilha.cpp \
       Gerenciadores/Gerenciador_Colisoes.cpp \
       Gerenciadores/Gerenciador_Grafico.cpp

all:
	$(CXX) $(SRCS) $(INCLUDES) -o $(TARGET) $(LIBS)

clean:
	del $(TARGET)