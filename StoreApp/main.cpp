#define _CRTDBG_MAP_ALLOC
#include <stdlib.h>
#include <crtdbg.h>
#include "console.h"
#include "test.h"

void adaugaAutomat(ProdusService& service) {
	service.adaugaProdus(1, "paine", "casa", 4, "Otomani");
	service.adaugaProdus(2, "salam", "florin", 6, "Caroli");
	service.adaugaProdus(3, "deodorant", "spray", 10, "Dove");
	service.adaugaProdus(4, "pateu", "vegetal", 5, "Ardealul");
	service.adaugaProdus(5, "palinca", "prune", 10, "Rieni");
}

int main() {

	{
		Test runTest;
		runTest.testAll();

		system("cls");

		//ProdusRepository repo;
		//ProdusFileRepository repo{ "Produse.txt" };
		RepositoryProbabilitate repo{ 0.5 };
		ProdusValidator validator;
		ProdusService service{ repo,validator };

		Console UI{ service };
		UI.run();
	}

	_CrtDumpMemoryLeaks();

	system("pause");
	return 0;
}