#include "routewhereused.h"
#include "jtextarea.h"
#include "namedbean.h"
#include "whereusedcollectors.h"

RouteWhereUsed::RouteWhereUsed(QObject *parent) : QObject(parent)
{

}
/**
 * Find Route references.
 *
 * @author Dave Sand Copyright (C) 2020
 */

///*public*/ class RouteWhereUsed {

    /**
     * Populate a textarea with the where used content for the supplied sensor.
     * @param route The route bean.
     * @return a populated textarea.
     */
    /*static*/ /*public*/ JTextArea* RouteWhereUsed::getWhereUsed(NamedBean* route) {
        JTextArea* textArea = new JTextArea();
        QString label = tr("Route");  // NOI18N
        textArea->append(tr("\t\t%1 %2	").arg(label).arg(route->getDisplayName()));  // NOI18N
        textArea->append(tr("\t\tListener count: %1	\n").arg(route->getNumPropertyChangeListeners()));  // NOI18N

        textArea->append(WhereUsedCollectors::checkLogixConditionals(route));
        return textArea;
    }
