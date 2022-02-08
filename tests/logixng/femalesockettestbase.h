#ifndef FEMALESOCKETTESTBASE_H
#define FEMALESOCKETTESTBASE_H

#include <QObject>

class FemaleSocketTestBase : public QObject
{
    Q_OBJECT
public:
    explicit FemaleSocketTestBase(QObject *parent = nullptr);

signals:

};

#endif // FEMALESOCKETTESTBASE_H
