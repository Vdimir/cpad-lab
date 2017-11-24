#include "main_window.h"
#include "ui_mainwindow.h"

#include <QFileDialog>

#include "data.h"
#include <QMessageBox>

MainWindow::MainWindow(QWidget* parent) :
    QMainWindow(parent)
{
    setupUi(this);

    setCentralWidget(mdiArea);
}

void MainWindow::on_actionOpen_triggered()
{
    const QString fileName = QFileDialog::getOpenFileName(this);

    if (fileName.isEmpty()) {
        return;
    }

    try {
        Data t = Data::fromFile(fileName);

        QFileInfo fi(fileName);

        TableWindow* child = new TableWindow(this, t, menuWindow);
        child->setWindowTitle(fileName);

        mdiArea->addSubWindow(child);
        child->show();

        auto act = new QAction(fi.fileName(), this);
        menuWindow->addAction(act);
        child->addMenuAction(act);


    } catch (BadFileError& err) {
        QMessageBox msgBox;
        msgBox.setText(tr("Error while open file!"));
        msgBox.setInformativeText(tr("File have wrong format."));
        msgBox.setStandardButtons(QMessageBox::Ok);
        int ret = msgBox.exec();
    }
}

void MainWindow::on_actionAbout_triggered()
{
    auto about_txt = tr("Application for editing csv files\n"
                        "First row must contain datatypes for columnns\n"
                        "Possible datatypes:\n"
                        "\"int\",\"string\",\"variant\",\"bool\"");

    QMessageBox::about(this, tr("Qt Csv Table Editor"), about_txt);
}

void MainWindow::on_actionClose_All_triggered()
{
    mdiArea->closeAllSubWindows();
}


void MainWindow::on_actionExit_triggered()
{
    mdiArea->closeAllSubWindows();
    close();
}

MainWindow::~MainWindow()
{
}
