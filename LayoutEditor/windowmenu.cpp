#include "windowmenu.h"
#include "windowinterface.h"
#include "jmrijframe.h"
#include "panelmenu.h"
#include <QSignalMapper>

WindowMenu::WindowMenu(QWidget *parent) :
    QMenu(parent)
{
}
/**
 * Creates a menu showing all open windows
 * and allows to bring one in front
 * <P>
 * @author	Giorgio Terdina   Copyright 2008
 * @version     $Revision: 22529 $
 * 18-Nov-2008 GT Replaced blank menu lines, due to untitled windows, with "Untitled" string
 */

///*public*/ class WindowMenu extends JMenu implements javax.swing.event.MenuListener {


/*public*/ WindowMenu::WindowMenu(WindowInterface* wi, QWidget *parent) : QMenu(tr("Window"), parent){
    //super(Bundle.getMessage("MenuWindow"));
    parentFrame = (QFrame*)parent;
    //addMenuListener(this);
    connect(this, SIGNAL(aboutToShow()), this, SLOT(menuSelected()));
}


/*public*/ void WindowMenu::menuSelected(/*MenuEvent e*/)
{
 QString windowName;
 framesList = JmriJFrame::getFrameList();
 clear();

//    add(new AbstractAction(Bundle.getMessage("MenuItemMinimize")){
//        /*public*/ void actionPerformed(ActionEvent e) {
//            // the next line works on Java 2, but not 1.1.8
//            if (parentFrame != null) {
//                parentFrame.setState(Frame.ICONIFIED);
//            }
//        }
//    });
#if 1
 //addSeparator();

 int framesNumber = framesList->size();
 QSignalMapper* sm = new QSignalMapper();
 for (int i = 0; i < framesNumber; i++)
 {
  JmriJFrame* iFrame = framesList->at(i);
  windowName = iFrame->windowTitle();
  if(windowName==("")) windowName = "Untitled";
  AbstractAction* newItem = new AbstractAction(windowName, this);
  sm->setMapping(newItem, iFrame);
  connect(newItem, SIGNAL(triggered()), sm, SLOT(map()));

//  {
//            /*public*/ void actionPerformed(ActionEvent e) {
//                JMenuItem selectedItem = (JMenuItem)e.getSource();
//                // Since different windows can have the same name, look for the position of the selected menu item
//                int itemCount = getItemCount();
//                // Skip possible other items at the top of the menu (e.g. "Minimize")
//                int firstItem = itemCount - framesList.size();
//                for (int i = firstItem; i < itemCount; i++) {
//                    if(selectedItem == getItem(i)) {
//                        i -= firstItem;
//                        // Retrieve the corresponding window
//                        if(i < framesList.size()) {	// "i" should always be < framesList.size(), but it's better to make sure
//                            framesList.get(i).setVisible(true);
//                            framesList.get(i).setExtendedState(Frame.NORMAL);
//                            return;
//                        }
//                    }
//                }
//            }
//        });
// ??        if(iFrame == parentFrame) newItem->setState(true);
        addAction(newItem);
    }
#endif
 connect(sm, SIGNAL(mapped(QWidget*)), this, SLOT(onItem(QWidget*)));
 //PanelMenu::instance()->updatePanelMenu(this);
}


void WindowMenu::onItem(QWidget* iFrame)
{
#if 0
           /*public*/ void actionPerformed(ActionEvent e) {
               JMenuItem selectedItem = (JMenuItem)e.getSource();
               // Since different windows can have the same name, look for the position of the selected menu item
               int itemCount = getItemCount();
               // Skip possible other items at the top of the menu (e.g. "Minimize")
               int firstItem = itemCount - framesList.size();
               for (int i = firstItem; i < itemCount; i++) {
                   if(selectedItem == getItem(i)) {
                       i -= firstItem;
                       // Retrieve the corresponding window
                       if(i < framesList.size()) {	// "i" should always be < framesList.size(), but it's better to make sure
                           framesList.get(i).setVisible(true);
                           framesList.get(i).setExtendedState(Frame.NORMAL);
                           return;
                       }
                   }
               }
           }
       });
 #endif
 JmriJFrame* jFrame = static_cast<JmriJFrame*>(iFrame);
 jFrame->setVisible(true);
}

///*public*/ void menuDeselected(MenuEvent e) {}
///*public*/ void menuCanceled(MenuEvent e) {}
