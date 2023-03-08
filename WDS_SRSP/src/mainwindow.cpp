#include "mainwindow.hh"
#include "ui_mainwindow.h"
#include "ui_settingwindow.h"
#include <QMessageBox>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    _portReader = new SerialPortReader(this);
    _sWindow = new SettingWindow(_portReader->getSerialSettings(), this);
    _plotWindow = new PlotWindow(this);
    _receiverThread = new ReceiverThread(_portReader);
    redLed();

    setupScene();
    setConnections();
    setupSpeedSpinBox();

    _translator = new QTranslator();
    ui->ObstacleCheckBox->setCheckState(Qt::Checked);
}

MainWindow::~MainWindow()
{
    delete ui;
    delete _portReader;
    delete _sWindow;
    delete _plotWindow;
    delete _receiverThread;
    delete _scene;
    delete _translator;
}


void MainWindow::on_ResetPushButton_clicked()
{
    resetSimulation();
}


void MainWindow::on_StopPushButton_clicked()
{
    _scene->stopSimulation();
}


void MainWindow::on_StartPushButton_clicked()
{
    _scene->startSimulation();
}


void MainWindow::on_ObstacleCheckBox_stateChanged(int arg1)
{
    if(arg1){
        emit obstacleON();
    }else{
        emit obstacleOFF();
    }
}

void MainWindow::on_SpeedCheckBox_stateChanged(int arg1)
{
    if(arg1){
        ui->speedWidget->show();
        ui->SpeedSpinBox->setValue(10);
        _scene->setCarSpeed(10);
        emit constSpeed();
    }else{
        ui->speedWidget->hide();
        emit variableSpeed();
    }
}

void MainWindow::on_connectAction_triggered()
{
    _portReader->openSerialPort();
}


void MainWindow::on_disconnectAction_triggered()
{
    _portReader->closeSerialPort();
    _scene->stopSimulation();
}


void MainWindow::on_settingAction_triggered()
{
    _sWindow->update();
    _sWindow->show();
    _scene->stopSimulation();
}

void MainWindow::on_serial_port_opened()
{
    if(_portReader->getPortOpened()){
        ui->mainConnectLabel->setText(tr("Połączono z mikrokontrolerem"));
        greenLed();
    }else{
        ui->mainConnectLabel->setText(tr("Brak połączenia z mikrokontrolerem"));
        redLed();
    }

}

void MainWindow::ErrorHandler(QString error_msg)
{
    QMessageBox::critical(this, tr("Błąd"), error_msg);
}

void MainWindow::crashInformation()
{
    QMessageBox msgBox;
    msgBox.setWindowTitle(tr("Kraksa"));
    msgBox.setText(tr("Kraksa!"));
    QPushButton *reset = msgBox.addButton(tr("Reset"), QMessageBox::ActionRole);
    msgBox.exec();
    if(msgBox.clickedButton() == reset){
        resetSimulation();
    }
}

void MainWindow::greenLed()
{
    ui->led->setPixmap(QPixmap(":/img/img/led/led_green.png"));
}

void MainWindow::redLed()
{
    ui->led->setPixmap(QPixmap(":/img/img/led/led_red.png"));
}

void MainWindow::setupScene()
{
    _scene = new Scene(this);
    w = ui->graphicsView->width();
    h = ui->graphicsView->height();
    _scene->setSceneRect(0,0, w, h);
    _scene->setBackgroundBrush(QBrush(QRgb(0xFFDFD3)));
    _scene->addRoad(w);
    _scene->addCar(w, h);
    _scene->addObstacles(w, h);

    ui->graphicsView->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    ui->graphicsView->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    ui->graphicsView->setScene(_scene);
}

void MainWindow::setConnections()
{
    connect(_sWindow, SIGNAL(connectToSerialPort()),
            _portReader, SLOT(openSerialPort()));
    connect(_sWindow, SIGNAL(disconectFromSerialPort()),
            _portReader, SLOT(closeSerialPort()));

    // port opened
    connect(_portReader, SIGNAL(portOpened()),
            this, SLOT(on_serial_port_opened()));
    connect(_portReader, SIGNAL(portOpened()),
            _receiverThread, SLOT(onPortOpened()));

    // port closed
    connect(_portReader, SIGNAL(portClosed()),
            this, SLOT(on_serial_port_opened()));

    // errors
    connect(_portReader, SIGNAL(portError(QString)),
            this, SLOT(ErrorHandler(QString)));
    connect(_receiverThread, SIGNAL(threadError(QString)),
            this, SLOT(ErrorHandler(QString)));

    // new data
    connect(_portReader, SIGNAL(newData(rawData)),
            _plotWindow, SLOT(new_data_received(rawData)));
    connect(_portReader, SIGNAL(newData(rawData)),
            _scene, SLOT(newDataArrived(rawData)));

    connect(this, SIGNAL(constSpeed()), _scene, SLOT(onConstSpeed()));
    connect(this, SIGNAL(variableSpeed()), _scene, SLOT(onVariableSpeed()));
    connect(this, SIGNAL(obstacleON()), _scene, SLOT(onObstaclesON()));
    connect(this, SIGNAL(obstacleOFF()), _scene, SLOT(onObstaclesOFF()));
    connect(_scene, SIGNAL(crashInformation()), this, SLOT(crashInformation()));
}

void MainWindow::setupSpeedSpinBox()
{
    ui->speedWidget->hide();
    ui->SpeedSpinBox->setMaximum(100);
    ui->SpeedSpinBox->setMinimum(10);
}

int MainWindow::changeLanguage(Language lang)
{

    if(lang == pl_PL)
    {
        qApp->removeTranslator(_translator);
        return 0;
    }
    if(lang == en_EN){
        if(_translator->load(":/translation/translation/WDS_SRSP_en_150.qm")){
            qApp->removeTranslator(_translator);
            qApp->installTranslator(_translator);
            return 0;
        }
    }
    return 1;
}

void MainWindow::retranslate()
{
    ui->retranslateUi(this);
    _plotWindow->retranslate();
    _sWindow->retranslate();
}

void MainWindow::resetSimulation()
{
    w = ui->graphicsView->width();
    h = ui->graphicsView->height();
    _scene->resetSimulation(w, h);
    ui->SpeedSpinBox->setValue(_scene->getCarSpeed());
    if(_scene->getConstSpeedState()){
        emit variableSpeed();
        ui->SpeedCheckBox->setCheckState(Qt::Unchecked);
    }
}


void MainWindow::on_FigurePushButton_clicked()
{
    _plotWindow->show();
}


void MainWindow::on_SpeedSpinBox_valueChanged(int arg1)
{
    _scene->setCarSpeed(arg1);
}

void MainWindow::resizeEvent(QResizeEvent *event)
{
    w = ui->graphicsView->width();
    h = ui->graphicsView->height();
    _scene->resizeSceneItems(w, h);
    _scene->setSceneRect(0, 0, w, h);
    QMainWindow::resizeEvent(event);
}


void MainWindow::on_polishAction_triggered()
{
    if(!changeLanguage(pl_PL)){
        retranslate();
        QMessageBox::information(this, tr("Język"), tr("Ustawiono język polski"));
    }
}


void MainWindow::on_englishAction_triggered()
{
    if(!changeLanguage(en_EN)){
        retranslate();
        QMessageBox::information(this, tr("Język"), tr("Ustawiono język angielski"));
    }
}

