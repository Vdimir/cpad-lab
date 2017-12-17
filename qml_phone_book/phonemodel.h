#ifndef PHONEMODEL_H
#define PHONEMODEL_H

#include <QAbstractListModel>
#include <QStringList>


class PhoneModel : public QAbstractListModel {
    Q_OBJECT
  public:
    explicit PhoneModel(QObject* parent = 0);

    enum Roles {
        NameRole = Qt::UserRole + 1,
        PhoneRole
    };


    virtual int rowCount(const QModelIndex& parent) const;
    virtual QVariant data(const QModelIndex& index, int role) const;
    virtual QHash<int, QByteArray> roleNames() const;

  private:
    QList<QList<QString> > m_data;
};

#endif // PHONEMODEL_H
