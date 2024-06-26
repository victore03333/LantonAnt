//
// Created by victor-manoel on 25/06/24.
//

#include "VLangtonAnt.h"
#include <SFML/Graphics.hpp>
#include <random>
#include <ctime>
#include <unistd.h>
#include <vector>
#include <iostream>

#define JANELA_X 300
#define JANELA_Y 300

VLangtonAnt::VLangtonAnt() {
    //numeros randomicos
    std::random_device rd;   // gerador não deterministico
    std::mt19937 gen(rd());  // gera uma semente
    std::uniform_int_distribution<> dist(0,255);//define os números aleatórios

    //divido o numero de pixel de x e y pela quantidade de quadrados que eu quero
    //para definir o tamanho do quadrado
    float tam_x = JANELA_X/NUM_QUADRADO;
    float tam_y = JANELA_Y/NUM_QUADRADO;

    //variavel para guardar a proxima posição onde um quadrado deve ficar
    float posicao_x;
    float posicao_y = 0;

    //definir regra
    regras = "EEDDDDEE"; //EEDDDDEE
    //define as cores para as regras
    for(int i=0; i<regras.length(); i++){
        sf::Color color(dist(gen), dist(gen), dist(gen), dist(gen));
        corExistentes.insert(corExistentes.end(), color);
    }

    //instaciar quadrados
    sf::RectangleShape quadrado(sf::Vector2f(tam_x, tam_y));
    std::vector<sf::RectangleShape> linha_de_quadrados;
    for(int i=0; i<NUM_QUADRADO; i++){
        posicao_x = 0;
        grade.insert(grade.end(), linha_de_quadrados);
        for(int j=0; j<NUM_QUADRADO; j++){
            grade[i].insert(grade[i].end(), quadrado);
            grade[i][j].setPosition(posicao_x, posicao_y);//define a posição do quadrado

            grade[i][j].setFillColor(corExistentes[0]);

            posicao_x+=tam_x;//pŕoxima posição no eixo x
        }
        posicao_y+=tam_y;//proxima posição no eixo y
    }

    std::vector<int> aux;
    for(int i=0; i<NUM_QUADRADO; i++){
        corGrade.insert(corGrade.end(), aux);
        for(int j=0; j<NUM_QUADRADO; j++){
            corGrade[i].insert(corGrade[i].end(), 0);
        }
    }

    //definir posição da formiga
    posicaoFormiga.x = NUM_QUADRADO/2;
    posicaoFormiga.y = NUM_QUADRADO/2;
    //definir a direção da formiga para cima
    direcaoFormiga = 'c';
}

//funcões públicas
void VLangtonAnt::exec() {

    sf::RenderWindow window(sf::VideoMode(JANELA_X, JANELA_Y), "Formiga");

    int cont=0;
    while (window.isOpen())
    {

        sf::Event event{};
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        if(cont == 5){//mostra na tela a cada 5 passos
            window.clear();
            desenha(window);
            cont=0;
        }
        cont++;

        passoDaFormiga();
        window.display();
        //pause(1);
    }
}
//funções privadas
//
void VLangtonAnt::pause(float delay1) {
    if (delay1<0.001)
        return; // pode ser ajustado e/ou evita-se valores negativos.

    float inst1=0, inst2=0;

    inst1 = (float)clock()/(float)CLOCKS_PER_SEC;

    while (inst2-inst1<delay1)
        inst2 = (float)clock()/(float)CLOCKS_PER_SEC;

}

void VLangtonAnt::desenha(sf::RenderWindow &window) {
    for(int i=0; i<NUM_QUADRADO; i++){
        for(int j=0; j<NUM_QUADRADO; j++){
            grade[i][j].setFillColor(corExistentes[corGrade[i][j]]); //atualiza a corExistentes da matriz
            window.draw(grade[i][j]);
        }
    }
}

void VLangtonAnt::passoDaFormiga() {
    int auxRegra;
    //mudar a cor
    if(corGrade[posicaoFormiga.x][posicaoFormiga.y] < regras.length()-1)//verifica as
        corGrade[posicaoFormiga.x][posicaoFormiga.y]++;//muda a cor atual do quadrado
    else
        corGrade[posicaoFormiga.x][posicaoFormiga.y]=0;

    switch (direcaoFormiga) {
        case 'c':
            if (posicaoFormiga.y>1)
                posicaoFormiga.y--;
            auxRegra = corGrade[posicaoFormiga.x][posicaoFormiga.y];//pega a cor da grade de onde a formiga está
            switch (regras[auxRegra]) {//verifica qual a regra para girar
                case 'D':
                    direcaoFormiga = 'd';
                    break;
                case 'E':
                    direcaoFormiga = 'e';
                    break;
                default:
                    std::cout << "erroC";
            }
            break;
        case 'b':
            if (posicaoFormiga.y<NUM_QUADRADO-1)
                posicaoFormiga.y++;
            auxRegra = corGrade[posicaoFormiga.x][posicaoFormiga.y];
            switch (regras[auxRegra]) {//verifica qual a regra para girar
                case 'D':
                    direcaoFormiga = 'e';
                    break;
                case 'E':
                    direcaoFormiga = 'd';
                    break;
                default:
                    std::cout << "erroB";
            }
            break;
        case 'd':
            if (posicaoFormiga.x<NUM_QUADRADO-1)
                posicaoFormiga.x++;
            auxRegra = corGrade[posicaoFormiga.x][posicaoFormiga.y];
            switch (regras[auxRegra]) {//verifica qual a regra para girar
                case 'D':
                    direcaoFormiga = 'b';
                    break;
                case 'E':
                    direcaoFormiga = 'c';
                    break;
                default:
                    std::cout << "erroD";
            }
            break;
        case 'e':
            if (posicaoFormiga.x>1)
                posicaoFormiga.x--;
            auxRegra = corGrade[posicaoFormiga.x][posicaoFormiga.y];
            switch (regras[auxRegra]) {//verifica qual a regra para girar
                case 'D':
                    direcaoFormiga = 'c';
                    break;
                case 'E':
                    direcaoFormiga = 'b';
                    break;
                default:
                    std::cout << "erroE";
            }
            break;
        default:
            std::cout << "ErroE" << std::endl;
    }
}