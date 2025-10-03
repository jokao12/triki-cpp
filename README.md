# Triki Game (Tic-Tac-Toe) en C++

## Descripción
Implementación completa del juego de triki (tic-tac-toe) en C++ con énfasis en manejo de memoria dinámica, punteros, y persistencia de datos mediante archivos binarios. El proyecto demuestra conceptos fundamentales de programación orientada a objetos y gestión manual de memoria.

## Tabla de Contenidos
- [Características](#características)
- [Diagrama UML](#diagrama-uml)
- [Manual de Usuario](#manual-de-usuario)
- [Autora](#autora)

---

## Características

### Funcionalidades del Juego
- Juego interactivo de triki 3x3 por consola
- Dos jugadores (X y O) con turnos alternados
- Detección automática de victoria (filas, columnas, diagonales)
- Detección de empate cuando el tablero se llena
- Validación de movimientos (posiciones válidas y casillas vacías)
- Interfaz intuitiva con coordenadas numéricas



## Manual de Usuario

### Menú Principal

Al ejecutar el programa, verás:
```
=== PROYECTO TRIKI - KAREN ORTIZ ===
Demostrando: Estructuras de datos, punteros, manejo de memoria

=== TRIKI CON MANEJO DE MEMORIA Y ARCHIVOS ===
1. Nueva partida
2. Cargar partida guardada
3. Ver partidas disponibles
4. Eliminar partida
5. Informacion del sistema
6. Salir
Selecciona una opcion:
```

### 1. Nueva Partida

**Paso a paso**:
1. Selecciona opción `1`
2. El programa muestra información de memoria (educativo)
3. Aparece el tablero vacío con coordenadas:
   ```
     0   1   2
   0   |   |  
     ---------
   1   |   |  
     ---------
   2   |   |  
   ```
4. Ingresa coordenadas en formato: `fila columna`
   - Ejemplo: `0 0` (esquina superior izquierda)
   - Ejemplo: `1 1` (centro)
5. Los jugadores alternan turnos automáticamente
6. El juego termina al detectar victoria o empate
7. Opción de guardar partida al finalizar

**Reglas de victoria**:
- 3 fichas iguales en fila horizontal
- 3 fichas iguales en columna vertical
- 3 fichas iguales en diagonal

### 2. Cargar Partida Guardada

**Paso a paso**:
1. Selecciona opción `2`
2. El sistema muestra lista numerada de partidas
3. Ingresa el número de la partida deseada
4. Si la partida no ha terminado: continúa jugando
5. Si la partida terminó: muestra el resultado

### 3. Ver Partidas Disponibles

Muestra lista de todas las partidas guardadas en el directorio `saves/`:
```
=== PARTIDAS GUARDADAS ===
1. partida1.triki
2. partida2.triki
3. partida_ganada.triki
=========================
```

### 4. Eliminar Partida

**Paso a paso**:
1. Selecciona opción `4`
2. Elige la partida a eliminar de la lista
3. Confirma la eliminación (`s`/`n`)
4. El archivo se elimina permanentemente

### 5. Información del Sistema

Muestra detalles técnicos:
- Conceptos de C++ implementados
- Direcciones de memoria del tablero (heap)
- Direcciones de variables (stack)
- Lista de archivos guardados con tamaños
- Información del directorio de guardado

**Ejemplo de salida**:
```
=== INFORMACION DE MEMORIA ===
Tablero en heap: 0x1a2b3c4d5e
Tamaño del tablero: 9 bytes
Dirección de currentPlayer (stack): 0x7ffe1234abcd
Valor actual: X
===============================
```

### 6. Salir

Cierra el programa correctamente, liberando toda la memoria asignada.

### Sistema de Coordenadas

```
       Columnas
        0   1   2
      +---+---+---+
F  0  |0,0|0,1|0,2|
i     +---+---+---+
l  1  |1,0|1,1|1,2|
a     +---+---+---+
s  2  |2,0|2,1|2,2|
      +---+---+---+
```

**Ejemplos prácticos**:
- Centro del tablero: `1 1`
- Esquina superior izquierda: `0 0`
- Esquina inferior derecha: `2 2`
- Medio superior: `0 1`

### Validaciones Automáticas

El sistema verifica:
- Coordenadas dentro del rango [0-2]
- Casilla vacía (no ocupada)
- Nombres de archivo válidos (sin caracteres especiales)
- Existencia de archivos al cargar

---



---

## Autora

**Karen Ortiz**

- **Institución**: [Instituto Tecnologico Metropolitano]
- **Curso**: Estructuras de Datos
- **GitHub**: [@jokao12](https://github.com/jokao12)
- **Repositorio**: [triki-cpp](https://github.com/jokao12/triki-cpp)

---

