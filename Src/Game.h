#ifndef GAME_H
#define GAME_H

#include <string>

class Game {
private:
    char* board;        // Puntero al tablero dinámico en heap
    int boardSize;      // Tamaño del tablero (9 para 3x3)
    char currentPlayer; // Jugador actual ('X' o 'O')
    bool gameEnded;     // Estado del juego
    char winner;        // Ganador del juego
    
    // Función helper para convertir (fila,columna) a índice
    int getIndex(int row, int col) const;
    
public:
    // Constructor y destructor
    Game();
    ~Game();
    
    // Constructor copia y operador asignación (Regla de los 3)
    Game(const Game& other);
    Game& operator=(const Game& other);
    
    // Métodos principales del juego
    void displayBoard() const;
    bool makeMove(int row, int col);
    bool checkWinner();
    bool isBoardFull() const;
    void switchPlayer();
    void resetGame();
    
    // Métodos de acceso (getters)
    char getCurrentPlayer() const;
    char getWinner() const;
    bool isGameEnded() const;
    char getCellValue(int row, int col) const;
    
    // Método principal de juego
    void playGame();
    
    // Métodos para manejo de archivos (para implementar después)
    bool saveGame(const std::string& filename) const;
    bool loadGame(const std::string& filename);
    
    // Método para mostrar información de memoria (educativo)
    void showMemoryInfo() const;
};

#endif