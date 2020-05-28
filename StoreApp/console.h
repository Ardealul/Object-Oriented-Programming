#pragma once
#include "service.h"

class Console {
private:
	ProdusService& service;

	/*
	citeste datele de la tastatura si adauga produs in lista de produse
	arunca exceptie daca produsul care se doreste a fi adaugat nu este valid
	*/
	void adaugaUI();

	/*
	citeste datele de al tastatura si adauga produs in lista de produse
	arunca exceptie daca produsul care se doreste a fi sters nu exista
	*/
	void stergeUI();

	/*
	citeste datele de la tastatura si modifica un produs din lista de produse
	arunca exceptie daca produsul care se doreste a fi modificata nu exista
	*/
	void modificaUI();

	/*
	citeste datele de la tastatura si tipareste produsul cautat
	arunca exceptie daca produsul nu exista
	*/
	void cautaUI();

	/*
	tipareste lista cu produsele existente
	*/
	void tipareste(const vector<Produs>& listaProduse);

	/*
	filtreaza lista de produse dupa tip
	*/
	void filtrareTip();

	/*
	filtreaza lista de produse dupa pret (produsele care au pret mai mic decat un pret dat)
	*/
	void filtrarePretMaiMic();

	/*
	filtreaza lista de produse dupa pret (produsele care au pret mai mare decat un pret dat)
	*/
	void filtrarePretMaiMare();

	/*
	filtreaza lista de produse dupa pret (produsele care au un pret incadrat intre doua preturi date)
	*/
	void filtrarePret();

	/*
	sorteaza dupa nume
	*/
	void sortareNume();

	/*
	sorteaza dupa producator
	*/
	void sortareProducator();

	/*
	sorteaza dupa tip si pret
	*/
	void sortareTipPret();

	/*
	efectueaza un raport dupa tip
	*/
	void raportTipUI();

	/*
	tipareste meniul
	*/
	void meniu();
	
	void UndoUI();

	//Cos Produs
	void meniuCos();
	void golesteCosUI();
	void adaugaInCosUI();
	void saveToCVS(const string& numeFisier);
	void genereazaCosUI();
	void tiparireCos(const vector<Produs>& cos);


public:
	Console(ProdusService& service) noexcept : service(service) {};
	
	//nu se permite copierea obiectelor de tip Console
	Console(const Console& ot) = delete;

	void run();
};