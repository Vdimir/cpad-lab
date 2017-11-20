
#include <QtWidgets/QApplication>
#include <QtWidgets/QTableView>
#include <QDebug>
#include "win/table_window.h"

#include "tablemodel.h"

#include "data.h"
int main(int argc, char* argv[])
{
    QApplication app(argc, argv);

    Data t = Data::fromFile("/home/vdimir/ext/cross-lab/table_editor/data/foo.csv");
    TableModel myModel(t);
    TableWindow win(0, &myModel);
    win.show();

    return app.exec();

    return 0;
}
