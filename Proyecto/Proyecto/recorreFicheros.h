#include <iostream>
#include <io.h>
#include <time.h>
#include <string>
using namespace std;
enum TiposArchivo
{
	PNG, TTF, CSV,WAV,MP3,INAPAT,ENEPAT,TMX,
};
const char * _TiposArchivo[] = { ".png", ".ttf",".csv",".wav",".mp3" , ".inapat",".enepat", ".tmx"};
string Chop(string &str)
{
	string res = str;
	int len = str.length();
	if (str[len - 1] == 'r')
	{
		res.replace(len - 1, 1, "\"");
	}
	len = str.length();
	if (str[len - 1] == 'n')
	{
		res.replace(len - 1, 1, "\"");
	}
	return res;
}
void DumpEntry(_finddata_t &data,TiposArchivo const & T)
{
	if ((data.attrib & _A_SUBDIR) == _A_SUBDIR)
	{
		cout << "[" << data.name << "]" << endl;
	}
	else
	{
		cout << data.name << endl;
		
	}
}
void kukxo(string dir, _finddata_t data, TiposArchivo const & T, vector<string> & ass){
	
	int ff = _findfirst((dir + "*.*").c_str(), &data);
	if (ff != -1)
	{
		int res = 0;
		res = _findnext(ff, &data);
		res = _findnext(ff, &data);
		while (res != -1)
		{
			if ((data.attrib & _A_SUBDIR) == _A_SUBDIR){
				kukxo(dir + data.name + "/", data, T, ass);
			}
			else if (string(data.name).find(_TiposArchivo[T])<string(data.name).size())
				ass.push_back(dir+data.name);
			res = _findnext(ff, &data);
		}
		_findclose(ff);
	}
}
vector<string> Buscador(TiposArchivo const T)
{
	vector<string> ass;
	string dir = "Material/";

	_finddata_t data;
	int ff = _findfirst((dir + "*.*").c_str(), &data);
	int res = _findnext(ff, &data);
	if (ff != -1)
	{
		res = _findnext(ff, &data);
		while (res != -1)
		{
			//DumpEntry(data,T);
			if ((data.attrib & _A_SUBDIR) == _A_SUBDIR){
				kukxo(dir+data.name+"/", data,T,ass);
			}
			else if (string(data.name).find(_TiposArchivo[T])<string(data.name).size())
				ass.push_back(dir + data.name);
			res = _findnext(ff, &data);

		}
		_findclose(ff);
	}
	return ass;
}