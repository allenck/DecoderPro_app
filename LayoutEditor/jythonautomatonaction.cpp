#include "jythonautomatonaction.h"
#include "QFileDialog"
#include "fileutil.h"
#include "jythonautomaton.h"
#include <QWidget>
#include <QObject>

//JythonAutomatonAction::JythonAutomatonAction(QObject *parent) :
//  QAction(parent)
//{
//}
/**
 * Swing action to create and register a JythonAutomaton object
 *
 * @author	Bob Jacobsen Copyright (C) 2003, 2007
 * @version $Revision: 28746 $
 */
///*public*/ class JythonAutomatonAction extends AbstractAction {

/**
 *
 */
//private static final long serialVersionUID = -6659056356505294196L;

/*public*/ JythonAutomatonAction::JythonAutomatonAction(QString s, QWidget* who)  : QAction(s, (QObject*)who)
{
    //super(s);
 _who = who;
 connect(this, SIGNAL(triggered()), this, SLOT(actionPerformed()));
}


/*public*/ void JythonAutomatonAction::actionPerformed(JActionEvent *  /*e*/)
{
    // create a SampleAutomaton
//    JFileChooser fci = jmri.jmrit.XmlFile.userFileChooser("Python script files", "py");
//    fci.setDialogTitle("Find desired script file");
//    int retVal = fci.showOpenDialog(_who);
//    // handle selection or cancel
//    if (retVal == JFileChooser.APPROVE_OPTION) {
//        File file = fci.getSelectedFile();
//        // create an object to handle script and run
//        (new JythonAutomaton(file.toString())).start();
//    }
 ((QWidget*)parent())->setCursor(Qt::WaitCursor);
 QString pathName = QFileDialog::getOpenFileName((QWidget*)parent(),tr("Find desired script file"),FileUtil::getProgramPath()+"jython" + QDir::separator(), "Python script files (*.py *.pyq)");
 ((QWidget*)parent())->setCursor(Qt::ArrowCursor);
 if(pathName == "") return;

 (new JythonAutomaton(pathName))->start();
}
