#include "jmrijframeaction.h"
#include "jmrijframe.h"
#include "class.h"
#include "logger.h"

JmriJFrameAction::JmriJFrameAction(QObject* parent) : AbstractAction(parent)
{

}
/**
 * Default form of action to create an object that's from a child class of
 * JmriJFrame. By using reflection, this cuts the loader dependency on the
 * loaded class.
 *
 * @author	Bob Jacobsen Copyright (C) 2007
 */
// /*public*/ class JmriJFrameAction extends AbstractAction {

/*public*/ JmriJFrameAction::JmriJFrameAction(QString s, QObject* parent) : AbstractAction(s, parent)
{
 log = new Logger("JmriJFrameAction");
    //super(s);
 //connect(this, SIGNAL(triggered(bool)), this, SLOT(actionPerformed()));
}

/**
 * Method to be overridden to make this work. Provide a completely qualified
 * class name, must be castable to JmriJFrame
 *
 * @return the default implementation returns an empty String
 */
// why isn't this abstract?
/*public*/ QString JmriJFrameAction::getName() {
    return "";
}

//@Override
/*public*/ void JmriJFrameAction::actionPerformed()
{
    QString name = getName();
    QString className = name.mid(name.lastIndexOf(".")+1);
    JmriJFrame* j = NULL;

    if (name != (""))
    {
        try {
            j = (JmriJFrame*) Class::forName(className); //.newInstance();
            j->initComponents();
            j->setVisible(true);
        } catch (ClassNotFoundException* ex1) {
            log->error("Couldn't create window, because couldn't find class: " + ex1->getMessage());
        } catch (Exception* ex2) {
            log->error("Exception creating frame: " + ex2->getMessage());
        }
    }
}
