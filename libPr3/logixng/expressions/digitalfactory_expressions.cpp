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
        expressionClasses.insert(QHash<Category*, QString> {{Category::COMMON, "And"}});
        expressionClasses.insert(QHash<Category*, QString> {{Category::COMMON, "Antecedent"}});
        expressionClasses.insert(QHash<Category*, QString> {{Category::OTHER, "DigitalCallModule"}});
        expressionClasses.insert(QHash<Category*, QString> {{Category::ITEM, "ExpressionBlock"}});
        expressionClasses.insert(QHash<Category*, QString> {{Category::ITEM, "ExpressionClock"}});
        expressionClasses.insert(QHash<Category*, QString> {{Category::ITEM, "ExpressionConditional"}});
        expressionClasses.insert(QHash<Category*, QString> {{Category::ITEM, "ExpressionDispatcher"}});
        expressionClasses.insert(QHash<Category*, QString> {{Category::ITEM, "ExpressionEntryExit"}});
        expressionClasses.insert(QHash<Category*, QString> {{Category::ITEM, "ExpressionLight"}});
        expressionClasses.insert(QHash<Category*, QString> {{Category::ITEM, "ExpressionLocalVariable"}});
        expressionClasses.insert(QHash<Category*, QString> {{Category::ITEM, "ExpressionMemory"}});
        expressionClasses.insert(QHash<Category*, QString> {{Category::ITEM, "ExpressionOBlock"}});
        expressionClasses.insert(QHash<Category*, QString> {{Category::ITEM, "ExpressionPower"}});
        expressionClasses.insert(QHash<Category*, QString> {{Category::ITEM, "ExpressionReference"}});
        expressionClasses.insert(QHash<Category*, QString> {{Category::ITEM, "ExpressionReporter"}});
        expressionClasses.insert(QHash<Category*, QString> {{Category::ITEM, "ExpressionScript"}});
        expressionClasses.insert(QHash<Category*, QString> {{Category::ITEM, "ExpressionSensor"}});
        expressionClasses.insert(QHash<Category*, QString> {{Category::ITEM, "ExpressionSignalHead"}});
        expressionClasses.insert(QHash<Category*, QString> {{Category::ITEM, "ExpressionSignalMast"}});
        expressionClasses.insert(QHash<Category*, QString> {{Category::ITEM, "ExpressionTurnout"}});
        expressionClasses.insert(QHash<Category*, QString> {{Category::ITEM, "ExpressionWarrant"}});
        expressionClasses.insert(QHash<Category*, QString> {{Category::OTHER, "False"}});
        expressionClasses.insert(QHash<Category*, QString> {{Category::COMMON, "DigitalFormula"}});
        expressionClasses.insert(QHash<Category*, QString> {{Category::OTHER, "Hold"}});
        expressionClasses.insert(QHash<Category*, QString> {{Category::OTHER, "LastResultOfDigitalExpression"}});
        expressionClasses.insert(QHash<Category*, QString> {{Category::OTHER, "LogData"}});
        expressionClasses.insert(QHash<Category*, QString> {{Category::COMMON, "Not"}});
        expressionClasses.insert(QHash<Category*, QString> {{Category::COMMON, "Or"}});
        expressionClasses.insert(QHash<Category*, QString> {{Category::OTHER, "TriggerOnce"}});
        expressionClasses.insert(QHash<Category*, QString> {{Category::OTHER, "True"}});
                return expressionClasses;
    }
