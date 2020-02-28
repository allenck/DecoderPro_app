#ifndef SIGNALSPEEDMAP_H
#define SIGNALSPEEDMAP_H

#include <QObject>
#include <QMap>
#include "exceptions.h"
#include "logger.h"
#include <QStringList>
#include "libPr3_global.h"
#include "bean.h"
#include "propertychangelistener.h"

class WarrantPreferencesListener;
class QDomElement;
class SignalSystem;
class LIBPR3SHARED_EXPORT SignalSpeedMap : public Bean
{
    Q_OBJECT
public:
 Q_INVOKABLE SignalSpeedMap(QObject *parent = nullptr);
 ~SignalSpeedMap() {}
 SignalSpeedMap(const SignalSpeedMap&): Bean() {}
 enum SPEEDS
 {
  PERCENT_NORMAL = 1,
  PERCENT_THROTTLE = 2,
  SPEED_MPH = 3,
  SPEED_KMPH = 4
 };
    //static /*public*/ SignalSpeedMap* getMap();
 Q_INVOKABLE /*public*/ void initialize();
    void loadMap();
    /*public*/ bool checkSpeed(QString name);
    /*public*/ QString getAspectSpeed(QString aspect, SignalSystem* system);
    /*public*/ QString getAspectExitSpeed(QString aspect, SignalSystem* system);
    /*public*/ QString getAppearanceSpeed(QString name) throw (NumberFormatException);
    /*public*/ QVector<QString> getValidSpeedNames();
    /*public*/ float getSpeed(QString name);
    /*public*/ QString getNamedSpeed(float speed);
    /*public*/ bool isRatioOfNormalSpeed();
    /*public*/ int getInterpretation();
    /*public*/ int getStepDelay();
    /*public*/ Q_DECL_DEPRECATED int getNumSteps();
    /*public*/ void setAspectTable(QMapIterator<QString, float> iter, int interpretation);
    /*public*/ void setAppearanceTable(QMapIterator<QString, QString>  iter);
    /*public*/ void setRampParams(float throttleIncr, int msIncrTime);
    /*public*/ void setDefaultThrottleFactor(float f);
    /*public*/ float getDefaultThrottleFactor();
    /*public*/ void setLayoutScale(float s) ;
    /*public*/ float getLayoutScale();
    /*public*/ void setMap(SignalSpeedMap* map) ;
    /*public*/ float getStepIncrement();
    /*public*/ QStringListIterator getAppearanceIterator();
    /*public*/ QStringListIterator getSpeedIterator();
    /*public*/ bool isAssignableFromType() {return true;}
    /*public*/ void loadRoot(/*@Nonnull*/ QDomElement root);
    /*public*/ void setAspects(/*@Nonnull*/ QMap<QString, float> map, int interpretation);
    /*public*/ void setAppearances(/*@Nonnull*/ QMap<QString, QString> map);

    signals:

    public slots:
    void propertyChange(PropertyChangeEvent*);

    private:
    static /*private*/ SignalSpeedMap* _map;
    static /*private*/ QMap<QString, float>* _table;// =  QMap<String, float>();
    static /*private*/ QMap<QString, QString>* _headTable;// = new QMap<QString, QString>();
    static /*private*/ int _interpretation;
    static /*private*/ bool _percentNormal;
    static /*private*/ int _sStepDelay;
    static /*private*/ int _numSteps;
    /*private*/ float _stepIncrement;// = 0.04f;       // ramp step throttle increment
    /*private*/ float _throttleFactor;// = 0.75f;
    /*private*/ float _scale;
    static Logger* log;
    WarrantPreferencesListener* warrantPreferencesListener = nullptr;
 friend class WarrantPreferencesListener;
};
Q_DECLARE_METATYPE(SignalSpeedMap)

class WarrantPreferencesListener : public PropertyChangeListener
{
 Q_OBJECT
 SignalSpeedMap* ssm;
public:
 WarrantPreferencesListener(SignalSpeedMap* ssm) {this->ssm = ssm;}
public slots:
 void propertyChange(PropertyChangeEvent* evt) override;
};
#endif // SIGNALSPEEDMAP_H
