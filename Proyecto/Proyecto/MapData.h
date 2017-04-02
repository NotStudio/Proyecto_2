#pragma once
#include <vector>
#include <string>
#include <unordered_map>
#include "rapidxml-1.13/rapidxml.hpp"
using namespace std;
namespace TMXReader{
	/// Shapes
	// -------------------------------------------
	struct Point
	{
		int x, y;
	};
	class ObjectShape
	{
	public:
		ObjectShape() {};
		ObjectShape(int, int, int = 0, int = 0);
	protected:
		int _x, _y, _w, _h;
	};
	class Ellipse:public ObjectShape
	{
	public:
		Ellipse(int x, int y, int w = 0, int h = 0):ObjectShape(x,y,w,h) {}
		void getCenter(int& cx, int& cy) {
			cx = _x + _w / 2;
			cy = _y + _h / 2;
		};
		void getRadius(int& rx, int &ry) {
			rx =_w / 2;
			ry =_h / 2;
		};
	private:
	};
	class PolyLine:public ObjectShape
	{
	public:
		PolyLine(int x, int y, string points);
		vector<Point> get_ShapePoints() { return _ShapePoints; };

	protected:
		vector<Point>_ShapePoints;
	};
	class Polygon:public PolyLine
	{
	public:
		Polygon(int x, int y, string points);

	private:

	};
	// -------------------------------------------

	class Properties
	{
	public:
		Properties();
		Properties(rapidxml::xml_node<> * nodo);
		void setProperties(rapidxml::xml_node<> * nodo);
		void setCustomProperties(rapidxml::xml_node<> * nodo);
		void getValue(const string&, int&);
		void getValue(const string&, string&);
		int getX(){ int a; getValue("x", a); return a; };
		int getY(){ int a; getValue("y", a); return a; };
		string getName(){ string a; getValue("name", a); return a; };
		string getType(){ string a; getValue("type", a); return a; };
		int getW(){ int a; getValue("width", a); return a; };
		int getH(){ int a; getValue("height", a); return a; };
	private:
		void setValue(const string&, const double&);
		void setValue(const string&, const string&);
		void setValue(const string&, const bool&);
		unordered_map<string, double> _intValues;
		unordered_map<string, string>_stringValues;
		unordered_map<string, bool>_boolValues;
	};


	class ObjectInfo : public Properties
	{
	public:
		ObjectInfo();
		ObjectInfo(rapidxml::xml_node<> * nodo);
		~ObjectInfo();
		ObjectShape getRect(){ return *_shape; };
	private:
		ObjectShape * _shape;
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
		void getLayer(Layer*, int = 0);
		void getLayer_by_name(Layer*, const string &);
		void getLayer_by_type(Layer*, const string&);
		void getLayer_by_type_name(Layer*, const string&, const string&);
		void getObjectGroup(Objectgroup*, int = 0);
		void getObjectGroup(Objectgroup*, string);
		int totalLayers() {
			return _layers.size();
		}
		int totalObjGroups() {
			return _objsGroups.size();
		}
	private:
		vector<Layer*> _layers;
		vector<Objectgroup*> _objsGroups;
	};
}

