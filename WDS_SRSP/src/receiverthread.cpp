#include "receiverthread.hh"

ReceiverThread::ReceiverThread(SerialPortReader *reader)
    : _portReader(reader)
{
    connect(_portReader, SIGNAL(finished()), this, SLOT(_finished()));
    connect(_portReader, SIGNAL(portError()), this, SLOT(_terminate()));
}

void ReceiverThread::run()
{
    if(!_portReader->getPortOpened()){
        emit threadError(tr("Błąd odczytu danych"));
        _terminate();
        return;
    }
    _portReader->readData();
}

void ReceiverThread::onPortOpened()
{
    if(!isRunning()){
        start();
    }else{
       m_cond.wakeOne();
    }
}

void ReceiverThread::_terminate()
{
    wait(1000);
    terminate();
    wait();
    qDebug() << "Unicestwiono watek";
}

void ReceiverThread::_finished()
{
    wait(1000);
    terminate();
    wait();
    qDebug() << "Koniec pracy watku/finish";
}


