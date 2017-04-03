#ifndef MAPDATA_H_
#define MAPDATA_H_


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
	protected:
		Properties();
		//you don't really care
		Properties(rapidxml::xml_node<> * nodo);
		//you don't really care
		void setProperties(rapidxml::xml_node<> * nodo);
		//you don't really care
		void setCustomProperties(rapidxml::xml_node<> * nodo);
	public:
		//get an int value from the properties, it will give you 0 if doesn't exists
		void getValue(const string&, int&);
		//get an string value from the properties, it will give you null string if doesn't exists
		void getValue(const string&, string&);
		//get x 
		int getX(){ int a; getValue("x", a); return a; };
		//get y
		int getY(){ int a; getValue("y", a); return a; };
		//get the name, if it has a name
		string getName(){ string a; getValue("name", a); return a; };
		//get the type, if it has a type
		string getType(){ string a; getValue("type", a); return a; };
		//get the width, if it has a width
		int getW(){ int a; getValue("width", a); return a; };
		//get the height, if it has a height
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
		// the number of objects
		int groupSize() { return _Objects.size(); };
		// get the first object with that name and that type in the group
		ObjectInfo* get_object(const string & name, const string & typ);
		// get an array of objects of the same type
		vector<ObjectInfo*> get_objects_by_type(const string & type);
		// get an array of objects of the same name
		vector<ObjectInfo*> get_objects_by_name(const string & name);
		// get an array of objects of the same name and same type
		vector<ObjectInfo*> get_objects_by_type_name(const string & type, const string & name);
		// get an array of objects without type and name
		vector<ObjectInfo*> get_undefined_objects();
		// i think the name speaks for it self
		vector<ObjectInfo*> GetAllObjects() { return _Objects; };
		// get the n object of the array
		ObjectInfo* at(int n) {
			try
			{
				return _Objects.at(n);
			}
			catch (out_of_range)
			{
				printf("the number %s is out of range you have to choose between 0 and %s \n", n, _Objects.size());
				return nullptr;
			}
		}

	private:
		vector<ObjectInfo*> _Objects;
	};


	class Layer : public Properties
	{
	public:
		Layer();
		Layer(rapidxml::xml_node<> * nodo);
		// get the map of the layer
		void getMap(vector<vector<int>>&);
		// get that cell from the map
		int getCell(int x, int y) {
			return map[y][x];
		}
	private:
		vector<vector<int>> map;
	};

	class MapData : public Properties
	{
	public:
		MapData();
		//give the file it will give you the map
		MapData(string);
		~MapData();
		// get the n layer
		Layer* getLayer( int = 0);
		// get the layer with that name
		Layer* getLayer_by_name(const string &);
		// get the layer with that type
		Layer* getLayer_by_type( const string&);
		// get the layer with that name and that type
		Layer* getLayer_by_type_name(const string&, const string&);
		// get the n group of objects
		Objectgroup* getObjectGroup( int = 0);
		// get the group of objects with that name
		Objectgroup* getObjectGroup( string);
		// total of layers
		int totalLayers() {
			return _layers.size();
		}
		// total of group of objects
		int totalObjGroups() {
			return _objsGroups.size();
		}
	private:
		vector<Layer*> _layers;
		vector<Objectgroup*> _objsGroups;
	};
}
#endif // !MAPDATA_H_

