#include <iostream>
#include <conio.h>
#include <ctime>
#include <cstdlib>

using namespace std;

const int SIZE = 3;
const int EMPTY = 0;

void taobang(int bang[][SIZE]) {
    system("cls"); 
    for (int i = 0; i < SIZE; ++i) {
        for (int j = 0; j < SIZE; ++j) {
            if (bang[i][j] == EMPTY) {
                cout << "   ";
            } else {
                cout << " " << bang[i][j] << " ";
            }
        }
        cout << endl;
    }
}

bool kiemtra(int bang[][SIZE]) {
    int tile = 1;
    for (int i = 0; i < SIZE; ++i) {
        for (int j = 0; j < SIZE; ++j) {
            if (bang[i][j] != tile && (i != SIZE - 1 || j != SIZE - 1)) {
                return false;
            }
            tile++;
        }
    }
    return true;
}

void hoanvi(int& a, int& b) {
    int temp = a;
    a = b;
    b = temp;
}

void sapxep(int bang[][SIZE], char huong, int& hang, int& cot) {
    int newRow = hang;
    int newCol = cot;

    switch (huong) {
        case 'S': case 's': 
            newRow = hang - 1;
            break;
        case 'W': case 'w': 
            newRow = hang + 1;
            break;
        case 'D': case 'd': 
            newCol = cot - 1;
            break;
        case 'A': case 'a': 
            newCol = cot + 1;
            break;
    }

    if (newRow >= 0 && newRow < SIZE && newCol >= 0 && newCol < SIZE) {
        hoanvi(bang[hang][cot], bang[newRow][newCol]);
        hang = newRow;
        cot = newCol;
    }
}

void taonbangngaunhien(int bang[][SIZE]) {
    srand(time(0));
    int flatBoard[SIZE * SIZE];
    for (int i = 0; i < SIZE * SIZE; ++i) {
        flatBoard[i] = i;
    }

    for (int i = SIZE * SIZE - 1; i > 0; --i) {
        int j = rand() % (i + 1);
        swap(flatBoard[i], flatBoard[j]);
    }

    for (int i = 0; i < SIZE; ++i) {
        for (int j = 0; j < SIZE; ++j) {
            bang[i][j] = flatBoard[i * SIZE + j];
        }
    }
}

void tugiai(int bang[][SIZE]) {
    srand(time(0));
    int moves = rand() % 50 + 50;

    int hang, cot;
    for (int i = 0; i < moves; ++i) {
        for (int j = 0; j < SIZE; ++j) {
            for (int k = 0; k < SIZE; ++k) {
                if (bang[j][k] == EMPTY) {
                    hang = j;
                    cot = k;
                    break;
                }
            }
        }

        char huong;
        switch (rand() % 4) {
            case 0: huong = 'W'; break;
            case 1: huong = 'S'; break;
            case 2: huong = 'A'; break;
            case 3: huong = 'D'; break;
        }

        sapxep(bang, huong, emptyRow, emptyCol);
    }
}

void ketthuc(int bang[][SIZE], int& hang, int& cot) {
    int tile = 1;
    for (int i = 0; i < SIZE; ++i) {
        for (int j = 0; j < SIZE; ++j) {
            if (bang[i][j] != EMPTY) {
                bang[i][j] = tile;
                tile++;
            }
        }
    }
    hang = SIZE - 1;
    cot = SIZE - 1;
}

void sapxeptheothutu(int bang[][SIZE]) {
    int tile = 1;
    for (int i = 0; i < SIZE; ++i) {
        for (int j = 0; j < SIZE; ++j) {
            bang[i][j] = tile;
            tile++;
        }
    }
    bang[SIZE - 1][SIZE - 1] = EMPTY;
}

int main() {
    int bang[SIZE][SIZE];
    int hang, cot;

    taonbangngaunhien(bang);
    tugiai(bang);

    for (int i = 0; i < SIZE; ++i) {
        for (int j = 0; j < SIZE; ++j) {
            if (bang[i][j] == EMPTY) {
                hang = i;
                cot = j;
            }
        }
    }

    while (true) {
        taobang(bang);

        if (kiemtra(bang)) {
            cout << "Chuc mung! Ban da vuot qua tro choi" << endl;
            break;
        }

        cout << "Su dung ' W , A , D , S' de di chuyen. Nhan 'Z' de ket thuc chuong trinh. Nhan 'O'de tu dong sap xep ";
        char move = _getch();

        if (move == 'Z' || move == 'z') {
            ketthuc(bang, hang, cot);
            break;
        } else if (move == 'O' || move == 'o') {
            sapxeptheothutu(bang);
        } else {
            sapxep(bang, move, hang, cot);
        }
    }

    return 0;
}

