#include "logframe.h"
#include <QBoxLayout>
#include "logpanel.h"

//LogFrame::LogFrame()
//{

//}
/**
 * Frame for adding to the log file.
 *
 * @author	Bob Jacobsen Copyright (C) 2007
 */
// /*public*/ class LogFrame extends jmri.util.JmriJFrame {

/*public*/ LogFrame::LogFrame(QWidget* parent ) : JmriJFrame(parent){
    //super();
}

//@Override
/*public*/ void LogFrame::initComponents() throw (Exception) {

    setTitle("Make Log Entry");
    QVBoxLayout* thisLayout;
    getContentPane()->setLayout(thisLayout = new QVBoxLayout()); //(getContentPane(), BoxLayout.Y_AXIS));

    thisLayout->addWidget(new LogPanel());

    adjustSize();
}
/*public*/ QString LogFrame::getClassName()
{
 return "jmri.jmrit.frame.LogFrame";
}
