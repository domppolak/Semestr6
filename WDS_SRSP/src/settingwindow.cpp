#include "settingwindow.hh"
#include "ui_settingwindow.h"

#include <QSerialPort>
#include <QSerialPortInfo>
#include <QList>

SettingWindow::SettingWindow(QSettings *serialSettings, QWidget *parent)
    : QDialog(parent)
    , _ui(new Ui::SettingWindow)
    , _serialSettings(serialSettings)
{

    _ui->setupUi(this);

    fillSerialPortsInfo();
    fillSerialPortParameters();
}

SettingWindow::~SettingWindow()
{
    delete _ui;
}

void SettingWindow::update()
{
    fillSerialPortsInfo();
    fillSerialPortParameters();
}

void SettingWindow::retranslate()
{
    _ui->retranslateUi(this);
}

void SettingWindow::on_serialPortComboBox_currentIndexChanged(int index)
{
    showPortInfo(index);
}

void SettingWindow::on_applyButton_clicked()
{
    updateSerialSettings();
}


void SettingWindow::on_disconnectButton_clicked()
{
    emit disconectFromSerialPort();
    hide();
}


void SettingWindow::on_connectButton_clicked()
{
    updateSerialSettings();
    emit connectToSerialPort();
    hide();
}

void SettingWindow::updateSerialSettings()
{
    _serialSettings->setValue("serial/indexName", _ui->serialPortComboBox->currentIndex());
    _serialSettings->setValue("serial/indexBaudRate", _ui->baudRateComboBox->currentIndex());
    _serialSettings->setValue("serial/indexWordLength", _ui->wordLengthComboBox->currentIndex());
    _serialSettings->setValue("serial/indexParity", _ui->parityComboBox->currentIndex());
    _serialSettings->setValue("serial/indexStopBits", _ui->stopBitsComboBox->currentIndex());

    _serialSettings->setValue("serial/name", _ui->serialPortComboBox->currentText());
    _serialSettings->setValue("serial/baudRate", static_cast<QSerialPort::BaudRate>(
                                  _ui->baudRateComboBox->itemData(_ui->baudRateComboBox->currentIndex()).toInt()));
    _serialSettings->setValue("serial/wordLengthBits", static_cast<QSerialPort::DataBits>(
                                  _ui->wordLengthComboBox->itemData(_ui->wordLengthComboBox->currentIndex()).toInt()));
    _serialSettings->setValue("serial/parity", static_cast<QSerialPort::Parity>(
                                  _ui->parityComboBox->itemData(_ui->parityComboBox->currentIndex()).toInt()));
    _serialSettings->setValue("serial/stopBits", static_cast<QSerialPort::StopBits>(
                                  _ui->stopBitsComboBox->itemData(_ui->stopBitsComboBox->currentIndex()).toInt()));
}

void SettingWindow::fillSerialPortsInfo()
{
    _ui->serialPortComboBox->clear();
    auto AvailablePorts = QSerialPortInfo::availablePorts();

    if(AvailablePorts.count() < 1){
        _ui->locationLabel->setText(QStringLiteral("N/A"));
        _ui->descriptionLabel->setText(QStringLiteral("N/A"));
        return;
    }

    for(const QSerialPortInfo &port : AvailablePorts){
        QStringList list;
        list << port.portName()
             << (!port.description().isEmpty() ? port.description() : QStringLiteral("N/A"))
             << port.systemLocation();

        _ui->serialPortComboBox->addItem(list.first(), list);
    }

    _ui->serialPortComboBox->setCurrentIndex(_serialSettings->value("serial/indexName", 0).toInt());
    _serialSettings->setValue("serial/name", _ui->serialPortComboBox->currentText());

    showPortInfo(_ui->serialPortComboBox->currentIndex());
}



void SettingWindow::fillBaudRateParameters()
{
    _ui->baudRateComboBox->clear();
    _ui->baudRateComboBox->addItem(QStringLiteral("1200"), QSerialPort::Baud1200);
    _ui->baudRateComboBox->addItem(QStringLiteral("2400"), QSerialPort::Baud2400);
    _ui->baudRateComboBox->addItem(QStringLiteral("4800"), QSerialPort::Baud4800);
    _ui->baudRateComboBox->addItem(QStringLiteral("9600"), QSerialPort::Baud9600);
    _ui->baudRateComboBox->addItem(QStringLiteral("19200"), QSerialPort::Baud19200);
    _ui->baudRateComboBox->addItem(QStringLiteral("38400"), QSerialPort::Baud38400);
    _ui->baudRateComboBox->addItem(QStringLiteral("57600"), QSerialPort::Baud57600);
    _ui->baudRateComboBox->addItem(QStringLiteral("115200"), QSerialPort::Baud115200);
}

void SettingWindow::fillWordLengthParameters()
{
    _ui->wordLengthComboBox->clear();
    _ui->wordLengthComboBox->addItem(QStringLiteral("5"), QSerialPort::Data5);
    _ui->wordLengthComboBox->addItem(QStringLiteral("6"), QSerialPort::Data6);
    _ui->wordLengthComboBox->addItem(QStringLiteral("7"), QSerialPort::Data7);
    _ui->wordLengthComboBox->addItem(QStringLiteral("8"), QSerialPort::Data8);
}

void SettingWindow::fillParityParameters()
{
    _ui->parityComboBox->clear();
    _ui->parityComboBox->addItem("None", QSerialPort::NoParity);
    _ui->parityComboBox->addItem("Even", QSerialPort::EvenParity);
    _ui->parityComboBox->addItem("Odd", QSerialPort::OddParity);
    _ui->parityComboBox->addItem("Space", QSerialPort::SpaceParity);
    _ui->parityComboBox->addItem("Mark", QSerialPort::MarkParity);
}

void SettingWindow::fillStopBitsParameters()
{
    _ui->stopBitsComboBox->clear();
    _ui->stopBitsComboBox->addItem(QStringLiteral("1"), QSerialPort::OneStop);
    _ui->stopBitsComboBox->addItem(QStringLiteral("2"), QSerialPort::TwoStop);
}

void SettingWindow::setDefaultIndexes()
{
    _ui->baudRateComboBox->setCurrentIndex(_serialSettings->value("serial/indexBaudRate", 3).toInt()); // 9600
    _ui->wordLengthComboBox->setCurrentIndex(_serialSettings->value("serial/indexWordLength", 3).toInt()); // 8 bits
    _ui->parityComboBox->setCurrentIndex(_serialSettings->value("serial/indexParity",0).toInt()); // none
    _ui->stopBitsComboBox->setCurrentIndex(_serialSettings->value("serial/indexStopBits", 0).toInt()); // 1
}

void SettingWindow::fillSerialPortParameters()
{
    fillBaudRateParameters();
    fillWordLengthParameters();
    fillParityParameters();
    fillStopBitsParameters();

    setDefaultIndexes();
}

void SettingWindow::showPortInfo(int index)
{
    if(index == -1){
        return;
    }

    const QStringList list = _ui->serialPortComboBox->itemData(index).toStringList();
    _ui->descriptionLabel->setText(QStringLiteral("%1").arg(list.count() > 1 ? list.at(1) : QStringLiteral("N/A")));
    _ui->locationLabel->setText(QStringLiteral("%1").arg(list.count() > 2 ? list.at(2) : QStringLiteral("N/A")));
}


