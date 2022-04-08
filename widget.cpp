#include "widget.h"
#include <QMessageBox>

// **** Русский язык работает и без метода QTextCodec ****

Widget::Widget(QWidget *parent)
    : QWidget(parent)
{
    //setupUi(this); // Это для не ручного ввода
    // создание и настройка самого окна
    setWindowTitle("Возведение в квадрат");
    frame = new QFrame(this);
    frame->setFrameShadow(QFrame::Raised);
    frame->setFrameShape(QFrame::Panel);

    // создаем все объекты
    inputLabel = new QLabel("Введите число:",
    this);
    inputEdit = new QLineEdit("",this);
    StrValidator *v = new StrValidator(inputEdit); // создаем наш валидатор
    inputEdit->setValidator(v); // если честно не очень понял зачем он тут нужен
    outputLabel = new QLabel("Результат:",
    this);
    outputEdit = new QLineEdit("",this);
    nextButton = new QPushButton("Следующее",
    this);
    exitButton = new QPushButton("Выход",
    this);
    calcButton = new QPushButton("Вычислить", this);

    // далее компановка
    QVBoxLayout *vLayout1 = new QVBoxLayout(frame); //создаем лэйаут
    //добавляем в левый лэйаут надписи и поля
    vLayout1->addWidget(inputLabel);
    vLayout1->addWidget(inputEdit);
    vLayout1->addWidget(outputLabel);
    vLayout1->addWidget(outputEdit);
    vLayout1->addStretch(); // пробел грубо говоря
    QVBoxLayout *vLayout2 = new QVBoxLayout();
    //добавляем в правый лэйаут кнопки
    vLayout2->addWidget(calcButton);
    vLayout2->addWidget(nextButton);
    vLayout2->addWidget(exitButton);
    vLayout2->addStretch(); // пробел грубо говоря
    QHBoxLayout *hLayout = new QHBoxLayout(this);
    // добавляем два прошлых к одному большому лейауту
    hLayout->addWidget(frame);
    hLayout->addLayout(vLayout2);

    begin();

    // создаем связи к кнопкам
    connect(exitButton,SIGNAL(clicked(bool)),
    this,SLOT(close()));
    connect(nextButton,SIGNAL(clicked(bool)),
    this,SLOT(begin()));
    connect(inputEdit,SIGNAL(returnPressed()), // связь к нажатию enter
    this,SLOT(calc()));
    connect(calcButton,SIGNAL(clicked(bool)),
    this,SLOT(calc()));
}

Widget::~Widget() // деструктор, не уверен что это необходимо, a.exec() должен всё удалять по идее
{
    delete inputLabel;
    delete inputEdit;
    delete outputLabel;
    delete outputEdit;
    delete nextButton;
    delete exitButton;
    delete calcButton;
    delete frame; // это должно быть последним
}

void Widget::begin()
{
    inputEdit->clear(); // очищаем поле
    nextButton->setEnabled(false); // прячем кнопку Следующее
    nextButton->setDefault(false);
    inputEdit->setEnabled(true);
    outputLabel->setVisible(false); // прячем лейбл с текстом "Результат"
    outputEdit->setVisible(false); // прячем поле вывода результата
    outputEdit->setEnabled(false); // в поле ничего нельзя вводить
    inputEdit->setFocus(); // фокус для клавиатуры на поле для ввода
}
void Widget::calc()
{
    bool Ok = true;
    float r, a;
    QString str = inputEdit->text();
    a=str.toDouble(&Ok); // если не получается перевести в тип дабл, то Ok = false
    if (Ok)
    {
        r=a*a;
        str.setNum(r);
        outputEdit->setText(str);
        inputEdit->setEnabled(false);
        outputLabel->setVisible(true); // показываем лейбл "Результат"
        outputEdit->setVisible(true); // показываем поле вывода
        nextButton->setDefault(true);
        nextButton->setEnabled(true);
        nextButton->setFocus();
    }
    else
        if (!str.isEmpty()) // если не пустое поле то вывод на экран ошибки
        {
            QMessageBox msgBox(QMessageBox::Information,
            "Возведение в квадрат.",
            "Введено неверное значение.",
            QMessageBox::Ok);
            msgBox.exec();
        }
}



