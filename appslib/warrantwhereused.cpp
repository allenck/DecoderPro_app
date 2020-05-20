#include "warrantwhereused.h"
#include "jtextarea.h"
#include "namedbean.h"
#include "whereusedcollectors.h"

WarrantWhereUsed::WarrantWhereUsed(QObject *parent) : QObject(parent)
{

}
/**
 * Find Warrant references.
 *
 * @author Dave Sand Copyright (C) 2020
 */

// /*public*/ class WarrantWhereUsed {

    /**
     * Populate a textarea with the where used content for the supplied bean.
     * @param warrant The warrant bean.
     * @return a populated textarea.
     */
    /*static*/ /*public*/ JTextArea* WarrantWhereUsed::getWhereUsed(NamedBean* warrant) {
        JTextArea* textArea = new JTextArea();
        QString label = tr("Warrant");  // NOI18N
        textArea->append(tr("\t\t%1 %2	").arg(label).arg(warrant->getDisplayName()));  // NOI18N
        textArea->append(tr("\t\tListener count: %1	\n").arg(warrant->getNumPropertyChangeListeners()));  // NOI18N

        textArea->append(WhereUsedCollectors::checkLogixConditionals(warrant));
        textArea->append(WhereUsedCollectors::checkOBlocks(warrant));
        textArea->append(WhereUsedCollectors::checkWarrants(warrant));
        return textArea;
    }
