#include "pickframe.h"
#include "../LayoutEditor/picklistmodel.h"
#include <QMenuBar>
#include "../LayoutEditor/pickpanel.h"
#include <QVBoxLayout>

//PickFrame::PickFrame(QWidget *parent) :
//    JmriJFrame(parent)
//{
//}
//public class PickFrame extends JmriJFrame {

/*public*/ PickFrame::PickFrame(QString title, QWidget *parent) : JmriJFrame(title, parent){
    setWindowTitle(title);
    /*
    addWindowListener(new java.awt.event.WindowAdapter() {
            public void windowClosing(java.awt.event.WindowEvent e) {
                dispose();
            }
        });
    */
    makeMenus();

    QList<PickListModel*> models = QList<PickListModel*>() << PickListModel::turnoutPickModelInstance() <<
                                PickListModel::sensorPickModelInstance() <<
                                PickListModel::signalHeadPickModelInstance() <<
                                PickListModel::signalMastPickModelInstance() <<
                                PickListModel::memoryPickModelInstance() <<
                                PickListModel::reporterPickModelInstance() <<
                                PickListModel::lightPickModelInstance() <<
                                PickListModel::warrantPickModelInstance() <<
                                PickListModel::oBlockPickModelInstance() <<
                                PickListModel::conditionalPickModelInstance() <<
                                PickListModel::entryExitPickModelInstance()

        ;
    //setContentPane(new PickPanel(models));
    //centralWidget()->layout()->addWidget(new PickPanel(models, this));
    setCentralWidget(new PickPanel(models, this));
    setVisible(true);
    pack();
}

/*private*/ void PickFrame::makeMenus() {
    QMenuBar* menuBar = new QMenuBar();
    //JMenu fileMenu = new JMenu(rb.getString("MenuFile"));
    //fileMenu.add(new jmri.configurexml.SaveMenu());
    //menuBar.add(fileMenu);
    setMenuBar(menuBar);
    addHelpMenu("package.jmri.jmrit.picker.PickTables", true);
}

// initialize logging
//static org.apache.log4j.Logger log = org.apache.log4j.Logger.getLogger(PickFrame.class.getName());
//}
/*public*/ QString PickFrame::getClassName()
{
 return "jmri.jmrit.picker.PickFrame";
}
