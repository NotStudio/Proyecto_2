# Como hacer una habitación
Guía para crear una habitacion, incluye  objetos del entorno (inanimados/inertes) y enemigos.
## Como diseñar un mapa
Usamos Tiled , para crear mapas metes un tilesheet que este validado, en la carpeta de  tilesheets. Usamos el formato por defecto de Tiled (.tmx), usando el script creado por Fran.
### información sobre los tiles
Los primeros 12 tiles (partiendo de 0) no tienen colisión, de ahí en adelante eso tiles tienen colisión.
Al meter los tiles en Tiled esta tiene tiene que ser la configuación ![configuración tilesheet](/DocImg/confTilsheet.png)

### Características de la habitación
- El ancho y el alto tienen que ser multiplos de 4
- Los siguientes tiles tienen que estar accesibles para el jugador, para no bloquear el acceso a una puerta.(el primer tile es el 0,0).
  - (ancho/2 -1 ,1),(ancho/2 ,1)
  - (ancho/2 -1 ,2),(ancho/2 ,2)
  - (ancho/2 -1 ,alto - 2 ),(ancho/2,alto - 2 )
  - (ancho/2 -1 ,alto - 3 ),(ancho/2,alto - 3 )
  - (ancho - 2 ,alto/2 - 1 ),(ancho - 2,alto/2  )
  - (ancho - 3 ,alto/2 - 1 ),(ancho - 3,alto/2  )
  - (1 ,alto/2 - 1 ),(1,alto/2)
  - (2 ,alto/2 - 1 ),(2,alto/2)
- Las 4 huecos tienen que ser accesibles en todas los mapas ocasiones.

### Ejemplos
- esta bien este mapa
![mapa correcto](DocImg/mapac1.png)
- la puerta norte es inaccesible
![mapa incorrecto](DocImg/mapai1.png)
- Tiles prohibidos de usar son usados
![mapa incorrecto](DocImg/mapai2.png)

## Meter Objetos en el mapa
para poder meter objetos (enemigos o inanimados), se tiene que crear una capa de objetos en el mapa de tiled, según sea enemigo o inanimado tiene que cumplir ciertas condiciones, algunas son comunes.

### Condiciones
#### Comunes
- Han de tener tipo y nombre. Atributos de un objeto Tiled.
- Los tipos tienen que ser validos y los nombre validos con tipos
- Ejemplos:
  - ![correcto](DocImg/objc1.png)
  - ![correcto](DocImg/objc2.png)
  - ![correcto](DocImg/obji1.png)
  - ![correcto](DocImg/obji2.png)

#### Inanimados
- Si un objeto bloquea una puerta, este objeto será eliminado (Los tiles mencionados antes), se borra si esta si se ha generado una puerta si no se borra.
- El Objeto tiene que ser un rectangulo.
- El tipo que hay que poner es inanimado.
- La lista de inanimados esta en el GDD.

#### Enemigos
- Da igual la forma con la que crees el objeto.
- No debe solapar con un inanimado, si no no se genera.
- El tipo que hay enemigo.
- La lista de enemigos esta en el GDD.
