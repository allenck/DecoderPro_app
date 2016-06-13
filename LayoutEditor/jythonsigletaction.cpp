#include "jythonsigletaction.h"
#include "jythonsiglet.h"
#include <QFileDialog>
#include "fileutil.h"

//JythonSigletAction::JythonSigletAction(QObject *parent) :
//  QAction(parent)
//{
//}
/**
 * Swing action to create and register a JythonSiglet object
 *
 * @author	Bob Jacobsen Copyright (C) 2003, 2007
 * @version $Revision: 28746 $
 */
// /*public*/ class JythonSigletAction extends AbstractAction {

/**
 *
 */
//private static final long serialVersionUID = -7767646852999362415L;

/*public*/ JythonSigletAction::JythonSigletAction(QString s, QWidget* who) : QAction(s, (QObject*)who)
{
 //super(s);
 _who = who;
}


/*public*/ void JythonSigletAction::actionPerformed(ActionEvent* e) {
    // create a SampleAutomaton
//    JFileChooser fci = jmri.jmrit.XmlFile.userFileChooser("Python script files", "py");
//    fci.setDialogTitle("Find desired script file");
//    int retVal = fci.showOpenDialog(_who);
//    // handle selection or cancel
//    if (retVal == JFileChooser.APPROVE_OPTION) {
//        File file = fci.getSelectedFile();
//        // create an object to handle script and run
//        (new JythonSiglet(file.toString())).start();
//    }
 ((QWidget*)parent())->setCursor(Qt::WaitCursor);
 QString pathName = QFileDialog::getOpenFileName((QWidget*)parent(),tr("Find desired script file"),FileUtil::getProgramPath()+"jython" + QDir::separator(), "Python script files (*.py *.pyq)");
 ((QWidget*)parent())->setCursor(Qt::ArrowCursor);
 if(pathName == "") return;

 (new JythonSiglet(pathName))->start();
}
