#ifndef WINMAIN_H
#define WINMAIN_H

#include <QMainWindow>
#include <QTableView>

#include "ui_mainwindow.h"
#include "tablemodel.h"
#include <set>
class TableWindow : public QMainWindow, public Ui::MainWindow {
    Q_OBJECT
  public:
    TableWindow(QWidget* parent, TableModel* model);


    ~TableWindow();

  protected:

  private slots:
    //
    void on_actionAdd_triggered();
    void on_actionDelete_triggered();
    void on_actionMove_triggered();
    //    void on_action_About_triggered();



  private:

    TableModel* m_pTableModel;


    typedef std::set <int> IntSet;

    void getSelectedRows(IntSet& rRows);

};

#endif // WINMAIN_H
