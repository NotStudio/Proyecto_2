#include"tmxReader.h"
ObjetoInfo::ObjetoInfo(string nombre, int px, int py, int add) { nombreEntidad = nombre; x = (px / 2); y = (py / 2); adicional = (add); }
ObjetoInfo::ObjetoInfo(string nombre, int px, int py, int pw, int ph) { nombreEntidad = (nombre); x = (px / 2); y = (py / 2); w = (pw / 2); h = (ph / 2); };
Mapinfo lector()
{
	xml_document<> doc;
	xml_node<> * root_node;
	ifstream theFile("untitled.tmx");
	vector<char> buffer((istreambuf_iterator<char>(theFile)), istreambuf_iterator<char>());
	buffer.push_back('\0');
	// Parse the buffer using the xml file parsing library into doc 
	doc.parse<0>(&buffer[0]);
	// Find our root node
	int width, height;
	string keku = "";
	root_node = doc.first_node("map");
	// Iterate over the brewery
	for (xml_node<> *brewery_node = root_node->first_node("layer"); brewery_node; brewery_node = brewery_node->next_sibling("layer"))
	{
		cout << brewery_node->name() << endl;
		printf("I have visited %s in %s. ",
			brewery_node->first_attribute("name")->value(),
			brewery_node->first_attribute("width")->value());
		width = atoi(brewery_node->first_attribute("width")->value());
		height = atoi(brewery_node->first_attribute("height")->value());
		// Interate over the beers
		for (xml_node<> * beer_node = brewery_node->first_node("data"); beer_node; beer_node = beer_node->next_sibling())
		{
			printf(" %s ", beer_node->first_attribute("encoding")->value());
			keku = beer_node->value();
			keku[0] = ' ';
		}
		cout << endl;
	}
	std::stringstream lilo(keku);
	string ala;
	vector<string> mapa;
	while (getline(lilo, ala, '\n'))
	{
		mapa.push_back(ala);
	}
	lilo.clear();
	Mapinfo mapInfo;
	mapInfo.Mapa = mapa;
	mapInfo.ancho = width;
	mapInfo.alto = height;
	root_node = doc.first_node("map");
	for (xml_node<> * brewery_node = root_node->first_node("objectgroup"); brewery_node; brewery_node = brewery_node->next_sibling("objectgroup"))
	{
		bool doIt = true;
		bool Enemigos = false;
		int NPatron = -1;
		try
		{
			string id = brewery_node->first_attribute("name")->value();
			if (id != "enemigos"&&id != "inanimados") {
				cout << "esta capa se llama " << id << endl;
				throw exception("becario");
			}
			else if (id == "enemigos")
				Enemigos = true;
			NPatron = atoi(brewery_node->first_node("properties")->first_node("property")->first_attribute("value")->value());

		}
		catch (const std::exception&)
		{
			doIt = false;
			cout << "La capa de objetos No tiene ningun NPatron, asegurate que es la primera propiedad y unica que existe, y que se llama enemigos o inanimados";
		}
		// Interate over the beers
		if (doIt) {
			for (xml_node<> * beer_node = brewery_node->first_node("object"); beer_node; beer_node = beer_node->next_sibling())
			{
				int x, y;
				string nombre;
				nombre = beer_node->first_attribute("name")->value();
				x = atoi(beer_node->first_attribute("x")->value());
				y = atoi(beer_node->first_attribute("y")->value());
				if (Enemigos) {
					try
					{
						mapInfo.meterPatronEnemigos(nombre, x, y, NPatron, atoi(beer_node->first_node("properties")->first_node("property")->first_attribute("value")->value()));
					}
					catch (const std::exception&)
					{
						mapInfo.meterPatronEnemigos(nombre, x, y, NPatron);
					}
				}
				else {
					mapInfo.meterPatronInanimados(nombre, x, y, atoi(beer_node->first_attribute("width")->value()), atoi(beer_node->first_attribute("height")->value()), NPatron);
				}
				printf(" %s ", beer_node->first_attribute("name")->value());
			}
		}
		cout << endl;
	}
	doc.clear();
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
