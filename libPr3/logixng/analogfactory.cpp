#include "analogfactory.h"
#include "analogexpressionanalogio.h"
class Base;
/**
 * The factory for DigitalAction classes.
 */
//@ServiceProvider(service = AnalogExpressionFactory.class)
//public class AnalogFactory implements AnalogExpressionFactory {

    //@Override
    /*public*/ QSet<QHash<Category, /*Class<? extends Base>*/QString> > AnalogFactory::getClasses() {
        QSet<QHash<Category, /*Class<? extends Base>>*/QString > > analogActionClasses = QSet<QHash<Category, /*Class<? extends Base>>*/QString> >();
        analogActionClasses.insert(QHash<Category, QString> {{Category::ITEM, "jmri.jmrit.actions.configurexml.AnalogActionLightIntensity"}});
        analogActionClasses.insert(QHash<Category, QString> {{Category::ITEM, "jmri.jmrit.actions.configurexml.AnalogActionMemory"}});
        analogActionClasses.insert(QHash<Category, QString> {{Category::COMMON, "jmri.jmrit.actions.configurexml.AnalogMany"}});
        return analogActionClasses;
    }
