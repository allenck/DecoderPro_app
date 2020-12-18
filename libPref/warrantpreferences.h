#ifndef WARRANTPREFERENCES_H
#define WARRANTPREFERENCES_H

#include "abstractpreferencesmanager.h"
#include <QMap>
#include "xmlfile.h"
#include "libpref_global.h"

class Profile;
class LIBPREFSHARED_EXPORT WarrantPreferences : public AbstractPreferencesManager
{
 Q_OBJECT
public:
 explicit WarrantPreferences(QObject *parent = 0);
 /*public*/ enum Shutdown {NO_MERGE, PROMPT, MERGE_ALL};
 /*public*/ static /*final*/ QString LAYOUT_PARAMS;// = "layoutParams";   // NOI18N
 /*public*/ static /*final*/ QString LAYOUT_SCALE;// = "layoutScale";     // NOI18N
 /*public*/ static /*final*/ QString SEARCH_DEPTH;// = "searchDepth";     // NOI18N
 /*public*/ static /*final*/ QString SPEED_MAP_PARAMS;// = "speedMapParams"; // NOI18N
 /*public*/ static /*final*/ QString RAMP_PREFS;// = "rampPrefs";         // NOI18N
 /*public*/ static /*final*/ QString TIME_INCREMENT;// = "timeIncrement"; // NOI18N
 /*public*/ static /*final*/ QString THROTTLE_SCALE;// = "throttleScale"; // NOI18N
 /*public*/ static /*final*/ QString RAMP_INCREMENT;// = "rampIncrement"; // NOI18N
 /*public*/ static /*final*/ QString STEP_INCREMENTS;// = "stepIncrements"; // NOI18N
 /*public*/ static /*final*/ QString SPEED_NAME_PREFS;// = "speedNames";   // NOI18N
 /*public*/ static /*final*/ QString SPEED_NAMES;// = SPEED_NAME_PREFS;
 /*public*/ static /*final*/ QString INTERPRETATION;// = "interpretation"; // NOI18N
 /*public*/ static /*final*/ QString APPEARANCE_PREFS;// = "appearancePrefs"; // NOI18N
 /*public*/ static /*final*/ QString APPEARANCES;// = "appearances"; // NOI18N

 /*public*/ void savePreferences(Profile* profile);

 ~WarrantPreferences() {}
 WarrantPreferences(const WarrantPreferences&) : AbstractPreferencesManager() {}
 /*public*/ static WarrantPreferences* getDefault();
 /*public*/ void openFile(QString name);
 /*public*/ void loadLayoutParams(QDomElement child);
 /*public*/ bool loadSpeedMap(QDomElement child);
 /*public*/ void save();
 /*public*/ bool store(QDomElement root);
 QT_DEPRECATED /*public*/ void apply();
 /*public*/ float getThrottleScale();
 /*public*/ void initialize(Profile* profile) throw (InitializationException);
 /*public*/ QMap<QString, QString> getAppearances();
 /*public*/ QMap<QString, float> getSpeedNames();
 /*protected*/ void setShutdown(Shutdown set);
 /*public*/ Shutdown getShutdown();
 /*public*/ float getLayoutScale();
 /*public*/ void setLayoutScale(float scale);

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
 // /*private*/ void setSpeedMap();
 QT_DEPRECATED float getScale();
 QT_DEPRECATED void setScale(float s);
 void setThrottleScale(float f);
 int getSearchDepth();
 void setSearchDepth(int d) ;
 int getTimeIncrement();
 void setTimeIncrement(int t);
 float getThrottleIncrement() ;
 void setThrottleIncrement(float ti);
 QMapIterator<QString, float> getSpeedNameEntryIterator();
 int getSpeedNamesSize();
 float getSpeedNameValue(QString key);
 void setSpeedNames(QMap<QString, float> map);
 QMapIterator<QString, QString> getAppearanceEntryIterator();
 int getAppearancesSize() ;
 QString getAppearanceValue(QString key);
 void setAppearances(QList<QPair<QString, QString>* > appearanceMap) ;
 int getInterpretation();
 void setInterpretation(int interp);
 Logger* log;
 XmlFile* xmlFile;
 QDomDocument doc;
 /*private*/ void setAppearances(QMap<QString, QString> map);
 Shutdown _shutdown;

protected:
 /*protected*/ void setSpeedNames(QList<QPair<QString, float>> speedNameMap);

friend class WarrantPreferencesPanel;
friend class NXFrame;
friend class SignalSpeedMap;
friend class SpeedUtil;
friend class WarrantPreferencesListener;
};
Q_DECLARE_METATYPE(WarrantPreferences)

/*public*/ /*static*/ class WarrantPreferencesXml : public  XmlFile
{
 Q_OBJECT
};
#endif // WARRANTPREFERENCES_H
