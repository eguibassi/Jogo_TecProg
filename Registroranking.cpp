#include "Registroranking.h"

RegistroRanking::RegistroRanking(): nome(""), pontos(0){}
RegistroRanking::~RegistroRanking(){}

void RegistroRanking::setNome(const std::string& nome){this->nome = nome;}
void RegistroRanking::setPontos(const int pontos){this->pontos = pontos;}
bool RegistroRanking::operator<(const RegistroRanking& outro) const
{
    if (pontos == outro.pontos){return nome > outro.nome;}
    
    return pontos < outro.pontos;
}