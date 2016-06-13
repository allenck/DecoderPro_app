#include "splashwindow.h"
#include "fileutil.h"
#include "jlabel.h"
#include "namedicon.h"
#include <QBoxLayout>
#include <QDesktopWidget>
#include <QApplication>

//SplashWindow::SplashWindow(QWidget *parent) :
//    JFrame(parent)
//{
//}
/**
 * A splash screen for showing during JMRI startup
 *
 * @author	Bob Jacobsen Copyright 2003
 * @author Dennis Miller Copyright 2007
 * @version $Revision: 28746 $
 */
///*public*/ class SplashWindow extends JFrame {

/**
 *
 */
//private static final long serialVersionUID = 300950834122464494L;

/*public*/ SplashWindow::SplashWindow(QWidget *parent)
    : JFrame("JMRI", parent)
{
 //super("JMRI");
 splashWindowDisplay(NULL);
}

/*public*/ SplashWindow::SplashWindow(QWidget* splashMsg, QWidget *parent)
    : JFrame("JMRI", parent)
{
 //super("JMRI");
 splashWindowDisplay(splashMsg);
}

/*public*/ void SplashWindow::splashWindowDisplay(QWidget* splashMsg)
{
 //this->setUndecorated(true);
 setWindowFlags(Qt::FramelessWindowHint);

 // get the splash image
    //MediaTracker mt = new MediaTracker(this);
    //splashIm = Toolkit.getDefaultToolkit().getImage(FileUtil.findURL("resources/logo.gif", FileUtil.Location.INSTALLED));
 splashIm = QImage(FileUtil::findURL("resources/logo.gif", FileUtil::INSTALLED).toString());
//    mt.addImage(splashIm, 0);
//    try {
//        mt.waitForID(0);
//    } catch (InterruptedException ie) {
//        Thread.currentThread().interrupt(); // retain if needed later
//    }

    //JLabel* l = new JLabel((NamedIcon*)new ImageIcon(splashIm, "JMRI splash screen"));
    JLabel* l = new JLabel(new NamedIcon(FileUtil::findURL("resources/logo.gif", FileUtil::INSTALLED).toString(),"JMRI splash screen"));
//    l.setOpaque(true);

 if (splashMsg != NULL)
 {
  QWidget* full = new QWidget();
  QVBoxLayout* fullLayout;
  full->setLayout(fullLayout = new QVBoxLayout); //(full, BoxLayout.Y_AXIS));
  l->setAlignment(Qt::AlignHCenter);
     //l->layout()->setAlignment(Qt::AlignCenter);
     //splashMsg->setAlignment(Qt::AlignHCenter);
  fullLayout->addWidget(l);
  fullLayout->addWidget(splashMsg, 0, Qt::AlignCenter);
     //getContentPane().add(full);
  setCentralWidget(full);
 }
 else
 {
  //getContentPane().add(l);
  setCentralWidget(l);
 }

 pack();

 /* Center the window and pad the frame size slightly to put some space
  * between logo and frame border*/
//    QSize screenDim
//            = Toolkit.getDefaultToolkit().getScreenSize();
 QDesktopWidget* desktop = QApplication::desktop();
 QSize screenDim = desktop->screen()->size();

 QRect winDim = frameGeometry();
 winDim.setHeight( winDim.height() + 10);
 winDim.setWidth( winDim.width() + 10);
 setLocation((screenDim.width() - winDim.width()) / 2,
            (screenDim.height() - winDim.height()) / 2);
 resize(winDim.width(), winDim.height());

 // and show
 setVisible(true);
}
