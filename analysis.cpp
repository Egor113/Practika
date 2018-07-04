#include "analysis.h"
#include <QString>
#include <QFileDialog>
#include <QDebug>

Analysis::Analysis()
{

}

bool Analysis:: sortCondition(Words w1,  Words w2)
{
    return w1.count > w2.count;
}

//bool Analysis:: sortCondition_ds(Words_ds w1,  Words_ds w2)
//{
//    int comp = w1.diagID.compare(w2.diagID);
//    if (comp < 0) return true;
//    else return false;
//}
bool Analysis:: sortCondition_ds2(Words w1,  Words w2)
{
    int comp = w1.ds.compare(w2.ds);
    if (comp < 0) return true;
    else return false;
}

void Analysis::pushwords()
{
    int i=0,
    count=0;// Счётчик символов разделения ';'
    bool find=false;
    std::set<char>  ch2;// Множество разделителей
    std::string buff;// Строка-буфер для считывания строк из файла

    ch2.insert('.'); //Добавление разделителей в множество разделителей;
    ch2.insert(',');
    ch2.insert(';');
    ch2.insert('"');
    ch2.insert('0');
    ch2.insert('1');
    ch2.insert('2');
    ch2.insert('3');
    ch2.insert('4');
    ch2.insert('5');
    ch2.insert('6');
    ch2.insert('7');
    ch2.insert('8');
    ch2.insert('9');
    ch2.insert('(');
    ch2.insert(')');
    ch2.insert('-');
    ch2.insert('NULL');

    Words words;
    words.count = 0;
    words.word = "";

    v.push_back(words);//Добавление первого элемента
    //в массив слов

    getline(fileReader, buff); // считывания первой(служебной) строки
    //заголовков из файла
    while(getline(fileReader, buff)) //Цикл считывание строк из файла
    {
        QTextCodec *codec = QTextCodec::codecForName("Windows-1251");
        QString str = codec->toUnicode(buff.c_str());
        i=0;
        find = true;//Переменная, хранящая информацию,
        //найден ли нужный столбец в файле или нет

        QStringList list;
        list = str.split(";");
        //qDebug() << list.last();
        if (find)//Если найден нужный столбец
        {
            str= list.last();
            std::string buffstr;
            buffstr = str.toStdString();
            //в str хранится строка из нужного столбца
            for(int i = 0; i < str.length(); ++i)//Цикл удаления символов-разделителей
            {
                    if (ch2.find(buffstr[i])!= ch2.end()) buffstr[i] = ' ';
                    //Если найден разделитель, то заменить его пробелом
            }
            str = QString::fromStdString(buffstr);
            std::string tmp;//В tmp будет храниться текущее слово
            std::istringstream ist(str.toStdString());
            while(ist >> tmp)//Пока не закончится строка str
            {
                if(tmp.length() >= 3)//Если длина слова меньше или равна 3
                {

                    bool match=false;
                    int i = 0;
                    while ((!match) && (i<v.size()))//Пока слово не найдено и не достингнут
                    //конец массива слов
                    {
                        if(tmp.compare(v[i].word)==0)//Если текущее слово совпало
                        //со словом из массива слов
                        {
                            v[i].count++;//увеличиваем поле-счётчик слов в массиве слов
                            match=true;
                        }
                        i++;
                    }
                    if (!match)//Если текущее слово встретилось в первый раз
                    {
                        Words w;
                        w.word  = tmp;
                        w.count = 1;
                        v.push_back(w);//То добавить его в массив слов
                    }
                }
            }
        }
    }
    ch2.clear(); //Очистим память, выделенную под множество разделителей
    std::string().swap(buff); //Очистим память, выделенную под строку buff
}
void Analysis::pushwords_ds()
{
    int i=0,
    count=0;// Счётчик символов разделения ';'
    bool find=false;
    std::set<char>  ch2,// Множество разделителей для разделения строки на слова
        ch;// Множество для выделенмя диагноза из строки
    std::string buff;// Строка-буфер для считывания строк из файла

    ch2.insert('.'); //Добавление разделителей в множество разделителей;
    ch2.insert(',');
    ch2.insert(';');
    ch2.insert('"');
    ch2.insert('0');
    ch2.insert('1');
    ch2.insert('2');
    ch2.insert('3');
    ch2.insert('4');
    ch2.insert('5');
    ch2.insert('6');
    ch2.insert('7');
    ch2.insert('8');
    ch2.insert('9');
    ch2.insert('(');
    ch2.insert(')');
    ch2.insert('-');
    ch2.insert('NULL');

    ch.insert('0');
    ch.insert('1');
    ch.insert('2');
    ch.insert('3');
    ch.insert('4');
    ch.insert('5');
    ch.insert('6');
    ch.insert('7');
    ch.insert('8');
    ch.insert('9');
    //ch.insert('.');

    Words words;
    words.count = 0;
    words.word = "";

    v.push_back(words);//Добавление первого элемента
    //в массив слов

//    Words_ds words_ds;
//    words_ds.diagID = "";
//    words_ds.v = v;

//    v_ds.push_back(words_ds);

    getline(fileReader, buff); // считывания первой(служебной) строки
    //заголовков из файла
    while(getline(fileReader, buff)) //Цикл считывание строк из файла
    {
        QTextCodec *codec = QTextCodec::codecForName("Windows-1251");
        QString str = codec->toUnicode(buff.c_str());
        QString str2,str3,strlast;
        str2 = str;
        i=0;
        find = true;//Переменная, хранящая информацию,
        bool end = false;
        //найден ли нужный столбец в файле или нет
        //std::cout << str.find('F')<< std::endl;
        if (str.indexOf('F')<str.length()) //Если в строке есть диагоноз
        {
            //То выделяем его в строку str2
            str2 = str.mid(str.indexOf('F'),7);
            str3 = str2;
            int count2 = 0;
            for(int i = str3.indexOf(".")+1 ; i < str3.length(); i++)
            {
                    if (ch.find(str3[i].toLatin1())== ch.end())
                    {
                        str2 = str3.remove(i,str3.length());
                        break;
                    }
            }
            //if (str2[str2.length()-1]=='.') str2.erase(str2.length()-1,1);
            strlast = str2;
            QStringList list;
            list = str.split(";");
            /*
            while (i!=str.length())//Цикл поиска нужного столбца в файле
            {
                if (str[i]==';')
                {
                    count++;
                }
                i++;
                if (count==13)//Если найден нужный столбец
                {
                    find=true;//То find=true
                    count=0;
                }
            }
            */
            if (find)//Если найден нужный столбец
            {
                str= list.last();
                //str=str.substr(str.find_last_of(";")+2,(str.length()-str.find_last_of(";")+2));
                //в str хранится строка из нужного столбца
                std::string buffstr;
                buffstr = str.toStdString();
                for(int i = 0; i < str.length(); ++i)//Цикл удаления символов-разделителей
                {
                        if (ch2.find(buffstr[i])!= ch2.end()) buffstr[i] = ' ';
                        //Если найден разделитель, то заменить его пробелом
                }
                str = QString::fromStdString(buffstr);
                std::string tmp;//В tmp будет храниться текущее слово
                std::istringstream ist(str.toStdString());
                while(ist >> tmp)//Пока не закончится строка str
                {
                    if(tmp.length() >= 3)//Если длина слова меньше или равна 3
                    {
                        if (ch2.find(tmp[tmp.length()-1])!= ch2.end()) tmp.erase(tmp.length()-1,1);
                        if (ch2.find(tmp[tmp.length()-1])!= ch2.end()) tmp.erase(tmp.length()-1,1);
                        bool match=false;
                        int i = 0;
                        while ((!match) && (i<v.size()))//Пока слово не найдено и не достингнут
                        //конец массива слов
                        {
                            if(tmp.compare(v[i].word)==0)//Если текущее слово совпало
                            //со словом из массива слов
                            {
                                if (QString::compare(str2, QString::fromStdString(v[i].ds)) == 0)
                                {
                                    v[i].count++;//увеличиваем поле-счётчик слов в массиве слов
                                    match=true;
                                }
                                else
                                {
                                    match = false;
//                                    Words_ds w_ds;
//                                    //w_ds.v = v;
//                                    w_ds.diagID = str2.toStdString();;
//                                    v_ds.push_back(w_ds);
                                }
                            }
                            i++;
                        }
                        /*
                        bool match_ds = false;
                        for (int j = 0; j<v_ds.size(); ++j)
                        {
                            if (QString::compare(str2, QString::fromStdString(v_ds[j].diagID)) == 0)
                            {
                                //v_ds[j].v = v;
                                match_ds = true;

                            }
                        }
                        if (!match_ds)
                        {
                            Words_ds w_ds;
                            w_ds.v = v;
                            w_ds.diagID = str2.toStdString();;
                            v_ds.push_back(w_ds);
                        }*/
                        if (!match)//Если текущее слово встретилось в первый раз
                        {
                            Words w;
                            w.word  = tmp;
                            w.count = 1;
                            //if (str2.length()>0)
                            w.ds = str2.toStdString();
                            v.push_back(w);//То добавить его в массив слов
                        }
                    }
                }
            }
        }
        else str2 = strlast;
        //std::cout << str2 << std::endl;
    }
    ch2.clear(); //Очистим память, выделенную под множество разделителей
    std::string().swap(buff); //Очистим память, выделенную под строку buff
}
void Analysis::pushchains()
{
    int i=0,
    count=0;// Счётчик символов разделения ';'
    bool find=false;
    std::set<char>  ch,ch2;// Множество разделителей
    std::string buff,// Строка-буфер для считывания строк из файла

    stroka=" ";//Строка для хранения текущего выражения

    ch.insert('.');//Добавление разделителей в множество разделителей;
    ch.insert(',');
    ch.insert(';');
    ch.insert('"');

    ch2.insert('(');
    ch2.insert(')');
    ch2.insert('"');

    Words words;
    words.count = 0;
    words.word = "";
    v.push_back(words);//Добавление первого элемента
    //в массив слов

    getline(fileReader, buff); // считывания первой(служебной) строки
    //заголовков из файла
    while(getline(fileReader, buff))//Цикл считывание строк из файла
    {
        QTextCodec *codec = QTextCodec::codecForName("Windows-1251");
        QString str = codec->toUnicode(buff.c_str());
        i=0;
        find = true;//Переменная, хранящая информацию,
        QStringList list;
        list = str.split(";");
        if (find)//Если найден нужный столбец
        {
            //[abc]
            str= list.last();
            QStringList chains = str.split(QRegularExpression("[,.()\"]"));
            /*
            for(int i = 0; i < chains.size(); ++i) {
                qDebug() << chains.at(i);
            }
            */
            for (int j = 0; j < chains.size(); ++j)
            {
                //QString s =
                std::string buffstr;
                buffstr = chains.at(j).toStdString();
                if (buffstr.length()>=3 )//Если длина слова меньше или равна 3
                {

                    bool match=false;
                    int i = 0;
                    while ((!match) && (i<v.size()))//Пока слово не найдено и не достингнут
                        //конец массива слов
                    {
                        if(buffstr.compare(v[i].word)==0)//Если текущее слово совпало
                            //со словом из массива слов
                        {
                            v[i].count++;//увеличиваем поле-счётчик слов в массиве слов
                            match=true;
                        }
                        i++;
                    }
                    if (!match)//Если текущее слово встретилось в первый раз
                    {
                        Words w;
                        w.word  = buffstr;
                        w.count = 1;
                        v.push_back(w);//То добавить его в массив слов
                    }
                }
            }
        }
    }
}
void Analysis::pushchains_ds()
{
    int i=0,
    count=0;// Счётчик символов разделения ';'
    bool find=false;
    std::set<char>  ch,ch2,ch3;// Множество разделителей
    std::string buff,// Строка-буфер для считывания строк из файла

    stroka=" ";//Строка для хранения текущего выражения

    ch.insert('.');//Добавление разделителей в множество разделителей;
    ch.insert(',');
    ch.insert(';');
    ch.insert('"');

    ch2.insert('(');
    ch2.insert(')');
    ch2.insert('"');

    ch3.insert('0');
    ch3.insert('1');
    ch3.insert('2');
    ch3.insert('3');
    ch3.insert('4');
    ch3.insert('5');
    ch3.insert('6');
    ch3.insert('7');
    ch3.insert('8');
    ch3.insert('9');

    Words words;
    words.count = 0;
    words.word = "";
    v.push_back(words);//Добавление первого элемента
    //в массив слов

    getline(fileReader, buff); // считывания первой(служебной) строки
    //заголовков из файла
    while(getline(fileReader, buff))//Цикл считывание строк из файла
    {
        QTextCodec *codec = QTextCodec::codecForName("Windows-1251");
        QString str = codec->toUnicode(buff.c_str());
        QString str2,str3,strlast;
        i=0;
        find = true;//Переменная, хранящая информацию,
        if (str.indexOf('F')<str.length()) //Если в строке есть диагоноз
        {
            //То выделяем его в строку str2
            str2 = str.mid(str.indexOf('F'),7);
            str3 = str2;
            int count2 = 0;
            for(int i = str3.indexOf(".")+1 ; i < str3.length(); i++)
            {
                if (ch3.find(str3[i].toLatin1())== ch3.end())
                {
                    str2 = str3.remove(i,str3.length());
                    break;
                }
            }
            strlast = str2;
            QStringList list;
            list = str.split(";");
            if (find)//Если найден нужный столбец
            {
                //[abc]
                str= list.last();
                QStringList chains = str.split(QRegularExpression("[,.()\"]"));
                /*
            for(int i = 0; i < chains.size(); ++i) {
                qDebug() << chains.at(i);
            }
            */
                for (int j = 0; j < chains.size(); ++j)
                {
                    //QString s =
                    std::string buffstr;
                    buffstr = chains.at(j).toStdString();
                    if (buffstr.length()>=3 )//Если длина слова меньше или равна 3
                    {

                        bool match=false;
                        int i = 0;
                        while ((!match) && (i<v.size()))//Пока слово не найдено и не достингнут
                            //конец массива слов
                        {
                            if(buffstr.compare(v[i].word)==0)//Если текущее слово совпало
                                //со словом из массива слов
                            {
                                if (QString::compare(str2, QString::fromStdString(v[i].ds)) == 0)
                                {
                                    v[i].count++;//увеличиваем поле-счётчик слов в массиве слов
                                    match=true;
                                }
                                else
                                {
                                    match = false;
//                                    Words_ds w_ds;
//                                    //w_ds.v = v;
//                                    w_ds.diagID = str2.toStdString();;
//                                    v_ds.push_back(w_ds);
                                }
                            }
                            i++;
                        }
                        if (!match)//Если текущее слово встретилось в первый раз
                        {
                            Words w;
                            w.word  = buffstr;
                            w.count = 1;
                            w.ds = str2.toStdString();
                            v.push_back(w);//То добавить его в массив слов
                        }
                    }
                }
            }
        }
        else str2 = strlast;
    }
}
void Analysis::sort()
{
    std::sort(v.begin(), v.end(), sortCondition);
}
//void Analysis::sort_ds()
//{
//    std::sort(v_ds.begin(), v_ds.end(), sortCondition_ds);
//}
void Analysis::sort_ds_2()
{
    std::sort(v.begin(), v.end(), sortCondition_ds2);
}
void Analysis::sort_buff()
{
    std::sort(buff_v.begin(), buff_v.end(), sortCondition);
}
void Analysis::push_ds()
{
    Analysis::sort_ds_2();
    for (int i = 0; i < v.size(); ++i)
    {
        buff_v.push_back(v[i]);
        if (v[i+1].ds != v[i].ds)
        {
            Analysis::sort_buff();
            Words_ds wds;
            wds.diagID = v[i].ds;
            wds.v = buff_v;
            v_ds.push_back(wds);
            buff_v.clear();
        }
    }
}

void Analysis::openfile()
{
    QString str = QFileDialog::getOpenFileName(0, "Open Dialog", "", "*.csv");
    if(str.length() == 0) return;
    fileReader.open(str.toStdString(), std::ios::in | std::ios::binary);

}
//void Analysis::get_ds(std::string str)
//{
//////    for (int i = 0; i < v.size(); ++i)
//////    {
//////        if (v[i].word == str)
//////        {
//////            CurrWord w_curr;
//////            w_curr.diagID = v[i].ds;
//////            w_curr.count = v[i].count;
//////            v_curr.push_back(w_curr);
//////        }
//////    }
////    for (int i = 0; i < v_ds.size(); ++i)
////    {
////        for (int j = 0; j < v_ds[i].v.size(); ++j)
////        {
////            if (v_ds[i].v[j].word == str)
////            {
////                CurrWord w_curr;
////                w_curr.diagID = v_ds[i].v[j].ds;
////                w_curr.count = v_ds[i].v[j].count;
////                v_curr.push_back(w_curr);
////            }
////        }
////    }
//}
