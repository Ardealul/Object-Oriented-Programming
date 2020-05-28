#pragma once
#include <qwidget.h>
#include <qpaintdevice.h>
#include <qpainter>

#include "service.h"
#include "observer.h"


class GUIDraw : public QWidget, public Observer {
private:
	ProdusService& service;
	Observable& obs;

	void paintEvent(QPaintEvent* ev) override;
	void update() override;

public:
	GUIDraw(ProdusService& service, Observable& obs) : service{ service }, obs{ obs }{
		obs.addObserver(this);
	}
};