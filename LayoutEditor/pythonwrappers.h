#ifndef PYTHONWRAPPERS_H
#define PYTHONWRAPPERS_H

#include <QObject>
class PythonWrappers : public QObject
{
 Q_OBJECT
public:
 explicit PythonWrappers(QObject *parent = 0);
 static void defineClasses();
signals:

public slots:
};
#endif // PYTHONWRAPPERS_H
