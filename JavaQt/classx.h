#ifndef CLASSX_H
#define CLASSX_H

#include <QObject>
template<class T>
class ClassX : public QObject
{
 //Q_OBJECT
public:

/*public*/ static T* forName(QString );
signals:

public slots:
};

#endif // CLASSX_H
