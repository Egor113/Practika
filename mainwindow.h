#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "analysis.h"
#include "widget.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:

    void on_btnFillChains_clicked();//Процедура заполнения таблицы
    // по нажатию кнопки "Определить частоту повторения выражений"

    void on_btnFillWords_clicked();//Процедура заполнения таблицы
    // по нажатию кнопки "Определить частоту повторения слов"

    void on_btnFillWords_ds_clicked();//Процедура заполнения таблицы
    // по нажатию кнопки "Определить частоту повторения слов с учетом диагноза"

    void on_btnFillChains_ds_clicked();//Процедура заполнения таблицы
    // по нажатию кнопки "Определить частоту повторения выражений с учетом диагноза"

    void on_btnWidgetShow_clicked();//Процедура отрисовки диаграммы

private:
    Ui::MainWindow *ui; //Форма главного меню
    Widget *w; //Форма диаграммы
};

#endif // MAINWINDOW_H
