#include <QDebug>
#include <QApplication>

#include "Public_Define.h"
#include "Struct_Define.h"
#include "Report.h"
#include "DB_ACCESS.h"
#include "MASTER.h"
#include "SLAVE.h"

#include "login.h"
#include "maincharge.h"


int main(int argc, char *argv[]) {
    QApplication a(argc, argv);
    login L;
    MainCharge W;
    if(L.exec() == QDialog::Accepted)
    {
        W.show();
        W.threadstart();
    }
    else
        return 0;


    return a.exec();
}
