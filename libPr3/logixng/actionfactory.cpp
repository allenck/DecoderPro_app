#include "actionfactory.h"
#include "categorydisplay.h"
#include <QSet>
#include <QMap>
#include "categoryloconet.h"

/**
 * The factory for LogixNG Display classes.
 *
 * @author Daniel Bergqvist Copyright 2021
 */
//@ServiceProvider(service = DigitalActionFactory.class)
///*public*/  class ActionFactory implements DigitalActionFactory {

    //@Override
    /*public*/  void ActionFactory::init() {
        CategoryDisplay::registerCategory();
    }

    //@Override
    /*public*/  QSet<QHash<Category, /*Class<? extends DigitalActionBean>*/QString>> ActionFactory::getActionClasses() {
        QSet<QHash<Category, /*Class<? extends DigitalActionBean>*/QString>> actionClasses = QSet<QHash<Category, /*Class<? extends DigitalActionBean>*/QString>> ();

        //actionClasses.insert(QHash<Category, QString> {{CategoryDisplay(), "jmri.jmrit.display.logixng.ActionPositionable"}});
        // We don't want to add these classes if we don't have a LocoNet connection
        if (CategoryLocoNet::hasLocoNet()) {
            actionClasses.insert(QHash<Category, QString> {{CategoryLocoNet::LOCONET, "jmri.jmrit.logixng.actions.ActionClearSlots"}});
            actionClasses.insert(QHash<Category, QString> {{CategoryLocoNet::LOCONET, "jmri.jmrit.logixng.actions.ActionUpdateSlots"}});
        }
        return actionClasses;
    }
