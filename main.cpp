#include "nouse.h"
#include <QDebug>
#include <QApplication>
#include <QtSql>

int main(int argc, char *argv[]) {
    QApplication a(argc, argv);
    NoUse w;
    w.show();

    return a.exec();
}
