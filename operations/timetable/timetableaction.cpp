#include "timetableaction.h"
#include "timetableframe.h"
#include "instancemanager.h"

/**
 * Swing action to create and register a TimeTableFrame
 *
 * @author Dave Sand Copyright (C) 2018
 */
// /*public*/ class TimeTableAction extends JmriAbstractAction {

/*public*/ TimeTableAction::TimeTableAction(QString s, QObject* parent) : AbstractAction(s, parent){
    //super(s);
 connect(this, SIGNAL(triggered(bool)), this, SLOT(actionPerformed()));
}

/*public*/ TimeTableAction::TimeTableAction(QObject* parent) : AbstractAction(tr("TimeTable"), parent) {
    //this("TimeTable");  // NOI18N
 connect(this, SIGNAL(triggered(bool)), this, SLOT(actionPerformed()));
}

//@Override
/*public*/ void TimeTableAction::actionPerformed(/*ActionEvent e*/) {
    if (InstanceManager::getNullableDefault("TimeTableFrame") != nullptr) {
        // Prevent duplicate copies
        return;
    }
    TimeTable::TimeTableFrame* f = new TimeTable::TimeTableFrame("");
    f->setVisible(true);
}

// never invoked, because we overrode actionPerformed above
//@Override
/*public*/ JmriPanel* TimeTableAction::makePanel() {
    throw  IllegalArgumentException("Should not be invoked");  // NOI18N
}
