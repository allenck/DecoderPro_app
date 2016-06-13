#ifndef DEFAULTSIGNALSYSTEM_H
#define DEFAULTSIGNALSYSTEM_H
#include "signalsystem.h"
#include <QVector>
class LIBPR3SHARED_EXPORT DefaultSignalSystem : public SignalSystem
{
    Q_OBJECT
public:
    //explicit DefaultSignalSystem(QObject *parent = 0);
    /*public*/ DefaultSignalSystem(QString systemName, QString userName="", QObject *parent = 0);
    /*public*/ void setProperty(QString aspect, QString key, QVariant value);
    /*public*/ QVariant getProperty(QString aspect, QString key);
    /*public*/ void setImageType(QString type);
    /*public*/ QStringList getImageTypeList();
    /*public*/ QString getAspect(QVariant obj, QString key);
    /*protected*/ QHash<QString, QVariant>* getTable(QString aspect);
    /*public*/ QStringList getAspects();
    /*public*/ QStringList getKeys();
    /*public*/ bool checkAspect(QString aspect) ;
    /*public*/ void loadDefaults() ;
    /*public*/ int getState() ;
    /*public*/ void setState(int s) ;
    /*public*/ float getMaximumLineSpeed();
    /*public*/ QString toString();
signals:

public slots:
private:
  Logger* log;
  float maximumLineSpeed;// = 0.0f;
protected:
  /*protected*/ QMap<QString, QHash<QString, QVariant>* >* aspects;// = QMap<QString, QHash<QString, QVariant>*>();

  /*protected*/ QVector<QString>* keys;// = new QVector<QString>();

  /*protected*/ QVector<QString>* imageTypes;// = new QVector<QString>();

};

#endif // DEFAULTSIGNALSYSTEM_H
