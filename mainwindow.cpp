#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QTextCodec> // подключение класса кодека текста
#include <QDebug>
#include "widget.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    w = NULL;
    connect(ui->btnExit, SIGNAL(clicked()), this, SLOT(close()));
}

MainWindow::~MainWindow()
{
    if(w != NULL) delete w;
    delete ui;
}


void MainWindow::on_btnFillChains_clicked()
{
    ui->tableWidget->clear();// Очистим содержимое таблицы
    ui->tableWidget->setColumnCount(2);// Установим число колонок таблицы равным 2
    Analysis an; // Создадим объект "Анализатор диагнозов"
    an.openfile();// и вызовем его метод,
    an.pushchains();//отвечающий за выделение выражений
    an.sort();
    //QTextCodec *codec = QTextCodec::codecForName("Windows-1251");
    QStringList header;
    header << "Сиптомы" << "Частота повторения";
    ui->tableWidget->setHorizontalHeaderLabels(header);
    ui->tableWidget->setRowCount(an.v.size());
    for (int i = 0 ; i < an.v.size(); i++)// Заполним табицу в цикле
    {
        QString word = QString::fromStdString(an.v[i].word);
        QString count = QString::number(an.v[i].count);
        ui->tableWidget->setItem(i,0,new QTableWidgetItem(QString(word)));
        ui->tableWidget->setItem(i,1,new QTableWidgetItem(QString(count)));
    }
}

void MainWindow::on_btnFillWords_clicked()
{
    ui->tableWidget->clear();
    ui->tableWidget->setColumnCount(2);
    Analysis an;
    an.openfile();
    an.pushwords();
    an.sort();
    QTextCodec *codec = QTextCodec::codecForName("Windows-1251");
    QStringList header;
    header << "Сиптомы" << "Частота повторения";
    ui->tableWidget->setHorizontalHeaderLabels(header);
    ui->tableWidget->setRowCount(an.v.size());
    for (int i = 0 ; i < an.v.size(); i++)
    {

        QString ds = QString::fromStdString(an.v[i].ds);
        QString word = QString::fromStdString(an.v[i].word);
        QString count = QString::number(an.v[i].count);

        ui->tableWidget->setItem(i,0,new QTableWidgetItem(QString(word)));
        ui->tableWidget->setItem(i,1,new QTableWidgetItem(QString(count)));
    }
}

void MainWindow::on_btnFillWords_ds_clicked()
{
    ui->tableWidget->clear();
    ui->tableWidget->setColumnCount(3);
    Analysis an;
    an.openfile();
    an.pushwords_ds();
    an.push_ds();
    //an.sort_ds();
    QStringList header;
    header << "Диагноз" << "Сиптомы" << "Частота повторения";
    ui->tableWidget->setHorizontalHeaderLabels(header);
    int sum = 0;
    for (int j=0; j<an.v_ds.size(); ++j)
    {
        Analysis::Words_ds wds = an.v_ds[j];
        for (int i = 0 ; i < (wds.v.size()); i++)
        {
            sum ++;
        }
    }
    ui->tableWidget->setRowCount(sum);
    sum = 0;
    for (int j=0; j<an.v_ds.size(); ++j)
    {
        Analysis::Words_ds wds = an.v_ds[j];
        for (int i = 0 ; i < (wds.v.size()); i++)
        {
            QString ds = QString::fromStdString(wds.diagID);
            QString word = QString::fromStdString(wds.v[i].word);
            QString count = QString::number(wds.v[i].count);
            //word = codec->toUnicode(an.v[i].word.c_str());
            ui->tableWidget->setItem(sum,0,new QTableWidgetItem(QString(ds)));
            ui->tableWidget->setItem(sum,1,new QTableWidgetItem(QString(word)));
            ui->tableWidget->setItem(sum,2,new QTableWidgetItem(QString(count)));
            sum ++;
        }
    }

}

void MainWindow::on_btnFillChains_ds_clicked()
{
    ui->tableWidget->clear();
    ui->tableWidget->setColumnCount(3);
    Analysis an;
    an.openfile();
    an.pushchains_ds();
    an.push_ds();
    //an.sort_ds();
    QStringList header;
    header << "Диагноз" << "Сиптомы" << "Частота повторения";
    ui->tableWidget->setHorizontalHeaderLabels(header);
    int sum = 0;
    for (int j=0; j<an.v_ds.size(); ++j)
    {
        Analysis::Words_ds wds = an.v_ds[j];
        for (int i = 0 ; i < (wds.v.size()); i++)
        {
            sum ++;
        }
    }
    ui->tableWidget->setRowCount(sum);
    sum = 0;
    for (int j=0; j<an.v_ds.size(); ++j)
    {
        Analysis::Words_ds wds = an.v_ds[j];
        for (int i = 0 ; i < (wds.v.size()); i++)
        {
            QString ds = QString::fromStdString(wds.diagID);
            QString word = QString::fromStdString(wds.v[i].word);
            QString count = QString::number(wds.v[i].count);
            //word = codec->toUnicode(an.v[i].word.c_str());
            ui->tableWidget->setItem(sum,0,new QTableWidgetItem(QString(ds)));
            ui->tableWidget->setItem(sum,1,new QTableWidgetItem(QString(word)));
            ui->tableWidget->setItem(sum,2,new QTableWidgetItem(QString(count)));
            sum ++;
        }
    }

}

void MainWindow::on_btnWidgetShow_clicked()
{
    if(w != NULL) delete w;
    w = new Widget();
    QVector <CurrWord> v_curr;
    QString text;
    text = ui->tableWidget->currentItem()->data(0).toString();
    //qDebug() << text;
    for (int i = 0 ; i < ui->tableWidget->rowCount(); i++)
    {
        //qDebug() << ui->tableWidget->item(i,1)->data(0).toString();
        if (text.compare(ui->tableWidget->item(i, 1)->data(0).toString()) == 0)
        {
            CurrWord w_curr;
            w_curr.diagID = ui->tableWidget->item(i, 0)->data(0).toString();
            w_curr.count = ui->tableWidget->item(i, 2)->data(0).toInt();
            v_curr.push_back(w_curr);
        }
    }
//  Формирование нового вектора (диагноз, кол-во повторений)
    w->setPlotParams(text,v_curr);
    //w->setPlotParams(text,an.v_curr);
    w->show();
}
