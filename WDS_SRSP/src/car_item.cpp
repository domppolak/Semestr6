#include "car_item.hh"
#include <QTimer>
#include <QRandomGenerator>
#include <QDebug>

CarItem::CarItem(const int &w, const int &h, QObject *parent)
    : QObject(parent)
{
    _stopCar = true;
    _pixmap = QPixmap(":/car/img/models/car.png");
    setPixmap(_pixmap);
    setFlag(QGraphicsItem :: ItemIsFocusable);
    setFocus();
    isVisible();
    resize(w, h);
}

void CarItem::resetPosition()
{
    setPos(235, 300);
}

void CarItem::move(moveData data)
{
    int tmpW, leftW, minus;
    if(_w > 1200){
        tmpW = _w - 375;
        leftW = 200;
        minus = 170;
    }else{
        tmpW = _w - 70;
        leftW = 70;
        minus = 150;
    }
    if(!_stopCar){
        if((pos().x() + data.X) > leftW && (pos().x() + 150 + data.X) < tmpW){
            setPos(x()+data.X, y());
        }
        if((pos().x() + data.X <= leftW)){
            setPos(leftW, y());
        }
        if((pos().x() + 150 + data.X) >= tmpW){
            setPos(tmpW - minus, y());
        }
    }
}

void CarItem::resize(const int &w, const int &h)
{
    int tmpW = w/5.4, tmpH = h/3.62;
    this->_w = w;
    this->_h = h;
    if(w > 1200){
        tmpW = w/5.8;
        tmpH = h/3.55;
        setPos(w/2-250, h-350);
    }else{
        setPos(w/2-125, h-200);
    }

    setPixmap(_pixmap.scaled(QSize(tmpW, tmpH)));
    update();
}



void CarItem::onStopCar()
{
    _stopCar = true;
}

void CarItem::onMoveCar()
{
    _stopCar = false;
}


