#include "reporterwhereused.h"
#include "jtextarea.h"
#include "namedbean.h"
#include "whereusedcollectors.h"

ReporterWhereUsed::ReporterWhereUsed(QObject *parent) : QObject(parent)
{

}
/**
 * Find Reporter references.
 *
 * @author Dave Sand Copyright (C) 2020
 */

// /*public*/ class ReporterWhereUsed {

    /**
     * Populate a textarea with the where used content for the supplied sensor.
     * @param reporter The reporter bean.
     * @return a populated textarea.
     */
    /*static*/ /*public*/ JTextArea* ReporterWhereUsed::getWhereUsed(NamedBean* reporter) {
        JTextArea* textArea = new JTextArea();
        QString label = tr("Reporter");  // NOI18N
        textArea->append(tr("\t\t%1 %2	").arg(label).arg(reporter->getDisplayName()));  // NOI18N
        textArea->append(tr("\t\tListener count: %1	\n").arg(reporter->getNumPropertyChangeListeners()));  // NOI18N

        textArea->append(WhereUsedCollectors::checkBlocks(reporter));
        return textArea;
    }
