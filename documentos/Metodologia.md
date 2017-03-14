# Metodología
## Toma decisiones
La toma general de decisiones sobre las tareas se deposita en las personas que han realizado ese trabajo, ya que lo han hecho según está descrito en la tarea (GDD y PivotalTracker). Es decir, cada avance en el desarrollo del juego es responsabilidad de las personas que han de implementarlo. Ahora bien, toda implementación está expuesta a crítica y evaluación del resto de componentes del estudio. En el caso de no haber concordancia de opiniones entre todos los desarrolladores, la decisión final residirá en las personas que la han implementado.
En cuanto a las decisiones importantes, cómo modificar, quitar o añadir nuevas 'features' al juego, debe llegarse a consenso entre todos los componentes del estudio. Si no se llega a consenso, no se lleva a cabo el cambio.
## Modus Operandi
El estudio está conformado actualmente por 8 personas. Para organizarnos y repartir las tareas, utilizamos distintas herramientas:

- Skype / Discord: herramientas principales para hablar mientras realizamos tareas fuera de la Universidad, hacer reuniones, etc.

- Pivotal Tracker: cada persona tiene una tarea activa en todo momento en Pivotal, de modo que siempre sabe cuál es su trabajo para esa semana. Al comenzar la tarea, hay que notificarlo en la aplicación. Así también, al terminar debemos marcarla como terminada. Los demás componentes del grupo han de evaluarla antes de aceptarla.

- Git y GitHub: repositorios en los que se encuentra el proyecto. En el máster en todo momento ha de haber una versión jugable del proyecto, pudiendo existir ramas que estén en desarrollo.
## Tareas especificas
### Diseñar una room
Al diseñar una Room se han de cumplir estas condiciones para que dicha room sea valida.
- Dos tamaños:
  - 20x20 (el nombre de la room tiene que ser [nombre sin Espacios]\_Grande.map)
  - 16x16(el nombre de la room tiene que ser [nombre sin Espacios]\_Peque.map)
- En no se pueden bloquear los tiles de entrada o de salida, es decir:
  - en las habitaciones 20x20 no se pueden colocar tiles que colisionen en las posiciones.
    - (1,9),(2,9),(17,9),(18,9)
    - (9,1),(9,2),(9,17),(9,18)
    - (1,10),(2,10),(17,10),(18,10)
    - (10,1),(10,2),(10,17),(10,18)
  - en las habitaciones 16x16 no se pueden colocar tiles que colisionen en las posiciones.
    - (1,7),(2,7),(13,7),(14,7)
    - (7,1),(7,2),(7,13),(7,14)
    - (1,8),(2,8),(13,8),(14,8)
    - (8,1),(8,2),(8,13),(8,14)
- Las habitaciones se pueden crear en tiled mientras, pero se han de exportar en formato **CSV Y LUEGO SE ELIMINEN LAS COMAS DEL ARCHIVO, PARA HACERLO SE TIENE QUE ABRIR DESDE UN EDITOR DE TEXTO Y REEMPLAZAR LAS COMAS POR UN ESPACIO** 
