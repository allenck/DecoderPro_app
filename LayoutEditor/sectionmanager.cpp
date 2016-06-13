#include "sectionmanager.h"
#include "layouteditor.h"
#include "abstractsignalheadmanager.h"
#include "connectivityutil.h"

/*static*/ SectionManager* SectionManager::_instance = NULL;

SectionManager::SectionManager(QObject *parent) :
    AbstractManager(parent)
{
 setObjectName("SectionManager");
 lastAutoSectionRef = 0;
 paddedNumber = new DecimalFormat("0000");
 registerSelf();
}
/**
 * Basic Implementation of a SectionManager.
 * <P>
 * This doesn't have a "new" interface, since Sections are
 * independently implemented, instead of being system-specific.
 * <P>
 * Note that Section system names must begin with IY, and be followed by a
 * string, usually, but not always, a number. All alphabetic characters
 * in a Section system name must be upper case. This is enforced when a Section
 * is created.
 * <P>
 *
 * <hr>
 * This file is part of JMRI.
 * <P>
 * JMRI is free software; you can redistribute it and/or modify it under
 * the terms of version 2 of the GNU General Public License as published
 * by the Free Software Foundation. See the "COPYING" file for a copy
 * of this license.
 * <P>
 * JMRI is distributed in the hope that it will be useful, but WITHOUT
 * ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
 * FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License
 * for more details.
 * <P>
 * @author      Dave Duchamp Copyright (C) 2008
 * @version	$Revision: 18102 $
 */
//public class SectionManager extends AbstractManager
//    implements java.beans.PropertyChangeListener {

//    public SectionManager() {
//        super();
//    }

int SectionManager::getXMLOrder(){
    return Manager::SECTIONS;
}

QString SectionManager::getSystemPrefix() { return "I"; }
char SectionManager::typeLetter() { return 'Y'; }

/**
 * Method to create a new Section if the Section does not exist
 *   Returns NULL if a Section with the same systemName or userName
 *       already exists, or if there is trouble creating a new Section.
 */
Section* SectionManager::createNewSection(QString systemName, QString userName)
{
    // check system name
    if ( (systemName==NULL) || (systemName.length()<1) ) {
        // no valid system name entered, return without creating
        return NULL;
    }
    QString sysName = systemName;
    if ( (sysName.length()<2) || (sysName.mid(0,2)!=("IY")) )
    {
        sysName = "IY"+sysName;
    }
    // Check that Section does not already exist
    Section* y;
    if (!userName.isEmpty())
    {
        y = getByUserName(userName);
        if (y!=NULL) return NULL;
    }
    QString sName = sysName.toUpper().trimmed();
    y = getBySystemName(sysName);
    if (y==NULL) y = getBySystemName(sName);
    if (y!=NULL) return NULL;
    // Section does not exist, create a new Section
    y = new Section(sName,userName);
    // save in the maps
    Register(y);
    /*The following keeps trace of the last created auto system name.
    currently we do not reuse numbers, although there is nothing to stop the
    user from manually recreating them*/
    if (systemName.startsWith("IY:AUTO:")){
        try {
            bool bOk=false;
            int autoNumber = systemName.mid(8).toInt(&bOk);
            if(!bOk )throw new NumberFormatException();
            if (autoNumber > lastAutoSectionRef) {
                lastAutoSectionRef = autoNumber;
            }
        } catch (NumberFormatException e){
            log.warn("Auto generated SystemName "+ systemName + " is not in the correct format");
        }
    }
    return y;
}

Section* SectionManager::createNewSection(QString userName) {
    int nextAutoSectionRef = lastAutoSectionRef+1;
    QString b = "IY:AUTO:";
    QString nextNumber = paddedNumber->format(nextAutoSectionRef);
    b.append(nextNumber);
    return createNewSection(b, userName);
}



/**
 * Remove an existing Section
 */
/*public*/ void SectionManager::deleteSection(Section* y) {
    // delete the Section
    deregister(y);
    y->dispose();
}

/**
 * Method to get an existing Section.  First looks up assuming that
 *      name is a User Name.  If this fails looks up assuming
 *      that name is a System Name.  If both fail, returns NULL.
 */
/*public*/ Section* SectionManager::getSection(QString name) {
    Section* y = getByUserName(name);
    if (y!=NULL) return y;
    return getBySystemName(name);
}

/*public*/ Section* SectionManager::getBySystemName(QString name) {
    QString key = name.toUpper();
    return (Section*)_tsys->value(key);
}

/*public*/ Section* SectionManager::getByUserName(QString key) {
    return (Section*)_tuser->value(key);
}

/**
 * Validates all Sections
 */
/*public*/ int SectionManager::validateAllSections(JmriJFrame* /*frame*/, LayoutEditor* lePanel)
{
 QStringList list = getSystemNameList();
 int numSections = 0;
 int numErrors = 0;
 if (list.size()<=0) return -2;
 for (int i = 0; i<list.size(); i++)
 {
  QString s = getBySystemName(list.at(i))->validate(lePanel);
  if (s!=(""))
  {
   log.error(s);
   numErrors ++;
  }
  numSections ++;
 }
 if (log.isDebugEnabled()) log.debug("Validated "+QString::number(numSections)+" Sections - "+ QString::number(numErrors)+" errors or warnings.");
 return numErrors;
}

/**
 * Checks direction sensors in SSL for signals.
 * Returns '0' for no errors
 * Returns n, where n is a positive number for number of errors or warnings
 * Returns -1 if there is no LayoutEditor panel
 * Returns -2 if there are no Sections defined
 */
/*public*/ int SectionManager::setupDirectionSensors(LayoutEditor* lePanel)
{
 if (lePanel==NULL) return -1;
 QStringList list = getSystemNameList();
 int numSections = 0;
 int numErrors = 0;
 if (list.size()<=0) return -2;
 for (int i = 0; i<list.size(); i++)
 {
  int errors = getBySystemName(list.at(i))->placeDirectionSensors(lePanel);
  numErrors = numErrors + errors;
  numSections ++;
 }
 if (log.isDebugEnabled()) log.debug("Checked direction sensors for "+QString::number(numSections)+
                " Sections - "+QString::number(numErrors)+" errors or warnings.");
 return numErrors;
}

/**
 * Removes direction sensors from SSL for all signals.
 * Returns '0' for no errors
 * Returns n, where n is a positive number for number of errors or warnings
 * Returns -1 if there is no LayoutEditor panel
 * Returns -2 if there are no Sections defined
 */
/*public*/ int SectionManager::removeDirectionSensorsFromSSL(LayoutEditor* lePanel)
{
 if (lePanel==NULL) return -1;
 ConnectivityUtil* cUtil = lePanel->getConnectivityUtil();
 QStringList list = getSystemNameList();
 if (list.size()<=0) return -2;
 int numErrors = 0;
 QStringList sensorList =  QStringList();
 for (int i = 0; i<list.size(); i++)
 {
  Section* s = getBySystemName(list.at(i));
  QString name = s->getReverseBlockingSensorName();
  if ( (name!=NULL) && (name!=("")) )
   sensorList.append(name);
  name = s->getForwardBlockingSensorName();
  if ( (name!=NULL) && (name!=("")) )
   sensorList.append(name);
 }
 AbstractSignalHeadManager* shManager = (AbstractSignalHeadManager*)InstanceManager::signalHeadManagerInstance();
    QStringList signalList = shManager->getSystemNameList();
    for (int j=0; j<signalList.size(); j++)
    {
     SignalHead* sh = shManager->getBySystemName(signalList.at(j));
     if (!cUtil->removeSensorsFromSignalHeadLogic(&sensorList,	sh)) numErrors ++;
 }
 return numErrors;
}

/**
 * Initialize all blocking sensors that exist - sets them to 'ACTIVE'
 */
/*public*/ void SectionManager::initializeBlockingSensors () {
    QStringList list = getSystemNameList();
    for (int i = 0; i<list.size(); i++) {
        Section* s = getBySystemName(list.at(i));
        try {
            if (s->getForwardBlockingSensor()!=NULL) {
                s->getForwardBlockingSensor()->setState(Sensor::ACTIVE);
            }
            if (s->getReverseBlockingSensor()!=NULL) {
                s->getReverseBlockingSensor()->setState(Sensor::ACTIVE);
            }
        } catch (JmriException* reason) {
            log.error ("Exception when initializing blocking Sensors for Section "+s->getSystemName());
        }
    }
}

/*static*/ /*public*/ SectionManager* SectionManager::instance() {
    if (_instance == NULL) {
        _instance = new SectionManager();
    }
    return (_instance);
}


//static org.apache.log4j.Logger log = org.apache.log4j.Logger.getLogger(SectionManager.class.getName());
