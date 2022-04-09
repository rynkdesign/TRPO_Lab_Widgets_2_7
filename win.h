#ifndef WIN_H
#define WIN_H

#include <QWidget>                                  // Подключение библиотек
#include <QFrame>
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>
#include <QValidator>

class Win : public QWidget               // Класс окна
{
    Q_OBJECT                                        // Макрос QT, обеспечивающий корректное создание сигналов и слотов
public:
    Win(QWidget *parent = nullptr);      // Конструктор
    ~Win() {}                            // Деструктор

private:
    QFrame *frame;                                  // Рамка
    QLabel *inputTitle;                             // Метка ввода
    QLineEdit *inputEdit;                           // Строчный редактор ввода
    QLabel *outputTitle;                            // Метка вывода
    QLineEdit *outputEdit;                          // Строчный редактор вывода
    QPushButton *nextButton;                        // Кнопка Следующее
    QPushButton *exitButton;                        // Кнопка Выход

public slots:                                       // Слоты:
    void begin();                                   // Слот для очитки виджета и подготовки его к новому вычислению
    void calc();                                    // Слот для вычисления
};

class StrValidator:public QValidator                // Класс компонента проверки ввода
{
    public:
    StrValidator(QObject *parent):QValidator(parent){}

    virtual State validate(QString &str,int &pos)const
    {
        return Acceptable;                          // Метод всегда принимает вводимую строку
    }
};


#endif // WIN_H
