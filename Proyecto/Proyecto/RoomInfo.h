#pragma once
#include <string>

class RoomInfo
{
public:
	RoomInfo(std::string fichero) :_fichero(fichero){};
	~RoomInfo(){};
	std::string fichero(){
		return _fichero;
	}
	void setPatrones(std::string _PatEne, std::string _PatObj){
		_Patrones = { _PatObj, _PatEne };
	}
	void setPatronEnemigos(std::string _PatEne){
		_Patrones.patronEnemigos=_PatEne;
	}
	void setPatronInanimados(std::string _PatIna){
		_Patrones.patronObjetos = _PatIna;
	}
	std::string PatronEnemigos(){
		return _Patrones.patronEnemigos;
	}
	std::string PatronObjetos(){
		return _Patrones.patronObjetos;
	}
	
private:
	std::string _fichero;
	//primer valor es
	struct Patrones
	{
		std::string patronObjetos;
		std::string patronEnemigos;
	}_Patrones;
};

