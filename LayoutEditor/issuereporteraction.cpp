#include "issuereporteraction.h"
#include "issuereporter.h"

/**
 * Action to report an issue to the JMRI developers.
 *
 * @author Randall Wood Copyright 2020
 */
//@API(status = API.Status.INTERNAL)
// /*public*/ class IssueReporterAction extends AbstractAction {

    /*public*/ IssueReporterAction::IssueReporterAction(QWidget* parent) : AbstractAction(tr("Report Issue..."), parent){
        //super(tr("IssueReporterAction.title", "..."));
    }

    //@Override
    /*public*/ void IssueReporterAction::actionPerformed(JActionEvent* e) {
        (new IssueReporter())->setVisible(true);
    }
