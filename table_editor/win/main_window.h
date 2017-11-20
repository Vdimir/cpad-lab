#ifndef WINMAIN_H
#define WINMAIN_H

#include <QMainWindow>
#include <QTableView>

#include "ui_mainwindow.h"
#include "tablemodel.h"
#include <set>
class MainWindow : public QMainWindow, public Ui::MainWindow {
    Q_OBJECT
  public:
    MainWindow(QWidget* parent, TableModel* model);


    ~MainWindow();

  protected:

  private slots:
    //
    //    void on_actionAddRow_triggered();
    //    void on_actionDeleteSelectedRows_triggered();
    //    void on_actionMoveSelectedRowsFront_triggered();
    //    void on_action_About_triggered();



  private:
    //
    TableModel* m_pTableModel;
    QTableView* m_pTableView;
    //
    typedef std::set <int> IntSet;
    //
    void getSelectedRows(IntSet& rRows);

};

#endif // WINMAIN_H
