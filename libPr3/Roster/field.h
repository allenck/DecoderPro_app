#ifndef FIELD_H
#define FIELD_H

#include <QObject>

class Field : public QObject
{
    Q_OBJECT
public:
    explicit Field(QObject *parent = 0);
    void set(QObject*, QVariant);
signals:

public slots:

};

#endif // FIELD_H
