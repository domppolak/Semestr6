#include <QString>
#include <QDebug>
#include <QSharedPointer>
#include <QTime>

#include "plotwindow.hh"
#include "ui_plotwindow.h"

PlotWindow::PlotWindow(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::PlotWindow)
{
    ui->setupUi(this);

    PlotWindow::MakePlot();
}

PlotWindow::~PlotWindow()
{
    delete ui;
}

void PlotWindow::retranslate()
{
    ui->retranslateUi(this);
}

void PlotWindow::new_data_received(rawData data)
{
    _time += static_cast<double>(10)/1000;
    ui->customPlot->graph(0)->addData(_time, data.X);
    ui->customPlot->graph(1)->addData(_time, data.Y);
    ui->customPlot->graph(2)->addData(_time, data.Z);\
    ui->customPlot->xAxis->setRange(_time, 8, Qt::AlignRight);
    ui->customPlot->replot();
    ui->customPlot->update();
}

void PlotWindow::MakePlot()
{
    ui->customPlot->legend->setVisible(true);
    ui->customPlot->setInteraction(QCP::iRangeDrag);
    ui->customPlot->setInteraction(QCP::iRangeZoom);

    ui->customPlot->plotLayout()->insertRow(0);
    ui->customPlot->plotLayout()->addElement(( new QCPTextElement(ui->customPlot, tr("Osie akcelerometru"), QFont("sans", 12, QFont::Bold))));

    ui->customPlot->addGraph();
    ui->customPlot->graph(0)->setPen(QPen(QColor("blue")));
    ui->customPlot->graph(0)->setName("X");

    ui->customPlot->addGraph();
    ui->customPlot->graph(1)->setPen(QPen(QColor("green")));
    ui->customPlot->graph(1)->setName("Y");

    ui->customPlot->addGraph();
    ui->customPlot->graph(2)->setPen(QPen(QColor("red")));
    ui->customPlot->graph(2)->setName("Z");

    ui->customPlot->yAxis->setRange(-2000, 2000);
    ui->customPlot->yAxis->setLabel(tr("Przyspieszenie [mg]"));

    QSharedPointer<QCPAxisTickerTime> timeTicker(new QCPAxisTickerTime);
    timeTicker->setTimeFormat("%h:%m:%s");
    ui->customPlot->xAxis->setTicker(timeTicker);
    ui->customPlot->axisRect()->setupFullAxesBox();
    ui->customPlot->xAxis->setLabel(tr("Czas [hh:mm:ss]"));
}
