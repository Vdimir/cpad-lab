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

        TableWindow* child = new TableWindow(this, t);
        child->setWindowTitle(fileName);

        mdiArea->addSubWindow(child);
        child->show();

    } catch (BadFileError& err) {
        QMessageBox msgBox;
        msgBox.setText("Error while open file!");
        msgBox.setInformativeText(err.what());
        msgBox.setStandardButtons(QMessageBox::Ok);
        int ret = msgBox.exec();
    }
}

void MainWindow::on_actionAbout_triggered()
{
    auto about_txt = QString::fromLocal8Bit("Application for editing csv files\n"
                                            "First row must contain datatypes for columnns\n"
                                            "Possible datatypes:\n"
                                            "\"int\",\"string\",\"variant\",\"bool\"");
    auto title_txt = QString::fromLocal8Bit("Qt Csv Table Editor");
    QMessageBox::about(this, title_txt, about_txt);
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
