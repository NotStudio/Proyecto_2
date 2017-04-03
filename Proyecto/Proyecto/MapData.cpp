#include "MapData.h"
#include <stdio.h>
#include <iostream>
#include <fstream>
#include <istream>
#include <sstream>


using namespace TMXReader;

enum tP
{
	BOOL,COLOR,FLOAT,FILES,INT,STRING,_end
};
const string types[]{ "bool","color","float","file","int","string" };
ObjectShape::ObjectShape(int x, int y, int w, int h) :_x(x), _y(y), _w(w), _h(h)
{
}


PolyLine::PolyLine(int x,int y,string points) :ObjectShape(x, y) {
	stringstream reader(points);
	while (getline(reader, points, ' '))
	{
		int auxX, auxY;
		stringstream subreader(points);
		getline(subreader, points, ',');
		auxX = atoi(points.c_str());
		getline(subreader, points, ',');
		auxY = atoi(points.c_str());
		_ShapePoints.push_back({ auxX, auxY });
	}
}


Polygon::Polygon(int x, int y, string points) :PolyLine(x, y, points) {

}


Properties::Properties()
{
}
Properties::Properties(rapidxml::xml_node<> * nodo)
{
	setProperties(nodo);
	if (nodo->first_node("properties")) {
		rapidxml::xml_node<> *auxNod = nodo->first_node("properties");
		setCustomProperties(auxNod);
	}
}
void Properties::setProperties(rapidxml::xml_node<> * nodo){
	for (rapidxml::xml_attribute<> * att = nodo->first_attribute(); att; att =att->next_attribute())
	{
		string name = att->name();
		string value = att->value();
		if (value != "" && !atof(value.c_str())){
			setValue(name, value);
		}
		else{
			setValue(name, atof(value.c_str()));
		}
	}
}
void Properties::setCustomProperties(rapidxml::xml_node<>* nodo)
{
	for (rapidxml::xml_node<> * proper = nodo->first_node("property"); proper; proper = proper->next_sibling()) {
		string name = proper->first_attribute("name")->value();
		string type = proper->first_attribute("type")->value();
		size_t i = 0;
		bool search = true;
		while (i!=_end&&search)
		{
			if (type == types[i])
				search = false;
			else
				i++;
		}
		switch (i)
		{
		case BOOL:
			setValue(name, (proper->first_attribute("value")->value() == "true"));
			break;
		case COLOR:
		case FILES:
		case STRING:
			setValue(name, proper->first_attribute("value")->value());
			break;
		case INT:
		case FLOAT:
			setValue(name, atof(proper->first_attribute("value")->value()));
			break;
		default:
			break;
		}
	}
}
void Properties::setValue(const string & name, const string & value){
	try
	{
		_stringValues.at(name) = value;

	}
	catch (out_of_range)
	{
		_stringValues.emplace(make_pair(name, value));

	}
}
void Properties::setValue(const string & name, const double & value){
	try
	{
		_intValues.at(name) = value;
	}
	catch (out_of_range)
	{
		_intValues.emplace(make_pair(name, value));
	}
}
void Properties::setValue(const string & name, const bool & value) {
	try
	{
		_boolValues.at(name) = value;
	}
	catch (out_of_range)
	{
		_boolValues.emplace(name, value);
	}
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
		value = NULL;
	}
}
ObjectInfo::ObjectInfo(rapidxml::xml_node<> * nodo) :Properties(nodo)
{
	if (nodo->first_node()) {
		rapidxml::xml_node<> * subnode = nodo->first_node();
		string shape = subnode->name();
		if (shape == "properties") {
			subnode = subnode->next_sibling();
			shape = subnode->name();
		}
		if(shape == "ellipse"){
			_shape = new Ellipse(getX(), getY(), getW(), getH());
		}
		else if (shape == "polyline") {
			_shape = new PolyLine(getX(), getY(), subnode->first_attribute()->value());
		}
		else if (shape == "polygon") {
			_shape = new Polygon(getX(), getY(), subnode->first_attribute()->value());
		}
		else {
			_shape = new ObjectShape(getX(), getY(), getW(), getH());
		}
	}
}
ObjectInfo::ObjectInfo()
{
	_shape = nullptr;
}

ObjectInfo::~ObjectInfo()
{
	delete _shape;
	_shape = nullptr;
}
Objectgroup::Objectgroup()
{
}

Objectgroup::Objectgroup(rapidxml::xml_node<> * nodo) :Properties(nodo)
{
	for (rapidxml::xml_node<> * obj = nodo->first_node("object"); obj; obj = obj->next_sibling("object"))
	{
		_Objects.push_back(new ObjectInfo(obj));
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
ObjectInfo* Objectgroup::get_object(const string & name, const string & type){
	size_t i = 0;
	ObjectInfo * obj=nullptr;
	bool doIt = true;
	while (i < _Objects.size()&&doIt)
	{
		if (_Objects[i]->getName() == name&& _Objects[i]->getType() == type){
			obj = _Objects[i];
			doIt = false;
		}
		i++;
	}
	return obj;
}
vector<ObjectInfo*> Objectgroup::get_objects_by_type(const string & type){
	vector<ObjectInfo*> objs;
	for (auto obj : _Objects){
		if (obj->getType() == type){
			objs.push_back(obj);
		}
	}
	return objs;
}
vector<ObjectInfo*> Objectgroup::get_objects_by_name(const string & name){
	vector<ObjectInfo*> objs;
	for (auto obj : _Objects){
		if (obj->getName() == name){
			objs.push_back(obj);
		}
	}
	return objs;
}
vector<ObjectInfo*>  Objectgroup::get_objects_by_type_name(const string & type, const string & name){
	vector<ObjectInfo*> objs;
	for (auto obj : _Objects){
		if (obj->getName() == name&&obj->getType() == type){
			objs.push_back(obj);
		}
	}
	return objs;
}
vector<ObjectInfo*> Objectgroup::get_undefined_objects(){
	return get_objects_by_type_name("", "");
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
	ifstream theFile(dir);
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

Layer* MapData::getLayer(int n)
{
	Layer * l = nullptr;
	try
	{
		l = _layers.at(n);
	}
	catch (out_of_range)
	{
		printf("layer %s is out of range /n", n);
	}
	return l;
}

Layer* MapData::getLayer_by_name(const string &n)
{
	Layer * l = nullptr;
	for (auto la : _layers) {
		if (la->getName() == n)
			l = la;
	}
	return l;
}

Layer* TMXReader::MapData::getLayer_by_type(const string &t)
{
	Layer * l = nullptr;
	for (auto la : _layers) {
		if (la->getType() == t)
			l = la;
	}
	return l;
}

Objectgroup* TMXReader::MapData::getObjectGroup( int n)
{
	Objectgroup * objg = nullptr;
	try
	{
		objg = _objsGroups.at(n);
	}
	catch (out_of_range)
	{
		printf("Object group number %s is out of range the max is %s \n", n, _objsGroups.size());
	}
	return objg;
}

Objectgroup* MapData::getObjectGroup(string n)
{
	Objectgroup* objg = nullptr;
	int i = 0;
	bool search = true;
	while (i < _objsGroups.size()&&search)
	{
		if(_objsGroups[i]->getName()==n){
			search = false;
			objg = _objsGroups[i];
		}
		i++;
	}
	if (i < _objsGroups.size()) {
		printf("the object group %s not found \n",n.c_str());
	}
	return objg;
}

