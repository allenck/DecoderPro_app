#include "stringfactory.h"
#include <QMap>
#include <QSet>

namespace Actions
{
 /**
  * The factory for StringAction classes.
  */
 //@ServiceProvider(service = StringActionFactory.class)
// /*public*/ class StringFactory implements StringActionFactory {
 //@Override
    /*public*/ QSet<QHash<Category, /*Class<? extends Base>*/QString>> StringFactory::getClasses() {
        QSet<QHash<Category, /*Class<? extends Base>*/QString>> stringActionClasses = QSet<QHash<Category, QString>>();
        stringActionClasses.insert(QHash<Category, QString> {{Category::ITEM, "jmri.jmrit.logixng.actions.StringActionMemory"}});
        stringActionClasses.insert(QHash<Category, QString> {{Category::ITEM, "jmri.jmrit.logixng.actions.StringActionStringIO"}});
        stringActionClasses.insert(QHash<Category, QString> {{Category::COMMON, "jmri.jmrit.logixng.actions.StringMany"}});
        return stringActionClasses;
    }
}
