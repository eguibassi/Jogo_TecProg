# 1. Variáveis
CXX = g++
TARGET = main.exe
LIBS = -lsfml-graphics -lsfml-window -lsfml-system

# 2. Lista de todos os seus arquivos .cpp
SRCS = main.cpp \
       Jogo.cpp \
	   menu.cpp \
       Ente.cpp \
       Fases/Fase.cpp \
       Fases/Fase_Primeira.cpp \
       Listas/ListaEntidades.cpp \
       Entidades/Entidade.cpp \
       Entidades/Projetil.cpp \
       Entidades/Personagens/personagem.cpp \
       Entidades/Personagens/Jogador.cpp \
       Entidades/Personagens/Inimigo.cpp \
       Entidades/Personagens/Goblin.cpp \
       Entidades/Personagens/Pekka.cpp \
       Entidades/Obstaculos/Obstaculo.cpp \
       Entidades/Obstaculos/Plataforma.cpp \
       Entidades/Obstaculos/ObstaculoDano.cpp \
       Entidades/Obstaculos/ObstaculoLento.cpp \
       Gerenciadores/Gerenciador_Colisoes.cpp \
       Gerenciadores/Gerenciador_Grafico.cpp

# 3. A "Regra" de compilação
all:
	$(CXX) $(SRCS) -o $(TARGET) $(LIBS)

# Regra para limpar o executável (opcional)
clean:
	del $(TARGET)