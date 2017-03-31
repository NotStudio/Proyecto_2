#include "MapData.h"
#include <stdio.h>
#include <iostream>
#include <fstream>
#include <istream>
#include <sstream>



Properties::Properties()
{
}
Properties::Properties(rapidxml::xml_node<> * nodo)
{
	setProperties(nodo);
}
void Properties::setProperties(rapidxml::xml_node<> * nodo){
	for (rapidxml::xml_attribute<> * att = nodo->first_attribute(); att; att =att->next_attribute())
	{
		string name = att->name();
		string value = att->value();
		if (value != "" && !atoi(value.c_str())){
			setValue(name, value);
		}
		else{
			setValue(name, atoi(value.c_str()));
		}
	}
}
void Properties::setValue(const string & name, const string & value){
	_stringValues.emplace(make_pair(name, value));
}
void Properties::setValue(const string & name, const int & value){
	_intValues.emplace(make_pair(name, value));
}
void Properties::getValue(const string&name, string&value){
	try{
		value = _stringValues.at(name);
	}
	catch (out_of_range){
		printf(" value %s not found, you get null string", name.c_str());
		value = "";
	}
}
void Properties::getValue(const string&name , int&value){
	try{
		value = _intValues.at(name);
	}
	catch (out_of_range){
		printf(" value %s not found, you get a 0", name.c_str());
		value = 0;
	}
}
ObjectInfo::ObjectInfo(rapidxml::xml_node<> * nodo) :Properties(nodo)
{
	_Rect = new SDL_Rect{ getX(), getY(), getW(), getH() };
}
ObjectInfo::ObjectInfo()
{
	_Rect = nullptr;
}

ObjectInfo::~ObjectInfo()
{
	delete _Rect;
	_Rect = nullptr;
}
Objectgroup::Objectgroup()
{
}

Objectgroup::Objectgroup(rapidxml::xml_node<> * nodo) :Properties(nodo)
{
	for (rapidxml::xml_node<> * obj = nodo->first_node("object"); obj; obj = obj->next_sibling("object"))
	{
		_Objects.push_back(new ObjectInfo(nodo));
	}
}

Objectgroup::~Objectgroup()
{
	for (size_t i = 0; i < _Objects.size(); i++)
	{
		delete _Objects[i];
		_Objects[i] = nullptr;
	}
}
void Objectgroup::get_object(const string & name, const string & type, ObjectInfo*obj){
	size_t i = 0;
	obj = nullptr;
	bool doIt = true;
	while (i < _Objects.size()&&doIt)
	{
		if (_Objects[i]->getName() == name&& _Objects[i]->getType() == type){
			obj = _Objects[i];
			doIt = false;
		}
		i++;
	}
}
void Objectgroup::get_objects_by_type(const string & type, vector<ObjectInfo*>& objs){
	for (auto obj : _Objects){
		if (obj->getType() == type){
			objs.push_back(obj);
		}
	}
}
void Objectgroup::get_objects_by_name(const string & name, vector<ObjectInfo*>& objs){
	for (auto obj : _Objects){
		if (obj->getName() == name){
			objs.push_back(obj);
		}
	}
}
void Objectgroup::get_objects_by_type_name(const string & type, const string & name, vector<ObjectInfo*> &objs){
	for (auto obj : _Objects){
		if (obj->getName() == name&&obj->getType() == type){
			objs.push_back(obj);
		}
	}
}
void Objectgroup::get_undefined_objects(vector<ObjectInfo*>& objs){
	get_objects_by_type_name("", "", objs);
}

Layer::Layer(rapidxml::xml_node<> * nodo) :Properties(nodo)
{
	string lin="";
	for (rapidxml::xml_node<> * capa = nodo->first_node("data"); capa; capa = capa->next_sibling("data"))
	{
		lin = capa->value();
		lin[0] = ' ';
	}
	stringstream lector(lin);
	int _y = 0;
	map.reserve(getH());
	while (getline(lector, lin, '\n'))
	{
		map.push_back(vector<int>());
		map[_y].reserve(getW());
		stringstream lector2(lin);
		while (getline(lector2, lin, ','))
		{
			map[_y].push_back(atoi(lin.c_str()));
		}
		_y++;
	}
	lector.clear();
}

Layer::Layer()
{
}
void Layer::getMap(vector<vector<int>>& m){
	m = map;
}

MapData::MapData(string dir)
{
	rapidxml::xml_document<> doc;
	rapidxml::xml_node<> * nodo;
	ifstream theFile("untitled.tmx");
	vector<char> buffer((istreambuf_iterator<char>(theFile)), istreambuf_iterator<char>());
	buffer.push_back('\0');
	// Parse the buffer using the xml file parsing library into doc 
	doc.parse<0>(&buffer[0]);
	nodo = doc.first_node("map");
	setProperties(nodo);
	for (rapidxml::xml_node<> * lay = nodo->first_node("layer"); lay ; lay = lay->next_sibling("layer"))
	{
		_layers.push_back(new Layer(lay));
	}
	nodo = doc.first_node("map");
	for (rapidxml::xml_node<> * objsG = nodo->first_node("objectgroup"); objsG; objsG = objsG->next_sibling("objectgroup"))
	{
		_objsGroups.push_back(new Objectgroup(objsG));
	}
}
MapData::MapData()
{

}


MapData::~MapData()
{
	for (auto obj : _layers){
		delete obj;
		obj = nullptr;
	}
	for (auto obj : _objsGroups){
		delete obj;
		obj = nullptr;
	}
}
