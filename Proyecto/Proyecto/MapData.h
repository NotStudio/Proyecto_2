#pragma once
#include <vector>
#include <string>
#include <unordered_map>
#include "rapidxml-1.13/rapidxml.hpp"
using namespace std;
namespace TMXReader{
	struct Rect{
		int x;
		int y;
		int w;
		int h;
	};
	class Properties
	{
	public:
		Properties();
		Properties(rapidxml::xml_node<> * nodo);
		void setProperties(rapidxml::xml_node<> * nodo);
		void getValue(const string&, int&);
		void getValue(const string&, string&);
		int getX(){ int a; getValue("x", a); return a; };
		int getY(){ int a; getValue("y", a); return a; };
		string getName(){ string a; getValue("name", a); return a; };
		string getType(){ string a; getValue("type", a); return a; };
		int getW(){ int a; getValue("width", a); return a; };
		int getH(){ int a; getValue("height", a); return a; };
	private:
		void setValue(const string&, const int&);
		void setValue(const string&, const string&);
		unordered_map<string, int> _intValues;
		unordered_map<string, string>_stringValues;
	};


	class ObjectInfo : public Properties
	{
	public:
		ObjectInfo();
		ObjectInfo(rapidxml::xml_node<> * nodo);
		~ObjectInfo();
		Rect getRect(){ return *_Rect; };
	private:
		Rect * _Rect;
	};
	class Objectgroup : public Properties
	{
	public:
		Objectgroup();
		Objectgroup(rapidxml::xml_node<> * nodo);
		~Objectgroup();
		void get_object(const string & name, const string & type, ObjectInfo*obj);
		void get_objects_by_type(const string & type, vector<ObjectInfo*>& objs);
		void get_objects_by_name(const string & name, vector<ObjectInfo*>& objs);
		void get_objects_by_type_name(const string & type, const string & name, vector<ObjectInfo*>& objs);
		void get_undefined_objects(vector<ObjectInfo*>& objs);
	private:
		vector<ObjectInfo*> _Objects;
	};


	class Layer : public Properties
	{
	public:
		Layer();
		Layer(rapidxml::xml_node<> * nodo);
		void getMap(vector<vector<int>>&);

	private:
		vector<vector<int>> map;
	};

	class MapData : public Properties
	{
	public:
		MapData();
		MapData(string);
		~MapData();
		void getLayer(Layer&, int = 0);
		void getLayer_by_name(Layer&, const string &);
		void getLayer_by_type(Layer&, const string&);
		void getLayer_by_type_name(Layer&, const string&, const string&);
		void getObjectGroup(Objectgroup&, int = 0);
		void getObjectGroup(Objectgroup&, string);
	private:
		vector<Layer*> _layers;
		vector<Objectgroup*> _objsGroups;
	};
}

