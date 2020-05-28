#include "repository.h"
#include <algorithm>

using std::for_each;
using std::find_if;

/*
  Adauga produs in lista cu produse
  Input: prod - Produs
  Output: exceptie - ProdusRepositoryException
  Arunca exceptie daca mai exista un produs identic in lista cu produse
*/
void ProdusRepository::adauga(const Produs& prod)
{
	//find_if returneaza pozitia
	auto gasit = find_if(listaProduse.begin(), listaProduse.end(), [prod](const Produs& p) noexcept	{return prod.getId() == p.getId(); });
	if (gasit == listaProduse.end()) { listaProduse.push_back(prod); }
	else throw ProdusRepositoryException("Produsul se afla deja in repository!\n");
}

/*
  Sterge produs din lista de produse
  Input: prod - Produs
  Output: exceptie - ProdusRepositoryException
  Arunca exceptie daca produsul nu exista in lista de produse
*/
void ProdusRepository::sterge(const Produs& prod)
{
	auto gasit = find_if(listaProduse.begin(), listaProduse.end(), [prod](const Produs& p) noexcept {return prod.getId() == p.getId(); });
	if (gasit==listaProduse.end())
	{
		throw ProdusRepositoryException("Produsul nu se afla in repository!\n");
	}
	auto rez = listaProduse.erase(gasit);
}

/*
  Modifica un anumit produs din lista de produse
  Input: prod - Produs
		 numeNou, tipNou, producatorNou - string
		 pretNou - int
  Output: exceptie - ProdusRepositoryException
  Arunca exceptie daca produsul nu exista in lista de produse
*/
void ProdusRepository::modifica(const Produs& prod, const string& numeNou, const string& tipNou, int pretNou, const string& producatorNou)
{
	numeNou, tipNou, pretNou, producatorNou;
	for_each(listaProduse.begin(), listaProduse.end(), [&](auto& p) {
		if (p.getId()==prod.getId())
		{
			p.setNume(numeNou);
			p.setTip(tipNou);
			p.setPret(pretNou);
			p.setProducator(producatorNou);
			return;
		}
	});
}

/*
  Cauta un anumit produs in lista de produse
  Input: id - int
  Output: exceptie - ProdusRepositoryException
  Arunca exceptie daca nu exista niciun produs cu caracteristicile introduse in lista de produse
*/
const Produs& ProdusRepository::cauta(int id) const
{
	vector<Produs>::const_iterator rez = find_if(listaProduse.begin(), listaProduse.end(), [id](const auto& prod) noexcept {return prod.getId() == id; });
	if (rez == listaProduse.end()) {
		throw ProdusRepositoryException("Produsul nu a fost gasit!");
	}
	else return *rez;
}

const vector<Produs> ProdusRepository::getAll()
{
	return listaProduse;
}

ostream & operator<<(ostream & out, const ProdusRepositoryException& mesaj)
{
	out << mesaj.mesaj;
	return out;
}

void RepositoryProbabilitate::adauga(const Produs & prod)
{
	auto const rez = rand() / float(RAND_MAX);
	if (rez<probabilitate)
	{
		throw ProdusRepositoryException("Nu se adauga! Exceptie!");
	}
	if (produse.find(prod.getId()) == produse.end()) {
		produse[prod.getId()] = prod;
	}
	else throw ProdusRepositoryException("Produsul se afla deja in repository!");
}

void RepositoryProbabilitate::sterge(const Produs & prod)
{
	auto const rez = rand() / float(RAND_MAX);
	if (rez<probabilitate)
	{
		throw ProdusRepositoryException("Nu se sterge! Exceptie!");
	}
	if (produse.find(prod.getId()) == produse.end()) {
		throw ProdusRepositoryException("Produsul cautat nu a fost gasit!");
	}
	else produse.erase(prod.getId());
}

void RepositoryProbabilitate::modifica(const Produs & prod, const string & numeNou, const string & tipNou, int pretNou, const string & producatorNou)
{
	auto const rez = rand() / float(RAND_MAX);
	if (rez < probabilitate) {
		throw ProdusRepositoryException("Nu se modifica! Exceptie!");
	}
	if (produse.find(prod.getId()) == produse.end()) {
		throw ProdusRepositoryException("Produsul nu a fost gasit!");
	}
	else
		produse[prod.getId()] = Produs{ prod.getId(),numeNou,tipNou,pretNou,producatorNou };
}

const Produs & RepositoryProbabilitate::cauta(int id) const
{
	auto const rez = rand() / float(RAND_MAX);
	if (rez<probabilitate)
	{
		throw ProdusRepositoryException("Nu se cauta! Exceptie!");
	}
	if (produse.find(id) == produse.end())
	{
		throw ProdusRepositoryException("Produsul nu a fost gasit!");
	}
	else return produse.at(id);
}

const vector<Produs> RepositoryProbabilitate::getAll()
{
	vector<Produs> rez;
	for (auto produs : produse) { rez.push_back(produs.second); }
	return rez;
}
