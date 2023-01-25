#include "stringfactory.h"

/**
 * The factory for DigitalAction classes.
 */
//@ServiceProvider(service = StringExpressionFactory.class)
//public class StringFactory implements StringExpressionFactory {

    //@Override
    /*public*/ QSet<QHash<Category, /*Class<? extends Base>*/QString>> StringFactory::getClasses() {
        QSet<QHash<Category, /*Class<? extends Base>*/QString>> stringExpressionClasses = QSet<QHash<Category, /*Class<? extends Base>*/QString>>();
        stringExpressionClasses.insert(QHash<Category, QString> {{Category::ITEM, "StringExpressionConstant"}});
        stringExpressionClasses.insert(QHash<Category, QString> {{Category::ITEM, "StringExpressionMemory"}});
        stringExpressionClasses.insert(QHash<Category, QString> {{Category::COMMON, "StringFormula"}});
        return stringExpressionClasses;
    }
