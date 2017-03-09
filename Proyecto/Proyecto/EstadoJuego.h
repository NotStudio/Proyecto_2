#ifndef ESTADO_JUEGO_H_
#define ESTADO_JUEGO_H_


class EstadoJuego
{
public:

	EstadoJuego()
	{
	}

	virtual ~EstadoJuego()
	{
	}

	virtual void draw() = 0;
	virtual void update() = 0;
};

#endif