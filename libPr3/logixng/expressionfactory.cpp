#include "expressionfactory.h"
#include "categoryloconet.h"
#include <QSet>
#include <QHash>
/**
 * The factory for LogixNG LocoNet classes.
 */
//@ServiceProvider(service = DigitalExpressionFactory.class)
//public class ExpressionFactory implements DigitalExpressionFactory {

    //@Override
    /*public*/ void ExpressionFactory::init() {
        CategoryLocoNet::registerCategory();
    }

    //@Override
    /*public*/ QSet<QHash<Category, /*Class<? extends DigitalExpressionBean>*/QString>> ExpressionFactory::getExpressionClasses() {
        QSet<QHash<Category,/* Class<? extends DigitalExpressionBean>*/QString>> expressionClasses = QSet<QHash<Category,/* Class<? extends DigitalExpressionBean>*/QString>>();

        // We don't want to add these classes if we don't have a LocoNet connection
        if (CategoryLocoNet::hasLocoNet()) {
            expressionClasses.insert(QHash<Category,QString> {{CategoryLocoNet::LOCONET, "ExpressionSlotUsage"}});
        }

        return expressionClasses;
    }



