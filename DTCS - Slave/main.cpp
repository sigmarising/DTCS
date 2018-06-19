#include "nouse.h"
#include <QDebug>
#include <QApplication>

#include "Public_Define.h"
#include "Struct_Define.h"
#include "Report.h"
#include "DB_ACCESS.h"
#include "MASTER.h"
#include "SLAVE.h"

#include "room.h"
#include "slavecharge.h"

extern int TheRoomId;
extern SLAVE * TSLAVE;

int main(int argc, char *argv[]) {
    QApplication a(argc, argv);
    Room W;
    Slavecharge SC;
    if(W.exec() == QDialog::Accepted)
    {
        SLAVE S(TheRoomId);
        TSLAVE = & S;

        if(SC.T_login2.exec() == QDialog::Accepted)
        {
            SC.show();
            SC.startThread();
            SC.showstatus();
        }
    }
    else
        return 0;



    return a.exec();
}
