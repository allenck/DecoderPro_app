#ifndef ASSUME_H
#define ASSUME_H

#include <QObject>

class Assume : public QObject
{
    Q_OBJECT
public:
    static void assumeTrue(bool);
signals:

public slots:

protected:
    explicit Assume(QObject *parent = nullptr);

};

#endif // ASSUME_H
