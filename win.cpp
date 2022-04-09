#include "win.h"

#include "win.h"
#include <QBoxLayout>
#include <QMessageBox>
#include <QTextCodec>

Win::Win(QWidget *parent): QWidget(parent)                                     // Конструктор нашего виджета
{
    QTextCodec::setCodecForLocale(QTextCodec::codecForName("Windows-1251"));        // Установка кодека для локализации виджета на русский язык
    setWindowTitle("Возведение в квадрат");
    frame = new QFrame(this);                                                       // Создание рамки
    frame->setFrameShadow(QFrame::Raised);                                          // Установка ее внешнего вида как в скриншоте в задании
    frame->setFrameShape(QFrame::Panel);
    inputTitle = new QLabel("Введите число:", this);                                // Создание заголовка над строкой ввода
    inputEdit = new QLineEdit("",this);                                             // Создание строки ввода

    StrValidator *v=new StrValidator(inputEdit);                                    // Создание объекта проверки ввода для строки ввода
    inputEdit->setValidator(v);                                                     // Подключение его к сроке ввода

    outputTitle = new QLabel("Результат:", this);                                   // Создание заголовка над строкой вывода
    outputEdit = new QLineEdit("",this);

    nextButton = new QPushButton("Следующее", this);                                // Создание кнопки Следующее
    exitButton = new QPushButton("Выход", this);                                    // Создание кнопки Выхода
    QVBoxLayout *vLayoutForNumbers = new QVBoxLayout(frame);                        // Создаем в рамке вертикальную разметку
    vLayoutForNumbers->addWidget(inputTitle);
    vLayoutForNumbers->addWidget(inputEdit);
    vLayoutForNumbers->addWidget(outputTitle);
    vLayoutForNumbers->addWidget(outputEdit);
    vLayoutForNumbers->addStretch();                                                // Добавляем растягиваемое пространство

    QVBoxLayout *vLayoutForButtons = new QVBoxLayout();                             // Такая же вертикальная разметка с кнопками
    vLayoutForButtons->addWidget(nextButton);
    vLayoutForButtons->addWidget(exitButton);
    vLayoutForButtons->addStretch();
    QHBoxLayout *hLayoutGeneral = new QHBoxLayout(this);                            // Создаем горизонтальную разметку
    hLayoutGeneral->addWidget(frame);                                               // Помещаем туда рамку
    hLayoutGeneral->addLayout(vLayoutForButtons);

    begin();                                                                        // Вызываем слот reset для подготовки виджета к вводу

    connect(exitButton,SIGNAL(clicked(bool)), this,SLOT(close()));                  // Поключение кнопки "выход" к слоту закрытия виджета
    connect(nextButton,SIGNAL(clicked(bool)), this,SLOT(begin()));                  // Кнопка "следующее" подключается к слоту очистки виджета и подготовки ео к следующему вводу
    connect(inputEdit,SIGNAL(returnPressed()), this,SLOT(calculate()));             // Нажатие клавиши "enter" в строке ввода подключается в вычислению результата

}

        void Win::begin()                                                        // Слот для очистки виджета и подготовки его к новому вычислению
        {

            nextButton->setEnabled(false);                                                  // Отключаем кнопку Следующее
            nextButton->setDefault(false);
            inputEdit->clear();                                                             // Очищаем строку ввода
            inputEdit->setEnabled(true);                                                    // Включаем её для ввода
            outputTitle->setVisible(false);                                                 // Скрываем заголовок
            outputEdit->setVisible(false);                                                  // Скрываем строку вывода
            outputEdit->setEnabled(false);                                                  // Выключаем строку вывода
            inputEdit->setFocus();
        }

        void Win::calc()                                                            // Слот для вычисления
        {
            bool Ok = true;                                                                 // Создаем флаг - корректен ли ввод?
            float r,a;                                                                      // Создаем переменные для вычисления квадрата
            QString str=inputEdit->text();                                                  // Копируем текст из строки ввода в строку QString
            a = str.toDouble(&Ok);                                                          // Конвертация строки в число, с проверкой
            if (Ok)                                                                         // Если ввод корректен то
            {
                r=a*a;                                                                      // Вычисляем квадрат
                str.setNum(r);
                outputEdit->setText(str);                                                   // Строку с числом записываем в строку вывода в виджете
                inputEdit->setEnabled(false);                                               // Отключаем строку ввода
                outputTitle->setVisible(true);
                outputEdit->setVisible(true);
                nextButton->setDefault(true);                                               // Кнопка Следующее доступна и становится кнопкой по умолчанию
                nextButton->setEnabled(true);
                nextButton->setFocus();
            }
            else
                if (!str.isEmpty())                                                         // Иначе и если строка ввода не пуста
                {
                    QMessageBox msgBox(QMessageBox::Information, "Возведение в квадрат", "Введено неверное значение.", QMessageBox::Ok);         // Окно с ошибкой
                    msgBox.exec();                                                                                                                                                   // Выводим
                }
        }
