#include "signalmastwhereused.h"
#include "jtextarea.h"
#include "namedbean.h"
#include "whereusedcollectors.h"

SignalMastWhereUsed::SignalMastWhereUsed(QObject *parent) : QObject(parent)
{

}
/**
 * Find signal mast references.
 *
 * @author Dave Sand Copyright (C) 2020
 */

///*public*/ class SignalMastWhereUsed {

    /**
     * Populate a textarea with the where used content for the supplied signal mast.
     * @param signalMast The signal mast bean.
     * @return a populated textarea.
     */
    /*static*/ /*public*/ JTextArea* SignalMastWhereUsed::getWhereUsed(NamedBean* signalMast) {
        JTextArea* textArea = new JTextArea();
        QString label = tr("SignalMast");  // NOI18N
        textArea->append(tr("\t\t%1 %2	").arg(label).arg(signalMast->getDisplayName()));  // NOI18N
        textArea->append(tr("\t\tListener count: %1	\n").arg(signalMast->getNumPropertyChangeListeners()));  // NOI18N

        textArea->append(WhereUsedCollectors::checkSignalMastLogic(signalMast));
        textArea->append(WhereUsedCollectors::checkSignalGroups(signalMast));
        textArea->append(WhereUsedCollectors::checkOBlocks(signalMast));
        textArea->append(WhereUsedCollectors::checkWarrants(signalMast));
        textArea->append(WhereUsedCollectors::checkEntryExit(signalMast));
        textArea->append(WhereUsedCollectors::checkLogixConditionals(signalMast));
        textArea->append(WhereUsedCollectors::checkPanels(signalMast));
        textArea->append(WhereUsedCollectors::checkCTC(signalMast));
        return textArea;
    }

