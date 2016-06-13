#ifndef WARRANTPREFERENCES_H
#define WARRANTPREFERENCES_H

#include <QObject>
#include <QMap>
#include "xmlfile.h"
#include "libpref_global.h"

class LIBPREFSHARED_EXPORT WarrantPreferences : public QObject
{
 Q_OBJECT
public:
 explicit WarrantPreferences(QObject *parent = 0);
 /*public*/ static /*final*/ QString layoutParams;// = "layoutParams";   // NOI18N
 /*public*/ static /*final*/ QString LayoutScale;// = "layoutScale";     // NOI18N
 /*public*/ static /*final*/ QString SearchDepth;// = "searchDepth";     // NOI18N
 /*public*/ static /*final*/ QString SpeedMapParams;// = "speedMapParams"; // NOI18N
 /*public*/ static /*final*/ QString RampPrefs;// = "rampPrefs";         // NOI18N
 /*public*/ static /*final*/ QString TimeIncrement;// = "timeIncrement"; // NOI18N
 /*public*/ static /*final*/ QString ThrottleScale;// = "throttleScale"; // NOI18N
 /*public*/ static /*final*/ QString RampIncrement;// = "rampIncrement"; // NOI18N
 /*public*/ static /*final*/ QString StepIncrements;// = "stepIncrements"; // NOI18N
 /*public*/ static /*final*/ QString SpeedNamePrefs;// = "speedNames";   // NOI18N
 /*public*/ static /*final*/ QString Interpretation;// = "interpretation"; // NOI18N
 /*public*/ static /*final*/ QString AppearancePrefs;// = "appearancePrefs"; // NOI18N
 WarrantPreferences(QString fileName, QObject *parent = 0);
 ~WarrantPreferences() {}
 WarrantPreferences(const WarrantPreferences&) : QObject() {}
 /*public*/ void openFile(QString name);
 /*public*/ void loadLayoutParams(QDomElement child);
 /*public*/ bool loadSpeedMap(QDomElement child);
 /*public*/ void save();
 /*public*/ bool store(QDomElement root);
 /*public*/ void apply();
 /*public*/ float getThrottleScale();

signals:

public slots:
private:
 /*private*/ QString  _fileName;
 /*private*/ float   _scale;// = 87.1f;
 /*private*/ int     _searchDepth;// = 20;
 /*private*/ float   _throttleScale;// = 0.5f;

 /*private*/ QMap<QString, float> _speedNames;
 /*private*/ QMap<QString, QString> _headAppearances;
 /*private*/ int _interpretation;// = SignalSpeedMap.PERCENT_NORMAL;    // Interpretation of values in speed name table

 /*private*/ int _msIncrTime ;//= 1000;         // time in milliseconds between speed changes ramping up or down
 /*private*/ float _throttleIncr;// = 0.04f;    // throttle increment for each ramp speed change
 /*private*/ void loadSpeedMapFromOldXml();
 /*private*/ void setNXFrame() ;
 /*private*/ void setSpeedMap();
 float getScale();
 void setScale(float s);
 void setThrottleScale(float f);
 int getSearchDepth();
 void setSearchDepth(int d) ;
 int getTimeIncre();
 void setTimeIncre(int t);
 float getThrottleIncre() ;
 void setThrottleIncre(float ti);
 QMapIterator<QString, float> getSpeedNameEntryIterator();
 int getSpeedNamesSize();
 float getSpeedNameValue(QString key);
 void setSpeedNames(QList<QPair<QString, float>* > speedNameMap);
 QMapIterator<QString, QString> getAppearanceEntryIterator();
 int getAppearancesSize() ;
 QString getAppearanceValue(QString key);
 void setAppearances(QList<QPair<QString, QString>* > appearanceMap) ;
 int getInterpretation();
 void setInterpretation(int interp);
 Logger* log;
 XmlFile* xmlFile;

friend class WarrantPreferencesPanel;
};
Q_DECLARE_METATYPE(WarrantPreferences)

/*public*/ /*static*/ class WarrantPreferencesXml : public  XmlFile
{
 Q_OBJECT
};
#endif // WARRANTPREFERENCES_H
