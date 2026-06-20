#pragma once
#include <string>

class RegistroRanking {
public:
    std::string nome;
    int pontos;
public:
    RegistroRanking();
    ~RegistroRanking();
    
    void setNome(const std::string& nome);
    void setPontos(const int pontos);
    bool operator<(const RegistroRanking& outro) const;
};