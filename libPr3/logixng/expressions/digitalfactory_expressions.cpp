#include "digitalfactory_expressions.h"
#include <QSet>
#include <QHash>
#include "../category.h"
/**
 * The factory for DigitalExpressionBean classes.
 */
//@ServiceProvider(service = DigitalExpressionFactory.class)
//public class DigitalFactory implements DigitalExpressionFactory {

    //@Override
    /*public*/ QSet<QHash<Category*, /*Class<? extends DigitalActionBean>*/QString>> DigitalFactory_Expressions::getExpressionClasses() {
        QSet<QHash<Category*,QString> > expressionClasses = QSet<QHash<Category*,QString> >();
        expressionClasses.insert(QHash<Category*, QString> {{Category::COMMON, "jmri.jmrit.logixng.expressions.And"}});
        expressionClasses.insert(QHash<Category*, QString> {{Category::COMMON, "jmri.jmrit.logixng.expressions.Antecedent"}});
        expressionClasses.insert(QHash<Category*, QString> {{Category::OTHER, "jmri.jmrit.logixng.expressions.DigitalCallModule"}});
        expressionClasses.insert(QHash<Category*, QString> {{Category::ITEM, "jmri.jmrit.logixng.expressions.ExpressionBlock"}});
        expressionClasses.insert(QHash<Category*, QString> {{Category::ITEM, "jmri.jmrit.logixng.expressions.ExpressionClock"}});
        expressionClasses.insert(QHash<Category*, QString> {{Category::ITEM, "jmri.jmrit.logixng.expressions.ExpressionConditional"}});
        expressionClasses.insert(QHash<Category*, QString> {{Category::ITEM, "jmri.jmrit.logixng.expressions.ExpressionDispatcher"}});
        expressionClasses.insert(QHash<Category*, QString> {{Category::ITEM, "jmri.jmrit.logixng.expressions.ExpressionEntryExit"}});
        expressionClasses.insert(QHash<Category*, QString> {{Category::ITEM, "jmri.jmrit.logixng.expressions.ExpressionLight"}});
        expressionClasses.insert(QHash<Category*, QString> {{Category::ITEM, "jmri.jmrit.logixng.expressions.ExpressionLocalVariable"}});
        expressionClasses.insert(QHash<Category*, QString> {{Category::ITEM, "jmri.jmrit.logixng.expressions.ExpressionMemory"}});
        expressionClasses.insert(QHash<Category*, QString> {{Category::ITEM, "jmri.jmrit.logixng.expressions.ExpressionOBlock"}});
        expressionClasses.insert(QHash<Category*, QString> {{Category::ITEM, "jmri.jmrit.logixng.expressions.ExpressionPower"}});
        expressionClasses.insert(QHash<Category*, QString> {{Category::ITEM, "jmri.jmrit.logixng.expressions.ExpressionReference"}});
        expressionClasses.insert(QHash<Category*, QString> {{Category::ITEM, "jmri.jmrit.logixng.expressions.ExpressionReporter"}});
        expressionClasses.insert(QHash<Category*, QString> {{Category::ITEM, "jmri.jmrit.logixng.expressions.ExpressionScript"}});
        expressionClasses.insert(QHash<Category*, QString> {{Category::ITEM, "jmri.jmrit.logixng.expressions.ExpressionSensor"}});
        expressionClasses.insert(QHash<Category*, QString> {{Category::ITEM, "jmri.jmrit.logixng.expressions.ExpressionSignalHead"}});
        expressionClasses.insert(QHash<Category*, QString> {{Category::ITEM, "jmri.jmrit.logixng.expressions.ExpressionSignalMast"}});
        expressionClasses.insert(QHash<Category*, QString> {{Category::ITEM, "jmri.jmrit.logixng.expressions.ExpressionTurnout"}});
        expressionClasses.insert(QHash<Category*, QString> {{Category::ITEM, "jmri.jmrit.logixng.expressions.ExpressionWarrant"}});
        expressionClasses.insert(QHash<Category*, QString> {{Category::OTHER, "jmri.jmrit.logixng.expressions.False"}});
        expressionClasses.insert(QHash<Category*, QString> {{Category::COMMON, "jmri.jmrit.logixng.expressions.DigitalFormula"}});
        expressionClasses.insert(QHash<Category*, QString> {{Category::OTHER, "jmri.jmrit.logixng.expressions.Hold"}});
        expressionClasses.insert(QHash<Category*, QString> {{Category::OTHER, "jmri.jmrit.logixng.expressions.LastResultOfDigitalExpression"}});
        expressionClasses.insert(QHash<Category*, QString> {{Category::OTHER, "jmri.jmrit.logixng.expressions.LogData"}});
        expressionClasses.insert(QHash<Category*, QString> {{Category::COMMON, "jmri.jmrit.logixng.expressions.Not"}});
        expressionClasses.insert(QHash<Category*, QString> {{Category::COMMON, "jmri.jmrit.logixng.expressions.Or"}});
        expressionClasses.insert(QHash<Category*, QString> {{Category::OTHER, "jmri.jmrit.logixng.expressions.TriggerOnce"}});
        expressionClasses.insert(QHash<Category*, QString> {{Category::OTHER, "jmri.jmrit.logixng.expressions.True"}});
                return expressionClasses;
    }
