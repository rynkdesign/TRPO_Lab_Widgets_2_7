#include "win.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    Win win;
    win.show();
    return app.exec();
}
