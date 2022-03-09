#include "analogfactory.h"
#include "analogexpressionanalogio.h"
class Base;
/**
 * The factory for DigitalAction classes.
 */
//@ServiceProvider(service = AnalogExpressionFactory.class)
//public class AnalogFactory implements AnalogExpressionFactory {

    //@Override
    /*public*/ QSet<QHash<Category*, /*Class<? extends Base>*/QString> > AnalogFactory::getClasses() {
        QSet<QHash<Category*, /*Class<? extends Base>>*/QString > > analogExpressionClasses = QSet<QHash<Category*, /*Class<? extends Base>>*/QString> >();
#if 1
        analogExpressionClasses.insert(QHash<Category*, QString> {{Category::ITEM, ".jmri.jmrit.logixng.AnalogExpressionAnalogIO"}});
        analogExpressionClasses.insert(QHash<Category*, QString> {{Category::ITEM, ".jmri.jmrit.logixng.expressions.AnalogExpressionConstant"}});
        analogExpressionClasses.insert(QHash<Category*, QString> {{Category::ITEM, ".jmri.jmrit.logixng.AnalogExpressionMemory"}});
        analogExpressionClasses.insert(QHash<Category*, QString> {{Category::COMMON, ".jmri.jmrit.logixng.expressions.AnalogFormula"}});
        analogExpressionClasses.insert(QHash<Category*, QString> {{Category::ITEM, ".jmri.jmrit.logixng.TimeSinceMidnight"}});
#else
        QMap<Category*, /*Class<? extends Base>>*/QString > map = QMap<Category*, /*Class<? extends Base>>*/QString >();
        map.insert(Category::ITEM, "AnalogExpressionAnalogIO");
        analogExpressionClasses.insert(map);
        map.clear();
        map.insert(Category::ITEM, "AnalogExpressionConstant");
        analogExpressionClasses.insert(map);
        map.clear();
        map.insert(Category::ITEM, "AnalogExpressionMemory");
        analogExpressionClasses.insert(map);
        map.clear();
        map.insert(Category::COMMON, "AnalogFormula");
        analogExpressionClasses.insert(map);
        map.clear();
        map.insert(Category::ITEM, "TimeSinceMidnight");
        analogExpressionClasses.insert(map);

#endif
        return analogExpressionClasses;
    }
