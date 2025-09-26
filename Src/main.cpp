#include "Game.h"
#include "FileManager.h"
#include <iostream>
#include <string>
#include <limits>

void showMainMenu() {
    std::cout << "\n=== TRIKI CON MANEJO DE MEMORIA Y ARCHIVOS ===\n";
    std::cout << "1. Nueva partida\n";
    std::cout << "2. Cargar partida guardada\n";
    std::cout << "3. Ver partidas disponibles\n";
    std::cout << "4. Eliminar partida\n";
    std::cout << "5. Informacion del sistema\n";
    std::cout << "6. Salir\n";
    std::cout << "Selecciona una opcion: ";
}

void showSavedGames() {
    FileManager fileManager;
    auto games = fileManager.listSavedGames();
    
    std::cout << "\n=== PARTIDAS GUARDADAS ===\n";
    if (games.empty()) {
        std::cout << "No hay partidas guardadas.\n";
        return;
    }
    
    for (size_t i = 0; i < games.size(); i++) {
        std::cout << (i + 1) << ". " << games[i] << "\n";
    }
    std::cout << "=========================\n";
}

std::string selectSavedGame() {
    FileManager fileManager;
    auto games = fileManager.listSavedGames();
    
    if (games.empty()) {
        std::cout << "No hay partidas guardadas.\n";
        return "";
    }
    
    showSavedGames();
    std::cout << "Selecciona el numero de partida (0 para cancelar): ";
    
    int choice;
    std::cin >> choice;
    
    if (choice < 1 || choice > static_cast<int>(games.size())) {
        std::cout << "Seleccion invalida.\n";
        return "";
    }
    
    return games[choice - 1];
}

void playNewGame() {
    Game triki;
    char saveChoice;
    
    std::cout << "\n=== NUEVA PARTIDA ===\n";
    triki.showMemoryInfo();
    triki.playGame();
    
    // Limpiar buffer ANTES de leer
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    
    std::cout << "\nDeseas guardar esta partida? (s/n): ";
    std::cin >> saveChoice;
    
    if (saveChoice == 's' || saveChoice == 'S') {
        std::string filename;
        
        // Limpiar buffer antes de leer filename
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        
        std::cout << "Nombre del archivo (sin extension): ";
        std::getline(std::cin, filename);  // Usar getline en lugar de >>
        
        if (triki.saveGame(filename)) {
            std::cout << "Partida guardada exitosamente!\n";
        } else {
            std::cout << "Error al guardar la partida.\n";
        }
    }
}

void loadAndPlayGame() {
    std::string filename = selectSavedGame();
    if (filename.empty()) {
        return;
    }
    
    Game triki;
    
    if (triki.loadGame(filename)) {
        std::cout << "\nPartida cargada. Continuando juego...\n";
        
        // Continuar solo si el juego no ha terminado
        if (!triki.isGameEnded()) {
            triki.playGame();
            
            // Ofrecer guardar de nuevo
            char saveChoice;
            std::cout << "\nDeseas guardar el progreso? (s/n): ";
            std::cin >> saveChoice;
            
            if (saveChoice == 's' || saveChoice == 'S') {
                if (triki.saveGame(filename.substr(0, filename.find(".triki")))) {
                    std::cout << "Progreso guardado!\n";
                }
            }
        } else {
            std::cout << "La partida cargada ya habia terminado.\n";
            std::cout << "Ganador: " << (triki.getWinner() != ' ' ? 
                         std::string(1, triki.getWinner()) : "Empate") << "\n";
        }
    }
}

void deleteGame() {
    std::string filename = selectSavedGame();
    if (filename.empty()) {
        return;
    }
    
    char confirm;
    std::cout << "Estas seguro de eliminar '" << filename << "'? (s/n): ";
    std::cin >> confirm;
    
    if (confirm == 's' || confirm == 'S') {
        FileManager fileManager;
        if (fileManager.deleteGame(filename)) {
            std::cout << "Partida eliminada exitosamente.\n";
        }
    } else {
        std::cout << "Eliminacion cancelada.\n";
    }
}

void showSystemInfo() {
    FileManager fileManager;
    
    std::cout << "\n=== INFORMACION DEL SISTEMA ===\n";
    std::cout << "Demostrando conceptos de C++:\n";
    std::cout << "- Manejo dinamico de memoria (new/delete)\n";
    std::cout << "- Punteros y aritmetica de punteros\n";
    std::cout << "- Regla de los 3 (constructor copia, operador=, destructor)\n";
    std::cout << "- Archivos binarios con punteros explicitos\n";
    std::cout << "- Gestion automatica de directorios\n";
    std::cout << "- Heap vs Stack memory\n\n";
    
    fileManager.showDirectoryInfo();
    
    // Crear objeto temporal para mostrar info de memoria
    Game tempGame;
    tempGame.showMemoryInfo();
}

int main() {
    std::cout << "=== PROYECTO TRIKI - KAREN ORTIZ ===\n";
    std::cout << "Demostrando: Estructuras de datos, punteros, manejo de memoria\n";
    
    int choice;
    bool running = true;
    
    while (running) {
        showMainMenu();
        std::cin >> choice;
        
        switch (choice) {
            case 1:
                playNewGame();
                break;
            case 2:
                loadAndPlayGame();
                break;
            case 3:
                showSavedGames();
                break;
            case 4:
                deleteGame();
                break;
            case 5:
                showSystemInfo();
                break;
            case 6:
                std::cout << "Gracias por usar el sistema!\n";
                std::cout << "Liberando memoria automaticamente...\n";
                running = false;
                break;
            default:
                std::cout << "Opcion invalida. Intenta de nuevo.\n";
                break;
        }
        
        if (running) {
            std::cout << "\nPresiona Enter para continuar...";
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cin.get();
        }
    }
    
    return 0;
}