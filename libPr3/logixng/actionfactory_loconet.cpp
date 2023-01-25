#include "actionfactory_loconet.h"
#include "categoryloconet.h"
#include <QSet>

/**
 * The factory for LogixNG LocoNet classes.
 */
//@ServiceProvider(service = DigitalActionFactory.class)
///*public*/  class ActionFactory implements DigitalActionFactory {

    //@Override
    /*public*/  void ActionFactory_LocoNet::init() {
        CategoryLocoNet::registerCategory();
    }

    //@Override
    /*public*/  QSet<QHash<Category, /*Class<? extends DigitalActionBean>*/QString>> ActionFactory_LocoNet::getActionClasses() {
        QSet<QHash<Category, /*Class<? extends DigitalActionBean>*/QString>> actionClasses = QSet<QHash<Category, /*Class<? extends DigitalActionBean>*/QString>>();

        // We don't want to add these classes if we don't have a LocoNet connection
        if (CategoryLocoNet::hasLocoNet()) {
            actionClasses.insert(QHash<Category, QString> {{CategoryLocoNet(), "jmri.jmrit.loconet/logixng.ActionClearSlots"}});
            actionClasses.insert(QHash<Category, QString> {{CategoryLocoNet(), "jmri.jmrit.loconet/logixng.ActionUpdateSlots"}});
        }

        return actionClasses;
    }
