#ifndef TRANSIT_H
#define TRANSIT_H
#include "abstractnamedbean.h"
#include "logger.h"
#include "exceptions.h"

class LayoutEditor;
class Block;
class Section;
class TransitSection;
class Transit : public AbstractNamedBean
{
    Q_OBJECT
public:
    //explicit Transit(QObject *parent = 0);
    /**
     * Constants representing the state of the Transit.
     * A Transit can be either:
     *     IDLE - available for assignment to an ActiveTrain, or
     *     ASSIGNED - assigned to an ActiveTrain
     */
    enum STATE
    {
    IDLE = 0x02,
    ASSIGNED = 0x04
    };
    /*public*/ Transit(QString systemName, QString userName="", QObject *parent = 0);
    /*public*/ int getState();
    /*public*/ void setState(int state);
    /*public*/ void addTransitSection(TransitSection* s);
    /*public*/ QList<TransitSection *> getTransitSectionList();
    /*public*/ int getMaxSequence();
    /*public*/ void removeAllSections();
    /*public*/ bool containsSection(Section* s);
    /*public*/ QList<Section *> getSectionListBySeq(int seq);
    /*public*/ QList<TransitSection *> getTransitSectionListBySeq(int seq);
    /*public*/ QList<int>* getSeqListBySection(Section* s);
    /*public*/ bool containsBlock(Block* b);
    /*public*/ int getBlockCount(Block* b);
    /*public*/ Section* getSectionFromBlockAndSeq(Block* b, int seq);
    /*public*/ Section* getSectionFromConnectedBlockAndSeq(Block* b, int seq);
    /*public*/ int getDirectionFromSectionAndSeq(Section* s, int seq);
    /*public*/ TransitSection* getTransitSectionFromSectionAndSeq(Section* s, int seq);
    /*public*/ QList<Block*>* getInternalBlocksList();
    /*public*/ QList<int>* getBlockSeqList();
    /*public*/ bool canBeResetWhenDone();
    /*public*/ QList<Block*>* getEntryBlocksList();
    /*public*/ QList<Block*>* getDestinationBlocksList(Block* startBlock, bool startInTransit);
    /*public*/ QList<int>* getDestBlocksSeqList();
    /*public*/ int checkSignals(LayoutEditor* panel);
    /*public*/ int validateConnectivity(LayoutEditor* panel);
    /*public*/ int initializeBlockingSensors();
    /*public*/ void removeTemporarySections();
    /*public*/ bool removeLastTemporarySection(Section* s);
    /*public*/ QString getBeanType() override;
    /*public*/ QList<NamedBeanUsageReport*>* getUsageReport(NamedBean* bean) override;
    /*public*/ void vetoableChange(PropertyChangeEvent* evt)  /*throw (PropertyVetoException)*/ override;

signals:
    
public slots:
private:
 Logger* log;
 /**
  *  Instance variables (not saved between runs)
  */
 /*private*/ int mState;// = Transit.IDLE;
 /*private*/ QList<TransitSection*>* mTransitSectionList;// = new ArrayList<TransitSection>();
 /*private*/ int mMaxSequence;// = 0;
 /*private*/ QList<int>* blockSecSeqList;// = new ArrayList<Integer>();
 /*private*/ QList<int>* destBlocksSeqList;// = new ArrayList<Integer>();

};

#endif // TRANSIT_H
