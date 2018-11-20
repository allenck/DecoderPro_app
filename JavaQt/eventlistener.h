#ifndef EVENTLISTENER_H
#define EVENTLISTENER_H

#include <QObject>
#include "javaqt_global.h"
class JAVAQTSHARED_EXPORT EventListener : public QObject
{
  Q_OBJECT
public:
    explicit EventListener(QObject *parent = 0);
    
signals:
    
public slots:
    
};

#endif // EVENTLISTENER_H
