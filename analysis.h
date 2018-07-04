#ifndef ANALYSIS_H
#define ANALYSIS_H

#include <conio.h>
#include <locale>
#include <string>
#include <iostream>
#include <QVector>
#include <vector>
#include <set>
#include <fstream>
#include <sstream>
#include <QString>
#include <QTextCodec>
#include <QtAlgorithms>
#include <algorithm>
#include <QRegularExpression>

class Analysis
{
public:
    struct Words { // Структрура для хранения
        std::string word; //слова(выражения)
        int         count; //частоты его повторения в тексте
        std::string ds; //и диагоноза
    };
    struct Words_ds
    {
        std::string diagID;
        std::vector<Words> v;
    };
    std::vector<Words> v; //Массив слов(выражений)
    std::vector<Words> buff_v;

    std::vector<Words_ds> v_ds;
    std::ifstream fileReader; //Файловая переменная
    void pushwords_ds(); //Процедура добавления слов в массив
    void pushchains_ds();//Процедура добавления выражений в массив
    void pushwords(); //Процедура добавления слов в массив
    void pushchains();//Процедура добавления выражений в массив
//  void sort_ds();
    void sort_ds_2();//Процедура сортировки слов (выражений) в массиве по диагнозу
    void sort();//Процедура сортировки слов (выражений) в массиве по частоте
    void sort_buff();//Процедура сортировки буферного массива
    void openfile();//Процедура открытия файла
    void push_ds();//Процедура добавления диагноза в массив
    //void get_ds(std::string str);
    //void print();
    Analysis();

private:
    bool static sortCondition(Words w1, Words w2);
    bool static sortCondition_ds(Words_ds w1, Words_ds w2);
    bool static sortCondition_ds2(Words w1, Words w2);
};

#endif // ANALYSIS_H
