#include "tablemodel.h"
#include "combo-delegate.h"
#include <QTime>
#include <QTimer>
#include <QPushButton>

TableModel::TableModel(Data data) : m_Data(data)
{
}



const QStringList& TableModel::getItemNames() const
{
    return m_Data.vars;
}


int TableModel::rowCount(
    const QModelIndex& rcParent) const
{
    return m_Data.getData().size();
}

int TableModel::columnCount(
    const QModelIndex& rcParent) const
{
    return m_Data.header.size();
}


QVariant TableModel::headerData(
    int nSection, Qt::Orientation nOrientation, int nRole) const
{
    if (nRole == Qt::DisplayRole &&
            nOrientation == Qt::Horizontal) {
        if (nSection < columnCount()) {
            if (m_Data.header[nSection] == Item::DatType::Bool) {
                return QString("Bool");
            }

            if (m_Data.header[nSection] == Item::DatType::Int) {
                return QString("Int");
            }

            if (m_Data.header[nSection] == Item::DatType::Str) {
                return QString("Str");
            }

            if (m_Data.header[nSection] == Item::DatType::Var) {
                return QString("Var");
            }

        }
    }

    //
    return QAbstractTableModel::headerData(
               nSection, nOrientation, nRole);
} // TableModel::headerData()

Qt::DropActions TableModel::supportedDropActions() const
{
    return Qt::CopyAction | Qt::MoveAction;
}

bool TableModel::insertRows(
    int nRow, int nCount, const QModelIndex& rcParent)
{
    if (nRow < 0) {
        nRow = rowCount();
    }

    beginInsertRows(QModelIndex(), nRow, nRow + nCount - 1);

    for (int i = 0; i < nCount; ++ i) {
        //        m_Data.data.insert(nRow, Data());
        // TODO
    }

    endInsertRows();

    return true;
}

bool TableModel::removeRows(
    int nRow, int nCount, const QModelIndex& rcParent)
{
    beginRemoveRows(QModelIndex(), nRow, nRow + nCount - 1);

    for (int i = 0; i < nCount; ++ i) {
        m_Data.data.removeAt(nRow);
    }

    endRemoveRows();
    return true;
}


bool TableModel::moveRows(
    const QModelIndex& rcParentSource, int nRowSource, int nCount,
    const QModelIndex& rcParentDest, int nChildDest)
{
    beginMoveRows(
        QModelIndex(), nRowSource, nRowSource + nCount - 1,
        QModelIndex(), nChildDest + nCount - 1);

    for (int i = 0; i < nCount; ++ i) {
        m_Data.data.move(nRowSource, nChildDest + i);
    }

    endMoveRows();
    return true;
} // TableModel::moveRows()


Qt::ItemFlags TableModel::flags(
    const QModelIndex& rcIndex) const
{
    Qt::ItemFlags nReturn =
        QAbstractTableModel::flags(rcIndex);

    nReturn |= Qt::ItemIsDropEnabled;

    if (rcIndex.isValid()) {
        nReturn |= Qt::ItemIsDragEnabled;

        if (m_Data.header[rcIndex.column()] == Item::DatType::Bool) {
            nReturn |= Qt::ItemIsUserCheckable;
        } else {
            nReturn |= Qt::ItemIsEditable;
        }
    }

    //
    return nReturn;
} // TableModel::flags()


void TableModel::sort(int nColumn, Qt::SortOrder nOrder)
{
    emit layoutAboutToBeChanged();

    emit layoutChanged();
} // TableModel::sort()

QVariant TableModel::data(
    const QModelIndex& rcIndex, int nRole) const
{
    if (rcIndex.isValid() &&
            rcIndex.row() < rowCount() &&
            rcIndex.column() < columnCount()) {
        const Item& rcData = m_Data.data[rcIndex.row()][rcIndex.column()];

        switch (nRole) {
            case Qt::DisplayRole:
            case Qt::EditRole:
                switch (m_Data.header[rcIndex.column()]) {
                    case Item::DatType::Bool:
                        return rcData.dat.toString();

                    case Item::DatType::Int:
                        return rcData.dat.toInt();

                    case Item::DatType::Str:
                        return rcData.dat.toString();

                    case Item::DatType::Var:
                        if (nRole == Qt::DisplayRole) {
                            return m_Data.vars[rcData.dat.toInt()];
                        } else {
                            return rcData.dat.toInt();
                        }
                } // m_Data.header[rcIndex.column()])

            case Qt::CheckStateRole:
                if (m_Data.header[rcIndex.column()] == Item::DatType::Bool) {
                    return
                        rcData.dat.toBool() ?
                        Qt::Checked : Qt::Unchecked;
                }
        }
    }

    //
    return QString();
} // TableModel::data()


bool TableModel::setData(
    const QModelIndex& rcIndex, const QVariant& rcValue, int nRole)
{
    if (rcIndex.isValid() &&
            rcIndex.row() < rowCount() &&
            rcIndex.column() < columnCount() &&
            (nRole == Qt::DisplayRole ||
             nRole == Qt::EditRole ||
             nRole == Qt::CheckStateRole)) {
        Item& rData = m_Data.data[rcIndex.row()][rcIndex.column() ];

        switch (nRole) {
            case Qt::DisplayRole:
            case Qt::EditRole:
                switch (m_Data.header[rcIndex.column()]) {
                    case Item::DatType::Bool:
                        rData.dat = rcValue.toBool();
                        break;

                    case Item::DatType::Int:
                        rData.dat = rcValue.toInt();
                        break;

                    case Item::DatType::Str:
                        rData.dat = rcValue.toString();
                        break;

                    case Item::DatType::Var:
                        rData.dat = rcValue.toInt();
                } // m_Data.header[rcIndex.column()])


                break;

            case Qt::CheckStateRole:
                if (m_Data.header[rcIndex.column()] == Item::DatType::Bool) {
                    rData.dat =
                        (rcValue.toInt() == Qt::Checked);
                }
        } // switch (nRole)

        emit dataChanged(rcIndex, rcIndex);

        return true;
    }

    //
    return false;
} // TableModel::setData()

QList<int> TableModel::getComboIdx()
{
    QList<int> res;

    for (auto i = 0; i != m_Data.header.size(); ++i) {
        if (m_Data.header[i] == Item::DatType::Var) {
            res << i;
        }
    }

    return res;
}
