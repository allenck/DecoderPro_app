#include "decoderpro3window.h"
#include "decoder3action.h"
#include <QApplication>
#include "apps3.h"

//DecoderPro3Window::DecoderPro3Window(QWidget *parent) :
//  RosterFrame(parent)
//{
//}
/**
 * Standalone DecoderPro3 Window.
 */
///*public*/  class DecoderPro3Window extends RosterFrame {

/**
 *
 */
//private static final long serialVersionUID = -7080210226059840968L;

/**
 * Loads Decoder Pro 3 with the default set of menus and toolbars
 */
/*public*/  DecoderPro3Window::DecoderPro3Window(QWidget *parent) :
  RosterFrame(QApplication::applicationName(), parent)
{
 //super(Application.getApplicationName());
}

/**
 * Loads Decoder Pro 3 with specific menu and toolbar files
 */
/*public*/  DecoderPro3Window::DecoderPro3Window(QString menuFile, QString toolbarFile, QWidget *parent) :
  RosterFrame(QApplication::applicationName(),
              menuFile,
              toolbarFile, parent)
{
//    super(Application.getApplicationName(),
//            menuFile,
//            toolbarFile);
}

void DecoderPro3Window::buildWindow()
{
 RosterFrame::buildWindow();
 this->setNewWindowAction(new Decoder3Action("newWindow", (WindowInterface*)this));
 this->allowQuit(true);
}

// for some reason, the super implementation does not get called automatically
//@Override
/*public*/  void DecoderPro3Window::remoteCalls(QStringList args)
{
 RosterFrame::remoteCalls(args);
}

//@Override
/*protected*/ void DecoderPro3Window::additionsToToolBar() {
    //This value may return null if the DP3 window has been called from a the traditional JMRI menu frame
    if (Apps3::buttonSpace() != nullptr) {
        getToolBar()->layout()->addWidget(Apps3::buttonSpace());
    }
    RosterFrame::additionsToToolBar();
}
