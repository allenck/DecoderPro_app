#ifndef DEFAULTSIGNALAPPEARANCEMAP_H
#define DEFAULTSIGNALAPPEARANCEMAP_H
#include "signalappearancemap.h"

class QDomElement;
class QDomNodeList;
class LIBPR3SHARED_EXPORT DefaultSignalAppearanceMap : public SignalAppearanceMap
{
    Q_OBJECT
public:
    //explicit DefaultSignalAppearanceMap(QObject *parent = 0);
    /*public*/ DefaultSignalAppearanceMap(QString systemName, QString userName);
    /*public*/ DefaultSignalAppearanceMap(QString systemName);
    static /*public*/ DefaultSignalAppearanceMap* getMap(QString signalSystemName, QString aspectMapName);
    static DefaultSignalAppearanceMap* loadMap(QString signalSystemName, QString aspectMapName) ;
    static void loadImageMaps(QDomNodeList img, QString name, DefaultSignalAppearanceMap* map);
    /*public*/ /*final*/ static const int NUMSPECIFIC = 4;
    static void loadSpecificMap(QString signalSystemName, QString aspectMapName, DefaultSignalAppearanceMap* SMmap, QDomElement root);
    static void loadSpecificAspect(QString signalSystemName, QString aspectMapName, int aspectType, DefaultSignalAppearanceMap* SMmap, QDomElement root);
    static void loadAspectRelationMap(QString signalSystemName, QString aspectMapName, DefaultSignalAppearanceMap* SMmap, QDomElement root);
    /*public*/ QString getProperty(QString aspect, QString key);
    /*public*/ QString getImageLink(QString aspect, QString type);
    /*public*/ QVector<QString> getImageTypes(QString aspect);
    /*public*/ void loadDefaults();
    /*public*/ bool checkAspect(QString aspect) ;
    /*public*/ void addAspect(QString aspect, QVector<int>* appearances);
    /*public*/ QStringList getAspects();
    /*public*/ QString getSpecificAppearance(int appearance);
    /*public*/ QVector<QString> getValidAspectsForAdvancedAspect(QString advancedAspect);
    /*public*/ SignalSystem* getSignalSystem();
    /*public*/ void setSignalSystem(SignalSystem* t);
    /*public*/ int getState();
    /*public*/ void setState(int s);
    /*public*/ QVector<int>* getAspectSettings(QString aspect);

public slots:
private:
 Logger* log;
protected:
    /*protected*/ QHash<QString, QHash<QString, QString> >* aspectAttributeMap;
            //= new QHash<QString, QHash<QString, QString>>();

    /*protected*/ QHash<QString, QHash<QString, QString> >* aspectImageMap;
            //= new QHash<QString, QHash<QString, QString>>();

    static QMap<QString, DefaultSignalAppearanceMap*>* maps;
            //= new QMap<QString, DefaultSignalAppearanceMap>();

    /*protected*/ QHash<int, QString>* specificMaps;
           // = new QHash<int, QString>();

    /*protected*/ QHash<QString, QVector<QString> >* aspectRelationshipMap;
           // = new QHash<QString, QStringList>();
    /*protected*/ SignalSystem* systemDefn;
/*protected*/ QMap<QString, QVector<int>* >* table;// = new QMap<QString, QList<int> >();
};

#endif // DEFAULTSIGNALAPPEARANCEMAP_H
