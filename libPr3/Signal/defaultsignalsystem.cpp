#include "defaultsignalsystem.h"
#include "exceptions.h"
#include "signalspeedmap.h"
#include "instancemanager.h"

//DefaultSignalSystem::DefaultSignalSystem(QObject *parent) :
//    SignalSystem(parent)
//{
//}
/**
 * Default implementation of a basic signal system definition.
 * <p>
 * The default contents are taken from the NamedBeanBundle properties file.
 * This makes creation a little more heavy-weight, but speeds operation.
 *
 *
 * @author	Bob Jacobsen Copyright (C) 2009
 * @version     $Revision: 22323 $
 */
///*public*/ class DefaultSignalSystem extends AbstractNamedBean implements SignalSystem  {

/*public*/ DefaultSignalSystem::DefaultSignalSystem(QString systemName, QString userName, QObject *parent) : SignalSystem(systemName, userName, parent)
{
    //super(systemName, userName);
    maximumLineSpeed = 0.0f;
    aspects = new QMap<QString, QHash<QString, QVariant>* >();

    keys = new QVector<QString>();

    imageTypes = new QVector<QString>();

}

///*public*/ DefaultSignalSystem(String systemName) {
//    super(systemName);
//}

/*public*/ void DefaultSignalSystem::setProperty(QString aspect, QString key, QVariant value) {
    getTable(aspect)->insert(key, value);
    if (! keys->contains(key)) keys->append(key);
}

/*public*/ QVariant DefaultSignalSystem::getProperty(QString aspect,QString key) {
    if (aspect=="") {
        return QVariant();
    }
    return getTable(aspect)->value(key);
}

/*public*/ void DefaultSignalSystem::setImageType(QString type) {
    if (! imageTypes->contains(type)) imageTypes->append(type);
}

/*public*/ QStringList DefaultSignalSystem::getImageTypeList() {
    return imageTypes->toList();
}

/*public*/ QString DefaultSignalSystem::getAspect(QVariant obj, QString key)
{
 if (obj==QVariant())
  return "";
 QStringListIterator aspectKeys( aspects->keys());
 while ( aspectKeys.hasNext() )
 {
        QString aspect = aspectKeys.next();
       if(getTable(aspect)->contains(key)){
           if (getTable(aspect)->value(key)==(obj))
               return aspect;
       }
    }
    return NULL;
}

/*protected*/ QHash<QString, QVariant>* DefaultSignalSystem::getTable(QString aspect) {
    QHash<QString, QVariant>* t = aspects->value(aspect);
    if ( t == NULL) {
        t = new QHash<QString, QVariant>();
        aspects->insert(aspect, t);
    }
    return t;
}

/*public*/ QStringList DefaultSignalSystem::getAspects() {
    return aspects->keys();
}

/*public*/ QStringList DefaultSignalSystem::getKeys() {
    return keys->toList();
}

/*public*/ bool DefaultSignalSystem::checkAspect(QString aspect) {
    return aspects->value(aspect) != NULL;
}

/*public*/ void DefaultSignalSystem::loadDefaults() {

    log->debug("start loadDefaults");

    QString aspect;
    QString key = tr("Speed");
    QString value;

    aspect = tr("Red");
    value = tr("SignalAspect_Speed_Stop");
    setProperty(aspect, key, value);

    aspect = tr("SignalAspectDefaultYellow");
    value = tr("SignalAspect_Speed_Approach");
    setProperty(aspect, key, value);

    aspect = tr("SignalAspectDefaultGreen");
    value = tr("SignalAspect_Speed_Clear");
    setProperty(aspect, key, value);

}


/*public*/ int DefaultSignalSystem::getState() {
    throw new /*NoSuchMethodError*/Exception();
}

/*public*/ void DefaultSignalSystem::setState(int s) {
    throw new /*NoSuchMethodError*/Exception();
}


/*public*/ float DefaultSignalSystem::getMaximumLineSpeed(){
    if(maximumLineSpeed == 0.0f){
        foreach(QString as, aspects->keys()){
            QString speed = getProperty(as, "speed").toString();
            if(speed!=NULL){
                float aspectSpeed = 0.0f;
                try {
                    aspectSpeed = speed.toFloat();
                }catch (NumberFormatException* nx) {
                    try{
                        aspectSpeed = static_cast<SignalSpeedMap*>(InstanceManager::getDefault("SignalSpeedMap"))->getSpeed(speed);
                    } catch (Exception* ex){
                        //Considered Normal if the speed does not appear in the map
                    }
                }
                if(aspectSpeed>maximumLineSpeed){
                    maximumLineSpeed=aspectSpeed;
                }
            }

        }
    }
    if(maximumLineSpeed ==0.0f){
        //no speeds configured so will use the default.
        maximumLineSpeed = static_cast<SignalSpeedMap*>(InstanceManager::getDefault("SignalSpeedMap"))->getSpeed("Maximum");
    }
    return maximumLineSpeed;
}


//@edu.umd.cs.findbugs.annotations.SuppressWarnings(value="SBSC_USE_STRINGBUFFER_CONCATENATION")
// Only used occasionally, so inefficient String processing not really a problem
// though it would be good to fix it if you're working in this area
/*public*/ QString DefaultSignalSystem::toString()
{
    QString retval = "SignalSystem "+getSystemName()+"\n";
    QStringListIterator e1 (getAspects());
    while (e1.hasNext()) {
        QString s1 = e1.next();
        retval += "  "+s1+"\n";
        QStringListIterator e2(getKeys());
        while (e2.hasNext()) {
            QString s2 = e2.next();
            retval += "    "+s2+": "+getProperty(s1, s2).toString()+"\n";
        }
    }
    return retval;
}

//    static org.apache.log4j.Logger log = org.apache.log4j.Logger.getLogger(DefaultSignalSystem.class.getName());
//}
