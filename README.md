# Instrucciones para ejecución

 - Clonar repositorio utilizando
    ```bash
    git clone carpeta_para_code
    ```
 - Ir a la carpeta **/build**
 - Realizar
    ```bash
    cmake path_hasta_build
    make
    ```
 - Para ejecutar server:
    ```bash
    ./server PORT 
    ```
 - Para ejecutar client:
     ```bash
    ./client_interface
    ```
 - Para ejecutar editor:
     ```bash
    ./client_editor
    ```

# Aclaraciones 

Se debe ejecutar primero el Server y luego el Client. 

# Dependencias
 - clang
 - make
 - build-essential
 - qt5-default
 - libqt5multimedia5-plugins
 - qtmultimedia5-dev
 - libyaml-cpp-dev
 - libsdl2-dev
 - libsdl2-image-dev
 - libsdl2-gfx-dev
 - libsdl2-mixer-dev
 - libsdl2-ttf-dev

# Alcance de la Entrega

## Lo que se tiene

#### Servidor
 - Esquema completo de hilos
 - Manejo de Lobby de partidas
 - Protocolo de comunicación funcional, pero no del todo escalable
 - Juego hardcodeado para dos jugadores (pero soporte para N jugadores)
 - Juego iniciado: recepción de posiciones para agregado de unidades a un mapa de juego
 - Broadcast de posiciones de unidades
 - Lógica básica de posiciones de A* (sin acceso a la hora de jugar)
 - Monitores para secciones críticas
 - Manejo de Multijugadores (aceptar múltiples clientes a la vez)

#### Cliente
 - Menú/Lobby -> HAY QUE CERRAR VENTANA DE "WAITING WINDOW" PARA PODER SEGUIR CON EL JUEGO
 - Esquema completo de hilos
 - Display básico del mapa y del overlay
 - Scrolling
 - Soporte básico de animaciones

#### Editor
 - Funcionamiento general

## Lo que estamos haciendo
#### Servidor
  - Movimiento de unidades _en partida_
  - Mejor protocolo con ID para cada unidad (para su trackeo)
  - Lógica de combate básica
  - Capacidad de "perder" (Base que puede ser atacada)
  - Broadcast de unidades destruídas

#### Cliente
  - Animaciones de movimiento, muerte, ataque
  - Pantalla de victoria/derrota
  - Mejora del overlay (para crear unidades)

## Lo que falta

#### General
 - Un cmake más limpio, aprovechando clases que puedan ser compartidas

#### Servidor
  - Apertura de YAML y lógica de traducción para los mapas.
  - Clase **Configuracion** (que vivirá en la clase Server. Será de sólo lectura y será recibida por referencia según corresponda). Se inicializa junto al servidor, abriendo desde un YAML de configuración.
  - Diferentes tipos de vehículos, unidades, armas.
  - Construcciones
  - Cosecha
  - Energía
  - Gusanos

#### Cliente
  - Mayor cantidad de animaciones.
  - Unidades, construcciones.
  - Soporte de Audio (voces, sonidos, música)

#### Editor
  - Mejoras de quality of life a la hora de armar un mapa.

