#include <QApplication>
#include <QLabel>
#include <QMainWindow>
#include "win_main.h"

int main(int nArgC, char *apszArgV[])
{
    QApplication app(nArgC, apszArgV);

    WinMain wm;
    wm.show();

    return app.exec();
}
