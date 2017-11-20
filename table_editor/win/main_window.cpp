
#include "main_window.h"
#include "tablemodel.h"
#include "combo-delegate.h"

MainWindow::MainWindow(QWidget* parent, TableModel* model)
    : QMainWindow(parent)
{
    setupUi(this);

    m_pTableModel = model;
    m_pTableView = new QTableView;

    m_pTableView->setModel(m_pTableModel);

    auto comboIdxs = model->getComboIdx();

    for (auto i = comboIdxs.begin(); i != comboIdxs.end(); ++i) {
        ComboDelegate* pDelegate = new ComboDelegate(m_pTableModel);

        m_pTableView->setItemDelegateForColumn(*i, pDelegate);

    }

    m_pTableView->setSelectionBehavior(QAbstractItemView::SelectRows);
    m_pTableView->setSelectionMode(QAbstractItemView::ExtendedSelection);
    m_pTableView->setDragEnabled(true);
    m_pTableView->setAcceptDrops(true);
    m_pTableView->setDropIndicatorShown(true);
    m_pTableView->setSortingEnabled(true);
    m_pTableView->sortByColumn(0, Qt::AscendingOrder);
    setCentralWidget(m_pTableView);
    //
    //    connect(
    //        m_pActionExit, SIGNAL(triggered()),
    //        this, SLOT(close()));

    m_tableView->verticalHeader()->hide();
    //    QObject::connect(ui->action_Exit, SIGNAL(triggered()), qApp, SLOT(quit()));
}


//void MainWindow::on_actionAddRow_triggered()
//{
//    const int cnRow = m_pTableModel->rowCount();
//    m_pTableModel->insertRow(cnRow);
//    QModelIndex indexNew = m_pTableModel->index(cnRow, 0);
//    m_pTableView->setCurrentIndex(indexNew);
//}



//void MainWindow::on_actionDeleteSelectedRows_triggered()
//{
//    IntSet rows;
//    getSelectedRows(rows);
//    //
//    IntSet::reverse_iterator
//    i = rows.rbegin(),
//    e = rows.rend();

//    for (; i != e; ++ i) {
//        m_pTableModel->removeRow(*i);
//    }
//}


//void MainWindow::on_actionMoveSelectedRowsFront_triggered()
//{
//    IntSet rows;
//    getSelectedRows(rows);
//    //
//    IntSet::iterator
//    i = rows.begin(),
//    e = rows.end();

//    for (int n = 0; i != e; ++ i, ++ n)
//        m_pTableModel->moveRow(
//            QModelIndex(), *i, QModelIndex(), n);
//}


void MainWindow::getSelectedRows(IntSet& rRows)
{
    QModelIndexList indexes =
        m_pTableView->selectionModel()->selectedIndexes();

    foreach (QModelIndex index, indexes) {
        rRows.insert(index.row());
    }
}

MainWindow::~MainWindow()
{
    delete m_pTableView;
}
