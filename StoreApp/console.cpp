#include "console.h"

using std::cin;
using std::endl;

void Console::tipareste(const vector<Produs>& listaProduse)
{
	if (listaProduse.size() == 0) {
		cout << "Lista de produse este goala!";
		return;
	}
	for (const auto& prod : listaProduse) {
		cout << "ID: " << prod.getId() << "\tNume: " << prod.getNume() << "\tTip: " << prod.getTip() << "\tPret: " << prod.getPret() << "\tProducator: " << prod.getProducator() << '\n';
	}
}

void Console::adaugaUI()
{
	int id, pret;
	string nume, tip, producator;
	cout << "ID: "; cin >> id;
	cout << "Nume: "; cin >> nume;
	cout << "Tip: "; cin >> tip;
	cout << "Pret: "; cin >> pret;
	cout << "Producator: "; cin >> producator;
	service.adaugaProdus(id, nume, tip, pret, producator);
	cout << "Produsul a fost adaugat cu succes!\n";
}

void Console::stergeUI()
{
	int id;
	cout << "ID: "; cin >> id;
	service.stergeProdus(id);
	cout << "Produsul a fost sters cu succes!\n";
}

void Console::modificaUI()
{
	int id, pretNou;
	string numeNou, tipNou, producatorNou;
	cout << "ID: "; cin >> id;
	cout << "Nume nou: "; cin >> numeNou;
	cout << "Tip nou: "; cin >> tipNou;
	cout << "Pret nou: "; cin >> pretNou;
	cout << "Producator nou: "; cin >> producatorNou;
	service.modificaProdus(id, numeNou, tipNou, pretNou, producatorNou);
	cout << "Produsul a fost modificat cu succes!\n";
}

void Console::cautaUI()
{
	int id;
	cout << "ID: "; cin >> id;
	Produs prod{ 1," "," ",0," " };
	prod = service.cautaProdus(id);
	cout << "Produsul cautat:\n";
	cout << "ID: " << prod.getId() << "\tNume: " << prod.getNume() << "\tTip: " << prod.getTip() << "\tPret: " << prod.getPret() << "\tProducator: " << prod.getProducator() << '\n';
}

void Console::filtrareTip()
{
	string tip;
	cout << "Tip: "; cin >> tip;
	cout << "Lista filtrata dupa tipul "<<tip<<" este: \n";
	tipareste(service.filtrareTip(tip));
}

void Console::filtrarePretMaiMic()
{
	int pretMax;
	cout << "Pret maxim: "; cin >> pretMax;
	cout << "Lista filtrata dupa pretul maxim "<<pretMax<<" este: \n";
	tipareste(service.filtrarePretMaiMic(pretMax));
}

void Console::filtrarePretMaiMare()
{
	int pretMin;
	cout << "Pret minim: "; cin >> pretMin;
	cout << "Lista filtrata dupa pretul minim "<<pretMin<<" este: \n";
	tipareste(service.filtrarePretMaiMare(pretMin));
}

void Console::filtrarePret()
{
	int pretMin, pretMax;
	cout << "Pret minim: "; cin >> pretMin;
	cout << "Pret maxim: "; cin >> pretMax;
	cout << "Lista filtrate dupa pretul minim "<<pretMin<<" si pretul maxim "<<pretMax<<" este: \n";
	tipareste(service.filtrarePret(pretMin, pretMax));
}

void Console::sortareNume()
{
	cout << "Lista sortata dupa nume este: \n";
	tipareste(service.sortareNume());
}

void Console::sortareProducator()
{
	cout << "Lista sortata dupa producator este: \n";
	tipareste(service.sortareProducator());
}

void Console::sortareTipPret()
{
	cout << "Lista sortata dupa pret este: \n";
	tipareste(service.sortareTipPret());
}

void Console::raportTipUI()
{
	vector<ProdusTipDTO> raport = service.raportTip();
	for (auto element : raport) {
		cout << "Cu tipul " << element.getTipDTO() << " sunt " << element.getNr() << " produse.\n";
	}
}

void Console::UndoUI()
{
	service.undo();
	cout << "Undo s-a efectuat cu succes!\n";
	tipareste(service.getAll());
}

void Console::meniu()
{
	cout << "\n";
	cout << "------------------------------------------------------\n";
	cout << "Meniu: \n";
	cout << " 1. Adauga\n";
	cout << " 2. Sterge\n";
	cout << " 3. Modifica\n";
	cout << " 4. Afisare\n";
	cout << " 5. Cauta\n";
	cout << " 6. Filtrare dupa tip\n";
	cout << " 7. Filtrare dupa pret mai mic\n";
	cout << " 8. Filtrare dupa pret mai mare\n";
	cout << " 9. Filtrare dupa pret\n";
	cout << " 10. Sortare dupa nume\n";
	cout << " 11. Sortare dupa producator\n";
	cout << " 12. Sortare dupa tip + pret\n";
	cout << " 13. Raport dupa tip\n";
	cout << " 14. UNDO\n";
	cout << "--------------\n";
	cout << " 15. Wishlist\n";
	cout << " 0. Inchide aplicatia\n";
	cout << "------------------------------------------------------\n";
}


void Console::meniuCos()
{
	cout << "\n";
	cout << "---------------------------\n";
	cout << "Meniu Wishlist: \n";
	cout << " 1. Goleste\n";
	cout << " 2. Adauga\n";
	cout << " 3. Salvare in fisier\n";
	cout << " 4. Genereaza\n";
	cout << " 5. Tipareste\n";
	cout << " 0. Iesire meniu Wishlist\n";
	cout << "---------------------------\n";
}

void Console::golesteCosUI()
{
	service.golesteCos();
	cout << "Wishlist gol!\n";
	cout << "Dimensiune Wishlist: " << service.getSizeCos() << "\n";
}

void Console::adaugaInCosUI()
{
	int id;
	cout << "Introduceti id: ";
	cin >> id;
	Produs p{ 0, " ", " ", 0, " " };
	p = service.cautaProdus(id);
	service.adaugaInCos(p);
	cout << "Produsul introdus s-a adaugat in Wishlist\n";
	cout << "Dimensiune Wishlist: " << service.getSizeCos() << "\n";
}

void Console::saveToCVS(const string & numeFisier)
{
	service.saveToCVS(numeFisier);
	cout << "Datele din cos au fost salvate cu succes in fisierul: " << numeFisier << std::endl;
}

void Console::genereazaCosUI()
{
	int numar;
	cout << "Cate produse doriti sa se genereze?\n";
	cin >> numar;
	service.genereazaCos(numar);
	cout << "S-au generat " << numar << " produse\n";
	cout << "Dimensiune Wishlist: " << service.getSizeCos() << "\n";
}

void Console::tiparireCos(const vector<Produs>& cos)
{
	if (cos.size() == 0)
	{
		cout << "Cosul cu produse este gol!\n";
		return;
	}
	for (const auto& produs : cos)
	{
		cout << "Nume: " << produs.getNume() << "\t" << " Tip: " << produs.getTip() << "\t" << " Pret: " <<produs.getPret() << "\t" << " Producator: " << produs.getProducator() << '\n';
	}
}

void Console::run()
{
	while (true)
	{
		meniu();
		int comanda;
		cout << "Introduceti comanda: "; cin >> comanda;
		try
		{
			switch (comanda) {
				case 1:
					adaugaUI();
					break;
				case 2:
					stergeUI();
					break;
				case 3:
					modificaUI();
					break;
				case 4:
					tipareste(service.getAll());
					break;
				case 5:
					cautaUI();
					break;
				case 6:
					filtrareTip();
					break;
				case 7:
					filtrarePretMaiMic();
					break;
				case 8:
					filtrarePretMaiMare();
					break;
				case 9:
					filtrarePret();
					break;
				case 10:
					sortareNume();
					break;
				case 11:
					sortareProducator();
					break;
				case 12:
					sortareTipPret();
					break;
				case 13:
					raportTipUI();
					break;
				case 14:
					UndoUI();
					break;
				case 15:
					meniuCos();
					int cmd;
					cout << "Introduceti comanda meniu Wishlist: ";
					cin >> cmd;
					switch (cmd)
					{
					case 1:
						golesteCosUI();
						break;
					case 2:
						adaugaInCosUI();
						break;
					case 3:
						saveToCVS("CosProdus.txt");
						break;
					case 4:
						genereazaCosUI();
						break;
					case 5:
						tiparireCos(service.getAllCos());
						break;
					case 0:
						cout << "Meniu Wishlist inchis\n";
						break;
					}
					break;
				case 0:
					cout << "Bye!\n";
					return;
				default:
					cout << "Comanda invalida! Incercati din nou!\n";
			}
		}
		catch (const ProdusRepositoryException& mesaj)
		{
			cout << mesaj << "\n";
		}
		catch (const ValidatorException& mesaj) {
			cout << mesaj << "\n";
		}
	}
}
