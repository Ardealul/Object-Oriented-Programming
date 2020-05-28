#pragma once
#include <qwidget.h>
#include "service.h"
#include <qpushbutton.h>
#include <qlineedit.h>
#include <qlistwidget.h>
#include <qboxlayout.h>
#include <qformlayout.h>
#include <qlabel.h>
#include <qstring.h>
#include <qerrormessage.h>
#include <qmessagebox.h>
#include <qtablewidget.h>
#include "CosGUI.h"
#include "observer.h"
#include "GUIDraw.h"

using std::to_string;
class MySweetyGUI: public QWidget, public Observable {
public:
	MySweetyGUI(ProdusService& service, Observable& obs) :service(service), obs(obs) {
		initGUIComponents();
		initialGUIState(service.getAll());
		connectSignals();
	}
private:
	ProdusService& service;
	Observable& obs;

	QPushButton* btnAdd = new QPushButton("Add");
	QPushButton* btnRem = new QPushButton("Remove");
	QPushButton* btnModif = new QPushButton("Update");
	QPushButton* btnUndo = new QPushButton("Undo");
	QPushButton* btnCos = new QPushButton("Cos");
	QPushButton* btnGenerareCos = new QPushButton("Genereaza cos");
	QPushButton* btnGolesteCos = new QPushButton("Goleste cos");
	QPushButton* btnSaveToCVS = new QPushButton("Save to CVS");
	QPushButton* btnDraw = new QPushButton("Cos Read Only");
	
	QPushButton* btnSortN = new QPushButton("Sort by name");
	QPushButton* btnSortP = new QPushButton("Sort by producator");
	QPushButton* btnSortTP = new QPushButton("Sort by tip+pret");
	
	QPushButton* btnFilterT = new QPushButton("Filtrare tip");
	QPushButton* btnFilterPL = new QPushButton("Filtrare pret mai mic");
	QPushButton* btnFilterPG = new QPushButton("Filtrare pret mai mare");
	QPushButton* btnFilterP = new QPushButton("Filtrare pret");

	QLineEdit* lineID = new QLineEdit;
	QLineEdit* lineNume = new QLineEdit;
	QLineEdit* lineTip = new QLineEdit;
	QLineEdit* linePret = new QLineEdit;
	QLineEdit* lineProducator = new QLineEdit;
	QLineEdit* filtruT = new QLineEdit;
	QLineEdit* filtruPL = new QLineEdit;
	QLineEdit* filtruPG = new QLineEdit;
	QLineEdit* filtruP1 = new QLineEdit;
	QLineEdit* filtruP2 = new QLineEdit;
	QLineEdit* lineGenerate = new QLineEdit;

	QListWidget* list = new QListWidget;
	QTableWidget* table = new QTableWidget(0,6,this);

	void initGUIComponents() {
		QWidget* main = new QWidget;

		QHBoxLayout* layout = new QHBoxLayout;
		QVBoxLayout* laySt = new QVBoxLayout;
		QVBoxLayout* layDr = new QVBoxLayout;

		QFormLayout* dreaptaSus = new QFormLayout;
		QHBoxLayout* layBtnSort = new QHBoxLayout;
		QHBoxLayout* layBtn = new QHBoxLayout;
		QHBoxLayout* layBtn2 = new QHBoxLayout;
		QHBoxLayout* titlu = new QHBoxLayout;

		QHBoxLayout* layFiltruT = new QHBoxLayout;
		QHBoxLayout* layFiltruPL = new QHBoxLayout;
		QHBoxLayout* layFiltruPG = new QHBoxLayout;
		QHBoxLayout* layFiltruP = new QHBoxLayout;
		QHBoxLayout* layDraw = new QHBoxLayout;

		QFormLayout* layGenerateCos = new QFormLayout;
		QHBoxLayout* layBtnCos = new QHBoxLayout;

		//stanga
		QLabel* produse = new QLabel("Produse");
		titlu->addStretch();
		titlu->addWidget(produse);
		titlu->addStretch();


		laySt->addLayout(titlu);
		//laySt->addWidget(list);
		laySt->addWidget(table);
		table->setSelectionMode(QAbstractItemView::SingleSelection);
		table->setHorizontalHeaderItem(0, new QTableWidgetItem("ID"));
		table->setHorizontalHeaderItem(1, new QTableWidgetItem("Nume"));
		table->setHorizontalHeaderItem(2, new QTableWidgetItem("Tip"));
		table->setHorizontalHeaderItem(3, new QTableWidgetItem("Pret"));
		table->setHorizontalHeaderItem(4, new QTableWidgetItem("Producator"));
		table->setHorizontalHeaderItem(5, new QTableWidgetItem("Nr"));


		layBtnSort->addWidget(btnSortN);
		layBtnSort->addWidget(btnSortP);
		layBtnSort->addWidget(btnSortTP);
		laySt->addLayout(layBtnSort);

		/*laySt->addWidget(btnFilterT);
		laySt->addWidget(btnFilterPL);
		laySt->addWidget(btnFilterPG);
		laySt->addWidget(btnFilterP);*/

		QLabel* lblFiltruT = new QLabel("Tip:");
		QLabel* lblFiltruPL = new QLabel("Pret maxim:");
		QLabel* lblFiltruPG = new QLabel("Pret minim:");
		QLabel* lblFiltruP1 = new QLabel("Minim:");
		QLabel* lblFiltruP2 = new QLabel("Maxim:");

		layFiltruT->addWidget(btnFilterT);
		layFiltruT->addWidget(lblFiltruT);
		layFiltruT->addWidget(filtruT);
		
		layFiltruPL->addWidget(btnFilterPL);
		layFiltruPL->addWidget(lblFiltruPL);
		layFiltruPL->addWidget(filtruPL);
		
		layFiltruPG->addWidget(btnFilterPG);
		layFiltruPG->addWidget(lblFiltruPG);
		layFiltruPG->addWidget(filtruPG);
		
		layFiltruP->addWidget(btnFilterP);
		layFiltruP->addWidget(lblFiltruP1);
		layFiltruP->addWidget(filtruP1);
		layFiltruP->addWidget(lblFiltruP2);
		layFiltruP->addWidget(filtruP2);
		
		laySt->addLayout(layFiltruT);
		laySt->addLayout(layFiltruPL);
		laySt->addLayout(layFiltruPG);
		laySt->addLayout(layFiltruP);

		//dreapta
		QLabel* lblID = new QLabel("ID:");
		QLabel* lblNume = new QLabel("Nume:");
		QLabel* lblTip = new QLabel("Tip:");
		QLabel* lblPret = new QLabel("Pret:");
		QLabel* lblProducator = new QLabel("Producator:");
		
		dreaptaSus->addRow(lblID, lineID);
		dreaptaSus->addRow(lblNume, lineNume);
		dreaptaSus->addRow(lblTip, lineTip);
		dreaptaSus->addRow(lblPret, linePret);
		dreaptaSus->addRow(lblProducator, lineProducator);

		layDr->addLayout(dreaptaSus);

		layBtn->addWidget(btnAdd);
		layBtn->addWidget(btnRem);
		layBtn->addWidget(btnModif);
		layDr->addLayout(layBtn);

		layBtn2->addWidget(btnUndo);
		layBtn2->addWidget(btnCos);

		layDr->addLayout(layBtn2);

		//optiuni cos
		QLabel* labelGenerate = new QLabel("Cate produse doriti sa generati?");
		layGenerateCos->addRow(labelGenerate, lineGenerate);
		layDr->addLayout(layGenerateCos);

		layBtnCos->addWidget(btnGenerareCos);
		layBtnCos->addWidget(btnGolesteCos);
		layBtnCos->addWidget(btnSaveToCVS);
		layDr->addLayout(layBtnCos);

		layDraw->addWidget(btnDraw);
		layDr->addLayout(layDraw);
		layDr->addStretch();

		layout->addLayout(laySt);
		layout->addLayout(layDr);
		main->setLayout(layout);
		main->show();
	}

	void initialGUIState(const vector<Produs> v) {
		table->setRowCount(0);
		int counter = 0; //am setat un contor pt elementele vectorului
		int size = service.getAll().size(); // dimensiunea vectorului
		list->clear();
		for (auto el : v) {
			table->insertRow(table->rowCount());

			int id = el.getId();
			string nume = el.getNume();
			string tip = el.getTip();
			int pret = el.getPret();
			string producator = el.getProducator();
			int nr = 0;
			for (auto el : service.getAll()) {
				if (el.getTip() == tip) {
					nr++;
				}
			}

			QTableWidgetItem* item1 = new QTableWidgetItem(to_string(id).c_str());
			QTableWidgetItem* item2 = new QTableWidgetItem(nume.c_str());
			QTableWidgetItem* item3 = new QTableWidgetItem(tip.c_str());
			QTableWidgetItem* item4 = new QTableWidgetItem(to_string(pret).c_str());
			QTableWidgetItem* item5 = new QTableWidgetItem(producator.c_str());
			QTableWidgetItem* item6 = new QTableWidgetItem(to_string(nr).c_str());


			if (counter < size / 3) {
				item1->setBackground(QBrush{ Qt::red,Qt::SolidPattern });
				item2->setBackground(QBrush{ Qt::red,Qt::SolidPattern });
				item3->setBackground(QBrush{ Qt::red,Qt::SolidPattern });
				item4->setBackground(QBrush{ Qt::red,Qt::SolidPattern });
				item5->setBackground(QBrush{ Qt::red,Qt::SolidPattern });
				item6->setBackground(QBrush{ Qt::red,Qt::SolidPattern });
			}
			else if (counter < 2 * size / 3) {
				item1->setBackground(QBrush{ Qt::yellow,Qt::SolidPattern });
				item2->setBackground(QBrush{ Qt::yellow,Qt::SolidPattern });
				item3->setBackground(QBrush{ Qt::yellow,Qt::SolidPattern });
				item4->setBackground(QBrush{ Qt::yellow,Qt::SolidPattern });
				item5->setBackground(QBrush{ Qt::yellow,Qt::SolidPattern });
				item6->setBackground(QBrush{ Qt::yellow,Qt::SolidPattern });
			}
			else {
				item1->setBackground(QBrush{ Qt::blue,Qt::SolidPattern });
				item2->setBackground(QBrush{ Qt::blue,Qt::SolidPattern });
				item3->setBackground(QBrush{ Qt::blue,Qt::SolidPattern });
				item4->setBackground(QBrush{ Qt::blue,Qt::SolidPattern });
				item5->setBackground(QBrush{ Qt::blue,Qt::SolidPattern });
				item6->setBackground(QBrush{ Qt::blue,Qt::SolidPattern });
			}
			counter++;
			table->setItem(table->rowCount() - 1, 0, item1);
			table->setItem(table->rowCount() - 1, 1, item2);
			table->setItem(table->rowCount() - 1, 2, item3);
			table->setItem(table->rowCount() - 1, 3, item4);
			table->setItem(table->rowCount() - 1, 4, item5);
			table->setItem(table->rowCount() - 1, 5, item6);

			/*QListWidgetItem* item = new QListWidgetItem{ QString::fromStdString(el.getNume()) };
			if (counter < size / 3) {
				item->setBackground(QBrush{ Qt::red,Qt::SolidPattern });
			}
			else if (counter < 2 * size / 3) {
				item->setBackground(QBrush{ Qt::yellow,Qt::SolidPattern });
			}
			else {
				item->setBackground(QBrush{ Qt::blue,Qt::SolidPattern });
			}
			counter++;
			list->addItem(item);*/
		}
		table->resizeColumnsToContents();
	}
	

	void connectSignals() {
		QObject::connect(btnAdd, &QPushButton::clicked, [&]() {
			try {
				int id = lineID->text().toInt();
				string nume = lineNume->text().toStdString();
				string tip = lineTip->text().toStdString();
				int pret = linePret->text().toInt();
				string producator = lineProducator->text().toStdString();
				service.adaugaProdus(id, nume, tip, pret, producator);
				initialGUIState(service.getAll());
				lineID->clear();
				lineNume->clear();
				lineTip->clear();
				linePret->clear();
				lineProducator->clear();
			}
			catch (ValidatorException& err) {
				QMessageBox::warning(nullptr, "Eroare", "Ai grija la validare!");
			}
			catch (ProdusRepositoryException& err) {
				QMessageBox::warning(nullptr, "Eroare", "Adaugat deja!");
			}
		});
		QObject::connect(btnRem, &QPushButton::clicked, [&]() {
			try {
				int id = lineID->text().toInt();
				service.stergeProdus(id);
				initialGUIState(service.getAll());
				lineID->clear();
			}
			catch(ProdusRepositoryException& err){
				QMessageBox::warning(nullptr, "Eroare", "Nu este gasit!");
			}
		});
		QObject::connect(btnModif, &QPushButton::clicked, [&]() {
			try
			{
				int id = lineID->text().toInt();
				string numeNou = lineNume->text().toStdString();
				string tipNou = lineTip->text().toStdString();
				int pretNou = linePret->text().toInt();
				string producatorNou = lineProducator->text().toStdString();
				service.modificaProdus(id, numeNou, tipNou, pretNou, producatorNou);
				initialGUIState(service.getAll());
				lineID->clear();
				lineNume->clear();
				lineTip->clear();
				linePret->clear();
				lineProducator->clear();
			}
			catch (ProdusRepositoryException& err)
			{
				QMessageBox::warning(nullptr, "Eroare", "Nu este gasit!");
			}
		});

		QObject::connect(table, &QTableWidget::itemSelectionChanged, [&]() {
			if (table->selectedItems().isEmpty()) {
				lineID->setText("");
				return;
			}
			QTableWidgetItem* id = table->selectedItems().at(0);
			/*QTableWidgetItem* nume = table->selectedItems().at(1);
			QTableWidgetItem* tip = table->selectedItems().at(2);
			QTableWidgetItem* pret = table->selectedItems().at(3);
			QTableWidgetItem* producator = table->selectedItems().at(4);
			QTableWidgetItem* nr = table->selectedItems().at(5);*/
			lineID->setText(id->text());
			/*lineNume->setText(nume->text());
			lineTip->setText(tip->text());
			linePret->setText(pret->text());
			lineProducator->setText(producator->text());
			nr->setText(nr->text());*/
			
		});

		//sort
		QObject::connect(btnSortN, &QPushButton::clicked, [&]() {
			initialGUIState(service.sortareNume());
		});
		QObject::connect(btnSortP, &QPushButton::clicked, [&]() {
			initialGUIState(service.sortareProducator());
		});
		QObject::connect(btnSortTP, &QPushButton::clicked, [&]() {
			initialGUIState(service.sortareTipPret());
		});
		//filtre
		QObject::connect(btnFilterT, &QPushButton::clicked, [&]() {
			string tip = filtruT->text().toStdString();
			initialGUIState(service.filtrareTip(tip));
			filtruT->clear();
		});
		QObject::connect(btnFilterPL, &QPushButton::clicked, [&]() {
			int pret = filtruPL->text().toInt();
			initialGUIState(service.filtrarePretMaiMic(pret));
			filtruPL->clear();
		});
		QObject::connect(btnFilterPG, &QPushButton::clicked, [&]() {
			int pret = filtruPG->text().toInt();
			initialGUIState(service.filtrarePretMaiMare(pret));
			filtruPG->clear();
		});
		QObject::connect(btnFilterP, &QPushButton::clicked, [&]() {
			int pretMin = filtruP1->text().toInt();
			int pretMax = filtruP2->text().toInt();
			initialGUIState(service.filtrarePret(pretMin,pretMax));
			filtruP1->clear();
			filtruP2->clear();
		});
		QObject::connect(btnUndo, &QPushButton::clicked, [&]() {
			try {
				service.undo();
				initialGUIState(service.getAll());
			}
			catch (ProdusRepositoryException& err) {
				QMessageBox::warning(nullptr, "Eroare", "Undo nu se mai poate efectua!");
			}
		});
		QObject::connect(btnCos, &QPushButton::clicked, [&]() {
			CosGUI* cosWindow = new CosGUI{ service, obs };
			cosWindow->setWindowModality(Qt::ApplicationModal);
			//cosWindow->show();
		});
		QObject::connect(btnGenerareCos, &QPushButton::clicked, [&]() {
			CosGUI* cosWindow = new CosGUI{ service, obs };
			cosWindow->setWindowModality(Qt::ApplicationModal);
			int nr = lineGenerate->text().toInt();
			service.genereazaCos(nr);
		});
		QObject::connect(btnGolesteCos, &QPushButton::clicked, [&]() {
			CosGUI* cosWindow = new CosGUI{ service, obs };
			cosWindow->setWindowModality(Qt::ApplicationModal);
			service.golesteCos();
		});
		QObject::connect(btnSaveToCVS, &QPushButton::clicked, [&]() {
			
		});
		QObject::connect(btnDraw, &QPushButton::clicked, [&]() {
			GUIDraw* draw = new GUIDraw{ service, obs };
			draw->show();
		});
	}
};