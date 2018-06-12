#ifndef NOUSE_H
#define NOUSE_H

#include <QDialog>

namespace Ui {
    class NoUse;
}

class NoUse : public QDialog {
    Q_OBJECT
public:
    explicit NoUse(QWidget *parent = 0);
    ~NoUse();

private:
    Ui::NoUse *ui;
};

#endif // NOUSE_H
