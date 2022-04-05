#include "actionfactory.h"
#include "categorydisplay.h"
#include <QSet>
#include <QMap>
#include "category.h"
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
    /*public*/  QSet<QHash<Category*, /*Class<? extends DigitalActionBean>*/QString>> ActionFactory::getActionClasses() {
        QSet<QHash<Category*, /*Class<? extends DigitalActionBean>*/QString>> actionClasses = QSet<QHash<Category*, /*Class<? extends DigitalActionBean>*/QString>> ();

        actionClasses.insert(QHash<Category*, QString> {{CategoryDisplay::DISPLAY, "jmri.jmrit.display.logixng.ActionPositionable"}});

        return actionClasses;
    }
