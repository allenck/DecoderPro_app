#include "turnoutwhereused.h"
#include "jtextarea.h"
#include "namedbean.h"
#include "whereusedcollectors.h"
TurnoutWhereUsed::TurnoutWhereUsed(QObject *parent) : QObject(parent)
{

}
/**
 * Find turnout references.
 *
 * @author Dave Sand Copyright (C) 2020
 */

// /*public*/ class TurnoutWhereUsed {

    /**
     * Populate a textarea with the where used content for the supplied turnout.
     * @param turnout The turnout bean.
     * @return a populated textarea.
     */
    /*static*/ /*public*/ JTextArea* TurnoutWhereUsed::getWhereUsed(NamedBean* turnout) {
        JTextArea* textArea = new JTextArea();
        QString label = tr("Turnout");  // NOI18N
        textArea->append(tr("\t\t%1 %2	").arg(label).arg(turnout->getDisplayName()));  // NOI18N
        textArea->append(tr("\t\tListener count: %1	\n").arg(turnout->getNumPropertyChangeListeners()));  // NOI18N

        textArea->append(WhereUsedCollectors::checkLights(turnout));
        textArea->append(WhereUsedCollectors::checkRoutes(turnout));
        textArea->append(WhereUsedCollectors::checkBlocks(turnout));
        textArea->append(WhereUsedCollectors::checkSignalHeadLogic(turnout));
        textArea->append(WhereUsedCollectors::checkSignalMastLogic(turnout));
        textArea->append(WhereUsedCollectors::checkSignalGroups(turnout));
        textArea->append(WhereUsedCollectors::checkOBlocks(turnout));
        textArea->append(WhereUsedCollectors::checkLogixConditionals(turnout));
        textArea->append(WhereUsedCollectors::checkPanels(turnout));
        textArea->append(WhereUsedCollectors::checkCTC(turnout));
        return textArea;
    }

