#ifndef COMBODELEGATE_H
#define COMBODELEGATE_H

#include <QStyledItemDelegate>

class ComboDelegate : public QStyledItemDelegate {
    Q_OBJECT
  public:

    ComboDelegate(QObject* pParent = 0);

  public:
    //
    virtual QWidget* createEditor(
        QWidget* pParent,
        const QStyleOptionViewItem& rcOption,
        const QModelIndex& rcIndex) const;

    virtual void setEditorData(
        QWidget* pEditor,
        const QModelIndex& rcIndex) const;

    virtual void setModelData(
        QWidget* pEditor,
        QAbstractItemModel* pModel,
        const QModelIndex& rcIndex) const;

    virtual void updateEditorGeometry(
        QWidget* pEditor,
        const QStyleOptionViewItem& rcOption,
        const QModelIndex& rcIndex) const;
}; // class ComboDelegate

#endif // COMBODELEGATE_H
