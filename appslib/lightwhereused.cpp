#include "lightwhereused.h"
#include "whereusedcollectors.h"
#include "namedbean.h"
#include "jtextarea.h"

LightWhereUsed::LightWhereUsed(QObject *parent) : QObject(parent)
{

}
/**
 * Find light references.
 *
 * @author Dave Sand Copyright (C) 2020
 */

// /*public*/ class LightWhereUsed {

    /**
     * Populate a textarea with the where used content for the supplied sensor.
     * @param light The light bean.
     * @return a populated textarea.
     */
    /*static*/ /*public*/ JTextArea* LightWhereUsed::getWhereUsed(NamedBean* light) {
        JTextArea* textArea = new JTextArea();
        QString label = tr("Light");  // NOI18N
        textArea->append(tr("\t\t%1 %2\n").arg(label).arg(light->getDisplayName()));  // NOI18N
        textArea->append(tr("\t/tListener count: %1\n").arg(light->getNumPropertyChangeListeners()));  // NOI18N

        textArea->append(WhereUsedCollectors::checkLogixConditionals(light));
        textArea->append(WhereUsedCollectors::checkPanels(light));
        return textArea;
    }

