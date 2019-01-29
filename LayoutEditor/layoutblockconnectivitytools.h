#ifndef LAYOUTBLOCKCONNECTIVITYTOOLS_H
#define LAYOUTBLOCKCONNECTIVITYTOOLS_H
#include "exceptions.h"
#include "logger.h"
#include "namedbean.h"
#include "block.h"
#include <QString>
#include "liblayouteditor_global.h"

class NamedBean;
class LayoutBlock;
class FacingProtecting;
class Block;
class LayoutEditor;
class BlocksTested;
class LIBLAYOUTEDITORSHARED_EXPORT LayoutBlockConnectivityTools : public QObject
{
 Q_OBJECT
public:
    LayoutBlockConnectivityTools();
    /**
     * Constant used in the getLayoutBlocks to represent a path from one Signal Mast
     * to another and that no mast should be in the path.
     */
    /*public*/ /*final*/const static int MASTTOMAST = 0x01;

    /**
     * Constant used in the getLayoutBlocks to represent a path from one Signal Head
     * to another and that no head should be in the path.
     */
    /*public*/ /*final*/const static int HEADTOHEAD = 0x02;

    /**
     * Constant used in the getLayoutBlocks to represent a path from one Sensor
     * to another and that no sensor should be in the path.
     */
    /*public*/ /*final*/ const static int SENSORTOSENSOR = 0x04;

    /**
     * Constant used in the getLayoutBlocks to represent a path from either
     * a Signal Mast or Head to another Signal Mast or Head and that no mast of
     * head should be in the path.
     */
    /*public*/ /*final*/const static int ANY = 0x08;

    /**
     * Constant used in the getLayoutBlocks to indicate that the the system should
     * not check for signal masts or heads on the path.
     */
    /*public*/ /*final*/const static int NONE = 0x00;


    /*public*/ /*final*/const static int HOPCOUNT = 0x00;
    /*public*/ /*final*/const static int METRIC = 0x01;
    /*public*/ /*final*/const static int DISTANCE = 0x02;
    /*public*/ bool checkValidDest(LayoutBlock* currentBlock, LayoutBlock* nextBlock, LayoutBlock* destBlock, LayoutBlock* destProBlock, int pathMethod) throw (JmriException);
    /*public*/ QList<NamedBean*> getBeansInPath(QList<LayoutBlock*> blocklist, LayoutEditor* panel, QString T);
    /*public*/ bool checkValidDest(NamedBean* sourceBean, NamedBean* destBean, int pathMethod) throw (JmriException);
    /*public*/ bool checkValidDest(LayoutBlock* currentBlock, LayoutBlock* nextBlock, LayoutBlock* destBlock, QList<LayoutBlock*> destBlockn1, int pathMethod) throw (JmriException);
    /*public*/ bool checkValidDest(LayoutBlock* facing, LayoutBlock* protecting, FacingProtecting* dest, int pathMethod) throw (JmriException);
    /*public*/ QList<LayoutBlock*> getLayoutBlocks(NamedBean* sourceBean, NamedBean* destBean, bool validateOnly, int pathMethod) throw (JmriException);
    /*public*/ QList<LayoutBlock*> getLayoutBlocks(LayoutBlock* sourceLayoutBlock, LayoutBlock* destinationLayoutBlock, LayoutBlock* protectingLayoutBlock, bool validateOnly, int pathMethod) throw (JmriException);
    /*public*/ QHash<NamedBean*, QList<NamedBean*> > discoverValidBeanPairs(LayoutEditor* editor, QString T, int pathMethod);
    /*public*/ QList<NamedBean*> discoverPairDest(NamedBean* source, LayoutEditor* editor, QString T, int pathMethod) throw (JmriException);
    QList<NamedBean*> discoverPairDest(NamedBean* source, LayoutBlock* lProtecting, LayoutBlock* lFacing, QList<FacingProtecting*> blockList, int pathMethod) throw (JmriException);
    QList<FacingProtecting*> generateBlocksWithBeans(LayoutEditor* editor, QString T);

private:
    /*private*/ static const int ttlSize = 50;
    /*private*/ bool canLBlockBeUsed(LayoutBlock* lBlock);
    QString lastErrorMessage;// = "Unknown Error Occured";
    int findBestHop(/*final*/ Block* preBlock, /*final*/ Block* currentBlock, Block* destBlock, int direction, QList<int> offSet, bool validateOnly, int pathMethod);
    /*private*/ bool checkForDoubleCrossover(Block* prevBlock, LayoutBlock* curBlock, Block* nextBlock);
    /*private*/ bool checkForLevelCrossing(LayoutBlock* curBlock);

 Logger* log;
};
/*static*/ class FacingProtecting : public QObject
{
    //Q_OBJECT
public:

    FacingProtecting(Block* facing, Block* protecting, NamedBean* bean){
        this->facing = facing;
        this->protecting = protecting;
        this->bean = bean;

    }

    Block* getFacing() { return facing; }

    Block* getProtecting() { return protecting; }

    NamedBean* getBean() { return bean; }

    //@Override
    /*public*/ bool equals(QObject* obj){
        if((FacingProtecting*)obj ==this)
            return true;
        if(obj ==NULL){
            return false;
        }

        if(!(this->metaObject()->className()==obj->metaObject()->className())){
            return false;
        }
        else{
            FacingProtecting* tmp = (FacingProtecting*)obj;
            if(tmp->getFacing()!=this->facing){
                return false;
            }
            if(tmp->getProtecting()!=this->protecting){
                return false;
            }
            if(tmp->getBean()!=this->bean){
                return false;
            }
        }
        return true;
    }

    //@Override
    /*public*/ int hashCode() {
        int hash = 7;
        hash = 37 * hash + (this->bean != NULL ? this->bean->hashCode() : 0);
        hash = 37 * hash + (this->facing != NULL ? this->facing->hashCode() : 0);
        hash = 37 * hash + (this->protecting != NULL ? this->protecting->hashCode() : 0);
        return hash;
    }
private:
    Block* facing;
    Block* protecting;
    NamedBean* bean;

};
/*static*/ class BlocksTested {

    LayoutBlock* block;
    QList<int> indexNumber;// =  QList<int>();

    BlocksTested(LayoutBlock* block){
        this->block=block;
        indexNumber = QList<int>();
    }

    void addIndex (int x){
        indexNumber.append(x);
    }

    int getLastIndex(){
        return indexNumber.at(indexNumber.size()-1); //get the last one in the list
    }

    QList<int> getTestedIndexes(){
        return indexNumber;
    }

    LayoutBlock* getBlock(){
        return block;
    }
    friend class LayoutBlockConnectivityTools;
};


#endif // LAYOUTBLOCKCONNECTIVITYTOOLS_H
