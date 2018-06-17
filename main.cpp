#include "nouse.h"
#include <QDebug>
#include <QApplication>

#include "Public_Define.h"
#include "Struct_Define.h"
#include "Report.h"
#include "DB_ACCESS.h"
#include "MASTER.h"
#include "SLAVE.h"

int main(int argc, char *argv[]) {
    QApplication a(argc, argv);
    NoUse w;
    w.show();

    MASTER d;
    SLAVE s(1);

    d.f_user_in(1,"1");
    s.f_Login("1");
    s.f_switch_on();
    d.f_update_slave_status();
    d.f_request_handle();

    return a.exec();
}
