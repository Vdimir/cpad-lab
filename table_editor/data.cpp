#include "data.h"
#include <QFile>
#include <QTextStream>
#include <QDebug>

Data::Data()
{ }

Data Data::fromFile(QString filename)
{
    Data t;
    t.filename = filename;
    QFile file(filename);

    if (!file.open(QIODevice::ReadOnly)) {
        throw BadFileError("File not exist");
    }

    QTextStream ts(&file);

    QString s = ts.readLine();
    QStringList headStr = s.split(",");

    QList<Item::DatType> header;

    for (auto h = headStr.begin(); h != headStr.end(); h++) {
        bool is_int = h->compare("int", Qt::CaseInsensitive) == 0;
        bool is_var = h->compare("variant", Qt::CaseInsensitive) == 0 ||
                      h->compare("var", Qt::CaseInsensitive) == 0;
        bool is_bool = h->compare("bool", Qt::CaseInsensitive) == 0;
        bool is_str = h->compare("string", Qt::CaseInsensitive) == 0 ||
                      h->compare("str", Qt::CaseInsensitive) == 0;

        if (is_int) {
            header << Item::DatType::Int;
        } else if (is_var) {
            header << Item::DatType::Var;
        } else if (is_bool) {
            header << Item::DatType::Bool;
        } else if (is_str) {
            header << Item::DatType::Str;
        } else {
            throw BadFileError("Error in header");
        }
    }

    if (header.empty()) {
        throw BadFileError("Error in header");
    }


    QStringList variants;

    while (!ts.atEnd()) {
        s = ts.readLine();
        QStringList datStr = s.split(",");


        if (datStr.empty() || (datStr.size() == 1 && datStr[0].isEmpty())) {
            continue;
        }

        if (datStr.size() != header.size()) {
            throw BadFileError("Error while reading file");
        }

        QList<Item> row;

        for (int i = 0; i != header.size(); ++i) {
            switch (header[i]) {
                case Item::DatType::Bool:
                    row << Item::fromBool(datStr[i] == "true");
                    break;

                case Item::DatType::Int:
                    row << Item::fromInt(datStr[i].toInt());
                    break;

                case Item::DatType::Str:
                    row << Item::fromSring(datStr[i]);
                    break;

                case Item::DatType::Var:
                    if (variants.indexOf(datStr[i]) == -1) {
                        variants << datStr[i];
                    }

                    row << Item::fromVar(variants.indexOf(datStr[i]));
                    break;

                default:
                    throw std::exception();
                    break;
            }
        } // for header

        t.data << row;
    } // while not eof

    t.vars = variants;
    t.header = header;

    file.close();

    return t;
}


void Data::addEmpty(int n)
{
    QList<Item> row;

    for (auto i = header.begin(); i != header.end(); ++i) {
        switch (*i) {
            case Item::DatType::Bool:
                row << Item::fromBool(true);
                break;

            case Item::DatType::Int:
                row << Item::fromInt(0);
                break;

            case Item::DatType::Str:
                row << Item::fromSring(QString(""));
                break;

            case Item::DatType::Var:
                row << Item::fromVar(0);
                break;

            default:
                throw std::exception();
                break;
        }
    }

    this->data.insert(n, row);
}

void Data::save()
{
    QFile file(filename);

    if (!file.open(QIODevice::WriteOnly)) {
        throw BadFileError("Cannot save file!");
    }


    QTextStream stream( &file );

    QStringList row;

    for (auto h = header.begin(); h != header.end(); ++h) {
        switch (*h) {
            case Item::DatType::Bool:
                row << "bool";
                break;

            case Item::DatType::Str:
                row << "string";
                break;

            case Item::DatType::Var:
                row << "variant";
                break;

            case Item::DatType::Int:
                row << "int";
                break;

            default:
                break;
        }
    }

    stream << row.join(",") << endl;
    row.clear();

    for (auto r = data.begin(); r != data.end(); ++r) {
        for (auto i = r->begin(); i != r->end(); ++i) {
            if (i->dtype == Item::DatType::Var) {
                row << vars[i->dat.toInt()];
            } else {
                row << i->dat.toString();
            }
        }

        stream << row.join(",") << endl;
        row.clear();
    }

    file.close();
}

const QList< QList<Item> >& Data::getData() const
{
    return data;
}


Item Item::fromInt(int v)
{
    Item t;
    t.dtype = Int;
    t.dat = v;
    return t;
}

Item Item::fromBool(bool v)
{
    Item t;
    t.dtype = Bool;
    t.dat = v;
    return t;
}

Item Item::fromSring(QString v)
{
    Item t;
    t.dtype = Str;
    t.dat = v;
    return t;
}

Item Item::fromVar(int v)
{
    Item t;
    t.dtype = Var;
    t.dat = v;
    return t;
}


Item::DatType Item::getType()
{
    return dtype;
}
