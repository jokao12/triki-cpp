#include "FileManager.h"
#include <iostream>
#include <fstream>
#include <filesystem>
#include <algorithm>
#include <ctime>
#include <sstream>

// CONSTRUCTOR POR DEFECTO
FileManager::FileManager() {
    // PUNTERO DINÁMICO - Aloca memoria en heap
    saveDirectory = new std::string("saves");
    maxSavedFiles = 10;
    
    // Crear directorio si no existe
    createDirectoryIfNotExists(*saveDirectory);
    
    std::cout << "[DEBUG FileManager] Memoria alocada para directorio: " 
              << (void*)saveDirectory << std::endl;
}

// CONSTRUCTOR CON DIRECTORIO PERSONALIZADO
FileManager::FileManager(const std::string& customDir) {
    saveDirectory = new std::string(customDir);
    maxSavedFiles = 10;
    
    createDirectoryIfNotExists(*saveDirectory);
    
    std::cout << "[DEBUG FileManager] Directorio personalizado creado: " 
              << *saveDirectory << std::endl;
}

// DESTRUCTOR - Libera memoria del heap
FileManager::~FileManager() {
    delete saveDirectory;
    std::cout << "[DEBUG FileManager] Memoria liberada del directorio" << std::endl;
}

// CONSTRUCTOR COPIA (Regla de los 3)
FileManager::FileManager(const FileManager& other) {
    // Alocar nueva memoria
    saveDirectory = new std::string(*(other.saveDirectory));
    maxSavedFiles = other.maxSavedFiles;
    
    std::cout << "[DEBUG FileManager] Copia creada con directorio: " 
              << *saveDirectory << std::endl;
}

// OPERADOR ASIGNACIÓN (Regla de los 3)
FileManager& FileManager::operator=(const FileManager& other) {
    if (this != &other) {  // Evitar auto-asignación
        // Liberar memoria actual
        delete saveDirectory;
        
        // Alocar nueva memoria y copiar
        saveDirectory = new std::string(*(other.saveDirectory));
        maxSavedFiles = other.maxSavedFiles;
    }
    return *this;
}

// MÉTODO PRIVADO - Crear directorio si no existe
bool FileManager::createDirectoryIfNotExists(const std::string& path) {
    try {
        // std::filesystem es C++17, manejo moderno de archivos
        if (!std::filesystem::exists(path)) {
            std::filesystem::create_directories(path);
            std::cout << "[INFO] Directorio creado: " << path << std::endl;
            return true;
        }
        return true;
    } catch (const std::filesystem::filesystem_error& e) {
        std::cerr << "[ERROR] No se pudo crear directorio: " << e.what() << std::endl;
        return false;
    }
}

// LISTAR PARTIDAS GUARDADAS
std::vector<std::string> FileManager::listSavedGames() const {
    std::vector<std::string> gameFiles;
    
    try {
        // Iterar por todos los archivos del directorio
        for (const auto& entry : std::filesystem::directory_iterator(*saveDirectory)) {
            if (entry.is_regular_file()) {
                std::string filename = entry.path().filename().string();
                
                // Solo archivos .triki
                if (filename.length() > 6 && 
                    filename.substr(filename.length() - 6) == ".triki") {
                    gameFiles.push_back(filename);
                }
            }
        }
        
        // Ordenar alfabéticamente
        std::sort(gameFiles.begin(), gameFiles.end());
        
    } catch (const std::filesystem::filesystem_error& e) {
        std::cerr << "[ERROR] Error accediendo al directorio: " << e.what() << std::endl;
    }
    
    return gameFiles;
}

// VERIFICAR SI ARCHIVO EXISTE
bool FileManager::fileExists(const std::string& filename) const {
    std::string fullPath = *saveDirectory + "/" + filename;
    return std::filesystem::exists(fullPath);
}

// ELIMINAR PARTIDA GUARDADA
bool FileManager::deleteGame(const std::string& filename) {
    if (!fileExists(filename)) {
        std::cout << "[WARNING] Archivo no existe: " << filename << std::endl;
        return false;
    }
    
    try {
        std::string fullPath = *saveDirectory + "/" + filename;
        std::filesystem::remove(fullPath);
        std::cout << "[INFO] Archivo eliminado: " << filename << std::endl;
        return true;
    } catch (const std::filesystem::filesystem_error& e) {
        std::cerr << "[ERROR] No se pudo eliminar: " << e.what() << std::endl;
        return false;
    }
}

// OPTIMIZACIÓN DE MEMORIA - Limpiar archivos antiguos
void FileManager::cleanOldSaves() {
    auto gameFiles = listSavedGames();
    
    if (gameFiles.size() <= static_cast<size_t>(maxSavedFiles)) {
        std::cout << "[INFO] No hay archivos que limpiar (" 
                  << gameFiles.size() << "/" << maxSavedFiles << ")" << std::endl;
        return;
    }
    
    // Ordenar por fecha de modificación (más antiguos primero)
    std::vector<std::pair<std::string, std::filesystem::file_time_type>> filesWithTime;
    
    for (const auto& file : gameFiles) {
        std::string fullPath = *saveDirectory + "/" + file;
        auto lastWrite = std::filesystem::last_write_time(fullPath);
        filesWithTime.push_back({file, lastWrite});
    }
    
    // Ordenar por tiempo (más antiguos primero)
    std::sort(filesWithTime.begin(), filesWithTime.end(),
              [](const auto& a, const auto& b) {
                  return a.second < b.second;
              });
    
    // Eliminar archivos más antiguos
    int filesToDelete = gameFiles.size() - maxSavedFiles;
    for (int i = 0; i < filesToDelete; i++) {
        deleteGame(filesWithTime[i].first);
    }
    
    std::cout << "[INFO] Limpieza completada. Eliminados: " << filesToDelete 
              << " archivos antiguos" << std::endl;
}

// MOSTRAR INFORMACIÓN DEL DIRECTORIO
void FileManager::showDirectoryInfo() const {
    std::cout << "\n=== INFORMACIÓN DEL FILEMANAGER ===" << std::endl;
    std::cout << "Directorio de guardado: " << *saveDirectory << std::endl;
    std::cout << "Dirección del puntero: " << (void*)saveDirectory << std::endl;
    std::cout << "Máximo archivos permitidos: " << maxSavedFiles << std::endl;
    
    auto files = listSavedGames();
    std::cout << "Archivos encontrados: " << files.size() << std::endl;
    
    for (const auto& file : files) {
        std::string fullPath = *saveDirectory + "/" + file;
        auto fileSize = std::filesystem::file_size(fullPath);
        std::cout << "  - " << file << " (" << fileSize << " bytes)" << std::endl;
    }
    std::cout << "==================================\n" << std::endl;
}

// GETTERS Y SETTERS
std::string FileManager::getSaveDirectory() const {
    return *saveDirectory;  // Desreferenciar el puntero
}

void FileManager::setSaveDirectory(const std::string& newDir) {
    *saveDirectory = newDir;  // Asignar nuevo valor al contenido del puntero
    createDirectoryIfNotExists(newDir);
}

int FileManager::getMaxSavedFiles() const {
    return maxSavedFiles;
}

void FileManager::setMaxSavedFiles(int maxFiles) {
    maxSavedFiles = (maxFiles > 0) ? maxFiles : 1;  // Mínimo 1 archivo
}

// MÉTODOS ESTÁTICOS - No necesitan instancia de la clase
bool FileManager::isValidFilename(const std::string& filename) {
    // Verificar que no esté vacío y no contenga caracteres peligrosos
    if (filename.empty() || filename.length() > 100) {
        return false;
    }
    
    // Caracteres no permitidos en nombres de archivo
    const std::string invalidChars = "\\/:*?\"<>|";
    for (char c : filename) {
        if (invalidChars.find(c) != std::string::npos) {
            return false;
        }
    }
    
    return true;
}

std::string FileManager::getCurrentTimestamp() {
    auto now = std::time(nullptr);
    auto tm = *std::localtime(&now);
    
    std::ostringstream oss;
    oss << (tm.tm_year + 1900) 
        << "-" << (tm.tm_mon + 1) 
        << "-" << tm.tm_mday 
        << "_" << tm.tm_hour 
        << "-" << tm.tm_min 
        << "-" << tm.tm_sec;
    
    return oss.str();
}