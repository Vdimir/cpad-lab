
#include "table_window.h"
#include "tablemodel.h"
#include "combo-delegate.h"
#include <QDebug>
#include <QCloseEvent>
#include <QMessageBox>

TableWindow::TableWindow(QWidget* parent, Data dataModel)
    : QMainWindow(parent), m_pTableModel(new TableModel(dataModel))
{
    setupUi(this);

    m_pTableView->setModel(m_pTableModel);

    auto comboIdxs = m_pTableModel->getComboIdx();

    for (auto i = comboIdxs.begin(); i != comboIdxs.end(); ++i) {
        ComboDelegate* pDelegate = new ComboDelegate(m_pTableModel);
        m_pTableView->setItemDelegateForColumn(*i, pDelegate);
    }

    m_pTableView->setSelectionBehavior(QAbstractItemView::SelectRows);
    //    m_pTableView->setSelectionMode(QAbstractItemView::ExtendedSelection);
    //    m_pTableView->setDragEnabled(true);
    //    m_pTableView->setAcceptDrops(true);
    //    m_pTableView->setDropIndicatorShown(true);
    //    m_pTableView->setSortingEnabled(true);
    //    m_pTableView->sortByColumn(0, Qt::AscendingOrder);
    setCentralWidget(m_pTableView);
    //
    //    connect(
    //        m_pActionExit, SIGNAL(triggered()),
    //        this, SLOT(close()));

    m_pTableView->verticalHeader()->hide();

    //    setAttribute(Qt::WA_DeleteOnClose);
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
    delete m_pTableModel;
}
