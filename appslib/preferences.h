#ifndef PREFERENCES_H
#define PREFERENCES_H

#include <QObject>
#include <QTextStream>
#include "exceptions.h"

class NodeChangeListener;
class PreferenceChangeListener;
class RuntimePermission;
class Permission;
class PreferencesFactory;
class Preferences : public QObject
{
 Q_OBJECT
public:
 /*public*/ static /*final*/ int MAX_KEY_LENGTH;// = 80;
 /*public*/ static /*final*/ int MAX_VALUE_LENGTH;// = 8*1024;
 /*public*/ static /*final*/ int MAX_NAME_LENGTH;// = 80;
 /*public*/ static Preferences* userNodeForPackage(QString c);
 /*public*/ static Preferences* systemNodeForPackage(QString c);
 /*public*/ static Preferences* userRoot();
 /*public*/ static Preferences* systemRoot();
 /*public*/ /*abstract*/ virtual void put(QString key, QString value);
 /*public*/ /*abstract*/ virtual QString get(QString key, QString def);
 /*public*/ /*abstract*/ virtual void remove(QString key);
 /*public*/ /*abstract*/ virtual void clear();
 /*public*/ /*abstract*/ virtual void putInt(QString key, int value);
 /*public*/ /*abstract*/ virtual int getInt(QString key, int def);
 /*public*/ /*abstract*/ virtual void putLong(QString key, long value);
 /*public*/ /*abstract*/ virtual long getLong(QString key, long def);
 /*public*/ /*abstract*/ virtual void putBoolean(QString key, bool value);
 /*public*/ /*abstract*/ virtual bool getBoolean(QString key, bool def);
 /*public*/ /*abstract*/ virtual void putFloat(QString key, float value);
 /*public*/ /*abstract*/ virtual float getFloat(QString key, float def);
 /*public*/ /*abstract*/ virtual void putDouble(QString key, double value);
 /*public*/ /*abstract*/ virtual double getDouble(QString key, double def);
 /*public*/ /*abstract*/ virtual void putByteArray(QString key, QByteArray* value);
 /*public*/ /*abstract*/ virtual QByteArray* getByteArray(QString key, QByteArray* def);
 /*public*/ /*abstract*/ virtual QStringList keys();
 /*public*/ /*abstract*/ virtual QStringList childrenNames();
 /*public*/ /*abstract*/ virtual Preferences* parent();
 /*public*/ /*abstract*/ virtual Preferences* node(QString pathName);
 /*public*/ /*abstract*/ virtual bool nodeExists(QString pathName);
 /*public*/ /*abstract*/ virtual void removeNode();
 /*public*/ /*abstract*/ virtual QString name();
 /*public*/ /*abstract*/ virtual QString absolutePath();
 /*public*/ /*abstract*/ virtual bool isUserNode();
 /*public*/ /*abstract*/ virtual QString toString();
 /*public*/ /*abstract*/ virtual void flush() throw (BackingStoreException);
 /*public*/ /*abstract*/ virtual void sync() throw (BackingStoreException);
 /*public*/ /*abstract*/ virtual void addPreferenceChangeListener(
     PreferenceChangeListener* pcl);
 /*public*/ /*abstract*/ virtual void removePreferenceChangeListener(
     PreferenceChangeListener* pcl);
 /*public*/ /*abstract*/ virtual void addNodeChangeListener(NodeChangeListener* ncl);
 /*public*/ /*abstract*/ virtual void removeNodeChangeListener(NodeChangeListener* ncl);
 /*public*/ /*abstract*/ virtual void exportNode(QTextStream* os);
 /*public*/ /*abstract*/ virtual void exportSubtree(QTextStream* os);
 /*public*/ static void importPreferences(QTextStream* is);

signals:

public slots:

private:
 /*private*/ static /*final*/ PreferencesFactory* _factory;// = factory();

 /*private*/ static PreferencesFactory* factory();
 /*private*/ static PreferencesFactory* factory1();
 /*private*/ static QString nodeName(QString c);
 /*private*/ static Permission* prefsPerm;// = new RuntimePermission("preferences");

protected:
 explicit /*protected*/ Preferences();


};

#endif // PREFERENCES_H
