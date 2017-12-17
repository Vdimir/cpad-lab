#include "phonemodel.h"

#include <QJsonObject>
#include <QJsonDocument>
#include <QJsonArray>
#include <QFile>
#include <QDebug>
#include <exception>

void readJson(QList<QList<QString> >& data)
{
    QString jsonFname(":/data/resources/phonebook.json");
    QFile file;
    file.setFileName(jsonFname);
    file.open(QIODevice::ReadOnly | QIODevice::Text);

    if (!file.isOpen()) {
        qWarning() << "phonebook.json not found";
    }

    QString val = file.readAll();
    file.close();

    QJsonDocument d = QJsonDocument::fromJson(val.toUtf8());
    QJsonObject phonebook = d.object();
    QJsonArray phoneList = phonebook["phonebook"].toArray();

    foreach (auto item, phoneList) {
        QList<QString> row;
        row << item.toObject()["name"].toString()
            << item.toObject()["phone"].toString();
        data << row;
    }
}


PhoneModel::PhoneModel(QObject* parent):
    QAbstractListModel(parent)
{
    readJson(m_data);
}

int PhoneModel::rowCount(const QModelIndex& parent) const
{
    if (parent.isValid()) {
        return 0;
    }

    return m_data.size();
}

QVariant PhoneModel::data(const QModelIndex& index, int role) const
{
    if (!index.isValid()) {
        return QVariant();
    }

    switch (role) {
        case NameRole:
            return m_data.at(index.row())[0];

        case PhoneRole:
            return m_data.at(index.row())[1];

        default:
            return QVariant();
    }
}

QHash<int, QByteArray> PhoneModel::roleNames() const
{
    QHash<int, QByteArray> roles = QAbstractListModel::roleNames();
    roles[NameRole] = "name";
    roles[PhoneRole] = "phone";

    return roles;
}
