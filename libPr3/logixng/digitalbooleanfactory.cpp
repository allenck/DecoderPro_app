#include "digitalbooleanfactory.h"
#include <QHash>
#include <QSet>
/**
 * The factory for DigitalAction classes.
 */
//@ServiceProvider(service = DigitalBooleanActionFactory.class)
//public  class DigitalBooleanFactory implements DigitalBooleanActionFactory {

    //@Override
    /*public*/ QSet<QHash<Category, /*Class<? extends Base>*/QString>> DigitalBooleanFactory::getClasses() {
        QSet<QHash<Category, /*Class<? extends Base>*/QString>> digitalBooleanActionClasses = QSet<QHash<Category, /*Class<? extends Base>*/QString>>();
        digitalBooleanActionClasses.insert(QHash<Category, QString> {{Category::COMMON, "jmri.jmrit.logixng.actions.DigitalBooleanMany"}});
        digitalBooleanActionClasses.insert(QHash<Category, QString> {{Category::COMMON, "jmri.jmrit.logixng.actions.DigitalBooleanOnChange"}});
        return digitalBooleanActionClasses;
    }
