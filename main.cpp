#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>
#include <SFML/Network.hpp>
#include <iostream>
#include <string>
#include <thread>


using namespace std;

void tabuleiro(vector<string> piece) {
    for (int i = 0; i < 4; i++) {
        cout << piece[i] << endl;
    }
    cout << endl;
}

pair<vector<string>, vector<int>> generate(vector<string> myvector, vector<pair<int,int>> positions){
    srand((unsigned) time(NULL));
    int seedx = rand() % 8;
    int seedy = rand() % 3;


    while(myvector[seedy][seedx] == 'O'){
        seedx = rand() % 8;
        seedy = rand() % 3;
    }
    myvector[seedy][seedx] = 'X';

    pair<vector<string>, vector<int>> MyPair = make_pair(myvector, vector<int> {seedy, seedx});
    return MyPair;
}


vector<string> update(vector<pair<int,int>> positions, vector<string> tabel, int body){
    for(int i = 0; i < body-1; i++){
        tabel[positions[i].first][positions[i].second] = 'O';
    }
    return tabel;


};

int main(){


    vector<string> piece = {
            {"---------"},
            {"---------"},
            {"---------"},
            {"---------"}
    };
    piece[2][4] = 'O';
    tabuleiro(piece);
    int y_final = 2;
    int x_final = 4;
    int last;
    int moved = 0;
    vector<pair <int,int>> positions = {};
    pair MyPair = generate(piece, positions);
    piece = MyPair.first;
    int seedy = MyPair.second[0];
    int seedx = MyPair.second[1];
    int body = 1;

    //Setting up a window
    sf::Window window(sf::VideoMode(640, 480), "My Window", sf::Style::Titlebar | sf::Style::Close);
    sf::Event ev;

    //
    while(window.isOpen()){
        this_thread::sleep_for((std::chrono::seconds(1)));
        moved = 0;
        while(positions.size() >= body){
            piece[positions[0].first][positions[0].second] = '-';
            positions.erase(positions.begin());
        }

        while (window.pollEvent(ev)){
            if(seedx == x_final && seedy == y_final){
                MyPair = generate(piece, positions);
                update(positions, piece, body);
                piece = MyPair.first;
                seedy = MyPair.second[0];
                seedx = MyPair.second[1];
                body++;
            }

            switch (ev.type){
                case sf::Event::Closed:
                    window.close();
                    break;
                case sf::Event::KeyPressed:
                    if(ev.key.code == sf::Keyboard::Left){
                        piece[y_final][x_final] = '-';
                        pair LastPosition {y_final, x_final};
                        x_final -= 1;
                        if (piece[y_final][x_final] != '-') {
                            cout << "You Lost";
                            return 0;
                        }else {
                            piece[y_final][x_final] = 'O';
                            last = -1;
                            moved = 1;
                            positions.push_back(make_pair(y_final, x_final));
                            piece = update(positions, piece, body);
                            tabuleiro(piece);
                            break;
                        }
                    } else if (ev.key.code == sf::Keyboard::Right){
                        piece[y_final][x_final] = '-';
                        x_final += 1;
                        if (piece[y_final][x_final] != '-'){
                            cout << "You Lost";
                            return 0;
                        }else {
                            piece[y_final][x_final] = 'O';
                            last = 1;
                            moved = 1;
                            positions.push_back(make_pair(y_final, x_final));
                            piece = update(positions, piece, body);
                            tabuleiro(piece);
                            break;
                        }
                    }else if (ev.key.code == sf::Keyboard::Up){
                        piece[y_final][x_final] = '-';
                        y_final -= 1;
                        if (piece[y_final][x_final] != '-') {
                            cout << "You Lost";
                            return 0;
                        }else {
                            piece[y_final][x_final] = 'O';
                            last = -10;
                            moved = 1;
                            positions.push_back(make_pair(y_final, x_final));
                            piece = update(positions, piece, body);
                            tabuleiro(piece);
                            break;
                        }
                    }else if (ev.key.code == sf::Keyboard::Down){
                        piece[y_final][x_final] = '-';
                        y_final += 1;
                        if (piece[y_final][x_final] != '-') {
                            cout << "You Lost";
                            return 0;
                        }else {
                            piece[y_final][x_final] = 'O';
                            positions.push_back(make_pair(y_final, x_final));
                            piece = update(positions, piece, body);
                            tabuleiro(piece);
                            last = 10;
                            moved = 1;
                            break;
                        }
                    }
            }



        }



        if (moved == 0){
            if(seedx == x_final && seedy == y_final){
                MyPair = generate(piece, positions);
                update(positions, piece, body);
                piece = MyPair.first;
                seedy = MyPair.second[0];
                seedx = MyPair.second[1];
                body++;
            }
            switch(last){
                case 1:
                    piece[y_final][x_final] = '-';
                    x_final += 1;
                    if (piece[y_final][x_final] != '-') {
                        cout << "You Lost";
                        return 0;
                    }else {
                        piece[y_final][x_final] = 'O';
                        positions.push_back(make_pair(y_final, x_final));
                        piece = update(positions, piece, body);
                        tabuleiro(piece);
                        break;
                    }
                case -1:
                    piece[y_final][x_final] = '-';
                    x_final -= 1;
                    if (piece[y_final][x_final] != '-') {
                        cout << "You Lost";
                        return 0;
                    }else {
                        piece[y_final][x_final] = 'O';
                        positions.push_back(make_pair(y_final, x_final));
                        piece = update(positions, piece, body);
                        tabuleiro(piece);
                        break;
                    }
                case 10:
                    piece[y_final][x_final] = '-';
                    y_final += 1;
                    if (piece[y_final][x_final] != '-') {
                        cout << "You Lost";
                        return 0;
                    }else {
                        piece[y_final][x_final] = 'O';
                        positions.push_back(make_pair(y_final, x_final));
                        piece = update(positions, piece, body);
                        tabuleiro(piece);
                        break;
                    }
                case -10:
                    piece[y_final][x_final] = '-';
                    y_final -= 1;
                    if (piece[y_final][x_final] != '-') {
                        cout << "You Lost";
                        return 0;
                    }else {
                        piece[y_final][x_final] = 'O';
                        positions.push_back(make_pair(y_final, x_final));
                        piece = update(positions, piece, body);
                        tabuleiro(piece);
                        break;
                    }
            }
        }
    }
    return 0;
}