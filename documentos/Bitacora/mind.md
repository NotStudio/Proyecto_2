```@mermaid
graph TB


Main---Juego
Juego---TexturasSDL

Juego---Objeto
Objeto---Entidad

Entidad-->|K|Juego

Juego---EstadoJuego
EstadoJuego---Estado
Juego---Zona
Zona---Base
Zona---Runs
Estado-->|J|Juego

Juego---Room
Room---Comun
Room---BossLevel
Zona-->Room
 ```

 ```@mermaid
 graph TB
 subgraph Entidades
 Ent(Entidad)---It(item)
 It---Historico
 It---Clave
 It---Consumible
 Ent---Per(Personaje)
 Per---NPC
 subgraph NPC'S
 NPC---Enemy
 NPC---Static
 end
 Per---Player
 subgraph PC
 Player---Toasty
 Player---Tamago
 end
 Ent---Interfaz
 subgraph menu
 Interfaz---Boton
 Interfaz---Cuadro[Cuadro de texto]
 end
 end
 ```

 ```@mermaid
 graph TB
 subgraph Estados
 Estado---Play
 Estado---Menu
 Estado---Pause
 Estado---GameOver
 end
 ```
