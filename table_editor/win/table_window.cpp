
#include "table_window.h"
#include "tablemodel.h"
#include "combo-delegate.h"
#include <QDebug>
#include <QCloseEvent>
#include <QMessageBox>

TableWindow::TableWindow(QWidget* parent, Data dataModel, QMenu *parent_menuWindow)
    : QMainWindow(parent), m_pTableModel(new TableModel(dataModel)),
    m_act(0), parent_menuWindow(parent_menuWindow)
{
    setupUi(this);

    m_pTableView->setModel(m_pTableModel);

    auto comboIdxs = m_pTableModel->getComboIdx();

    for (auto i = comboIdxs.begin(); i != comboIdxs.end(); ++i) {
        ComboDelegate* pDelegate = new ComboDelegate(m_pTableModel);
        m_pTableView->setItemDelegateForColumn(*i, pDelegate);
    }

    m_pTableView->setSelectionBehavior(QAbstractItemView::SelectRows);

    setCentralWidget(m_pTableView);


    m_pTableView->verticalHeader()->hide();

    setAttribute(Qt::WA_DeleteOnClose);
}


void TableWindow::on_actionAdd_triggered()
{
    const int cnRow = m_pTableModel->rowCount();
    m_pTableModel->insertRow(cnRow);
    QModelIndex indexNew = m_pTableModel->index(cnRow, 0);
    m_pTableView->setCurrentIndex(indexNew);
}


void TableWindow::on_actionDelete_triggered()
{
    IntSet rows;
    getSelectedRows(rows);
    IntSet::reverse_iterator
    i = rows.rbegin(),
    e = rows.rend();

    for (; i != e; ++ i) {
        m_pTableModel->removeRow(*i);
    }
}

void TableWindow::closeEvent (QCloseEvent* event)
{
    QMessageBox::StandardButton resBtn =
        QMessageBox::question( this, tr("Save changes?"),
                               tr("Save changes in %1?").arg(this->windowTitle()),
                               QMessageBox::No | QMessageBox::Yes,
                               QMessageBox::Yes);

    if (resBtn == QMessageBox::Yes) {
        on_actionSave_triggered();
    }

    if (parent_menuWindow && m_act)
    {
      parent_menuWindow->removeAction(m_act);
    }

}

void TableWindow::on_actionSave_triggered()
{
    m_pTableModel->saveData();
}

//void TableWindow::on_actionMove_triggered()
//{
//    IntSet rows;
//    getSelectedRows(rows);
//    IntSet::iterator
//    i = rows.begin(),
//    e = rows.end();

//    for (int n = 0; i != e; ++ i, ++ n) {
//        m_pTableModel->moveRow(QModelIndex(), *i, QModelIndex(), n);
//    }
//}

void TableWindow::activateWindow() {
    this->show();
    this->setWindowState(Qt::WindowActive) ;
    this->raise();
    this->setFocus();
}

void TableWindow::addMenuAction(QAction* act) {
    m_act = act;
    connect(m_act, &QAction::triggered, this,
      &TableWindow::activateWindow);
}

void TableWindow::getSelectedRows(IntSet& rRows)
{
    QModelIndexList indexes =
        m_pTableView->selectionModel()->selectedIndexes();

    foreach (QModelIndex index, indexes) {
        rRows.insert(index.row());
    }
}

TableWindow::~TableWindow()
{
    if (m_act) delete m_act;
    delete m_pTableModel;
}
