#include "Game.h"
#include <iostream>

int main() {
    std::cout << "=== TRIKI CON MANEJO DE MEMORIA ===\n";
    std::cout << "Demostrando: punteros, heap, stack, new/delete\n\n";
    
    // Crear objeto Game en stack (constructor se ejecuta)
    Game triki;
    
    std::cout << "Iniciando juego...\n";
    triki.playGame();
    
    std::cout << "\nGracias por jugar!\n";
    std::cout << "Liberando memoria automáticamente...\n";
    
    return 0;  // Destructor se ejecuta automáticamente
}