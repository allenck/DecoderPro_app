#include "blockcontentsicon.h"
#include "loggerfactory.h"
#include "positionablepopuputil.h"
#include "transferhandler.h"
#include "editor.h"
#include "instancemanager.h"
#include "jtextfield.h"
#include "joptionpane.h"
#include "throttlemanager.h"
#include "dcclocoaddress.h"
#include "rosterentry.h"
#include "abstractaction.h"
#include "dispatcherframe.h"
#include "activetrain.h"
#include "throttleframemanager.h"
#include "throttlewindow.h"
#include "addresspanel.h"
#include "activatetrainframe.h"

/**
 * An icon to display the value contained within a Block.<P>
 *
 * @author Bob Jacobsen Copyright (c) 2004
 */
// /*public*/ class BlockContentsIcon extends MemoryIcon implements java.beans.PropertyChangeListener {


/**
 * {@inheritDoc}
 */
/*public*/ BlockContentsIcon::BlockContentsIcon(QString s, Editor* editor, QObject* parent) : MemoryIcon(s, editor, parent){
    //super(s, editor);
    common();
    resetDefaultIcon();
    _namedIcon = defaultIcon;
    //By default all text objects are left justified
    _popupUtil->setJustification(LEFT);
//    this->setTransferHandler(new TransferHandler());
}

/*public*/ BlockContentsIcon::BlockContentsIcon(NamedIcon* s, Editor* editor, QObject* parent) :MemoryIcon(s, editor, parent){
    //super(s, editor);
    common();
    setDisplayLevel(Editor::LABELS);
    defaultIcon = s;
    _popupUtil->setJustification(LEFT);
    log->debug(QString("BlockContentsIcon ctor= ") + "BlockContentsIcon");
//    this->setTransferHandler(new TransferHandler());
}

void BlockContentsIcon::common()
{
 defaultIcon = NULL;
 map = NULL;

}

//@Override
/*public*/ Positionable* BlockContentsIcon::deepClone() {
    BlockContentsIcon* pos = new BlockContentsIcon("", _editor);
    return finishClone(pos);
}

/*protected*/ Positionable* BlockContentsIcon::finishClone(BlockContentsIcon* pos) {
    pos->setBlock(namedBlock);
    pos->setOriginalLocation(getOriginalX(), getOriginalY());
    if (map != NULL) {
        QStringListIterator iterator(map->keys());
        while (iterator.hasNext()) {
            QString key = iterator.next();
            QString url = map->value(key)->getName();
            pos->addKeyAndIcon(NamedIcon::getIconByName(url), key);
        }
    }
    return MemoryIcon::finishClone(pos);
}

//@Override
/*public*/ void BlockContentsIcon::resetDefaultIcon()
{
    defaultIcon = new NamedIcon(":/resources/icons/misc/X-red.gif",
            "resources/icons/misc/X-red.gif");
}

/**
 * Attached a named Block to this display item
 *
 * @param pName Used as a system/user name to lookup the Block object
 */
/*public*/ void BlockContentsIcon::setBlock(QString pName) {
    if (InstanceManager::getNullableDefault("BlockManager") != NULL) {
        Block* block = ((BlockManager*)InstanceManager::getDefault("BlockManager"))->
                provideBlock(pName);
        setBlock(((NamedBeanHandleManager*)InstanceManager::getDefault("NamedBeanHandleManager"))->getNamedBeanHandle(pName, block));
    } else {
        log->error("No Block Manager for this protocol, icon won't see changes");
    }
    updateSize();
}

/**
 * Attached a named Block to this display item
 *
 * @param m The Block object
 */
/*public*/ void BlockContentsIcon::setBlock(NamedBeanHandle<Block*>* m) {
    if (namedBlock != NULL) {
        //getBlock()->removePropertyChangeListener(this);
     disconnect(getBlock(), SIGNAL(propertyChange(PropertyChangeEvent*)));
    }
    namedBlock = m;
    if (namedBlock != NULL) {
        //getBlock()->addPropertyChangeListener(this, namedBlock.getName(), "Block Icon");
     connect(getBlock(), SIGNAL(propertyChange(PropertyChangeEvent*)), this, SLOT());
        displayState();
        setName(namedBlock->getName());
    }
}

/*public*/ NamedBeanHandle<Block*>* BlockContentsIcon::getNamedBlock() {
    return namedBlock;
}

/*public*/ Block* BlockContentsIcon::getBlock() {
    if (namedBlock == NULL) {
        return NULL;
    }
    return namedBlock->getBean();
}

//@Override
/*public*/ NamedBean* BlockContentsIcon::getNamedBean() {
    return getBlock();
}

//@Override
/*public*/ QMap<QString, NamedIcon*>* BlockContentsIcon::getMap()
{
    return map;
}

//@Override
/*public*/ QString BlockContentsIcon::getNameString() {
    QString name;
    if (namedBlock == NULL) {
        name = tr("<Not connected>");
    } else if (getBlock()->getUserName() != NULL) {
        name = getBlock()->getUserName() + " (" + getBlock()->getSystemName() + ")";
    } else {
        name = getBlock()->getSystemName();
    }
    return name;
}

//@Override
/*public*/ bool BlockContentsIcon::showPopUp(QMenu* popup) {
    if (isEditable() && selectable) {
        popup->addSeparator();

        QStringListIterator iterator(map->keys());
        while (iterator.hasNext()) {
            QString key = iterator.next();
            //String value = ((NamedIcon)map.get(key)).getName();
            AbstractAction* act;
            QSignalMapper* mapper = new QSignalMapper();
            popup->addAction(act = new AbstractAction(key, this));
            mapper->setMapping(act, key);
            connect(act, SIGNAL(triggered(bool)), mapper, SLOT(map()));

//            {
//                //@Override
//                /*public*/ void actionPerformed(ActionEvent e) {
//                    String key = e.getActionCommand();
//                    setValue(key);
//                }
//            });
              connect(mapper, SIGNAL(mapped(QString)), this, SLOT(setValue(QString)));
        }
        return true;
    }  // end of selectable
    if (re != NULL)
    {
     QAction* act;
        popup->addAction(act = new AbstractAction("Open Throttle",this));
//        {
//            //@Override
//            /*public*/ void actionPerformed(ActionEvent e) {
//                ThrottleFrame tf = InstanceManager.getDefault(ThrottleFrameManager.class).createThrottleFrame();
//                tf.toFront();
//                tf.getAddressPanel().setRosterEntry(re);
//            }
//        });
        connect(act, SIGNAL(triggered()), this, SLOT(on_newThrottle()));

        /*final*/ df = (DispatcherFrame*) InstanceManager::getNullableDefault("DispatcherFrame");
        if (df != NULL) {
            /*final*/  at = df->getActiveTrainForRoster(re);
            if (at != NULL) {
             QAction* terminateTrain;
                popup->addAction(terminateTrain = new AbstractAction(tr("Terminate Train"),this));
//                {
//                    //@Override
//                    /*public*/ void actionPerformed(ActionEvent e) {
//                        df.terminateActiveTrain(at);
//                    }
//                });
                connect(terminateTrain, SIGNAL(triggered()), this, SLOT(on_terminateTrain_triggered()));
                QAction* extraSections;
                popup->addAction(extraSections =new AbstractAction(tr("Allocate Extra Sections"), this));
//                {
//                    //@Override
//                    /*public*/ void actionPerformed(ActionEvent e) {
//                        //Just brings up the standard allocate extra frame, this could be expanded in the future
//                        //As a point and click operation.
//                        df.allocateExtraSection(e, at);
//                    }
//                });
                  connect(extraSections, SIGNAL(triggered(bool)), this, SLOT(on_extraSections_triggered()));
                if (at->getStatus() == ActiveTrain::DONE) {
                 QAction* restart;
                    popup->addAction(restart = new AbstractAction("Restart", this));
//                    {
//                        //@Override
//                        /*public*/ void actionPerformed(ActionEvent e) {
//                            at.allocateAFresh();
//                        }
//                    });
                    connect(restart, SIGNAL(triggered()), this, SLOT(on_restart_triggered()));
                }
            } else {
             QAction* newTrain;
                popup->addAction(newTrain = new AbstractAction(tr("Create New Train"),this));
//                {
//                    //@Override
//                    /*public*/ void actionPerformed(ActionEvent e) {
//                        if (!df.getNewTrainActive()) {
//                            df.getActiveTrainFrame().initiateTrain(e, re, getBlock());
//                            df.setNewTrainActive(true);
//                        } else {
//                            df.getActiveTrainFrame().showActivateFrame(re);
//                        }
//                    }

//                });
                connect(newTrain, SIGNAL(triggered(bool)), this, SLOT(on_newTrain_triggered()));

            }
        }
        return true;
    }
    return false;
}

void BlockContentsIcon::on_newThrottle()
{
 ThrottleWindow* tf = ((ThrottleFrameManager*) InstanceManager::getDefault("ThrottleFrameManager"))->createThrottleFrame();
 tf->toFront();
 tf->getAddressPanel()->setRosterEntry(re);

}
void BlockContentsIcon::on_terminateTrain_triggered()
{
 df->terminateActiveTrain(at);
}

void BlockContentsIcon::on_extraSections_triggered()
{
 df->allocateExtraSection(NULL,at);
}

void BlockContentsIcon::on_restart_triggered()
{
 at->allocateAFresh();
}

void BlockContentsIcon::on_newTrain_triggered()
{
 if (!df->getNewTrainActive()) {
     df->getActiveTrainFrame()->initiateTrain(NULL, re, getBlock());
     df->setNewTrainActive(true);
 } else {
     df->getActiveTrainFrame()->showActivateFrame(re);
 }

}
/**
 * Text edits cannot be done to Block text - override
 */
//@Override
/*public*/ bool BlockContentsIcon::setTextEditMenu(QMenu* popup) {
 QAction* editBlockValue;
    popup->addAction(editBlockValue = new AbstractAction(tr("Edit Block Value"),this));
//    {
//        //@Override
//        /*public*/ void actionPerformed(ActionEvent e) {
//            editBlockValue();
//        }
//    });
    connect(editBlockValue, SIGNAL(triggered()), this, SLOT(editBlockValue()));
    return true;
}

/**
 * Drive the current state of the display from the state of the Block Value
 */
//@Override
/*public*/ void BlockContentsIcon::displayState() {
    if (log->isDebugEnabled()) {
        log->debug("displayState");
    }
    if (namedBlock == NULL) {  // use default if not connected yet
        setIcon(defaultIcon);
        updateSize();
        return;
    }
    if (re != NULL) {
        InstanceManager::throttleManagerInstance()->removeListener(re->getDccLocoAddress(), (PropertyChangeListener*)this);
        re = NULL;
    }
    QVariant key = getBlock()->getValue();
    MemoryIcon::displayState(key);
}

//@Override
/*public*/ bool BlockContentsIcon::setEditIconMenu(QMenu* popup)
{
    QString txt = tr("Edit %1 Icon...").arg(tr("BeanNameBlock"));
    QAction* editIcon;
    popup->addAction(editIcon = new AbstractAction(txt, this));
//    {
//        //@Override
//        /*public*/ void actionPerformed(ActionEvent e) {
//            edit();
//        }
//    });
    connect(editIcon, SIGNAL(triggered()), this, SLOT(edit()));
}

//@Override
/*protected*/ void BlockContentsIcon::edit() {
    makeIconEditorFrame(this, "Block", true, NULL); // NOI18N
    _iconEditor->setPickList(PickListModel::blockPickModelInstance());
//    ActionListener addIconAction = new ActionListener() {
//        //@Override
//        /*public*/ void actionPerformed(ActionEvent a) {
//            editBlock();
//        }
//    };
    AddBCIconActionListener* addIconAction = new AddBCIconActionListener(this);

    _iconEditor->complete(addIconAction, false, true, true);
    _iconEditor->setSelection(getBlock());
}
AddBCIconActionListener::AddBCIconActionListener(BlockContentsIcon *icon) { this->icon = icon;}
void AddBCIconActionListener::actionPerformed() { icon->editBlock();}

void BlockContentsIcon::editBlock() {
    setBlock(_iconEditor->getTableSelection()->getDisplayName());
    updateSize();
    _iconEditorFrame->dispose();
    _iconEditorFrame = NULL;
    _iconEditor = NULL;
//    invalidate();
    updateScene();
}

//@Override
/*public*/ void BlockContentsIcon::dispose()
{
    if (getBlock() != NULL) {
        //getBlock()->removePropertyChangeListener(this);
     disconnect(getBlock(), SIGNAL(propertyChange(PropertyChangeEvent*)), this, SLOT(propertyChange(PropertyChangeEvent*)));
    }
    namedBlock = NULL;
    if (re != NULL) {
        InstanceManager::throttleManagerInstance()->removeListener(re->getDccLocoAddress(), (PropertyChangeListener*)this);
        re = NULL;
    }
    MemoryIcon::dispose();
}

//@Override
/*public*/ void BlockContentsIcon::mouseDoubleClickEvent(QMouseEvent* e)
{
 editBlockValue();
}

/*protected*/ void BlockContentsIcon::editBlockValue() {
    JTextField* newBlock = new JTextField(20);
    if (getBlock()->getValue() != QVariant()) {
        newBlock->setText(getBlock()->getValue().toString());
    }
    //Object[] options = {tr("ButtonCancel"), tr("ButtonOK"), newBlock};
    QVariantList options = QVariantList();
    options << tr("Cancel") << tr("Ok") << VPtr<JTextField>::asQVariant(newBlock);
    int retval = JOptionPane::showOptionDialog(this,
            tr("Edit Current Block Value"), namedBlock->getName(),
            0, JOptionPane::INFORMATION_MESSAGE, QIcon(),
            options, options.at(1));

    if (retval != 1) {
        return;
    }
    setValue(newBlock->text());
    updateSize();
}

//@Override
/*protected*/ QVariant BlockContentsIcon::getValue() {
    if (getBlock() == NULL) {
        return QVariant();
    }
    return getBlock()->getValue();
}

//@Override
/*protected*/ void BlockContentsIcon::setValue(QVariant val) {
    getBlock()->setValue(val);
}

/*private*/ /*final*/ /*static*/ Logger* BlockContentsIcon::log = LoggerFactory::getLogger("BlockContentsIcon");
