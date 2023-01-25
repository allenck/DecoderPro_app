#include "analogfactory_expressions.h"
#include <QSet>
/**
 * The factory for DigitalAction classes.
 */
//@ServiceProvider(service = AnalogExpressionFactory.class)
// /*public*/ class AnalogFactory implements AnalogExpressionFactory {

    //@Override
    /*public*/ QSet<QHash<Category, /*Class<? extends Base>*/QString>> AnalogFactory_Expressions::getClasses() {
        QSet<QHash<Category, /*Class<? extends Base>*/QString>> analogExpressionClasses =  QSet<QHash<Category, /*Class<? extends Base>*/QString>> ();
        analogExpressionClasses.insert(QHash<Category, QString> {{Category::ITEM, ".jmri.jmrit.expressions.AnalogExpressionAnalogIO"}});
        analogExpressionClasses.insert(QHash<Category, QString> {{Category::ITEM, ".jmri.jmrit.expressions.AnalogExpressionConstant"}});
        analogExpressionClasses.insert(QHash<Category, QString> {{Category::ITEM, ".jmri.jmrit.expressions.AnalogExpressionMemory"}});
        analogExpressionClasses.insert(QHash<Category, QString> {{Category::COMMON, ".jmri.jmrit.expressions.AnalogFormula"}});
        analogExpressionClasses.insert(QHash<Category, QString> {{Category::ITEM, ".jmri.jmrit.expressions.TimeSinceMidnight"}});
        return analogExpressionClasses;
    }
