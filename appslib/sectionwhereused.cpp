#include "sectionwhereused.h"
#include "jtextarea.h"
#include "namedbean.h"
#include "whereusedcollectors.h"

SectionWhereUsed::SectionWhereUsed(QObject *parent) : QObject(parent)
{

}
/**
 * Find Section references.
 *
 * @author Dave Sand Copyright (C) 2020
 */

// /*public*/ class SectionWhereUsed {

    /**
     * Populate a textarea with the where used content for the supplied sensor.
     * @param section The section bean.
     * @return a populated textarea.
     */
    /*static*/ /*public*/ JTextArea* SectionWhereUsed::getWhereUsed(NamedBean* section) {
        JTextArea* textArea = new JTextArea();
        QString label = tr("Section");  // NOI18N
        textArea->append(tr("\t\t%1 %2	").arg(label).arg(section->getDisplayName()));  // NOI18N
        textArea->append(tr("\t\tListener count: %1	\n").arg(section->getNumPropertyChangeListeners()));  // NOI18N

        textArea->append(WhereUsedCollectors::checkTransits(section));
        return textArea;
    }
