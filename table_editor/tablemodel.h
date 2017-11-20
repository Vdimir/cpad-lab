#ifndef MYMODEL_H
#define MYMODEL_H

#include <QAbstractTableModel>
#include <data.h>
class TableModel : public QAbstractTableModel {
    Q_OBJECT

  public:
    const QStringList& getItemNames() const;


  public:
    TableModel(Data dat);
    int rowCount(const QModelIndex& parent = QModelIndex()) const override ;
    int columnCount(const QModelIndex& parent = QModelIndex()) const override;


    virtual QVariant data(
        const QModelIndex& rcIndex, int nRole) const;
    virtual bool setData(
        const QModelIndex& rcIndex, const QVariant& rcValue, int nRole);
    virtual QVariant headerData(
        int nSection, Qt::Orientation nOrientation, int nRole) const;
    virtual Qt::DropActions supportedDropActions() const;
    virtual bool insertRows(
        int nRow, int nCount, const QModelIndex& rcParent = QModelIndex());
    virtual bool removeRows(
        int nRow, int nCount, const QModelIndex& rcParent = QModelIndex());

    virtual bool moveRows(
        const QModelIndex& rcParentSource, int nRowSource, int nCount,
        const QModelIndex& rcParentDest, int nChildDest);
    virtual Qt::ItemFlags flags(
        const QModelIndex& rcIndex) const;
    virtual void sort(
        int nColumn, Qt::SortOrder nOrder = Qt::AscendingOrder);


    QList<int> getComboIdx();
    void saveData();
  private:
    Data m_Data;
}; // class TableModel

#endif
