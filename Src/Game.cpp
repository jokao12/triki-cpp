#include "Game.h"
#include <iostream>
#include <fstream>

// Constructor - aloca memoria en el heap
Game::Game() {
    boardSize = 9;  // 3x3 = 9 posiciones
    board = new char[boardSize];  // Memoria dinámica en heap
    
    // Inicializar todas las posiciones del tablero
    for (int i = 0; i < boardSize; i++) {
        board[i] = ' ';
    }
    
    currentPlayer = 'X';
    gameEnded = false;
    winner = ' ';
    
    std::cout << "[DEBUG] Memoria alocada para tablero: " << boardSize << " bytes\n";
}

// Destructor - libera memoria del heap
Game::~Game() {
    delete[] board;
    std::cout << "[DEBUG] Memoria liberada del tablero\n";
}

// Constructor copia (Regla de los 3)
Game::Game(const Game& other) {
    boardSize = other.boardSize;
    board = new char[boardSize];  // Nueva memoria
    
    // Copiar contenido
    for (int i = 0; i < boardSize; i++) {
        board[i] = other.board[i];
    }
    
    currentPlayer = other.currentPlayer;
    gameEnded = other.gameEnded;
    winner = other.winner;
}

// Operador de asignación (Regla de los 3)
Game& Game::operator=(const Game& other) {
    if (this != &other) {  // Evitar auto-asignación
        // Liberar memoria actual
        delete[] board;
        
        // Alocar nueva memoria
        boardSize = other.boardSize;
        board = new char[boardSize];
        
        // Copiar contenido
        for (int i = 0; i < boardSize; i++) {
            board[i] = other.board[i];
        }
        
        currentPlayer = other.currentPlayer;
        gameEnded = other.gameEnded;
        winner = other.winner;
    }
    return *this;
}

// Función helper: convierte (fila, columna) a índice lineal
int Game::getIndex(int row, int col) const {
    return row * 3 + col;  // Fórmula: fila*ancho + columna
}

void Game::displayBoard() const {
    std::cout << "\n  0   1   2\n";
    for (int row = 0; row < 3; row++) {
        std::cout << row << " ";
        for (int col = 0; col < 3; col++) {
            int index = getIndex(row, col);
            std::cout << board[index];
            if (col < 2) std::cout << " | ";
        }
        std::cout << "\n";
        if (row < 2) std::cout << "  ---------\n";
    }
    std::cout << "\n";
}

bool Game::makeMove(int row, int col) {
    // Validar posición
    if (row < 0 || row > 2 || col < 0 || col > 2) {
        return false;
    }
    
    int index = getIndex(row, col);
    
    // Verificar si la posición está ocupada
    if (board[index] != ' ') {
        return false;
    }
    
    // Hacer el movimiento
    board[index] = currentPlayer;
    return true;
}

bool Game::checkWinner() {
    // Verificar filas
    for (int row = 0; row < 3; row++) {
        if (board[getIndex(row, 0)] != ' ' && 
            board[getIndex(row, 0)] == board[getIndex(row, 1)] && 
            board[getIndex(row, 1)] == board[getIndex(row, 2)]) {
            winner = board[getIndex(row, 0)];
            gameEnded = true;
            return true;
        }
    }
    
    // Verificar columnas
    for (int col = 0; col < 3; col++) {
        if (board[getIndex(0, col)] != ' ' && 
            board[getIndex(0, col)] == board[getIndex(1, col)] && 
            board[getIndex(1, col)] == board[getIndex(2, col)]) {
            winner = board[getIndex(0, col)];
            gameEnded = true;
            return true;
        }
    }
    
    // Verificar diagonal principal (0,0 -> 1,1 -> 2,2)
    if (board[getIndex(0, 0)] != ' ' && 
        board[getIndex(0, 0)] == board[getIndex(1, 1)] && 
        board[getIndex(1, 1)] == board[getIndex(2, 2)]) {
        winner = board[getIndex(0, 0)];
        gameEnded = true;
        return true;
    }
    
    // Verificar diagonal secundaria (0,2 -> 1,1 -> 2,0)
    if (board[getIndex(0, 2)] != ' ' && 
        board[getIndex(0, 2)] == board[getIndex(1, 1)] && 
        board[getIndex(1, 1)] == board[getIndex(2, 0)]) {
        winner = board[getIndex(0, 2)];
        gameEnded = true;
        return true;
    }
    
    return false;
}

bool Game::isBoardFull() const {
    for (int i = 0; i < boardSize; i++) {
        if (board[i] == ' ') {
            return false;
        }
    }
    return true;
}

void Game::switchPlayer() {
    currentPlayer = (currentPlayer == 'X') ? 'O' : 'X';
}

void Game::resetGame() {
    // Reinicializar tablero
    for (int i = 0; i < boardSize; i++) {
        board[i] = ' ';
    }
    
    currentPlayer = 'X';
    gameEnded = false;
    winner = ' ';
}

char Game::getCurrentPlayer() const {
    return currentPlayer;
}

char Game::getWinner() const {
    return winner;
}

bool Game::isGameEnded() const {
    return gameEnded;
}

char Game::getCellValue(int row, int col) const {
    if (row >= 0 && row < 3 && col >= 0 && col < 3) {
        return board[getIndex(row, col)];
    }
    return ' ';
}

void Game::playGame() {
    int row, col;
    
    std::cout << "=== JUEGO DE TRIKI (con manejo de memoria) ===\n";
    std::cout << "Coordenadas: fila columna (0-2)\n";
    showMemoryInfo();  // Mostrar info de memoria
    
    while (!gameEnded) {
        displayBoard();
        
        std::cout << "Turno del jugador " << currentPlayer << "\n";
        std::cout << "Ingresa fila y columna: ";
        
        std::cin >> row >> col;
        
        if (makeMove(row, col)) {
            if (checkWinner()) {
                displayBoard();
                std::cout << "¡Jugador " << winner << " gana!\n";
                break;
            } else if (isBoardFull()) {
                displayBoard();
                std::cout << "¡Empate!\n";
                gameEnded = true;
                break;
            }
            switchPlayer();
        } else {
            std::cout << "Movimiento inválido. Intenta de nuevo.\n";
        }
    }
}

bool Game::saveGame(const std::string& filename) const {
    // Por implementar en siguiente rama
    return false;
}

bool Game::loadGame(const std::string& filename) {
    // Por implementar en siguiente rama
    return false;
}

void Game::showMemoryInfo() const {
    std::cout << "\n=== INFORMACIÓN DE MEMORIA ===\n";
    std::cout << "Tablero en heap: " << (void*)board << "\n";
    std::cout << "Tamaño del tablero: " << boardSize << " bytes\n";
    std::cout << "Dirección de currentPlayer (stack): " << (void*)&currentPlayer << "\n";
    std::cout << "Valor actual: " << currentPlayer << "\n";
    std::cout << "===============================\n\n";
}