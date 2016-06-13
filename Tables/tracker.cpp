#include "tracker.h"
#include "oblock.h"
#include <QLinkedList>
#include <QDateTime>
#include "inputdialog.h"
#include "portal.h"
#include "opath.h"
#include "inputdialog.h"
#include <QMessageBox>

//Tracker::Tracker(QObject *parent) :
//  QObject(parent)
//{
//}
/**
 * Track an occupied block to its adjacent blocks.
 *
 * @version $Revision: 22833 $
 * @author	Pete Cressman Copyright (C) 2013
 */
///*public*/ class Tracker {

//	OBlock _currentBlock;
//	OBlock _prevBlock;

    /**
     * Must Call setupCheck() after constructor to check environment of train
     *
     * @param block
     * @param name
     */
    Tracker::Tracker(OBlock* block, QString name, QObject *parent) :
      QObject(parent)
    {
     log = new Logger("Tracker");
        _trainName = name;
        _occupies =  QLinkedList<OBlock*>();
        _markerForeground = block->getMarkerForeground();
        _markerBackground = block->getMarkerBackground();
        _markerFont = block->getMarkerFont();
        _occupies.push_front(block);
        _time = /*System.currentTimeMillis();*/QDateTime::currentMSecsSinceEpoch();
        block->_entryTime = _time;
        showBlockValue(block);
    }

    /**
     * Creator of a tracker must call immediately after constructor to verify
     * the blocks occupied by the train at start. _occupies should contain
     * exactly one block->
     */
    /*public*/ void Tracker::setupCheck() {
        if (log->isDebugEnabled()) {
            log->debug("setupCheck() for \"" + _trainName + "\"");
        }
        QList<OBlock*> adjacentBlocks = makeRange();
        QList<OBlock*> occupy =  QList<OBlock*>();
        QListIterator<OBlock*> it(adjacentBlocks);
        while (it.hasNext()) {
            OBlock* b = it.next();
            if (b!=(getHeadBlock()) && b->getValue() == QVariant() && (b->getState() & OBlock::OCCUPIED) != 0) {
                occupy.append(b);
            }
        }
        if (occupy.size() > 0) {
            QVector<QString> blocks = QVector<QString>(occupy.size() + 1);
            QListIterator<OBlock*> iter( occupy);
            int i = 0;
            blocks.replace(i++, tr("none"));
            while (iter.hasNext())
            {
                blocks.replace(i++,  iter.next()->getDisplayName());
            }
            QVariant* selection;
//            Object selection = JOptionPane.showInputDialog(NULL,
//                    tr("MultipleStartBlocks", _occupies.peekFirst().getDisplayName(), _trainName),
//                    tr("WarningTitle"), JOptionPane.INFORMATION_MESSAGE, NULL, blocks, NULL);
            InputDialog* dlg = new InputDialog(tr("\" occupies block \"%1\". However adjacent are also occupied.\n Please select any additional block (or none) that train \"%2\" occupies.").arg(_occupies.first()->getDisplayName()).arg(_trainName),"");
            iter = QListIterator<OBlock*>(occupy);
            while (iter.hasNext()) {
                OBlock* b = iter.next();
                if (b->getDisplayName()==(selection->toString())) {
                    showBlockValue(b);
                    _occupies.append(b);	// make additional block the tail
                    _headPortal = getPortalBetween(getHeadBlock(), getTailBlock());
                    _tailPortal = _headPortal;
                    break;
                }
            }
            makeRange();
        }
    }

    /*
     * Jiggle state so Indicator icons show block value
     */
    /*private*/ void Tracker::showBlockValue(OBlock* block) {
        block->setValue(_trainName);
        block->setMarkerBackground(_markerBackground);
        block->setMarkerForeground(_markerForeground);
        block->setMarkerFont(_markerFont);
        block->setState(block->getState() | OBlock::RUNNING);
    }

    /*protected*/ QString Tracker::getTrainName() {
        return _trainName;
    }

    /*final*/ /*protected*/ OBlock* Tracker::getHeadBlock() {
        return _occupies.first();
    }

    /*final*/ /*protected*/ OBlock* Tracker::getTailBlock() {
        return _occupies.last();
    }

    /*protected*/ QString Tracker::getStatus() {
        long et = (/*System.currentTimeMillis()*/QDateTime::currentMSecsSinceEpoch() - _time) / 1000;
        if (getHeadBlock() == NULL) {
            return tr("Location of \"%1\" not known. ").arg( _trainName);
        }
        return tr("Train \"%1\" has occupied block \"%2\" for %3 minutes %4 seconds.").arg( _trainName).arg( getHeadBlock()->getDisplayName()).arg( et / 60).arg( et % 60);
    }

    /*static*/ /*private*/ Portal* Tracker::getPortalBetween(OBlock* blkA, OBlock* blkB) {
     Logger* log = new Logger("Tracker");
        QList<Portal*> listA = blkA->getPortals();
        QList<Portal*> list = QList<Portal*>();

        QListIterator<Portal*> iter(listA);
        while (iter.hasNext()) {
            Portal* p = iter.next();
            if (blkB==(p->getOpposingBlock(blkA))) {
                list.append(p);
            }
        }
        int size = list.size();
        if (size == 0) {
            Logger::error("No portal between blocks \"" + blkA->getDisplayName() + "\" and \""
                    + blkB->getDisplayName() + "\".");
            return NULL;
        }
        if (size > 1) {
            log->info(size + " portals between blocks \"" + blkA->getDisplayName() + "\" and \""
                    + blkB->getDisplayName() + "\".");
        }
        return list.at(0);
    }

    /**
     * Build array of blocks reachable from head and tail portals
     */
    /*private*/ QList<OBlock*> Tracker::makeRange() {
        if (log->isDebugEnabled()) {
            log->debug("Make range for \"" + _trainName + "\"");
        }
        _headRange =  QList<OBlock*>();
        _tailRange =  QList<OBlock*>();
        _lostRange =  QList<OBlock*>();
        OBlock* headBlock = getHeadBlock();
        OBlock* tailBlock = getTailBlock();
        if (_headPortal == NULL) {
            QList<Portal*> list = headBlock->getPortals();
            QListIterator<Portal*> iter(list);
            while (iter.hasNext()) {
                OBlock* b = iter.next()->getOpposingBlock(headBlock);
                addtoHeadRange(b);
            }
        } else {
            QList<OPath*>* pathList = _headPortal->getPathsWithinBlock(headBlock);
            QListIterator<OPath*> iter(*pathList);
            while (iter.hasNext()) {
                OPath* path = iter.next();
                Portal* p = path->getToPortal();
                OBlock* b = NULL;
                if (p != NULL && _headPortal!=(p)) {
                    b = p->getOpposingBlock(headBlock);
                } else {
                    p = path->getFromPortal();
                    if (p != NULL && _headPortal!=(p)) {
                        b = p->getOpposingBlock(headBlock);
                    }
                }
                addtoHeadRange(b);
            }
            pathList = _tailPortal->getPathsWithinBlock(tailBlock);
            iter = QListIterator<OPath*>(*pathList);
            while (iter.hasNext()) {
                OPath* path = iter.next();
                Portal* p = path->getToPortal();
                OBlock* b = NULL;
                if (p != NULL && _tailPortal!=(p)) {
                    b = p->getOpposingBlock(tailBlock);
                } else {
                    p = path->getFromPortal();
                    if (p != NULL && _tailPortal!=(p)) {
                        b = p->getOpposingBlock(tailBlock);
                    }
                }
                addtoTailRange(b);
            }
        }
        _time = QDateTime::currentMSecsSinceEpoch();
        if (log->isDebugEnabled()) {
            log->debug("   _headRange.size()= " + QString::number(_headRange.size()));
            log->debug("   _tailRange.size()= " + QString::number(_tailRange.size()));
            log->debug("   _lostRange.size()= " + QString::number(_lostRange.size()));
            log->debug("   _occupies.size()= " + QString::number(_occupies.size()));
        }

        return getRange();
    }

    /*private*/ void Tracker::addtoHeadRange(OBlock* b) {
        if (b != NULL && !_headRange.contains(b) && !_occupies.contains(b)) {
            if ((b->getState() & OBlock::OCCUPIED) == 0) {
                _headRange.append(b);
            } else {
                _lostRange.append(b);
                if (log->isDebugEnabled()) {
                    log->debug("Adjacent block \"" + b->getDisplayName() + "\" is already occupied.  Tracking of \""
                            + _trainName + "\" from headBlock= \"" + getHeadBlock()->getDisplayName() + "\" may fail to be accurate.");
                }
            }
        }
    }

    /*private*/ void Tracker::addtoTailRange(OBlock* b) {
        if (b != NULL && !_tailRange.contains(b) && !_occupies.contains(b)) {
            if ((b->getState() & OBlock::OCCUPIED) == 0) {
                _tailRange.append(b);
            } else {
                _lostRange.append(b);
                if (log->isDebugEnabled()) {
                    log->debug("Adjacent block \"" + b->getDisplayName() + "\" is already occupied.  Tracking of \""
                            + _trainName + "\" from tailBlock= \"" + getTailBlock()->getDisplayName() + "\" may fail to be accurate.");
                }
            }
        }
    }

    /**
     * Note: Caller will modify List
     */
    /*protected*/ QList<OBlock*> Tracker::getRange() {
        QList<OBlock*> range =  QList<OBlock*>();
        if (log->isDebugEnabled()) {
            log->debug("Get range for \"" + _trainName + "\"");
        }
        if (_occupies.isEmpty() || _occupies.size() == 0) {
            return range;
        }
        QLinkedListIterator<OBlock*> it(_occupies);
        while (it.hasNext()) {
            OBlock* b = it.next();
            range.append(b);
            if (log->isDebugEnabled()) {
                log->debug("   " + b->getDisplayName() + " value= " + b->getValue().toString());
            }
        }
        if (log->isDebugEnabled()) {
            log->debug("_headRange for headBlock= " + getHeadBlock()->getDisplayName());
        }
        {
        QListIterator<OBlock*> it(_headRange);
        while (it.hasNext()) {
            OBlock* b = it.next();
            range.append(b);
            if (log->isDebugEnabled()) {
                log->debug("   " + b->getDisplayName() + " value= " + b->getValue().toString());
            }
        }
        if (log->isDebugEnabled()) {
            log->debug("_tailRange for tailBlock= " + getTailBlock()->getDisplayName());
        }
        it = QListIterator<OBlock*>(_tailRange);
        while (it.hasNext()) {
            OBlock* b = it.next();
            range.append(b);
            if (log->isDebugEnabled()) {
                log->debug("   " + b->getDisplayName() + " value= " + b->getValue().toString());
            }
        }
        it = QListIterator<OBlock*>(_lostRange);
        while (it.hasNext()) {
            OBlock* b = it.next();
            range.append(b);
            if (log->isDebugEnabled()) {
                log->debug("   " + b->getDisplayName() + " value= " + b->getValue().toString());
            }
        }
     }
     return range;
    }

    /*protected*/ QLinkedList<OBlock*> Tracker::getBlocksOccupied() {
        return _occupies;
    }

    /*protected*/ void Tracker::removeBlock(OBlock* block) {
        _occupies.removeOne(block);
        QList<Portal*> list = block->getPortals();
        QListIterator<Portal*> iter(list);
        while (iter.hasNext()) {
            OBlock* b = iter.next()->getOpposingBlock(block);
            if ((b->getState() & OBlock::DARK) !=0) {
                _occupies.removeOne(b);
                removeName(b);
                _lostRange.append(b);  // needed to find on recovery
            }
        }
        removeName(block);
    }
    /*private*/ void Tracker::removeName(OBlock* block) {
        if (_trainName==(block->getValue())) {
         block->setValue(QVariant());
            block->setState(block->getState() & ~OBlock::RUNNING);
        }
    }

    /*protected*/ int Tracker::move(OBlock* block, int state) {
        if (log->isDebugEnabled()) {
            log->debug("move( " + block->getDisplayName() + ", " + QString::number(state)+")");
        }
        if ((state & OBlock::OCCUPIED) != 0) {
            if (_occupies.contains(block)) {
                if (log->isDebugEnabled()) {
                    log->debug("Block \"" + block->getDisplayName() + "\" already occupied by \"" + _trainName + "\"!");
                }
            }
            if (_lostRange.contains(block)) {
                if (log->isDebugEnabled()) {
                    log->debug("\"" + _trainName + "\" should not be listening to block \"" + block->getDisplayName() + "\"");
                }
            }
            if (_headRange.contains(block)) {
                _headPortal = getPortalBetween(getHeadBlock(), block);
                _occupies.insert(_occupies.begin(), block);
                showBlockValue(block);
                if (_tailPortal == NULL) {
                    _tailPortal = _headPortal;
                }
            } else if (_tailRange.contains(block)) {
                _tailPortal = getPortalBetween(getTailBlock(), block);
                _occupies.append(block);
                showBlockValue(block);
                if (_headPortal == NULL) {
                    _headPortal = _tailPortal;
                }
            } else {
                return ERROR_BLOCK;
            }
            makeRange();
            return ENTER_BLOCK;
        } else if ((state & OBlock::UNOCCUPIED) != 0) {
            if (_lostRange.contains(block)) {
                //OK, just do makeRange
            } else {
                if (!_occupies.contains(block)) {
                    // a different train can leave an adjacent block held in _lostRange.
                    if (log->isDebugEnabled()) {
                        log->debug("Block \"" + block->getDisplayName() + "\" is not occupied by \"" + _trainName + "\"!");
                    }
                    return ERROR_BLOCK;
                }
            }
            removeBlock(block);
            int size = _occupies.size();
            if (size == 0) {
                Logger::error("\"" + block->getDisplayName() + "\", going inactive, is last block occupied by \"" + _trainName + "\"!");
                if (recovery(block)) {
                    return ENTER_BLOCK;
                }
                return NO_BLOCK;
            } else if (size == 1) {
                _headPortal = NULL;
                _tailPortal = NULL;
            } else {
#if 0
                _headPortal = getPortalBetween(_occupies.at(1), _occupies.getFirst());
                _tailPortal = getPortalBetween(_occupies.get(size - 2), _occupies.getLast());
#endif
            }
            makeRange();
            return LEAVE_BLOCK;
        }
        return NO_BLOCK;
    }

    /**
     * Called when _occupies is empty
     *
     * @param block
     * @return
     */
    /*private*/ bool Tracker::recovery(OBlock* block) {
        if (_occupies.size()==0) {
         QListIterator<OBlock*> it(_headRange);
            while (it.hasNext()) {
                OBlock* b = it.next();
                if ((b->getState() & (OBlock::DARK | OBlock::OCCUPIED)) != 0) {
                    _lostRange.append(b);
                    if (log->isDebugEnabled()) {
                        log->debug("  _lostRange.add " + b->getDisplayName() + " value= " + b->getValue().toString());
                    }
                }
            }
            it = QListIterator<OBlock*>(_tailRange);
            while (it.hasNext()) {
                OBlock* b = it.next();
                if ((b->getState() & (OBlock::DARK | OBlock::OCCUPIED)) != 0) {
                    _lostRange.append(b);
                    if (log->isDebugEnabled()) {
                        log->debug("  _lostRange.add " + b->getDisplayName() + " value= " + b->getValue().toString());
                    }
                }
            }
        }
        if (log->isDebugEnabled()) {
            log->debug("recovery( " + block->getDisplayName() + ") + _lostRange.size()= "+ QString::number(_lostRange.size()));
        }
        if (!_lostRange.isEmpty() || _lostRange.size() == 0) {
            return false;
        }
        OBlock* blk;
//          = (OBlock*) JOptionPane.showInputDialog(NULL, tr("TrackerNoCurrentBlock",
//                _trainName, block->getDisplayName()) + "\n" + tr("PossibleLocation"),
//                tr("WarningTitle"), JOptionPane.INFORMATION_MESSAGE, NULL,
//                _lostRange.toArray(), NULL);
          QMessageBox::information(NULL, tr("Info"), tr("\"%1\" unknown. Its last known location at \"%2\" is unoccupied.").arg(_trainName).arg(block->getDisplayName()));
        if (blk != NULL) {
            _occupies.prepend( blk);
            showBlockValue(blk);
        } else {
            return false;
        }
        setupCheck();
        return true;
    }

    /*public*/ QString Tracker::toString() {
        return _trainName;
    }

