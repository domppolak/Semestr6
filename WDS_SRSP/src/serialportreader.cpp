#include "serialportreader.hh"

#include <QMessageBox>
#include <QDebug>


SerialPortReader::SerialPortReader(QObject *parent) : QObject(parent)
{
    _portOpened = false;
    _serialPort = new QSerialPort(this);
    _serialSettings = new QSettings("SRSP", "serial");

    connect(_serialPort, SIGNAL(errorOccured(QSerialPort::SerialPortError)), this, SLOT(serialErrorHandler(QSerialPort::SerialPortError)));
}

SerialPortReader::~SerialPortReader()
{
    delete _serialSettings;
    delete _serialPort;
}

void SerialPortReader::readData()
{
    int errorRead = 0;
    while(_portOpened){
        if(!readDataFromSerial()){
            ++errorRead;
        }else{
            errorRead = 0;
        }

        if(errorRead == 10){
            emit portError(tr("Błąd odczytu danych"));
            closeSerialPort();
            break;
        }

    }
    emit finished();
}

void SerialPortReader::openSerialPort()
{
    _serialPort->setPortName(_serialSettings->value("serial/name").toString());
    _serialPort->setBaudRate(static_cast<QSerialPort::BaudRate>(_serialSettings->value("serial/baudRate").toInt()));
    _serialPort->setDataBits(static_cast<QSerialPort::DataBits>(_serialSettings->value("serial/wordLengthBits").toInt()));
    _serialPort->setParity(static_cast<QSerialPort::Parity>(_serialSettings->value("serial/parity").toInt()));
    _serialPort->setStopBits(static_cast<QSerialPort::StopBits>(_serialSettings->value("serial/stopBits").toInt()));
    _serialPort->setFlowControl(QSerialPort::NoFlowControl);

    if(_serialPort->open(QSerialPort::ReadOnly)){
        _portOpened = true;
        qDebug() << "Port otwarty";
        emit portOpened();
    }else{
        if(_serialPort->isOpen() && _portOpened){
            emit portError(tr("Port otwarty"));
        }else{
            _portOpened = false;
            emit portError(tr("Nie udalo sie polaczyc z mikrokontrolerem"));
        }
    }
}

void SerialPortReader::closeSerialPort()
{
    if(_serialPort->isOpen()){
        _serialPort->close();
        _portOpened = false;
        emit portClosed();
    }
}

int SerialPortReader::readDataFromSerial()
{
    rawData data;
    QString msgBegin, msgEnd;
    uint16_t sumReaded, sumComputed;
    QTextStream stream(_serialPort->readAll());
    stream >> msgBegin;
    if(!_serialPort->waitForReadyRead(500) &&  msgBegin != "!!"){
        return 0;
    }

    stream >> data.X >> data.Y >> data.Z >> sumReaded >> msgEnd;
    if(stream.status() == QTextStream::Ok && msgEnd == "!!"){
        sumComputed = data.X + data.Y + data.Z + 2*data.X+3*data.Y;
        if(sumComputed == sumReaded){
            qDebug() << data.X << " " << data.Y << " " << data.Z;
            emit newData(data);
            return 1;
        }
    }
    return 0;
}

void SerialPortReader::serialErrorHandler(QSerialPort::SerialPortError errorMessage)
{
    if(errorMessage == QSerialPort::ResourceError){
        emit portError(_serialPort->errorString());
        _portOpened = false;
        closeSerialPort();
    }
}

