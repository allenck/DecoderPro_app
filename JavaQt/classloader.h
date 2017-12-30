#ifndef CLASSLOADER_H
#define CLASSLOADER_H

#include <QObject>

class ClassLoader : public QObject
{
 Q_OBJECT
public:
 //explicit ClassLoader(QObject *parent = 0);

signals:

public slots:
protected:
 /*protected*/ ClassLoader(ClassLoader* parent);
 /*protected*/ ClassLoader();
 friend class StartupActionsManager;

};

#endif // CLASSLOADER_H
