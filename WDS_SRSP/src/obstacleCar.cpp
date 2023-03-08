#include "obstacleCar.hh"
#include "car_item.hh"

ObstacleCar::ObstacleCar(const int &w, const int &h, const int &speed, QObject *parent)
    : QObject(parent)
    , QGraphicsPixmapItem()
    , _speed(speed)
{
    srand(time(NULL));
    _pixmap = QPixmap(":/car/img/models/car.png");
    resize(w, h);
    setFlag(QGraphicsItem :: ItemIsFocusable);
    setFocus();
    isVisible();
    setRandomPos();
    _timer = new QTimer();
    connect(_timer, SIGNAL(timeout()), this, SLOT(move()));
}

ObstacleCar::~ObstacleCar()
{
    delete _timer;
}

void ObstacleCar::setSpeed(const int &speed)
{
    _speed = speed;
}

/*int ObstacleCar::getSpeed() const
{
    return this->_speed;
}*/

void ObstacleCar::move()
{
    setPos(x(), y() + _speed);

    QList<QGraphicsItem *> colliding_Items = collidingItems();
    for(int i=0; i<colliding_Items.size(); i++){
        auto &item = *colliding_Items[i];
        if(typeid(item) == typeid(CarItem)){
            emit crash();
            return;
        }
    }
    if(y() > _h+200){
        setRandomPos();
    }
}

void ObstacleCar::stopObstacles()
{
    _timer->stop();
}

void ObstacleCar::startObstacles()
{
    _timer->start(25);
}

void ObstacleCar::resize(const int &w, const int &h)
{
    int tmpW = w/5.4, tmpH = h/3.62;
    this->_h = h;
    this->_w = w;
    if(w > 1200){
        tmpW = w/5.8;
        tmpH = h/3.55;
    }

    setPixmap(_pixmap.scaled(QSize(tmpW, tmpH)));
    update();
}

void ObstacleCar::setRandomPos()
{
    int randomNum = 0;
    if(_w > 1200){
        randomNum = rand() % ((int)(_w - 600)) + 200;
    }
    else{
        randomNum = rand() % ((int)(_w - 300)) + 150;
    }

    setPos(randomNum, -400);
}
