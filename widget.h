#ifndef WIDGET_H
#define WIDGET_H
#include <QVBoxLayout>
#include <QPushButton>
#include <QVector>
#include <QDebug>
#include "qcustomplot.h"
#include "analysis.h"

struct CurrWord// Структура для хранения диагноза
               // и частоты
{
    QString diagID;
    int count;
};

class Widget : public QWidget
{
    Q_OBJECT

public:
    explicit Widget(QWidget *parent = 0);
    QString word; //Строка для храения слова (выражения)
    QVector<CurrWord> v; //Вектор для хранения диагноза и частоты
    void setPlotParams(QString str, QVector<CurrWord> vect);// Процедура инициализации

private:
    QCustomPlot *customPlot;
    QVBoxLayout *vbox;
    QPushButton *res;
    QCPBars *fossil;

private slots:
    void rndres();
};

#endif // WIDGET_H
