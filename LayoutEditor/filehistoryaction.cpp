#include "filehistoryaction.h"
#include "jmrijframe.h"
#include "jtextarea.h"
#include <QScrollArea>
#include "filehistory.h"
#include "instancemanager.h"

//FileHistoryAction::FileHistoryAction(QObject *parent) :
//  AbstractAction(parent)
//{
//}
/**
 * Swing action to display the file revision history
 *
 * @author	Bob Jacobsen Copyright (C) 2009
 * @version $Revision: 28746 $
 */
///*public*/ class FileHistoryAction extends AbstractAction {

/**
 *
 */
//private static final long serialVersionUID = -7063215106558684398L;

/*public*/ FileHistoryAction::FileHistoryAction(QString s,QObject *parent) :
  AbstractAction(s, parent) {
  //super(s);
 common();
}

/*public*/ FileHistoryAction::FileHistoryAction(QObject *parent) :
  AbstractAction(tr("File History"), parent) {
    //this("File History");
 common();
}

void FileHistoryAction::common()
{
 connect(this, SIGNAL(triggered()), this, SLOT(actionPerformed()));
}

/*public*/ void FileHistoryAction::actionPerformed(JActionEvent * /*e*/)
{
 JFrame* frame = new JmriJFrameX("FileHistory");
//    {

//        /**
//         *
//         */
//        private static final long serialVersionUID = 6117481384011187775L;
//    };  // JmriJFrame to ensure fits on screen

 JTextArea* pane = new JTextArea();
 pane->append("\n"); // add a little space at top
 pane->setReadOnly(true);

 QScrollArea* scroll = new QScrollArea(pane);
 //frame.getContentPane().add(scroll);
 frame->setCentralWidget(scroll);
 scroll->setWidgetResizable(true);
 scroll->setWidget(pane);

 FileHistory* r = (FileHistory*)InstanceManager::getDefault("FileHistory");
 if (r == NULL)
 {
  pane->append("<No History Found>\n");
 }
 else
 {
  pane->append(r->toString());
 }

 pane->append("\n"); // add a little space at bottom

 //frame.pack();
 frame->adjustSize();

 // start scrolled to top
// JScrollBar b = scroll.getVerticalScrollBar();
// b.setValue(b.getMaximum());

 // show
 frame->setVisible(true);
}
