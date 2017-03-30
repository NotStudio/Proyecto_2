#include"tmxReader.h"
ObjetoInfo::ObjetoInfo(string nombre, string type, int px, int py, int add) { nombreEntidad = nombre; tipo = type; x = (px / 2); y = (py / 2); }
ObjetoInfo::ObjetoInfo(string nombre, string type, int px, int py, int pw, int ph) { nombreEntidad = (nombre); tipo = type;x = (px / 2); y = (py / 2); w = (pw / 2); h = (ph / 2); };
Mapinfo lector()
{
	xml_document<> doc;
	xml_node<> * root_node;
	ifstream theFile("untitled.tmx");
	Mapinfo mapInfo;
	vector<char> buffer((istreambuf_iterator<char>(theFile)), istreambuf_iterator<char>());
	buffer.push_back('\0');
	// Parse the buffer using the xml file parsing library into doc 
	doc.parse<0>(&buffer[0]);
	// Find our root node
	int width, height;
	string aux;
	root_node = doc.first_node("map");
	// Iterate over the brewery
	for (xml_node<> *layer = root_node->first_node("layer"); layer; layer = layer->next_sibling("layer"))
	{
		width = atoi(layer->first_attribute("width")->value());
		height = atoi(layer->first_attribute("height")->value());
		// Interate over the beers
		for (xml_node<> * capa = layer->first_node("data"); capa; capa = capa->next_sibling("data"))
		{
			aux = capa->value();
			aux[0] = ' ';
		}
		cout << endl;
	}
	mapInfo.Mapa.reserve(height);
	stringstream lector(aux);
	int _y=0;
	while (getline(lector,aux, '\n'))
	{
		mapInfo.Mapa.push_back(vector<int>());
		mapInfo.Mapa[_y].reserve(width);
		stringstream lector2(aux);
		while (getline(lector2, aux, ','))
		{
			mapInfo.Mapa[_y].push_back(atoi(aux.c_str()));
		}
		_y++;
	}
	lector.clear();
	mapInfo.ancho = width;
	mapInfo.alto = height;

	root_node = doc.first_node("map");
	int ncapa = -1;
	for (xml_node<> * capa = root_node->first_node("objectgroup"); capa; capa = capa->next_sibling("objectgroup"))
	{
		ncapa++;
		mapInfo.Patrones.push_back(Patron());
		for (xml_node<> * objeto = capa->first_node("object"); objeto; objeto = objeto->next_sibling("object"))
		{

			if (objeto->first_attribute("type")) {
				string type = objeto->first_attribute("type")->value();
				if (objeto->first_attribute("name")) {
					string name = objeto->first_attribute("name")->value();
					int x = atoi(objeto->first_attribute("x")->value())/2;
					int y = atoi(objeto->first_attribute("y")->value())/2;
					if (type == "enemigo") {
						mapInfo.Patrones[ncapa].meter(ObjetoInfo(name, type, x, y, 0));
					}
					else if (type == "inanimado") {
						int w = atoi(objeto->first_attribute("width")->value()) / 2;
						int h = atoi(objeto->first_attribute("height")->value()) / 2;
						mapInfo.Patrones[ncapa].meter(ObjetoInfo(name, type, x, y, w,h));
					}
					else {
						cout << "Becario el tipo que has puesto no existe\n";
					}
				}
				else {
					cout << "Becario te has olvidado de ponerle un nombre al objeto \n";
				}
			}
			else {
				cout << "Becario te has olvidado de ponerle un tipo al objeto \n";
			}
		}
	}
	doc.clear();
	theFile.close();
	return mapInfo;

}

vector<ObjetoInfo> getPatron(int n)
{
	xml_document<> doc;
	xml_node<> * root_node;
	ifstream theFile("untitled.tmx");
	vector<char> buffer((istreambuf_iterator<char>(theFile)), istreambuf_iterator<char>());
	buffer.push_back('\0');
	// Parse the buffer using the xml file parsing library into doc 
	doc.parse<0>(&buffer[0]);
	return vector<ObjetoInfo>();
}
