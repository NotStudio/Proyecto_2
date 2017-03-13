#include "Perseguidor.h"
#include "checkML.h"


//HAY QUE CAMBIAR EL STRING QUE PASA COMO ID
Perseguidor::Perseguidor(Juego* punteroJuego, SDL_Rect a) : Enemigo(punteroJuego, a, "Gato"), coefMov(7.0f)
{
	stats.daño = 1;

}
void Perseguidor::move(){
	float x = static_cast<Entidad*>(pJuego->getPlayer())->getX();
	float y = static_cast<Entidad*>(pJuego->getPlayer())->getY();
	b2Vec2 velFloat;
	velFloat.x = 0.0f;
	velFloat.y = 0.0f;
	
	b2Vec2 posJug = b2Vec2(x, y);
	//Vector para la diferencia entre el vect del jugador y el vect del enemigoPerseguidor
	b2Vec2 vecDir = posJug - pos;

	//Calculamos el vector unitario del vector de direccion.
	b2Vec2 unitario = b2Vec2((vecDir.x / vecDir.Length()), (vecDir.y / vecDir.Length()));

	velFloat.x = unitario.x*coefMov;
	velFloat.y = unitario.y*coefMov;

	body->SetLinearVelocity(velFloat);
}
void Perseguidor::update() {
	Entidad::update();
	move();
	
}
void Perseguidor::onColisionEnter(Objeto* contactObject) {
	Jugable * k = dynamic_cast<Jugable *>(contactObject);
	if (k != nullptr)
	{
		cout << "Colision\n";
		k->restaVidas(stats.daño);
		cout << "Vidas Jugador: " << k->getVidas() << '\n';
	
	}
}

Perseguidor::~Perseguidor()
{
}
