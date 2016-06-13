#ifndef PROGRAMMINGMODE_H
#define PROGRAMMINGMODE_H

#include <QObject>

class ProgrammingMode : public QObject
{
    Q_OBJECT
public:
    //explicit ProgrammingMode(QObject *parent = 0);
    /*public*/ ProgrammingMode(QString standardName, QString localName="standardName",QObject *parent = 0);
    /*public*/ QString toString();
    /*public*/ QString getStandardName();
    /*public*/ bool equals(QObject* o);
    /*public*/ int hashCode();

signals:

public slots:
private:
    /*private*/ QString standardName;
    /*private*/ QString localName;

};

#endif // PROGRAMMINGMODE_H
