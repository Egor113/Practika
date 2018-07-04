#include "widget.h"
#include "qcustomplot.h"

Widget::Widget(QWidget *parent) :
    QWidget(parent)
{
    resize(500,400);
    setWindowTitle(QString::fromUtf8("Гистограмма"));
    customPlot = new QCustomPlot(this);
    vbox = new QVBoxLayout(this);


    vbox->addWidget(customPlot);
    res = new QPushButton(QString::fromUtf8("Показать или обновить гистограмму"),this);
    vbox->addWidget(res);
    setLayout(vbox);
    // Сигналы
    connect(res,SIGNAL(clicked()),this,SLOT(rndres()));
}

void Widget::rndres()
{

    fossil = new QCPBars(customPlot->xAxis, customPlot->yAxis);

    //customPlot->addPlottable(fossil);
    //customPlot->addPlottable(fossil);
    // Установки цвета:
    QPen pen;
    pen.setWidthF(1.5);//Толщина контура столбца
    fossil->setName(word); // Легенда
    pen.setColor(QColor(50, 50, 100));// Цвет контура столбца
    fossil->setPen(pen);
    // Цвет самого столбца, четвертый параметр - прозрачность
    fossil->setBrush(QColor(50, 50, 250, 70));

    // Установки значений оси X:
    QVector<double> ticks;
    QVector<QString> labels;
    for(int i = 0; i < v.size(); ++i) {
        ticks << i+1;
        labels << v[i].diagID;
    }
//    ticks << 1 << 2 << 3 << 4 << 5 << 6 << 7;
//    labels << "1" << "2" << "3" << "4" << "5" << "6" << "7";
//    customPlot->xAxis->setAutoTicks(false);
//    customPlot->xAxis->setAutoTickLabels(false);
//    customPlot->xAxis->setTickVector(ticks);
//    customPlot->xAxis->setTickVectorLabels(labels);
//    customPlot->xAxis->setSubTickCount(0);
    customPlot->xAxis->setLabel(QString::fromUtf8("Диагнозы"));
    //customPlot->xAxis->setupTickVectors();
    customPlot->xAxis->setTickLength(0, 4);
    customPlot->xAxis->grid()->setVisible(true);
    customPlot->xAxis->setRange(0, 8);

    // Установки значений оси Y:
    customPlot->yAxis->setRange(0, 12.1);
    customPlot->yAxis->setPadding(5);
    customPlot->yAxis->setLabel(QString::fromUtf8("Частота повторения"));
    customPlot->yAxis->grid()->setSubGridVisible(true);
    QPen gridPen;
    gridPen.setStyle(Qt::SolidLine);
    gridPen.setColor(QColor(0, 0, 0, 25));
    customPlot->yAxis->grid()->setPen(gridPen);
    gridPen.setStyle(Qt::DotLine);
    customPlot->yAxis->grid()->setSubGridPen(gridPen);


    // Данные:
    QVector<double> fossilData;
    for(int i = 0; i < v.size(); ++i)
        fossilData.append((double)(v[i].count));
//    qsrand (time(NULL));
//    fossilData  << qrand() % 10 + 2.5
//                << qrand() % 10 + 2.5
//                << qrand() % 10 + 2.5
//                << qrand() % 10 + 2.5
//                << qrand() % 10 + 2.5
//                << qrand() % 10 + 2.5
//                << qrand() % 10 + 2.5;
    fossil->setData(ticks, fossilData);

    // Легенда:
    customPlot->legend->setVisible(true);
    customPlot->axisRect()->insetLayout()->setInsetAlignment(0, Qt::AlignTop|Qt::AlignHCenter);
    customPlot->legend->setBrush(QColor(255, 255, 255, 200));
    QPen legendPen;
    legendPen.setColor(QColor(130, 130, 130, 200));
    customPlot->legend->setBorderPen(legendPen);
    QFont legendFont = font();
    legendFont.setPointSize(10);
    customPlot->legend->setFont(legendFont);
    customPlot->setInteractions(QCP::iRangeDrag | QCP::iRangeZoom);
    customPlot->replot();

    // Сброс всех установок графика:
    customPlot->removePlottable(fossil);

}
void Widget::setPlotParams(QString str, QVector<CurrWord> vect)
{
    word = str;
    v = vect;
}
