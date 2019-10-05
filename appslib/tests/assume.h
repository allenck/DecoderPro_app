#ifndef ASSUME_H
#define ASSUME_H

#include <QObject>

class Assume : public QObject
{
    Q_OBJECT
public:
    static void assumeTrue(bool);
    /*public*/ static void assumeTrue(QString message, bool b);

signals:

public slots:

protected:
    explicit Assume(QObject *parent = nullptr);

};

#endif // ASSUME_H
