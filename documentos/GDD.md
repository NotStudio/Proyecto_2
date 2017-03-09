# nombre Juego
## Resumen
| Genero | Público | Modos de juego | Plataforma | Calificación |
|:-------|:--------|:---------------|:-----------|:-------------|
| undefined | undefined    |1 Jugador| PC  | Undefined |
## Descripción
"Nombre juego" es un juego en 2D que mezcla componentes de rol (crafteo de objetos) con la acción directa, que se ubica temporalmente algunos años mas tarde de nuestra era.  En él, debemos avanzar por distintas zonas con un elenco variado de personajes jugables, máquinas electrónicas de que poseen una IA muy desarrollada. En dichas zonas, debemos derrotar a los enemigos y conseguir recursos para ayudar al personaje principal, 'Nombre tostadora', en su misión por volver a la estación espacial de la que ha caído por error a la Tierra para volver junto con su compañero humano "Nombre del pavo", un astronauta residente en la estación. Sin embargo, "la tostadora" pronto se dará cuenta que no todo continúa como cuando el dejó el planeta.
## Portada
portada del juego

## 5 Primeros minutos del Juego
Durante los primeros momentos del juego, se realiza una especie de tutorial en la que el jugador va aprendiendo poco a poco las mecánicas básicas del juego: movimiento, ataque, recolección de items, crafteo, etc. Al completar el tutorial, el jugador llegará a lo que será su base durante todo el juego.
## Jugabilidad
### Mecánica
La mecánica del juego puede dividirse en varios aspectos. Por un lado tenemos el movimiento. El jugador puede desplazarse a lo largo de los niveles con las teclas A, W, S, y D, por lo que existen 4 direcciones posibles pero que al combinarse dan lugar a 8. La velocidad de desplazamiento dependerá del atributo correspondiente del personaje. En cuanto al ataque, se ejecuta con las teclas de dirección. Existen varias formas de ataque que dependen del personaje jugable que hayamos seleccionado para jugar:

- Ataque a melee: ataque a corta distancia que puede realizarse en 4 direcciones. Su rango dependerá del personaje seleccionado.

- Ataque a distancia: el personaje lanza proyectiles que recorren el nivel hasta impactar con algo o llegar a su máximo rango, que dependerá de los atributos del personaje.
### Dinámica
El juego tiene 2 rasgos respecto a la dinámica, Survival y Arcade, una necesita de la otra, es necesario realizar la parte Arcade para poder avanzar en la Survival y esta amplia la parte Arcade.
#### Survival
Esta parte de la dinámica es la que hace avanzar directamente la historia o desarrollo del juego y se desarrolla en Refugio/Base. Tiene que ver con desbloqueo de zonas, lo que amplia la parte Arcade, crafteo de objetos, y el desarrollo de los Personajes (selección de los personajes). El objetivo principal de esta parte es el desbloqueo de todas las zonas para llegar a la ultima zona y acabar el juego.
#### Arcade
Esta parte de la dinámica consiste en completar las zonas, que se componen de un número de niveles/habitaciones fijo, para obtener recursos, y estos poder ser usados en la parte Survival del juego. Se desarrolla en las habitaciones, se tienen que acabar con todos los enemigos de la habitción para poder pasar una habitación colindante de la actual y llegar al acceso del siguiente nivel que estará en una habitación del nivel.
### Estética
Pixel-art, cartoon, post-apocalíptico.
## Menús
### Inicio
### Principal
### Pausa
## Localidades
### La Base o Refugio
Donde se realiza parte survival del juego.
Se pueden realizar las siguientes acciones:
- Guardado automático, al entrar a la base.
- Comprar
- Elegir zona para jugar.
- Craftear.
- Elegir personaje.
### Zonas
- Donde se obtienen recursos para la parte survival del juegeo
- Hay 1 boss por zona.
- Hay 3 tipos de recursos por zona: Recursos genéricos, comunes entre las diferentes zonas, recursos específicos de cada zona y el      recurso que da el boss.
- Las zonas se organizan por niveles o pisos.
- La forma de colocar habitaciones es aleatoria.
- Las habitaciones son estructuralmente iguales para todas las zonas.
- Enemigos diferentes por zona.
- tilesheets diferentes por zona.

#### The Natural Preserve
Un bosque de chatarra, es la primera zona que tienes al comenzar el juego.
#### Hipsters Sancturary
Una PinApple Store, es la segunda zona que se desbloquea, se desbloquea cuando se craftea los engranajes.
#### Several Motors Museum
Un Desguace.
#### Beautiful Refinery
Hornos

### Habitaciones/Niveles
- Es donde se juega a la parte Arcade del juego (disparar y desplazarse).
- Puede haber o no enemigos en una habitación.
- Hay X variantes de una misma habitación.
- Una habitación tiene que estar conectada minimo a otra habitación.

## Historia
Año 16DB, Estacion espacial “Shuppatsu”, un asteroide colisiona contra la estacion provocando el desprendimiento de uno de los módulos, el cual se precipita sobre la Tierra.
Al estrellarse sobre la superficie terrestre en una pradera aparece entre el humo una tostadora que debido al impacto se ha encendido.
## Personajes

| Sprite                                             | Nombre           | Descripción | HP | At | Ve | FA |
| :-------------:                                    | :-------------   |:---|:---:|:---:|:---:|:---:|
| <img src="DocImg/pp.jpg" width="50" height="50">   | Toasty           | Personaje principal de la historia es na tostadora | ? | ? | ? | ? |
| <img src="dirección" width="50" height="50">       | Gotchi           | Personaje desbloqueable, para poder jugar con el se necesitan Pilas | ? | ? | ? | ? |

## Objetos
### Consumible
Objetos que se agotan y afectan a las stats del jugador, los cambios no serán permanentes, solo durarán hasta el final de la run, se gastan en el acto.
Se consiguen matando enemigos o encotrandolos por el mapa.

| Sprite                                             | Nombre           |efecto        |
| :-------------:                                    |:-------------    |:-------------|
| <img src="DocImg/pp.jpg" width="50" height="50"> | Objeto generico  | efecto generico |
| <img src="Direccion" height="50" width="50">     | Bateria de Coche | maxHP+1, HP+1 |
| <img src="Direccion" height="50" width="50">     | Pila             | HP+1 |
| <img src="Direccion" height="50" width="50">     | Cable            | Ve+1 |
| <img src="Direccion" height="50" width="50">     | Transistor       | At+1 |




### Clave
Estos objetos sirven para craftear otros objetos o craftear objetos para desbloquear zonas. Se obtienen por crafteo o en zonas especificas.

| Sprite                                           | Nombre           |Uso                | Obtención |
| :-------------:                                  |:-------------    |:-------------     |:---|
| <img src="DocImg/pp.jpg" width="50" height="50"> | Objeto generico  | efecto generico   | generico|
| <img src="DocImg/pp.jpg" width="50" height="50"> | Chatarra         | Crafteo           | the Natural Preserve |
| <img src="DocImg/pp.jpg" width="50" height="50"> | Madera           | Crafteo           | the Natural Preserve |
| <img src="DocImg/pp.jpg" width="50" height="50"> | Estaño           | Crafteo           | Hipsters Sancturary |
| <img src="DocImg/pp.jpg" width="50" height="50"> | Chip             | Crafteo           | Hipsters Sancturary |
| <img src="DocImg/pp.jpg" width="50" height="50"> | Litio            | Crafteo           | Hipsters Sancturary |
| <img src="DocImg/pp.jpg" width="50" height="50"> | Petroleo         | Crafteo           | S. Motors Museum |
| <img src="DocImg/pp.jpg" width="50" height="50"> | Carbón           | Crafteo           | S. Motors Museum |
| <img src="DocImg/pp.jpg" width="50" height="50"> | Tanque           | Crafteo           | S. Motors Museum |
| <img src="DocImg/pp.jpg" width="50" height="50"> | Olla a presión   | Crafteo           | S. Motors Museum |
| <img src="DocImg/pp.jpg" width="50" height="50"> | Tuberías         | Crafteo           | S. Motors Museum |
| <img src="DocImg/pp.jpg" width="50" height="50"> | Eje              | Crafteo           | Madera + Madera |
| <img src="DocImg/pp.jpg" width="50" height="50"> | Engranaje        | Crafteo           | Chatarra + Chatarra |
| <img src="DocImg/pp.jpg" width="50" height="50"> | Engranajes       | Crafteo           | Engranaje + Engranaje |
| <img src="DocImg/pp.jpg" width="50" height="50"> | Circuitos        | Crafteo           | Chatarra + Estaño |
| <img src="Direccion" height="50" width="50">     | Pila de botón    | Canjeable por una partida con el Tamagochi | Chatarra + Litio|
| <img src="DocImg/pp.jpg" width="50" height="50"> | Tanque a Presión TP | Crafteo           | Olla + Tanque |
| <img src="DocImg/pp.jpg" width="50" height="50"> | Refinador Express RE     | Crafteo           | TP + Tuberías |


### Histórico
Para el desarrollo de la historia, se craftean y se consiguen matando a jefes.

| Sprite                               | Nombre                 |Obtención        |
| :-------------:                      |:-------------          |:-------------   |
| <img src=" " width="50" height="50"> | Mecanismo(Engranajes)  | Engranajes + Eje        |
| <img src="" width="50" height="50">  | Circuitos Electronicos | Chip + Estaño        |
| <img src="" width="50" height="50">  | Combustible            | RE + Petroleo |
| <img src=" " width="50" height="50"> | Acero                  | Crafteo |


## NPC's

| Sprite                                             | Nombre           |localizaciones    | descripcion | HP | At | Ve | FA |
| :-------------:                                    | :-------------   |:---|:---|:---:|:---:|:---:|:---:|
| <img src="dirección" width="50" height="50">     | Nombre           | localizaciones | descripción | HP | At | Ve | FA |

## Referencias
- The binding of Isaac.

- Enter the gungeon.

## Agradecimientos
- Special Superextra thanks to Hideo Kojima
