# webiwabo

Proyecto semestral de Programación de Computadores | Grupo 20

## Estructura

* assets: archivos estáticos (imágenes, efectos de sonido y música)
* include: solo archivos .h
* source: solo archivos .c
* config.txt: configuración inicial del juego

## Requisitos

* [raylib](https://github.com/raysan5/raylib) instalado en el sistema

## Ejecución

./webiwabo

El programa debe ejecutarse desde la carpeta que contiene config.txt

## Controles

Clic izquierdo: Selección, recoger sol, usar pala
1, 2, 3, 4, 5: Selección rápida de semilla
M: Pausar / reanudar música
flecha arriba/abajo: Subir / bajar volumen

## Configuración

El archivo config.txt contiene pares "clave valor", uno por línea. Si el archivo no existe o falta una clave, se usan valores por defecto.

clave, descripción, valor por defecto:
soles_iniciales, soles al comenzar la partida, 50
zombies_total, zombies que aparecen en la partida (máximo 33), 33
vida_casa, zombies que pueden llegar a la casa antes de perder, 1
SetTargetFPS, fotogramas por segundo, 30
SetMusicVolume, volumen de la música (0.0 a 1.0), 0.8
filtro_r, color rojo, 255
filtro_g, color verde, 255
filtro_b, color azul, 255

Ejemplos:

```
soles_iniciales 100
zombies_total 20
vida_casa 3
SetTargetFPS 30
SetMusicVolume 0.5
filtro_r 160
filtro_g 110
filtro_b 255
```
```
soles_iniciales 25
zombies_total 33
vida_casa 2
SetTargetFPS 60
SetMusicVolume 1.0
filtro_r 255
filtro_g 240
filtro_b 40
```
## Créditos y propiedad intelectual

*Plants vs. Zombies*, sus personajes, nombres, concepto de juego y banda sonora son propiedad intelectual de **PopCap Games** y **Electronic Arts Inc.** Todos los derechos pertenecen a sus respectivos dueños.

### Arte

Todos los dibujos e imágenes de este repositorio (plantas, zombies, semillas, proyectiles, soles, pala y césped) fueron creados a mano por Celeste Ignacia Cruz Merino (Grupo 20). No se utilizó arte original de PopCap. Los diseños están inspirados en los personajes de la franquicia, cuyos derechos pertenecen a PopCap / EA.

### Sonido y música

Los efectos de sonido y la banda sonora provienen del juego original *Plants vs. Zombies* (© PopCap Games / Electronic Arts) y se obtuvieron desde [KHInsider](https://downloads.khinsider.com/game-soundtracks/album/plants-vs.-zombies-2009-gamerip-pc-ios-x360-ps3-ds-android-mobile-psvita-xbox-one-ps4-switch). No son obra de los autores de este proyecto.

### Herramientas

* [raylib](https://www.raylib.com/): biblioteca gráfica y de audio (licencia zlib/libpng)

### Uso de inteligencia artificial

Durante el desarrollo se utilizó la inteligencia artificial con el único proposito de que ayudara a encontrar y entender fallos de compilación y de lógica.
Y también para correcciones en la redacción de este archivo.