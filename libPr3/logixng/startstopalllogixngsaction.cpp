#include "startstopalllogixngsaction.h"
#include "instancemanager.h"
#include "defaultlogixngmanager.h"

/**
 * Swing action to create and register a TimeDiagram object.
 *
 * @author Daniel Bergqvist Copyright (C) 2018
 */
// /*public*/  class StartStopAllLogixNGsAction extends AbstractAction {


    /*public*/  StartStopAllLogixNGsAction::StartStopAllLogixNGsAction(QString s, bool start, QObject *parent) : AbstractAction(s, parent) {
        //super(s);
        _start = start;
        connect(this, SIGNAL(triggered(bool)), this, SLOT(actionPerformed()));
    }

    /*public*/  StartStopAllLogixNGsAction::StartStopAllLogixNGsAction(bool start, QObject *parent) : AbstractAction(tr("Time Diagram"), parent) {
        //this(tr("Time Diagram"), start);  // NOI18N
     connect(this, SIGNAL(triggered(bool)), this, SLOT(actionPerformed()));
    }

    //@Override
    /*public*/  void StartStopAllLogixNGsAction::actionPerformed(JActionEvent* e) {
        if (_start) {
            ((DefaultLogixNGManager*)InstanceManager::getDefault("LogixNG_Manager"))->activateAllLogixNGs();
        } else {
            ((DefaultLogixNGManager*)InstanceManager::getDefault("LogixNG_Manager"))->deActivateAllLogixNGs();
        }
    }
