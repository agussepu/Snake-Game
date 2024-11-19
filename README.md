# Objetivos Básicos
    [] Funcionamiento basico del juego (colosion,manzana,serpiente)
    [] Saludar al jugador por su nombre
    [] Presentar cosigna del juego al empezar
    [] Mostrar ranking de jugadores al perder hasta que se presione una tecla

---
# Objetivos Generales
    [] ...
    
---
# Disposición Archivos Ideal
project/
│
├── src/                     # Carpeta para el código fuente
│   ├── main.c               # Entrada principal del programa
│   ├── grid.c               # Lógica del tablero (dibujar el grid)
│   ├── snake.c              # Lógica de la serpiente (movimiento, colisión, etc.)
│   ├── apple.c              # Lógica de la manzana (posición, reaparición)
│   ├── score.c              # Sistema de puntuación
│   ├── ranking.c            # Gestión del ranking de puntajes
│   └── events.c             # Manejo de eventos (teclado, salir del juego)
│
├── include/                 # Encabezados
│   ├── grid.h
│   ├── snake.h
│   ├── apple.h
│   ├── score.h
│   ├── ranking.h
│   └── events.h
│
└── Makefile                 # Archivo para compilar el proyecto
