#include "analogfactory.h"
#include "analogexpressionanalogio.h"
class Base;
/**
 * The factory for DigitalAction classes.
 */
//@ServiceProvider(service = AnalogExpressionFactory.class)
//public class AnalogFactory implements AnalogExpressionFactory {

    //@Override
    /*public*/ QSet<QMap<Category::TYPE, /*Class<? extends Base>*/QString>> getClasses() {
        QSet<QMap<Category::TYPE, /*Class<? extends Base>>*/QString >> analogExpressionClasses = QSet<QMap<Category::TYPE, /*Class<? extends Base>>*/QString>>();
#if 1
        analogExpressionClasses.insert(QMap<Category::TYPE, QString> {{Category::TYPE::ITEM, "AnalogExpressionAnalogIO"}});
        analogExpressionClasses.insert(QMap<Category::TYPE, QString> {{Category::TYPE::ITEM, "AnalogExpressionConstant"}});
        analogExpressionClasses.insert(QMap<Category::TYPE, QString> {{Category::TYPE::ITEM, "AnalogExpressionMemory"}});
        analogExpressionClasses.insert(QMap<Category::TYPE, QString> {{Category::TYPE::COMMON, "AnalogFormula"}});
        analogExpressionClasses.insert(QMap<Category::TYPE, QString> {{Category::TYPE::ITEM, "TimeSinceMidnight"}});
#endif
        return analogExpressionClasses;
    }
