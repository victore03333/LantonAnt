//
// Created by victor-manoel on 25/06/24.
//

#ifndef TRABALHO_VLANGTONANT_H
#define TRABALHO_VLANGTONANT_H
#include "VLangtonAnt.h"
#include <SFML/Graphics.hpp>
#include <vector>
#include <string>

#define NUM_QUADRADO 100

struct cordenada{
    int x;
    int y;
};
class VLangtonAnt {
private:
    void passoDaFormiga();
    void pause(float delay1);
    void desenha(sf::RenderWindow &window);

    //matriz
    std::vector<std::vector<sf::RectangleShape>> grade;
    std::vector<std::vector<int>> corGrade;

    //regras e suas cores
    std::vector<sf::Color> corExistentes;
    std::string regras;

    //posição atual da formiga
    cordenada posicaoFormiga;

    char direcaoFormiga;
public:
    VLangtonAnt();
    void exec();
};


#endif //TRABALHO_VLANGTONANT_H
