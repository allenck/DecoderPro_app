#include "oblockwhereused.h"
#include "jtextarea.h"
#include "namedbean.h"
#include "whereusedcollectors.h"

OBlockWhereUsed::OBlockWhereUsed(QObject *parent) : QObject(parent)
{

}
/**
 * Find OBlock references.
 *
 * @author Dave Sand Copyright (C) 2020
 */

// /*public*/ class OBlockWhereUsed {

/**
 * Populate a textarea with the where used content for the supplied sensor.
 * @param oblock The oblock bean.
 * @return a populated textarea.
 */
/*static*/ /*public*/ JTextArea* OBlockWhereUsed::getWhereUsed(NamedBean* oblock) {
    JTextArea* textArea = new JTextArea();
    QString label = tr("OBlock");  // NOI18N
    textArea->append(tr("\t\t%1 %2	").arg(label).arg(oblock->getDisplayName()));  // NOI18N
    textArea->append(tr("\t\tListener count: %1	\n").arg(oblock->getNumPropertyChangeListeners()));  // NOI18N

    textArea->append(WhereUsedCollectors::checkLogixConditionals(oblock));
    textArea->append(WhereUsedCollectors::checkOBlocks(oblock));
    textArea->append(WhereUsedCollectors::checkWarrants(oblock));
    textArea->append(WhereUsedCollectors::checkPanels(oblock));
    return textArea;
}
