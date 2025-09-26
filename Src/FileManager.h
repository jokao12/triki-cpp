#ifndef FILEMANAGER_H
#define FILEMANAGER_H

#include <string>
#include <vector>

class FileManager {
private:
    // PUNTERO DINAMICO - Demuestra uso de memoria heap
    std::string* saveDirectory;  // Directorio donde se guardan las partidas
    int maxSavedFiles;          // Limite de archivos guardados
    
    // METODO PRIVADO - Helper function
    bool createDirectoryIfNotExists(const std::string& path);
    
public:
    // CONSTRUCTOR Y DESTRUCTOR - Manejo de memoria dinamica
    FileManager();
    FileManager(const std::string& customDir);  // Constructor con directorio personalizado
    ~FileManager();
    
    // CONSTRUCTOR COPIA Y OPERADOR ASIGNACION (Regla de los 3)
    FileManager(const FileManager& other);
    FileManager& operator=(const FileManager& other);
    
    // METODOS PRINCIPALES DE GESTION DE ARCHIVOS
    std::vector<std::string> listSavedGames() const;
    bool fileExists(const std::string& filename) const;
    bool deleteGame(const std::string& filename);
    
    // OPTIMIZACION DE MEMORIA
    void cleanOldSaves();  // Elimina archivos antiguos si superan el limite
    void showDirectoryInfo() const;  // Muestra info del directorio y archivos
    
    // GETTERS Y SETTERS
    std::string getSaveDirectory() const;
    void setSaveDirectory(const std::string& newDir);
    int getMaxSavedFiles() const;
    void setMaxSavedFiles(int maxFiles);
    
    // METODOS ESTATICOS - No necesitan instancia de la clase
    static bool isValidFilename(const std::string& filename);
    static std::string getCurrentTimestamp();  // Para nombres de archivo unicos
};

#endif