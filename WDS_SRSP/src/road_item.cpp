#include "road_item.hh"


RoadItem::RoadItem(const int &w)
{
    _speed = MIN_SPEED;
    _pixmap = QPixmap(":/road/img/road/road5.png");
    resize(w);
    setFlag(QGraphicsItem :: ItemIsFocusable);
    setFocus();
    isVisible();
    _timer = new QTimer();
    connect(_timer, SIGNAL(timeout()), this, SLOT(move()));
}

RoadItem::~RoadItem()
{
    delete _timer;
}


void RoadItem::setSpeed(const int &speed)
{
    int tmp = speed;
    if(speed > MAX_SPEED){
        tmp = MAX_SPEED;
    }
    if(speed < MIN_SPEED){
        tmp = MIN_SPEED;
    }
    this->_speed = tmp;
}

int RoadItem::getSpeed() const
{
    return this->_speed;
}

void RoadItem::move()
{
    setPos(x(), y()+_speed);
    if(y() > -250){
        setPos(x(), -600);
    }
}

void RoadItem::startAnimation()
{
    _timer->start(25);
}

void RoadItem::stopAnimation()
{
    _timer->stop();
}

void RoadItem::speedChanged(moveData data)
{
    if( data.Y < -350){
        setSpeed(getSpeed() - 1);
    }
    if(data.Y > 350){
        setSpeed(getSpeed() + 1);
    }
}

void RoadItem::resize(const int &w)
{
    int tmpW = w/1.4;
    if(w>1100){
        tmpW = w/1.55;
    }
    setPos(w/2 - tmpW/2, -600);
    setPixmap(_pixmap.scaled(QSize(tmpW, 1500)));
    update();
}
