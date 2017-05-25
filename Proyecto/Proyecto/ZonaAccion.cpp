#include "ZonaAccion.h"
#include "checkML.h"
#include "TileInfo.h"

vector<string> roomtype = { "Ini","Normal","Boss","Base"};

ZonaAccion::ZonaAccion(Juego* punteroJuego): ZonaJuego(punteroJuego)
{
	//Inicializamos el array de habitaciones
	niveles = new vector<Room*>;
	niveles->reserve(25);
	//Cambiamos el estado del jugador
	static_cast<Jugable*>(pJuego->getPlayer())->cambiaEstado(Jugable::JUGANDO);
	//Cambiamos su posición al centro del nivel inicial.
}


ZonaAccion::~ZonaAccion()
{
	for (size_t i = 0; i < niveles->size(); i++)
	{
		delete niveles->at(i);
		niveles->at(i) = nullptr;
	}
	delete niveles;
	niveles = nullptr;
	
}
void ZonaAccion::draw(){
	ZonaJuego::draw();

	//Descomentar para ver la disposición de las habitaciones

	for (size_t i = 0; i < niveles->size(); i++)
	{
		SDL_Rect aux = niveles->at(i)->getArea();
		aux.x /= 64; aux.y /= 64; aux.h /= 64; aux.w /= 64; aux.x += 100; aux.y += 100;
		SDL_RenderDrawRect(pJuego->getRender(), &aux);
	}
}

void ZonaAccion::update(){
	//Sin terminar. LLamar solo a setNivelActual cuando se cambie de nivel, no todo el rato.
	setNivelActual();
	ZonaJuego::update();
}

bool ZonaAccion::CheckSolapaRooms(const SDL_Rect & R)
{
	bool flag = true;
	for (size_t i = 0; i < niveles->size()&&flag; i++)
	{
		if (SDL_HasIntersection(&R, &niveles->at(i)->getArea()))
			flag = false;
	}
	return flag;
}

void ZonaAccion::BuildIniRoom(size_t Planta)
{
	BuildRoom(Ini);
}
void ZonaAccion::BuildFinRoom(size_t Planta)
{
	BuildRoom(Fin);
}

void ZonaAccion::BuildRoom(RoomType RoomType_, size_t Planta)
{
	SDL_Delay(1 + rand() % 4);
	srand(SDL_GetTicks());
	Direcciones d=Sinsitio;
	TMXReader::MapData * MapData_=nullptr;
	switch (RoomType_)
	{
	case ZonaJuego::Ini:
		MapData_ = pJuego->getIniRoom();
		break;
	case ZonaJuego::Normal:
		MapData_ = pJuego->getRoom();
		break;
	case ZonaJuego::Boss:
		MapData_ = pJuego->getBossRoom(id);
		break;
	case ZonaJuego::Base:
		MapData_ = pJuego->getBaseRoom();
		break;
	case ZonaJuego::Fin:
		MapData_ = pJuego->getFinRoom();
		break;
	case ZonaJuego::Tutorial:
		MapData_ = pJuego->getTutorialRoom();
	default:
		break;
	}
	if (niveles->size() > 0) {
		SDL_Point p_=getPosiblePositionRoom(MapData_,d);
		niveles->push_back(new Room(pJuego, this, MapData_, p_));
		niveles->at(niveles->size() - 1)->setPuertas(d);
	}
	else {
		niveles->push_back(new Room(pJuego, this, MapData_,SDL_Point{0,0}));
	}
}
SDL_Point ZonaAccion::getPosiblePositionRoom( TMXReader::MapData * Data_,Direcciones& d)
{
	SDL_Rect Rect_ = { 0,0,Data_->getLayer()->getW()*TILE_HEIGHT,Data_->getLayer()->getH()*TILE_HEIGHT };
	int i = niveles->size()-1;
	srand(SDL_GetTicks());
	bool Search = true;
	SDL_Point point;
	do
	{
		vector<pair<SDL_Point, Direcciones>> Points = getPosicionesLados(niveles->at(i),Rect_);
		if (Points.size() != 0) {
			srand(SDL_GetTicks());
			int o = rand() % Points.size();
			point = Points[o].first;
			d = Points[o].second;
			niveles->at(i)->setPuertas(Direcciones(-d));
			Search = false;
		}
		else {
			i--;
		}

	} while (Search);
	return point;
}
vector<pair<SDL_Point, Direcciones>> ZonaAccion::getPosicionesLados(Room * Room_, SDL_Rect&Rect_)
{
	SDL_Rect aux_ = Room_->getArea();
	vector<pair<SDL_Point, Direcciones>> Points;
	Points.reserve(4);
	Rect_.x = aux_.x + (aux_.w - Rect_.w) / 2;
	Rect_.y = aux_.y - Rect_.h;
	if (CheckSolapaRooms(Rect_))
		Points.push_back(make_pair(SDL_Point{ Rect_.x,Rect_.y }, Sur));
	Rect_.y = aux_.y + aux_.h;
	if (CheckSolapaRooms(Rect_))
		Points.push_back(make_pair(SDL_Point{ Rect_.x,Rect_.y }, Norte));
	Rect_.y = aux_.y + (aux_.h - Rect_.h) / 2;
	Rect_.x = aux_.x - Rect_.w;
	if (CheckSolapaRooms(Rect_))
		Points.push_back(make_pair(SDL_Point{ Rect_.x,Rect_.y }, Este));
	Rect_.x = aux_.x + aux_.w;
	if (CheckSolapaRooms(Rect_))
		Points.push_back(make_pair(SDL_Point{ Rect_.x,Rect_.y }, Oeste));
	return Points;

}

void ZonaAccion::setHabitaciones(int NumeroHabitaciones, int NumeroDescansos)
{
	BuildIniRoom();
	static_cast<Jugable*>(pJuego->getPlayer())->setPos(niveles->at(0)->getArea().w/2, niveles->at(0)->getArea().h/2);
	RoomType lastType = Ini;
	int descansos = 1;
	for (size_t i = 0; i <NumeroHabitaciones; i++)
	{
		if (lastType == Ini) {
			BuildRoom(Normal);
			lastType = Normal;
		}
		else {
			if (rand() % NumeroHabitaciones <= NumeroDescansos) {
				BuildIniRoom();
				lastType = Ini;
				NumeroDescansos--;
			}
			else {
				BuildRoom(Normal);
				lastType = Normal;
			}

		}
	}
	if (lastType == Ini) {
		BuildIniRoom();
	}	
	BuildRoom(Boss);
	BuildFinRoom();
}



void ZonaAccion::setNivelActual(){
	//Actualizamos el parametro que indica el nivel en el que estamos
	//y  se lo notificamos a la cámara.
	Room * anterior ;
	if (nivelActual) {
		anterior = nivelActual;
	}
	else {
		anterior = niveles->at(0);
	}
	SDL_Point pj;
	pj.x = static_cast<Entidad*>(pJuego->getPlayer())->getX();
	pj.y = static_cast<Entidad*>(pJuego->getPlayer())->getY();
	int i = 0;
	bool stop = false;
	for (size_t i = 0; i < niveles->size(); i++)
	{
		if (niveles->at(i)->dentroRoom(&pj)) 
			nivelActual = niveles->at(i);
		else niveles->at(i)->stop();
	}
	try
	{
		pJuego->getCamera()->setLimite(nivelActual->getArea());
	}
	catch (const std::exception&)
	{
		pJuego->getCamera()->setLimite(niveles->front()->getArea());
	}

}
