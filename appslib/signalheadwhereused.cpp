#include "signalheadwhereused.h"
#include "jtextarea.h"
#include "namedbean.h"
#include "whereusedcollectors.h"

SignalHeadWhereUsed::SignalHeadWhereUsed(QObject *parent) : QObject(parent)
{

}
/**
 * Find signal head references.
 *
 * @author Dave Sand Copyright (C) 2020
 */

///*public*/ class SignalHeadWhereUsed {

    /**
     * Populate a textarea with the where used content for the supplied signal head.
     * @param signalHead The signal head bean.
     * @return a populated textarea.
     */
    /*static*/ /*public*/ JTextArea* SignalHeadWhereUsed::getWhereUsed(NamedBean* signalHead) {
        JTextArea* textArea = new JTextArea();
        QString label = tr("SignalHead");  // NOI18N
        textArea->append(tr("\t\t%1 %2	").arg(label).arg(signalHead->getDisplayName()));  // NOI18N
        textArea->append(tr("\t\tListener count: %1	\n").arg(signalHead->getNumPropertyChangeListeners()));  // NOI18N

        textArea->append(WhereUsedCollectors::checkSignalHeadLogic(signalHead));
        textArea->append(WhereUsedCollectors::checkSignalGroups(signalHead));
        textArea->append(WhereUsedCollectors::checkOBlocks(signalHead));
        textArea->append(WhereUsedCollectors::checkWarrants(signalHead));
        textArea->append(WhereUsedCollectors::checkEntryExit(signalHead));
        textArea->append(WhereUsedCollectors::checkLogixConditionals(signalHead));
        textArea->append(WhereUsedCollectors::checkPanels(signalHead));
        textArea->append(WhereUsedCollectors::checkCTC(signalHead));
        return textArea;
    }
