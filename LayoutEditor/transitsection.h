#ifndef TRANSITSECTION_H
#define TRANSITSECTION_H

#include <QObject>
#include "logger.h"

class TransitSectionAction;
class Section;
class TransitSection : public QObject
{
    Q_OBJECT
public:
    //explicit TransitSection(QObject *parent = 0);
    /*public*/ TransitSection(Section* s, int seq, int direction, QObject *parent);
    /*public*/ TransitSection(Section* s, int seq, int direction, bool alt, QObject *parent);
    /*public*/ TransitSection(QString secName, int seq, int direction, bool alt, QObject *parent);
    /*public*/ Section* getSection();
    /*public*/ QString getSectionName();
    /*public*/ int getDirection();
    /*public*/ int getSequenceNumber();
    // /*public*/ void addAction( TransitSectionAction act );
    /*public*/ bool isAlternate();
    /*public*/ void setAlternate( bool alt );
#if 0
    /** 
     * Get a copy of this TransitSection's TransitSectionAction list
     */
    /*public*/ ArrayList<TransitSectionAction> getTransitSectionActionList() {
#endif
signals:

public slots:
private:
    // instance variables
    /*private*/ Section* mSection;// = null;
    /*private*/ int mSequence;// = 0;
    /*private*/ int mDirection;// = 0;
    /*private*/ QList<TransitSectionAction>* mTransitSectionActionList;// = newQList<TransitSectionAction>();
    /*private*/ bool mAlternate;// = false;
    
    // temporary variables and method for delayed initialization of Section
    /*private*/ QString tSectionName;// = "";
    /*private*/ bool needsInitialization;// = false;
    /*private*/ void initialize();
    Logger* log;
    void common();
};

#endif // TRANSITSECTION_H
