#include "inputwindowaction.h"
#include "jframe.h"
#include <QBoxLayout>
#include "inputwindow.h"
#include "PythonQt.h"
//#include "PythonQt_QtAll.h"
#include "jmrijframe.h"
#include "jmriuserpreferencesmanager.h"
#include "instancemanager.h"
#include "userpreferencesmanager.h"


//InputWindowAction::InputWindowAction(QObject *parent) :
//  AbstractAction(parent)
//{
//}
/**
 * This Action runs creates an InputWindow for sending input to the global
 * jython interpreter
 *
 * @author	Bob Jacobsen Copyright (C) 2004
 * @version $Revision: 28746 $
 */
// /*public*/ class InputWindowAction extends AbstractAction {

/**
 *
 */
//private static final long serialVersionUID = 7519659048278662430L;

/**
 * Constructor just initializes parent class.
 *
 * @param name Action name
 */
/*public*/ InputWindowAction::InputWindowAction(QString name, QObject *parent) :
  AbstractAction(name, parent)
{
 //super(name);
 common();
}

/*public*/ InputWindowAction::InputWindowAction(QObject *parent) :
  AbstractAction(tr("Script Input Window"),parent)
{
 //super("Script Input Window");
 common();
}
void InputWindowAction::common()
{
 pref = (UserPreferencesManager*)InstanceManager::getDefault("UserPreferencesManager");
 connect(this, SIGNAL(triggered()), this, SLOT(actionPerformed()));
}

/**
 * Invoking this action via an event triggers display of a file dialog. If a
 * file is selected, it's then invoked as a script.
 *
 * @param e
 */
/*public*/ void InputWindowAction::actionPerformed(JActionEvent * /*e*/)
{
 //PythonInterp.getPythonInterpreter();
 PythonQt::self()->getMainModule();

//    java.util.ResourceBundle rb = java.util.ResourceBundle.getBundle("jmri.jmrit.jython.JythonBundle");

 f = new JmriJFrameX(tr("Script Entry"));
 //f.getContentPane().setLayout(new javax.swing.BoxLayout(f.getContentPane(), javax.swing.BoxLayout.Y_AXIS));
 QWidget* centralWidget = new QWidget;
 QBoxLayout* centralWidgetLayout = new QVBoxLayout();
 centralWidget->setLayout(centralWidgetLayout);
 f->setCentralWidget(centralWidget);
 centralWidgetLayout->addWidget(new InputWindow());
 f->addWindowListener(new IWWindowListener(this));

 f->pack();
 if(pref->getSaveWindowLocation(QString(this->metaObject()->className())))
 {
  f->move(pref->getWindowLocation(QString(this->metaObject()->className())));
 }

 if(pref->getSaveWindowSize(QString(this->metaObject()->className())))
 {
  f->resize(pref->getWindowSize(QString(this->metaObject()->className())));
 }
 else
  f->resize(800, 400);

 f->setVisible(true);

}

/*public*/ JFrame* InputWindowAction::getFrame() {
    return f;
}

IWWindowListener::IWWindowListener(InputWindowAction *parent)
{
 this->parent = parent;
}

void IWWindowListener::windowClosing(QCloseEvent */*e*/)
{
 //parent->pref->setSaveWindowLocation(QString(parent->metaObject()->className()),true);
 parent->pref->setWindowLocation(QString(parent->metaObject()->className()), parent->f->pos());
 //parent->pref->setSaveWindowSize(QString(parent->metaObject()->className()),true);
 parent->pref->setWindowSize(QString(parent->metaObject()->className()), parent->f->size());
}
