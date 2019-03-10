#include "throttlestablecellrenderer.h"
#include "namedicon.h"
#include "rostericonfactory.h"
#include "borderlayout.h"
#include <QWidget>
#include <QFrame>
#include "throttlewindow.h"
#include <QLabel>
#include <QProgressBar>
#include "jlabel.h"
#include "throttleframemanager.h"
#include "throttlespreferences.h"

ThrottlesTableCellRenderer::ThrottlesTableCellRenderer(QObject *parent) :
    QObject(parent)
{
}
// /*public*/ class ThrottlesTableCellRenderer implements TableCellRenderer {
///*private*/ /*static*/ /*final*/ NamedIcon* ThrottlesTableCellRenderer::fwdIcon = new NamedIcon("program:resources/icons/throttles/up-green.png",":/resources/icons/throttles/up-green.png");
///*private*/ /*static*/ /*final*/ NamedIcon* ThrottlesTableCellRenderer::bckIcon = new NamedIcon("program:resources/icons/throttles/down-green.png",":/resources/icons/throttles/down-green.png");
///*private*/ /*static*/ /*final*/ NamedIcon* ThrottlesTableCellRenderer::estopIcon = new NamedIcon("program:resources/icons/throttles/estop24.png",":/resources/icons/throttles/estop24.png"); /*private*/ /*static*/ /*final*/ RosterIconFactory* ThrottlesTableCellRenderer::iconFactory =  new RosterIconFactory(32);
///*final*/ /*static*/ int ThrottlesTableCellRenderer::height = 42;

/*public*/ QWidget* ThrottlesTableCellRenderer::getTableCellRendererComponent(QTableView* jtable, QVariant value, bool bln, bool bln1, int i, int i1)
{
 fwdIcon = new NamedIcon("program:resources/icons/throttles/up-green.png",":/resources/icons/throttles/up-green.png");
 bckIcon = new NamedIcon("program:resources/icons/throttles/down-green.png",":/resources/icons/throttles/down-green.png");
 estopIcon = new NamedIcon("program:resources/icons/throttles/estop24.png",":/resources/icons/throttles/estop24.png"); /*private*/ /*static*/
 iconFactory =  new RosterIconFactory(32);
 height = 42;
 QFrame* retPanel = new QFrame();
 QVBoxLayout* retPanelLayout;
 retPanel->setLayout(retPanelLayout = new QVBoxLayout());

 if (value == QVariant())
 {
  return retPanel;
 }

 //ThrottleFrame tf = (ThrottleFrame) value;
 ThrottleWindow* tf = VPtr<ThrottleWindow>::asPtr(value);
 ImageIcon* icon = NULL;
 QString text = "";
 if (tf->getRosterEntry() != NULL)
 {
  //icon = iconFactory->getIcon(tf->getAddressPanel().getRosterEntry());
  icon = ThrottlesTableCellRenderer::iconFactory->getIcon(tf->getRosterEntry()->getIconPath());
  //text = tf->getAddressPanel().getRosterEntry().getId();
  text = tf->getRosterEntry()->getId();
 }
// else if ((tf->getAddressPanel().getCurrentAddress() != NULL) && (tf.getAddressPanel().getThrottle() != NULL))
// {
//        if (tf->getAddressPanel().getCurrentAddress().getNumber() == 0) {
//            text = tr("Default DC control") + " - " + tf->getAddressPanel().getCurrentAddress();
//        } else if (tf->getAddressPanel().getCurrentAddress().getNumber() == 3) {
//            text = tr("Default DCC control") + " - " + tf->getAddressPanel().getCurrentAddress();
//        } else {
//            text = tr("ThrottleAddress") + " " + tf->getAddressPanel().getCurrentAddress();
//        }
// }
 else
 {
  text = tr("Not assigned");
 }
//    if (icon != NULL) {
//        icon->setImageObserver(jtable);
//    }
 JLabel* locoID = new JLabel();
//    locoID->setHorizontalAlignment(JLabel.CENTER);
//    locoID.setVerticalAlignment(JLabel.CENTER);
 locoID->setAlignment(Qt::AlignCenter);
 locoID->setVisible(true);
 if(icon != NULL)
  locoID->setIcon(new NamedIcon(icon->location(), icon->description()));
 locoID->setText(text);
 retPanelLayout->addWidget(locoID, 0,Qt::AlignCenter);

 //if (tf->getAddressPanel().getThrottle()!=NULL)
 if(tf->getRosterEntry() != NULL && tf->getThrottle() != NULL)
 {
  QWidget* ctrlPanel = new QWidget();
  QHBoxLayout* ctrlPanelLayout;
  ctrlPanel->setLayout(ctrlPanelLayout = new QHBoxLayout());
  //Throttle* thr = tf->getAddressPanel().getThrottle();
  Throttle* thr = tf->getThrottle();
  JLabel* dir = new JLabel();
  if (ThrottleFrameManager::instance()->getThrottlesPreferences()->isUsingExThrottle()
                && ThrottleFrameManager::instance()->getThrottlesPreferences()->isUsingFunctionIcon())
  {
   if (thr->getIsForward())
   {
    dir->setIcon(fwdIcon);
    dir->setText(tr("Forward"));
   }
   else
   {
    dir->setIcon(bckIcon);
    dir->setText(tr("Reverse"));
   }
   dir->setVisible(true);
  }
  else
  {
   if (thr->getIsForward())
   {
    dir->setText(tr("Forward"));
   }
   else
   {
    dir->setText(tr("Reverse"));
   }
  }
  dir->setAlignment(Qt::AlignVCenter);
  ctrlPanelLayout->addWidget(dir, 0, Qt::AlignLeft);
  if (ThrottleFrameManager::instance()->getThrottlesPreferences()->isUsingExThrottle()
        && ThrottleFrameManager::instance()->getThrottlesPreferences()->isUsingFunctionIcon())
  {
   if (thr->getSpeedSetting()==-1)
   {
    JLabel* estop = new JLabel();
    estop->resize( QSize(64, height - 8));
    estop->setAlignment(Qt::AlignHCenter);
    estop->setIcon(estopIcon);
    ctrlPanelLayout->addWidget(estop, 0, Qt::AlignCenter);
   }
   else
   {
    QProgressBar* speedBar = new QProgressBar();
    speedBar->setMinimumSize( QSize(64, height - 8));
    speedBar->setMinimum(0);
    speedBar->setMaximum(100);
    speedBar->setValue((int) (thr->getSpeedSetting() * 100.0));
    ctrlPanelLayout->addWidget(speedBar, 0, Qt::AlignCenter);
   }
  }
  else
  {
   QLabel* speedLabel = new QLabel("");
   if (thr->getSpeedSetting()==-1)
   {
    speedLabel->setText(" "+tr("EStop")+" ");
   }
   else
   {
    speedLabel->setText(QString::number(thr->getSpeedSetting() * 100.0)+"% ");
   }
   ctrlPanelLayout->addWidget(speedLabel, 0, Qt::AlignCenter);
  }
  retPanelLayout->addWidget(ctrlPanel, 0, Qt::AlignLeft);
 }

 //retPanel.setBorder(BorderFactory.createBevelBorder(BevelBorder.RAISED));
 retPanel->setFrameStyle(QFrame::Raised);
 retPanel->setLineWidth(2);
 return retPanel;
}
