#ifndef WIDGET_H
#define WIDGET_H

#include "ui_widget.h"

#include <QWidget>
//#include <QLineEdit> // почему-то не включался в QWidget
//#include <QTextCodec>
#include <QtGui>

class Widget : public QWidget, private Ui::Widget // класс окна
{
    Q_OBJECT // макрос Qt, обеспечивает корректное создание сигналов и слотов
protected:
    //QTextCodec *codec; // для русского языка
    QFrame *frame; // рамка
    QLabel *inputLabel; // метка ввода
    QLineEdit *inputEdit; // строчный редактор ввода
    QLabel *outputLabel; // метка вывода
    QLineEdit *outputEdit; // строчный редактор вывода
    QPushButton *nextButton; // кнопка Следующее
    QPushButton *exitButton; // кнопка Выход
    QPushButton *calcButton; // кнопка вычислить

public:
    Widget(QWidget *parent = 0); // конструктор
    ~Widget();
public slots:
    void begin(); // метод начальной настройки интерфейса
    void calc(); // метод реализации вычислений
private slots:
    void on_nextButton_clicked();
};

class StrValidator:public QValidator // класс компонента проверки ввода
{
public:
    StrValidator(QObject *parent):QValidator(parent){}
virtual State validate(QString &str,int &pos)const
{
    return Acceptable; // метод всегда принимает вводимую строку
}
};
#endif // WIDGET_H
