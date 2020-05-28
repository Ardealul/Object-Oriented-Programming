#include "GUIDraw.h"
#include <algorithm>
#include <random>
#include <vector>
#include <qcolor.h>

void GUIDraw::update()
{
	repaint();
}

void GUIDraw::paintEvent(QPaintEvent * ev)
{
	int i = 0, x = 0, y = 0, w = 0, h = 0, random = 0, random2 = 0, l = service.getAllCos().size();
	QPainter p{ this };
	vector<QColor> paints = { Qt::black, Qt::red, Qt::blue, Qt::green, Qt::yellow, Qt::lightGray, Qt::darkBlue, Qt::darkCyan, Qt::darkGray, Qt::darkGreen, Qt::darkMagenta, Qt::darkRed, Qt::darkYellow };
	for (i = 0; i < l; i++) {
		std::mt19937 mt{ std::random_device{}() };
		const std::uniform_int_distribution<> dist(0, 12);
		random = dist(mt) % 3;
		random2 = dist(mt);
		p.setPen(paints[random2]);
		if (random == 0) {
			std::mt19937 mt{ std::random_device{}() };
			const std::uniform_int_distribution<> dist(1, 300);
			x = dist(mt);
			y = dist(mt);
			w = dist(mt);
			h = dist(mt);
			QRect r(x, y, w, h);
			p.drawEllipse(r);
		}
		if (random == 1) {
			int x = 0, y = 0, w = 0, h = 0, random2 = 0;
			std::mt19937 mt{ std::random_device{}() };
			const std::uniform_int_distribution<> dist(1, 300);
			x = dist(mt);
			y = dist(mt);
			w = dist(mt);
			h = dist(mt);
			QRect r(x, y, w, h);
			p.drawRect(r);
		}
		if (random == 2) {
			int x = 0, y = 0, w = 0, h = 0, random2 = 0;
			std::mt19937 mt{ std::random_device{}() };
			const std::uniform_int_distribution<> dist(1, 300);
			x = dist(mt);
			y = dist(mt);
			w = dist(mt);
			h = dist(mt);
			QRect r(x, y, w, h);
			p.drawChord(x, y, w, h, 3000, 3000);
		}
	}
}

