
#include <QtWidgets/QApplication>
#include <QtWidgets/QTableView>
#include <QDebug>

#include "win/main_window.h"

#include "data.h"
int main(int argc, char* argv[])
{
    QApplication app(argc, argv);

    //    Data t = Data::fromFile("/home/vdimir/ext/cross-lab/table_editor/data/foo.csv");
    //    TableModel myModel(t);
    MainWindow win;
    win.show();

    return app.exec();

    return 0;
}
