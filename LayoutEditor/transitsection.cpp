#include "transitsection.h"
#include "instancemanager.h"

//TransitSection::TransitSection(QObject *parent) :
//    QObject(parent)
//{
//}
/**
 * This class holds information and options for a Section when assigned to a Transit. 
 * Corresponds to an allocatable "Section" of track assigned to a Transit.
 * <P>
 * A TransitSection holds the following information: 
 *  Section ID
 *  Section Direction 
 *  Sequence number of Section within the Transit
 *  Special actions list for train in this Section, if requested (see TransitSectionAction.java)
 *  Whether this Section is a primary section or an alternate section
 * <P>
 * A TransitSection is referenced via a list in its parent Transit, and is 
 *	stored on disk when its parent Transit is stored.
 * <P>
 * Provides for delayed initializatio of Section when loading panel files, so that this is not 
 *	dependent on order of items in the panel file.
 *
 * @author	Dave Duchamp  Copyright (C) 2008
 * @version	$Revision: 19233 $
 */
///*public*/ class TransitSection {

/**
 * Main constructor method
 */
/*public*/ TransitSection::TransitSection(Section* s, int seq, int direction, QObject *parent) : QObject(parent)
{
    common();
    mSection = s;
    mSequence = seq;
    mDirection = direction;
}

/** 
 * Convenience constructor
 */
/*public*/ TransitSection::TransitSection(Section* s, int seq, int direction, bool alt, QObject *parent) : QObject(parent){
    common();
    mSection = s;
    mSequence = seq;
    mDirection = direction;
    mAlternate = alt;
}

/**
 * Special constructor to delay Section initialization
 */
/*public*/ TransitSection::TransitSection(QString secName, int seq, int direction, bool alt, QObject *parent) : QObject(parent){
    common();
    tSectionName = secName;
    mSequence = seq;
    mDirection = direction;
    mAlternate = alt;
    needsInitialization = true;
}
void TransitSection::common()
{
    log = new Logger("TransitSection");
 // instance variables
 mSection = NULL;
 mSequence = 0;
 mDirection = 0;
 // mTransitSectionActionList = new ArrayList<TransitSectionAction>();
 mAlternate = false;

 // temporary variables and method for delayed initialization of Section
 tSectionName = "";
 needsInitialization = false;
}
/*private*/ void TransitSection::initialize() 
{
    if (tSectionName == "NULL")
    {
        log->error("Null Section Name when initializing a TransitSection");
    }
    else {                
        mSection = InstanceManager::sectionManagerInstance()->getSection(tSectionName);
        if (mSection==NULL)
            log->error("Missing Section - "+tSectionName+" - when initializing a TransitSection");
    }
    needsInitialization = false;
}

/**
 * Access methods
 */
/*public*/ Section* TransitSection::getSection() { 
    if (needsInitialization) initialize();
    return mSection; 
}
/*public*/ QString TransitSection::getSectionName() {
    if (needsInitialization) initialize();
    QString s = mSection->getSystemName();
    QString u = mSection->getUserName();
    if ( (u!=NULL) && (u!= "") ) {
        return (s+"( "+u+" )");
    }
    return s;
}
// Note: once TransitSection is created, Section and its sequence and direction may not be changed.
/*public*/ int TransitSection::getDirection() { return mDirection; }
/*public*/ int TransitSection::getSequenceNumber() { return mSequence; }
// /*public*/ void addAction( TransitSectionAction act ) { mTransitSectionActionList.add(act); }
/*public*/ bool TransitSection::isAlternate() { return mAlternate; }
/*public*/ void TransitSection::setAlternate( bool alt )	{ mAlternate = alt; }
#if 0 // TODO:
/** 
 * Get a copy of this TransitSection's TransitSectionAction list
 */
/*public*/ ArrayList<TransitSectionAction> getTransitSectionActionList() {
    ArrayList<TransitSectionAction> list = new ArrayList<TransitSectionAction>();
    for (int i = 0; i<mTransitSectionActionList.size(); i++)
        list.add(mTransitSectionActionList.get(i));
    return list;
}
#endif

//static org.apache.log4j.Logger log = org.apache.log4j.Logger.getLogger(TransitSection.class.getName());
//}
