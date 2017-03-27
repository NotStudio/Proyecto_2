# Como hacer una habitación
Guía para crear una habitacion, incluye  objetos del entorno (inanimados/inertes) y enemigos.
## Como diseñar un mapa
Usamos Tiled , para crear mapas metes un tilesheet que este validado [este te vale](../Proyecto/Material/tilesheet_zon1.png), lo exportas como csv, lo metes en la carpeta mapas , le pones un nombrey lo guardas en [esta carpeta](../Proyecto/Material/Maps).
### información sobre los tiles
Los primeros 12 tiles (partiendo de 0) no tienen colisión. el resto si, hay 24(el ultimo tile es el tile 23)
### Características de la habitación
- El ancho y el alto tienen que ser divisibles entre 4
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
Creamos un txt y lo guardamos en formato .inapat (Sigue siendo igual en un txt) que se llame como el mapa que hemos creado, y lo metemos en [esta carpeta](../Proyecto/Material/Maps/Patrones).
### Sintaxis
Funciona leyendos lineas, cada linea tiene q la siguiente información
```
tuberia 3 2 0.5
agujero 14 13 2
```
#### Descripción
1. Primer valor
  - Es el nombre del objeto
  - **Tiene que estar en minusculas y sin acentos, si no se genera**
2. Segundo valor
  - El tile X donde esta su esquina superior derecha, un entero
3. Tercer valor
  - El tile Y donde esta su esquina superior derecha, un entero
4. Cuarto valor
  - La escala del objeto, un float, hay figuras bastante grandes, asi controlamos su tamaño sin tener que deformar la imagen.
  - El factor de tamaño de los objetos inertes estan en el GDD

### Condiciones
- Si un objeto bloquea una puerta, este objeto será eliminado (Los tiles mencionados antes).

## Meter enemigos
Creamos un txt y lo guardamos en formato .inepat que se llame como el mapa que hemos creado, y lo metemos en [esta carpeta](../Proyecto/Material/Maps/Patrones).
### Sintaxis
Cada linea tiene  la siguiente información.
```
perseguidor 10 8
sierra 14 13 0
```
#### Descripción
1. Primer valor
  - Es el nombre del enemigo si no existe no pasa nada
  - **Tiene que estar en minusculas y sin acentos, si no se genera**
2. Segundo valor
  - El tile X donde esta su esquina superior derecha, un entero
3. Tercer valor
  - El tile Y donde esta su esquina superior derecha, un entero
4. Cuarto valor (algunos enemigos)
  - Indica algo dependiendo de enemigo que se quiera generar
    - Sierra (indica la dirección en la que se mueve, si  le  das 1 se mueve de izquierda derecha,0 arriba abajo),

### Condiciones
- Si un enemigo se genera  encima de un objeto, tile o enemigo que colisiona , será eliminado. Los tiles que ocupan los enemigos vienen el GDD.
- Si pones el 4º valor a un enemigo que no lo necesita no pasa nada.
- Si no pones el 4º valor a un enemigo que lo necesita no pasa nada, se asigna un valor aleatorio.
- Tiene que estar dentro del margen , si no no se genera, es decir si tu pones en el tile (-1,0) no se genera.

## Ejemplo
### Paso 1
Abrimos tiled y creamos un mapa, con esta configuración.
![confmapa](/DocImg/confMapa.png)
Remarcado el tamaño del mapa, es importantes que las cifras sean divisibles entre cuatro, el resto tiene que estar como la imagen.
### Paso 2
Añadimos un conjunto de patrones, el tilesheet, [este te vale](../Proyecto/Material/tilesheet_zon1.png).
### Paso 3
Ya creado el mapa, y exportado el tilesheet es importante que el mapa este cerrado. ![confmapa](/DocImg/mapaCorrecto.png)
 este mapa es un mapa de 20*20 que esta bien, porque cumple las condiciones explicadas en el apartado de diseñar un mapa, los tiles en un recuadro y rodeados son tiles que tienen que estar accesibles.

 E.G. Si el mapa es así, no sería valido.
![inmapa](/DocImg/mapaInCorrecto.png)
El jugador no puede acceder a la puerta este del mapa.

![inmapa2](/DocImg/mapaInCorrecto2.png)
 Incomunica 2 partes del mapa (Todas las partes deben estar comunciadas)


### Paso 4
Terminado el mapa, quedaría así.
![confmapa2](/DocImg/mapaCorrecto2.png)
 Exportamos el mapa csv y lo guardamos en [esta carpeta](../Proyecto/Material/Maps).
### Paso 5
Ahora metemos los inanimados, seguimos los pasos del apartado de **Meter inanimados**,.
### Paso 6

![confmapa2](/DocImg/bujero.png)


Supongamos que queremos meter un agujero, , miramos cual es el tile que ocupa, el que esté mas cercano a la esquina superior izquierda, es decir tienendo en cuenta que un agujero tiene ratio 1:1, la linea el fichero sería.
```
agujero 5 3 2
```

### Paso 7
Ahora metemos los enemigos, seguimos los pasos del apartado de **Meter enemigos**.

### Paso 8
![confmapa2](/DocImg/enemigos.png)
Supongamos que quermos meter un enemigo bomba y  Sierra, que vaya arriba y abajo. en los siguientes cuadros, (verde bomba, azul Sierra). el archivo sería así.
```
bomba 2 3
sierra 12 10 1
```
sigue las condiciones y todo ira bien.
# Fin del tutorial
