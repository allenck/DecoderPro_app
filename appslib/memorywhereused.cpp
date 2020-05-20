#include "memorywhereused.h"
#include "jtextarea.h"
#include "namedbean.h"
#include "whereusedcollectors.h"

MemoryWhereUsed::MemoryWhereUsed(QObject *parent) : QObject(parent)
{

}
/**
 * Find memory references.
 *
 * @author Dave Sand Copyright (C) 2020
 */

// /*public*/ class MemoryWhereUsed {

    /**
     * Populate a textarea with the where used content for the supplied memory.
     * @param memory The memory bean.
     * @return a populated textarea.
     */
    /*static*/ /*public*/ JTextArea*MemoryWhereUsed:: getWhereUsed(NamedBean* memory) {
        JTextArea* textArea = new JTextArea();
        QString label = tr("Memory");  // NOI18N
        textArea->append(tr("\t\t%1 %2	").arg(label).arg(memory->getDisplayName()));  // NOI18N
        textArea->append(tr("\t\tListener count: %1	\n").arg(memory->getNumPropertyChangeListeners()));  // NOI18N

        textArea->append(WhereUsedCollectors::checkLayoutBlocks(memory));
        textArea->append(WhereUsedCollectors::checkLogixConditionals(memory));
        textArea->append(WhereUsedCollectors::checkPanels(memory));
        return textArea;
    }
