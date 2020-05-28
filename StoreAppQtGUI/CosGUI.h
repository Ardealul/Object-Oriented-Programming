#pragma once
#include "repository.h"
#include "service.h"
#include "qwidget.h"
#include <qboxlayout.h>
#include <qformlayout.h>
#include <qlineedit.h>
#include <qtablewidget.h>
#include <qpushbutton.h>
#include <qlabel.h>
#include <qlistwidget.h>
#include <sstream>
#include "CosProdus.h"
#include "observer.h"

using std::stringstream;

class CosGUI :public QWidget, public Observer {
public:
	CosGUI( ProdusService& service, Observable& obs ) : cos(service), obs(obs) {
		initComponents();
		//initialGUIState();
		connectSignals();
		loadCos();
	};

	void update() override {
		loadCos();
		obs.notify();
	}

	//~CosGUI() = default;
	~CosGUI() {
		cos.removeObserver(this);
	}

private:
	ProdusService& cos;
	Observable& obs;

	//QTableWidget* table = new QTableWidget(0,5,this);
	QListWidget* lista = new QListWidget;

	QBoxLayout* layout = new QHBoxLayout;
	QVBoxLayout* leftSide = new QVBoxLayout;
	QVBoxLayout* rightSide = new QVBoxLayout;
	QFormLayout* form = new QFormLayout;
	QHBoxLayout* btnRight = new QHBoxLayout;
	QHBoxLayout* layGenerate = new QHBoxLayout;
	QHBoxLayout* titlu = new QHBoxLayout;

	QLineEdit* lineID = new QLineEdit;
	QLineEdit* lineNume = new QLineEdit;
	QLineEdit* lineTip = new QLineEdit;
	QLineEdit* linePret = new QLineEdit;
	QLineEdit* lineProducator = new QLineEdit;
	QLineEdit* nrToGenerate = new QLineEdit;

	QPushButton* btnAdd = new QPushButton("Adauga in cos");
	QPushButton* btnRemove = new QPushButton("Goleste cos");
	QPushButton* btnGenerate = new QPushButton("Genereaza cos");
	QPushButton* btnSaveToCVS = new QPushButton("Save to a CVS file");

	QLabel* total = new QLabel();

	void initComponents() {

		cos.addObserver(this);
		
		QWidget* main = new QWidget;

		//stanga
		QLabel* labelTitlu = new QLabel("Cos de cumparaturi");
		titlu->addStretch();
		titlu->addWidget(labelTitlu);
		titlu->addStretch();
		leftSide->addLayout(titlu);
		leftSide->addWidget(lista);

		total->setText("Total: 0");
		QFont font = total->font();
		font.setPointSize(10);
		total->setFont(font);

		leftSide->addWidget(total);
		leftSide->addStretch();

		//dreapta
		QLabel* labelID = new QLabel("ID");
		/*QLabel* labelNume = new QLabel("Nume");
		QLabel* labelTip = new QLabel("Tip");
		QLabel* labelPret = new QLabel("Pret");
		QLabel* labelProducator = new QLabel("Producator");*/
		
		form->addRow(labelID, lineID);
		/*form->addRow(labelNume, lineNume);
		form->addRow(labelTip, lineTip);
		form->addRow(labelPret, linePret);
		form->addRow(labelProducator, lineProducator);*/
		rightSide->addLayout(form);
		
		btnRight->addWidget(btnAdd);
		btnRight->addWidget(btnRemove);
		btnRight->addWidget(btnSaveToCVS);

		QLabel* labelGenerate = new QLabel("Cate doriti sa se genereze?");
		layGenerate->addWidget(labelGenerate);
		layGenerate->addWidget(nrToGenerate);
		layGenerate->addWidget(btnGenerate);
		
		rightSide->addLayout(layGenerate);
		rightSide->addLayout(btnRight);
		rightSide->addStretch();

		//imbinare
		layout->addLayout(leftSide);
		layout->addLayout(rightSide);

		main->setLayout(layout);
		main->show();

	}

	void loadCos() {
		lista->clear();
		for (const auto& produs : cos.getAllCos()) {
			QListWidgetItem* item = new QListWidgetItem(QString{ string{QString::number(produs.getId()).toStdString() + "   " + produs.getNume() + "   " + produs.getTip() + "   " + QString::number(produs.getPret()).toStdString() + "   " + produs.getProducator()}.c_str() });
			lista->addItem(item);
		}
		total->setText(QString{ "Total: " }+QString::number(calculateTotal()));
	}

	int calculateTotal() {
		int suma = 0;
		for (const auto& produs : cos.getAllCos()) {
			suma += produs.getPret();
		}
		return suma;
	}

	//nu ne mai foloseste, am inlocuit functia cu loadCos()
	void initialGUIState() {
		lista->clear();
		for (auto produs : cos.getAllCos()) {
			QListWidgetItem* item = new QListWidgetItem(QString::fromStdString(produs.getProdus()), lista);
			item->setData(Qt::UserRole, QString::fromStdString(produs.getNume()));
		}
	}

	void connectSignals() {
		QObject::connect(btnAdd, &QPushButton::clicked, [&]() {
			try {
				int id = lineID->text().toInt();
				Produs p = cos.cautaProdus(id);
				cos.adaugaInCos(p);
				//initialGUIState();
				loadCos();
				//lineID->clear();
			}
			catch (ProdusRepositoryException& eroare) {
				QMessageBox::warning(nullptr, "Eroare", "Produsul nu a fost gasit!");
			}
			catch (ValidatorException& eroare) {
				QMessageBox::warning(nullptr, "Eroare", "Ai grija la  validare!");
			}
		});
		QObject::connect(btnRemove, &QPushButton::clicked, [&]() {
			cos.golesteCos();
			loadCos();
		});
		QObject::connect(btnGenerate, &QPushButton::clicked, [&]() {
			int nr = nrToGenerate->text().toInt();
			cos.genereazaCos(nr);
			loadCos();
		});
		QObject::connect(btnSaveToCVS, &QPushButton::clicked, [&]() {
			cos.saveToCVS("CosProdus.txt");
		});
	}
};