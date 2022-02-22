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
    /*public*/ void setProperty(QString aspect, QString key, QVariant value) override;
    /*public*/ QVariant getProperty(QString aspect, QString key) override;
    /*public*/ void setImageType(QString type) override;
    /*public*/ QStringList getImageTypeList() override;
    /*public*/ QString getAspect(QVariant obj, QString key) override;
    /*protected*/ QHash<QString, QVariant>* getTable(QString aspect);
    /*public*/ QStringList getAspects() override;
    /*public*/ QStringList getKeys() override;
    /*public*/ bool checkAspect(QString aspect) override ;
    /*public*/ void loadDefaults() ;
    /*public*/ int getState()  override;
    /*public*/ void setState(int s) override ;
    /*public*/ float getMaximumLineSpeed() override;
    /*public*/ QString toString();

    QObject* self() override{return (QObject*)this;}

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
