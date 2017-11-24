#ifndef WINMAIN_H
#define WINMAIN_H

#include <QMainWindow>
#include <QTableView>

#include "ui_tablewindow.h"
#include "tablemodel.h"

#include <set>

class TableWindow : public QMainWindow, public Ui::TableWindow {
    Q_OBJECT
  public:

    TableWindow(QWidget* , Data , QMenu *);
    ~TableWindow();
    void closeEvent (QCloseEvent* event);
    void addMenuAction(QAction* act);

  public slots:
    void activateWindow();
  protected:

  private slots:
    void on_actionAdd_triggered();
    void on_actionDelete_triggered();
    void on_actionSave_triggered();


  private:
    TableModel* m_pTableModel;
    QAction* m_act;

    QMenu *parent_menuWindow;

    typedef std::set <int> IntSet;

    void getSelectedRows(IntSet& rRows);
};

#endif // WINMAIN_H
