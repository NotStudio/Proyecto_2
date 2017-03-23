# Como hacer una habitación
Esta guía es para poder crear una habitación para el juego para que se pueda meter dentro del juego, incluye como meter los objetos del entorno (inanimados/inertes) y enemigos.
## Como diseñar un mapa
Usamos Tiled para crear mapas metes un tilesheet que este validado [este te vale](../Proyecto/Material/tilesheet_zon1.png), lo exportas como csv y lo metes en la carpeta mapas y le pones un nombre, lo guardas en [esta carpeta](../Proyecto/Material/Maps).
### información sobre los tiles
Los primeros 12 tiles (partiendo de 0) no tienen colisión. el resto si, hay 24(el ultimo tile es el tile 23)
### Características de la habitación
- Los el ancho y el alto tienen que ser divisibles entre 4
- Los siguientes tiles tienen que estar accesibles para el jugador, para no bloquear el acceso a una puerta.(el primer tile es el 0,0).
  - (ancho/2 -1 ,1),(ancho/2 ,1)
  - (ancho/2 -1 ,2),(ancho/2 ,2)
  - (ancho/2 -1 ,alto - 2 ),(ancho/2,alto - 2 )
  - (ancho/2 -1 ,alto - 3 ),(ancho/2,alto - 3 )
  - (ancho - 2 ,alto/2 - 1 ),(ancho - 2,alto/2  )
  - (ancho - 3 ,alto/2 - 1 ),(ancho - 3,alto/2  )
  - (1 ,alto/2 - 1 ),(1,alto/2)
  - (2 ,alto/2 - 1 ),(2,alto/2)

### Ejemplos
luego meto Ejemplos visuales
## Meter inanimados
Este creamos un txt y lo guardamos en formato .inapat (esto es para encontrarlos más facilmente, sigue siendo igual en un txt) que se llame como el mapa que hemos creado, y lo metemos en [esta carpeta](../Proyecto/Material/Maps/Patrones).
### Sintaxis
funciona leyendos lineas, es decir en cada linea tiene que haber la siguiente información.(en el ejemplo so dos lineas de texto)
```
tuberia 3 2 0.5
agujero 14 13 2
```
#### Descripción
1. primer valor
  - Es el nombre del objeto si no existe no pasa nada
  - **Tiene que estar en minusculas y sin acentos, si no se genera**
2. Segundo valor
  - El tile X donde esta su esquina superior derecha, un entero
3. Tercer valor
  - El tile Y donde esta su esquina superior derecha, un entero
4. Cuarto valor
  - La escala del objeto, un float, hay figuras bastante grandes, asi controlamos su tamaño sin tener que deformar la imagen.
  - el factor de tamaño de los objetos inertes estan en el GDD

### Condiciones
- Si un objeto bloquea una puerta, este objeto será eliminado (Los tiles mencionados antes).
- Se pueden colocar donde quieras, pero si bloquean una puerta se eliminan.

## Meter enemigos
Este creamos un txt y lo guardamos en formato .inepat (esto es para encontrarlos más facilmente, sigue siendo igual en un txt) que se llame como el mapa que hemos creado, y lo metemos en [esta carpeta](../Proyecto/Material/Maps/Patrones).
### Sintaxis
funciona leyendos lineas, es decir en cada linea tiene que haber la siguiente información.(en el ejemplo so dos lineas de texto)
```
perseguidor 10 8
sierra 14 13 0
```
#### Descripción
1. primer valor
  - Es el nombre del enemigo si no existe no pasa nada
  - **Tiene que estar en minusculas y sin acentos, si no se genera**
2. Segundo valor
  - El tile X donde esta su esquina superior derecha, un entero
3. Tercer valor
  - El tile Y donde esta su esquina superior derecha, un entero
4. Cuarto valor (algunos enemigos)
  - Es un valor que lo necesitan algunos enemigos, es un entero. Indica algo dependiendo de enemigo que se quiera generar
  - Lista de los que tienen el 4º valor
    - Sierra (indica la dirección en la que se mueve, si le das 1 se mueve de izquierda derecha,0 arriba abajo),

### Condiciones
- Si un enemigo se genera se genera encima de un objeto, tile o enemigo que colisiona , este enemigo será eliminado. Los tiles que ocupan los enemigos vienen el GDD.
- Si pones el 4º valor a un enemigo que no lo necesita no pasa nada.
- Si no pones el 4º valor a un enemigo que lo necesita no pasa nada, se asigna un valor aleatorio.
- Tiene que estar dentro del margen , si no no se genera, es decir si tu pones en el tile (-1,0) no se genera.

## Ejemplos de todo
Mas tarde
