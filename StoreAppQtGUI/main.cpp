#include "lab1011.h"
#include <QtWidgets/QApplication>
#include "service.h"
#include "MySweetyGUI.h"
#include "CosGUI.h"

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);
	lab1011 w;
	ProdusRepository repo;
	ProdusValidator val;
	Observable obs;
	ProdusService service{ repo,val };
	service.adaugaProdus(1, "paine", "casa", 5, "piata");
	service.adaugaProdus(2, "paste", "fainoase", 9, "Carbonara");
	service.adaugaProdus(3, "bere", "blonda", 3, "Heineken");
	service.adaugaProdus(4, "pateu", "vegetal", 7, "Ardealul");
	service.adaugaProdus(5, "oua", "casa", 10, "piata");
	service.adaugaProdus(6, "suc", "cola", 6, "Coca-Cola");
	
	MySweetyGUI gui{ service, obs };
	//CosGUI gui{ service };
	 
	

	return a.exec();
}
