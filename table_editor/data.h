#ifndef DATA_H
#define DATA_H
#include <QVariant>
#include <vector>
#include <exception>

class Item {
  public:
    enum DatType {
        Int,
        Bool,
        Var,
        Str
    };

    static Item fromInt(int v);
    static Item fromBool(bool v);
    static Item fromSring(QString v);
    static Item fromVar(int v);

    DatType getType();
    QVariant dat;
    DatType dtype;

  protected:

    Item() {}
};


class Data {

  public:
    static Data fromFile(QString filename);
    const QList< QList<Item> >& getData() const;
    QStringList vars;
    QList<Item::DatType> header;
    QList< QList<Item> > data;
    void addEmpty(int);
    void save();

  protected:
    QString filename;
    Data();

};


class BadFileError: public std::exception {

    const char* err;
  public:
    BadFileError(const char* _err) : err(_err) {

    }

    virtual const char* what() const throw() {
        return err;
    }
};

#endif // DATA_H
