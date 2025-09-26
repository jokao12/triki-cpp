#include "Game.h"
#include <iostream>
#include <fstream>
#include "FileManager.h" 

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
    // Crear instancia de FileManager
    FileManager fileManager;
    
    // Validar nombre del archivo
    if (!FileManager::isValidFilename(filename)) {
        std::cout << "[ERROR] Nombre de archivo inválido: " << filename << std::endl;
        return false;
    }
    
    // Agregar extension si no la tiene
    std::string fullFilename = filename;
    if (fullFilename.find(".triki") == std::string::npos) {
        fullFilename += ".triki";
    }
    
    // Crear ruta completa
    std::string fullPath = fileManager.getSaveDirectory() + "/" + fullFilename;
    
    // Abrir archivo binario para escritura
    std::ofstream file(fullPath, std::ios::binary);
    
    if (!file.is_open()) {
        std::cout << "[ERROR] No se pudo crear el archivo: " << fullPath << std::endl;
        return false;
    }
    
    std::cout << "\n=== GUARDANDO PARTIDA CON PUNTEROS ===" << std::endl;
    
    // USO DE PUNTEROS EXPLICITO:
    // 1. Puntero al tablero (ya lo tenemos)
    char* boardPtr = board;
    std::cout << "Direccion del tablero: " << (void*)boardPtr << std::endl;
    
    // 2. Punteros a las variables de estado
    const char* playerPtr = &currentPlayer;
    const bool* gameEndedPtr = &gameEnded;
    const char* winnerPtr = &winner;
    
    std::cout << "Direccion currentPlayer: " << (void*)playerPtr << std::endl;
    std::cout << "Direccion gameEnded: " << (void*)gameEndedPtr << std::endl;
    std::cout << "Direccion winner: " << (void*)winnerPtr << std::endl;
    
    // ESCRITURA USANDO ARITMETICA DE PUNTEROS:
    // Escribir tablero byte por byte
    for (int i = 0; i < boardSize; i++) {
        char* currentPos = boardPtr + i;  // Aritmética de punteros
        file.write(currentPos, sizeof(char));
        std::cout << "Escribiendo posicion [" << i << "]: '" 
                  << *currentPos << "' desde " << (void*)currentPos << std::endl;
    }
    
    // Escribir estado usando punteros
    file.write(playerPtr, sizeof(char));
    file.write(reinterpret_cast<const char*>(gameEndedPtr), sizeof(bool));
    file.write(winnerPtr, sizeof(char));
    
    file.close();
    
    std::cout << "Partida guardada exitosamente: " << fullFilename << std::endl;
    std::cout << "====================================\n" << std::endl;
    
    // Mostrar información del directorio
    fileManager.showDirectoryInfo();
    
    return true;
}


// Implementar loadGame() en Game.cpp
bool Game::loadGame(const std::string& filename) {
    // Crear instancia de FileManager
    FileManager fileManager;
    
    // Validar nombre del archivo
    if (!FileManager::isValidFilename(filename)) {
        std::cout << "[ERROR] Nombre de archivo invalido: " << filename << std::endl;
        return false;
    }
    
    // Agregar extension si no la tiene
    std::string fullFilename = filename;
    if (fullFilename.find(".triki") == std::string::npos) {
        fullFilename += ".triki";
    }
    
    // Verificar que el archivo existe
    if (!fileManager.fileExists(fullFilename)) {
        std::cout << "[ERROR] Archivo no encontrado: " << fullFilename << std::endl;
        return false;
    }
    
    // Crear ruta completa
    std::string fullPath = fileManager.getSaveDirectory() + "/" + fullFilename;
    
    // Abrir archivo binario para lectura
    std::ifstream file(fullPath, std::ios::binary);
    
    if (!file.is_open()) {
        std::cout << "[ERROR] No se pudo abrir el archivo: " << fullPath << std::endl;
        return false;
    }
    
    std::cout << "\n=== CARGANDO PARTIDA CON PUNTEROS ===" << std::endl;
    
    // USO DE PUNTEROS EXPLICITO PARA LECTURA:
    // 1. Puntero al tablero para lectura byte por byte
    char* boardPtr = board;
    std::cout << "Direccion del tablero para lectura: " << (void*)boardPtr << std::endl;
    
    // 2. Punteros a variables de estado
    char* playerPtr = &currentPlayer;
    bool* gameEndedPtr = &gameEnded;
    char* winnerPtr = &winner;
    
    std::cout << "Direccion currentPlayer: " << (void*)playerPtr << std::endl;
    std::cout << "Direccion gameEnded: " << (void*)gameEndedPtr << std::endl;
    std::cout << "Direccion winner: " << (void*)winnerPtr << std::endl;
    
    // LECTURA USANDO ARITMETICA DE PUNTEROS:
    // Leer tablero byte por byte
    for (int i = 0; i < boardSize; i++) {
        char* currentPos = boardPtr + i;  // Aritmetica de punteros
        file.read(currentPos, sizeof(char));
        std::cout << "Leyendo posicion [" << i << "]: '" 
                  << *currentPos << "' en direccion " << (void*)currentPos << std::endl;
    }
    
    // Leer estado usando punteros
    file.read(playerPtr, sizeof(char));
    file.read(reinterpret_cast<char*>(gameEndedPtr), sizeof(bool));
    file.read(winnerPtr, sizeof(char));
    
    file.close();
    
    std::cout << "Partida cargada exitosamente: " << fullFilename << std::endl;
    std::cout << "Estado actual:" << std::endl;
    std::cout << "  - Jugador actual: " << *playerPtr << std::endl;
    std::cout << "  - Juego terminado: " << (*gameEndedPtr ? "Si" : "No") << std::endl;
    std::cout << "  - Ganador: " << (*winnerPtr != ' ' ? std::string(1, *winnerPtr) : "Ninguno") << std::endl;
    std::cout << "===================================\n" << std::endl;
    
    // Mostrar tablero cargado
    displayBoard();
    
    return true;
}

void Game::showMemoryInfo() const {
    std::cout << "\n=== INFORMACIÓN DE MEMORIA ===\n";
    std::cout << "Tablero en heap: " << (void*)board << "\n";
    std::cout << "Tamaño del tablero: " << boardSize << " bytes\n";
    std::cout << "Dirección de currentPlayer (stack): " << (void*)&currentPlayer << "\n";
    std::cout << "Valor actual: " << currentPlayer << "\n";
    std::cout << "===============================\n\n";
}