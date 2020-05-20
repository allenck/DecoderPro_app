#include "blockwhereused.h"
#include "jtextarea.h"
#include "namedbean.h"
#include "whereusedcollectors.h"

BlockWhereUsed::BlockWhereUsed(QObject *parent) : QObject(parent)
{

}
/**
 * Find Block references.
 *
 * @author Dave Sand Copyright (C) 2020
 */

// /*public*/ class BlockWhereUsed {

    /**
     * Populate a textarea with the where used content for the supplied sensor.
     * @param block The block bean.
     * @return a populated textarea.
     */
    /*static*/ /*public*/ JTextArea* BlockWhereUsed::getWhereUsed(NamedBean* block) {
        JTextArea* textArea = new JTextArea();
        QString label = tr("Block");  // NOI18N
        textArea->append(tr("\t\t%1 %2	").arg(label).arg(block->getDisplayName()));  // NOI18N
        textArea->append(tr("\t\tListener count: %1	\n").arg(block->getNumPropertyChangeListeners()));  // NOI18N

        textArea->append(WhereUsedCollectors::checkLayoutBlocks(block));
        textArea->append(WhereUsedCollectors::checkSignalMastLogic(block));
        textArea->append(WhereUsedCollectors::checkSections(block));
        textArea->append(WhereUsedCollectors::checkPanels(block));
        textArea->append(WhereUsedCollectors::checkCTC(block));
        return textArea;
    }
