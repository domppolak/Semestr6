#include "scene.hh"
#include <QBrush>
#include <ctime>
#include <QMessageBox>
Scene::Scene(QObject *parent)
    : QGraphicsScene(parent)
{
    srand(time(NULL));
    _constSpeed = false;
    _simulationON = false;
    _itemDeleted = true;
    _obstacleON  = true;
}

Scene::~Scene()
{
    delete _road;
    delete _mainCar;
    delete _obstacleCar;
}

void Scene::addCar(const int &w, const int &h)
{
    _mainCar = new CarItem(w, h);
    addItem(_mainCar);
    connect(this, SIGNAL(startSimulationItems()), _mainCar, SLOT(onMoveCar()));
    connect(this, SIGNAL(stopSimulationItems()), _mainCar, SLOT(onStopCar()));
}

void Scene::addRoad(const int &w)
{
    _road = new RoadItem(w);
    addItem(_road);
    connect(this, SIGNAL(startSimulationItems()), _road, SLOT(startAnimation()));
    connect(this, SIGNAL(stopSimulationItems()), _road, SLOT(stopAnimation()));
}

void Scene::addObstacles(const int &w, const int &h)
{
    if(_itemDeleted){
        _obstacleCar = new ObstacleCar(w, h, _road->getSpeed());
        addItem(_obstacleCar);
        connect(this, SIGNAL(startSimulationItems()), _obstacleCar, SLOT(startObstacles()));
        connect(this, SIGNAL(stopSimulationItems()), _obstacleCar, SLOT(stopObstacles()));
        connect(_obstacleCar, SIGNAL(crash()), this, SLOT(carCrash()));
        _itemDeleted = false;
    }
}

void Scene::newDataArrived(rawData data)
{
    if(_simulationON){
        moveData move;
        move.X = data.X/100;
        move.Y = data.Y;
        _mainCar->move(move);
        if(!_constSpeed){
            _road->speedChanged(move);
        }
    }
}

void Scene::startSimulation()
{
    _simulationON = true;
    emit startSimulationItems();
}

void Scene::stopSimulation()
{
    _simulationON = false;
    emit stopSimulationItems();
}

void Scene::resetSimulation(const int &w, const int &h)
{
    _simulationON = false;
    removeItem(_road);
    removeItem(_mainCar);
    delete _road;
    delete _mainCar;
    deleteObstacles();
    addRoad(w);
    addCar(w, h);
    if(_obstacleON){
        addObstacles(w, h);
    }
}

void Scene::onConstSpeed()
{
    this->_constSpeed = true;
}

void Scene::onVariableSpeed()
{
    this->_constSpeed = false;
}

void Scene::carCrash()
{
    emit stopSimulationItems();
    emit crashInformation();

}

void Scene::respObstacles()
{
    addObstacles(_w, _h);
}

void Scene::onObstaclesON()
{
    _obstacleON = true;
    resetSimulation(_w, _h);
}

void Scene::onObstaclesOFF()
{
    deleteObstacles();
    _obstacleON = false;
}

void Scene::deleteObstacles()
{
    if(!_itemDeleted){
        removeItem(_obstacleCar);
        delete _obstacleCar;
        _itemDeleted = true;
    }
}

void Scene::setCarSpeed(const int &speed)
{
    _road->setSpeed(speed);
    _obstacleCar->setSpeed(speed);
}

int Scene::getCarSpeed() const
{
    return _road->getSpeed();
}

bool Scene::getConstSpeedState() const
{
    return this->_constSpeed;
}

void Scene::resizeSceneItems(const int &w, const int &h)
{
    this->_w = w;
    this->_h = h;
    _mainCar->resize(w, h);
    _road->resize(w);
    _obstacleCar->resize(w, h);
    update();
}

