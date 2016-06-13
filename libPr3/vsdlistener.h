#ifndef VSDLISTENER_H
#define VSDLISTENER_H

#include <QObject>

class PhysicalLocation;
class Logger;
class AudioListener;
class ListeningSpot;
class VSDListener : public QObject
{
 Q_OBJECT
public:
 explicit VSDListener(QObject *parent = 0);
/*public*/ /*final*/ static QString ListenerSysNamePrefix;// = "IAL$VSD:";
 /*public*/ VSDListener(QString sname,QObject *parent = 0);
 /*public*/ VSDListener(QString sname, QString uname, QObject *parent = 0);
 /*public*/ VSDListener(AudioListener* l, QObject *parent = 0);
 ///*public*/ VSDListener(QObject *parent = 0);
 /*public*/ QString getSystemName();
 /*public*/ QString getUserName();
 /*public*/ ListeningSpot* getLocation() ;
 /*public*/ void setSystemName(QString s);
 /*public*/ void setUserName(QString u);
 /*public*/ void setLocation(ListeningSpot* l);
 /*public*/ void setPosition(PhysicalLocation* p);
signals:

public slots:
private:
 /*private*/ AudioListener* _listener;
 /*private*/ QString _sysname;
 /*private*/ QString _username;
 /*private*/ ListeningSpot* _location;
 Logger* log;
 void common();
};

#endif // VSDLISTENER_H
