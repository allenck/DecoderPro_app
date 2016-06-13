#ifndef INITIALIZER_H
#define INITIALIZER_H
#include <QObject>

template<class T>
class initializer : public QObject
{
 //Q_OBJECT
public:
 QObject* getDefault(QString type);
};

#endif // INITIALIZER_H
