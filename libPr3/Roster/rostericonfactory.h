#ifndef ROSTERICONFACTORY_H
#define ROSTERICONFACTORY_H

#include <QObject>
#include <QMap>
#include "imageicon.h"

class RosterEntry;
class RosterIconFactory : public QObject
{
 Q_OBJECT
public:
    /*explicit*/ RosterIconFactory(QObject *parent = 0);
    RosterIconFactory(int height, QObject *parent = 0);
    ImageIcon* getIcon(QString id);
    /*public*/ ImageIcon* getIcon(RosterEntry* re);
    static RosterIconFactory* instance();

signals:
    
public slots:
private:
 int iconHeight;
    QMap<QString,ImageIcon*> icons;
    static RosterIconFactory* _instance;
};

#endif // ROSTERICONFACTORY_H
