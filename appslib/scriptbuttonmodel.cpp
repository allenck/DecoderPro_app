#include "scriptbuttonmodel.h"
#include "jmriscriptenginemanager.h"
#include "loggerfactory.h"
#include "apps.h"
#include <QPushButton>
#include "apps3.h"
#include "file.h"
#include <QBoxLayout>

ScriptButtonModel::ScriptButtonModel()
{

}
/**
 *
 * @author Randall Wood
 */
///*public*/ class ScriptButtonModel extends AbstractStartupModel {

/*private*/ /*final*/ /*static*/ Logger* ScriptButtonModel::log = LoggerFactory::getLogger("ScriptButtonModel");

/*public*/ File* ScriptButtonModel::getScript() {
    return this->script;
}

/*public*/ void ScriptButtonModel::setScript(File* script) {
    this->script = script;
}

//@Override
/*public*/ QString ScriptButtonModel::toString() {
    return tr("<html>%1<br>%2</html>").arg(this->getName()).arg(this->getScript()->toString());
}

//@Override
/*public*/ void ScriptButtonModel::performAction(QString) throw (JmriException) {
    if (Apps::buttonSpace() != NULL) {
        QPushButton* b = new QPushButton((new ScriptButtonAction(this))->text());
        Apps::buttonSpace()->layout()->addWidget(b);
    } else if (Apps3::buttonSpace() != NULL) {
        QPushButton* b = new QPushButton((new ScriptButtonAction(this))->text());
        Apps3::buttonSpace()->layout()->addWidget(b);
    }
}

//    /*private*/ static class ScriptButtonAction extends AbstractAction {

//        ScriptButtonModel model;

    /*public*/ ScriptButtonAction::ScriptButtonAction(ScriptButtonModel* model) {
        this->model = model;
        AbstractAction::putValue(Action::NAME, model->getName());
    }

    //@Override
    /*public*/ void ScriptButtonAction::actionPerformed(ActionEvent* /*e*/) {
        try {
            JmriScriptEngineManager::getDefault()->eval(model->getScript());
        } catch (/*ScriptException | */IOException ex) {
            model->log->error(tr("Unable to run script %1.").arg(model->getScript()->toString()), ex);
        }
    }

