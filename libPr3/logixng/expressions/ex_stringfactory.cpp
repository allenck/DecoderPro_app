#include "ex_stringfactory.h"

/**
 * The factory for DigitalAction classes.
 */
//@ServiceProvider(service = StringExpressionFactory.class)
//public class StringFactory implements StringExpressionFactory {
namespace Expressions
{
    //@Override
    /*public*/ QSet<QHash<Category, /*Class<? extends Base>*/QString>> StringFactory::getClasses() {
        QSet<QHash<Category,/* Class<? extends Base>*/QString>> stringExpressionClasses = QSet<QHash<Category,QString>>();
        stringExpressionClasses.insert(QHash<Category, QString> {{Category::ITEM, "jmri.jmrit.logixng.expressions.StringExpressionConstant"}});
        stringExpressionClasses.insert(QHash<Category, QString> {{Category::ITEM, "jmri.jmrit.logixng.expressions.StringExpressionMemory"}});
        stringExpressionClasses.insert(QHash<Category, QString> {{Category::COMMON, "jmri.jmrit.logixng.expressions.StringFormula"}});
        return stringExpressionClasses;
    }

}
