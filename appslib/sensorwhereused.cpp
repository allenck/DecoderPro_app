#include "sensorwhereused.h"
#include "whereusedcollectors.h"
#include "jtextarea.h"
#include "namedbean.h"
#include "sensor.h"

SensorWhereUsed::SensorWhereUsed(QObject *parent) : QObject(parent)
{

}
/**
 * Find sensor references.
 *
 * @author Dave Sand Copyright (C) 2020
 */
// /*public*/ class SensorWhereUsed {

    /**
     * Populate a textarea with the whereused content for the supplied sensor.
     * @param sensor The sensor bean.
     * @return a populated textarea.
     */
    /*static*/ /*public*/ JTextArea* SensorWhereUsed::getWhereUsed(NamedBean* sensor) {
        JTextArea* textArea = new JTextArea();
        QString label = tr("Sensor");  // NOI18N
        textArea->append(tr("\t\t%1 %2\n").arg(label).arg(sensor->getDisplayName()));  // NOI18N
        textArea->append(tr("\t\tListener count: %1\n").arg(sensor->getNumPropertyChangeListeners()));  // NOI18N

        textArea->append(WhereUsedCollectors::checkTurnouts(sensor));
        textArea->append(WhereUsedCollectors::checkLights(sensor));
        textArea->append(WhereUsedCollectors::checkRoutes(sensor));
        textArea->append(WhereUsedCollectors::checkBlocks(sensor));
        textArea->append(WhereUsedCollectors::checkLayoutBlocks(sensor));
        textArea->append(WhereUsedCollectors::checkSignalHeadLogic(sensor));
        textArea->append(WhereUsedCollectors::checkSignalMastLogic(sensor));
        textArea->append(WhereUsedCollectors::checkSignalGroups(sensor));
        textArea->append(WhereUsedCollectors::checkOBlocks(sensor));
        textArea->append(WhereUsedCollectors::checkEntryExit(sensor));
        textArea->append(WhereUsedCollectors::checkLogixConditionals(sensor));
        textArea->append(WhereUsedCollectors::checkSections(sensor));
        textArea->append(WhereUsedCollectors::checkTransits(sensor));
        textArea->append(WhereUsedCollectors::checkPanels(sensor));
        textArea->append(WhereUsedCollectors::checkCTC(sensor));
        return textArea;
    }
