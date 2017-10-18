#ifndef WIN_ABOUT_H
#define WIN_ABOUT_H

#include <QDialog>
#include "context.h"

namespace Ui {
class SetRange_Dialog;
}

class SetRange_Dialog : public QDialog
{
    Q_OBJECT

public:
    explicit SetRange_Dialog(QWidget *parent, RangeContext defaultVal);
    ~SetRange_Dialog();

    void getData(RangeContext &);

private:
    Ui::SetRange_Dialog *ui;
};



#endif // WIN_ABOUT_H
