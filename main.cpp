/*
 * Noms       : Alan Sottile et Boris Hutzli
 * Date rendu : 29.09.2022
 * Labo       : Tic Tac Toe
 */

#include <iostream>

using namespace std;

const int GRID_SIDE_SIZE = 3;
const string PLAYER_ONE_NAME = "joueur 1";
const string PLAYER_TWO_NAME = "joueur 2";
const char PLAYER_ONE_CHAR = 'O';
const char PLAYER_TWO_CHAR = 'X';

enum CellType {
    Empty,
    PlayerOne,
    PlayerTwo
};

// Affiche le résultat de la partie
bool displayResults(CellType winnerType = Empty) {
    string winner;
    switch (winnerType) {
        case PlayerOne:
            cout << PLAYER_ONE_NAME << " a gagne" << endl;
            return true;
        case PlayerTwo:
            cout << PLAYER_TWO_NAME << " a gagne" << endl;
            return true;
        default:
            cout << "Personne a gagne" << endl;
            return false;
    }
}

// Affiche les caractères des joueurs
char cellCharDisplay(CellType cellType) {
    switch (cellType) {
        case PlayerOne:
            return PLAYER_ONE_CHAR;
        case PlayerTwo:
            return PLAYER_TWO_CHAR;
        default:
            return ' ';
    }
}

// Vérifie si un joueur à gagné
bool checkWinner(const CellType (&gameData)[GRID_SIDE_SIZE][GRID_SIDE_SIZE]) {

    // Vérification horizontale
    for (int i = 0; i < GRID_SIDE_SIZE; i++) {
        CellType type = gameData[i][0];
        if (type != CellType::Empty && gameData[i][1] == type && gameData[i][2] == type) {
            displayResults(type);
            return true;
        }
    }

    // Vérification verticale
    for (int i = 0; i < GRID_SIDE_SIZE; i++) {
        CellType type = gameData[0][i];
        if (type != CellType::Empty && gameData[1][i] == type && gameData[2][i] == type) {
            displayResults(type);
            return true;
        }
    }

    // Vérification diagonale haut-gauche à bas-droite
    {
        CellType type = gameData[0][0];
        if (type != CellType::Empty && gameData[1][1] == type && gameData[2][2] == type) {
            displayResults(type);
            return true;
        }
    }

    // Vérification diagonale haut-droite à bas-gauche
    {
        CellType type = gameData[0][2];
        if (type != CellType::Empty && gameData[1][1] == type && gameData[2][0] == type) {
            displayResults(type);
            return true;
        }
    }

    return false;
}

// Vérifie si toutes les cases sont remplies
bool checkTie(const CellType (&gameData)[GRID_SIDE_SIZE][GRID_SIDE_SIZE]) {
    for (int y = 0; y < GRID_SIDE_SIZE; y++) {
        for (int x = 0; x < GRID_SIDE_SIZE; x++) {
            if (gameData[y][x] == CellType::Empty) {
                return false;
            }
        }
    }

    displayResults();
    return true;
}

// Affiche la grille du jeu avec les pions à partir de gameData
void displayGrid(const CellType (&gameData)[GRID_SIDE_SIZE][GRID_SIDE_SIZE]) {
    cout << "   0   1   2 " << endl;
    for (int y = 0; y < GRID_SIDE_SIZE * 2; y++) {
        if (y % 2 == 0) {
            cout << y/2 << " ";
            for (int x = 0; x < GRID_SIDE_SIZE; x++) {
                cout << " " << cellCharDisplay(gameData[y/2][x]);
                if (x < GRID_SIDE_SIZE - 1) {
                    cout << " |";
                }
            }
            cout << endl;
        } else {
            if (y < GRID_SIDE_SIZE * 2 - 1) {
                cout << "  --- --- ---" << endl;
            }
        }
    }

    cout << endl;
}

// Récupère le nom du joueur à partir du bool (true = joueur 1, false = joueur 2)
string getPlayerName(bool player) {
    return player ? PLAYER_ONE_NAME : PLAYER_TWO_NAME;
}

int main() {
    bool gameEnded = false;
    bool playerTurn = false; // true = joueur 1, false = joueur 2

    // Tableau contenant les données des cases
    CellType gameData[GRID_SIDE_SIZE][GRID_SIDE_SIZE] = {
            {Empty, Empty, Empty},
            {Empty, Empty, Empty},
            {Empty, Empty, Empty}
    };
    cout << "  "<< endl;
    cout << "+-------------+"<< endl;
    cout << "| Tic-tac-toe |"<< endl;
    cout << "+-------------+"<< endl;
    cout << "  "<< endl;
    displayGrid(gameData);

    while (!gameEnded) {
        playerTurn = !playerTurn;

        char xCoord, yCoord; // Coordonées de la case où le joueur veut placer son pion
        cout << "C'est au " << getPlayerName(playerTurn) << " a jouer" << endl;
        cout << "Ecrivez les coordonees de la case dans laquelle vous voudriez placer votre pion (0, 1, 2):" << endl;

        bool cellFree; // true si la case du pion placé était vide

        do {
            // Redemande la coordonnée x si elle n'est pas à 0, 1 ou 2
            do {
                cout << "x : ";
                cin >> xCoord;
                xCoord -= '0';
            } while (xCoord > 2);

            // Redemande la coordonnée y si elle n'est pas à 0, 1 ou 2
            do {
                cout << "y : ";
                cin >> yCoord;
                yCoord -= '0';
            } while (yCoord > 2);

            if (gameData[yCoord][xCoord] != CellType::Empty) {
                cellFree = false;
                cout << "Il y a deja un pion sur cette case!" << endl;
            } else {
                cellFree = true;
            }
        } while (!cellFree);

        // Insère la donnée dans le tableau des cases à la coordonnée saise
        gameData[yCoord][xCoord] = playerTurn ? CellType::PlayerOne : CellType::PlayerTwo;

        cout << "\n\n";

        displayGrid(gameData);
        gameEnded = checkWinner(gameData);
        if (!gameEnded) {
            gameEnded = checkTie(gameData);
        }
    }

    return 0;
}
