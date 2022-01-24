#include "abstractfilemodelfactory.h"
#include "loggerfactory.h"
#include "jfilechooser.h"
#include "startupactionsmanager.h"
#include "instancemanager.h"
#include "file.h"

AbstractFileModelFactory::AbstractFileModelFactory()
{
 chooser = NULL;
}
/**
 * Provide an abstract StartupModelFactory with common methods for factories
 * that manipulate models that open files.
 *
 * @author Randall Wood
 */
///*public*/ abstract class AbstractFileModelFactory implements StartupModelFactory {

/*private*/ /*final*/ /*static*/ Logger* AbstractFileModelFactory::log = LoggerFactory::getLogger("AbstractFileModelFactory");

//@Override
/*public*/ QString AbstractFileModelFactory::getDescription() {
    //return Bundle.getMessage(this->getModelClass().getCanonicalName());
 return QString(this->metaObject()->className());
}

/**
 * This factory simply displays a {@link javax.swing.JFileChooser} to allow
 * users to configure the action. Subclasses to performAction the correct file
chooser by implementing this method.
 *
 * @return a configured file chooser.
 */
/*abstract*/ /*protected*/ JFileChooser* AbstractFileModelFactory::setFileChooser() {return NULL;}

//@Override
/*public*/ QString AbstractFileModelFactory::getActionText() {
    return tr("%1...").arg(this->getDescription());
}

//@Override
/*public*/ void AbstractFileModelFactory::editModel(StartupModel* model, QWidget* parent) {
    //if (this->getModelClass().isInstance(model))
 if(Class::forName(this->getModelClass())->isInstance(model))
    {
        if (this->chooser == NULL) {
            this->chooser = this->setFileChooser();
            this->chooser->setDialogTitle(this->getDescription());
            this->chooser->setDialogType(JFileChooser::CUSTOM_DIALOG);
        }
        if (this->chooser->showOpenDialog(parent) == JFileChooser::APPROVE_OPTION) {
            try {
                QString name = model->getName();
                if (name == NULL || name != (this->chooser->getSelectedFile()->getCanonicalPath())) {
                    model->setName(this->chooser->getSelectedFile()->getCanonicalPath());
                    ((StartupActionsManager*)InstanceManager::getDefault("StartupActionsManager"))->setRestartRequired();
                }
            } catch (IOException* ex) {
                log->error(tr("File %1 does not exist.").arg(this->chooser->getSelectedFile()->toString()));
            }
        }
    }
}

//@Override
/*public*/ void AbstractFileModelFactory::initialize() {
    // nothing to do
}
