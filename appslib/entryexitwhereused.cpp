#include "entryexitwhereused.h"
#include "jtextarea.h"
#include "namedbean.h"
#include "entryexitpairs.h"
#include "whereusedcollectors.h"

EntryExitWhereUsed::EntryExitWhereUsed(QObject *parent) : QObject(parent)
{

}
/**
 * Find entry/exit references.
 *
 * @author Dave Sand Copyright (C) 2020
 */

///*public*/ class EntryExitWhereUsed {

    /**
     * Populate a textarea with the where used content for the supplied bean.
     * @param entryexit The entry/exit bean.
     * @return a populated textarea.
     */
    /*static*/ /*public*/ JTextArea* getWhereUsed(NamedBean* entryexit) {
        JTextArea* textArea = new JTextArea();
        QString label = ("EntryExit");  // NOI18N
        textArea->append(QString("\t\t%1 %2").arg(label).arg(entryexit->getDisplayName()));  // NOI18N
        textArea->append(QString("\t\tListener count: %1	").arg(entryexit->getNumPropertyChangeListeners()));  // NOI18N

        textArea->append(WhereUsedCollectors::checkLogixConditionals(entryexit));
        textArea->append(WhereUsedCollectors::checkEntryExit(entryexit));
        return textArea;
    }
