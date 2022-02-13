#include "analogfactory.h"
#include "analogexpressionanalogio.h"
class Base;
/**
 * The factory for DigitalAction classes.
 */
//@ServiceProvider(service = AnalogExpressionFactory.class)
//public class AnalogFactory implements AnalogExpressionFactory {

    //@Override
    /*public*/ QSet<QMap<Category*, /*Class<? extends Base>*/QString>> getClasses() {
        QSet<QMap<Category*, /*Class<? extends Base>>*/QString >> analogExpressionClasses = QSet<QMap<Category*, /*Class<? extends Base>>*/QString>>();
#if 1
        analogExpressionClasses.insert(QMap<Category*, QString> {{Category::ITEM, "AnalogExpressionAnalogIO"}});
        analogExpressionClasses.insert(QMap<Category*, QString> {{Category::ITEM, "AnalogExpressionConstant"}});
        analogExpressionClasses.insert(QMap<Category*, QString> {{Category::ITEM, "AnalogExpressionMemory"}});
        analogExpressionClasses.insert(QMap<Category*, QString> {{Category::COMMON, "AnalogFormula"}});
        analogExpressionClasses.insert(QMap<Category*, QString> {{Category::ITEM, "TimeSinceMidnight"}});
#endif
        return analogExpressionClasses;
    }
