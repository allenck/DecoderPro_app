#include "analogfactory.h"
#include "analogexpressionanalogio.h"
class Base;
/**
 * The factory for DigitalAction classes.
 */
//@ServiceProvider(service = AnalogExpressionFactory.class)
//public class AnalogFactory implements AnalogExpressionFactory {

    //@Override
    /*public*/ QSet<QMap<Category, /*Class<? extends Base>*/Base*>> getClasses() {
        QSet<QMap<Category*, /*Class<? extends Base>>*/Base*> >analogExpressionClasses = QSet<QMap<Category*, /*Class<? extends Base>>*/Base*>>();
        analogExpressionClasses.insert(QMap<Category::ITEM, AnalogExpressionAnalogIO()>));
        analogExpressionClasses.insert(new AbstractMap.SimpleEntry<>(Category::ITEM, "AnalogExpressionConstant"));
        analogExpressionClasses.insert(new AbstractMap.SimpleEntry<>(Category::ITEM, "AnalogExpressionMemory"));
        analogExpressionClasses.insert(new AbstractMap.SimpleEntry<>(Category::COMMON, "AnalogFormula"));
        analogExpressionClasses.insert(new AbstractMap.SimpleEntry<>(Category::ITEM, "TimeSinceMidnight"));
        return analogExpressionClasses;
    }
