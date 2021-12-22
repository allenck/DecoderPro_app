#include "nixieclockframe.h"
#include "instancemanager.h"
#include "editor.h"
#include "simpletimebase.h"
#include <QVector>
#include <QStatusBar>
/**
 * Frame providing a simple clock showing Nixie tubes.
 * <P>
 * A Run/Stop button is built into this, but because I
 * don't like the way it looks, it's not currently
 * displayed in the GUI.
 *
 *
 * @author			Ken Cameron   Copyright (C) 2007
 * @version			$Revision: 22216 $
 *
 * This was a very direct steal from the Nixie clock code, ver 1.12.
 * Thank you Bob Jacobson.
 *
 */
//public class LcdClockFrame extends JmriJFrame implements java.beans.PropertyChangeListener {


    //"base" variables used to hold original gifs, other variables used with scaled images

/*public*/ NixieClockFrame::NixieClockFrame(QObject *parent) : JmriJFrame("Nixie Clock", parent)
{
 log = new Logger("NixieClockFrame");
 tubes =  QVector<NamedIcon*>(10, NULL);
 baseTubes =  QVector<NamedIcon*>(10, NULL);
 statusBar()->setVisible(false);
 setWindowTitle("Nixie Clock");
 resize(60,32);

 clock = static_cast<Timebase*>(InstanceManager::getDefault("Timebase"));
 h1 = new JLabel();
 h2 = new JLabel();
 m1 = new JLabel();
 m2 = new JLabel();
 colon = new JLabel;
 QWidget* centralWidget = new QWidget();
 setCentralWidget(centralWidget);
 QHBoxLayout* l;
 centralWidget->setLayout(l = new QHBoxLayout);
 l->setMargin(0);
 l->setContentsMargins(0,0,0,0);
 l->setSpacing(0);
 //Load the images (these are now the larger version of the original gifs
 for (int i = 0; i < 10; i++)
 {
  baseTubes.replace(i, new NamedIcon(":/resources/icons/misc/Nixie/M" + QString("%1").arg(i) + "B.gif", ":/resources/icons/misc/Nixie/M" + QString("%1").arg(i) + "B.gif"));
  tubes.replace(i, new NamedIcon(":/resources/icons/misc/Nixie/M" + QString("%1").arg(i) + "B.gif", ":/resources/icons/misc/Nixie/M" + QString("%1").arg(i) + "B.gif"));
 }
 colonIcon = new NamedIcon(":/resources/icons/misc/Nixie/colonB.gif", ":/resources/icons/misc/LCD/colonb.gif");
 baseColon = new NamedIcon(":/resources/icons/misc/Nixie/colonB.gif", ":/resources/icons/misc/Nixie/colonB.gif");
 // set initial size the same as the original gifs
 for (int i = 0; i < 10; i++)
 {
  QImage scaledImage = baseTubes.at(i)->getImage().scaled(23,32);
  NamedIcon* icon = tubes.at(i);
  icon->setImage(scaledImage);
 }
 QImage scaledImage = baseColon->getImage().scaled(12,32);
 colonIcon->setImage(scaledImage);

 // determine aspect ratio of a single digit graphic
 iconAspect = 24./32.;

 // determine the aspect ratio of the 4 digit base graphic plus a half digit for the colon
 // this DOES NOT allow space for the Run/Stop button, if it is
 // enabled.  When the Run/Stop button is enabled, the layout will have to be changed
 aspect =  (4.5*24.)/32.;

 // listen for changes to the timebase parameters
// ((SimpleTimebase*)clock)->PropertyChangeSupport::addPropertyChangeListener((PropertyChangeListener*)this);
 connect(clock, SIGNAL(minuteTick()), this, SLOT(update()));


 // init GUI
 m1 = new JLabel(tubes.at(0));
 m2 = new JLabel(tubes.at(0));
 h1 = new JLabel(tubes.at(0));
 h2 = new JLabel(tubes.at(0));
 colon = new JLabel(colonIcon);
 getContentPane()->setLayout(new QHBoxLayout(getContentPane()/*, BoxLayout.X_AXIS*/));
    getContentPane()->layout()->addWidget(h1);
    getContentPane()->layout()->addWidget(h2);
    getContentPane()->layout()->addWidget(colon);
    getContentPane()->layout()->addWidget(m1);
    getContentPane()->layout()->addWidget(m2);

    getContentPane()->layout()->addWidget(b = new QPushButton(tr("Stop")));
//    b.addActionListener( new ButtonListener());
    // since Run/Stop button looks crummy, don't display for now
    b->setVisible(false);

 update();
 pack();

 // request callback to update time
 clock->addMinuteChangeListener( this);
 //connect(clock, SIGNAL(propertyChange(PropertyChangeEvent*)), this, SLOT(propertyChange(PropertyChangeEvent*)));
//    {
//     /*public*/ void propertyChange(PropertyChangeEvent* e)
//     {
//      update();
//     }
//    });

    SimpleTimebase* c = (SimpleTimebase*) clock;
    connect(c, SIGNAL(minuteTick()), this, SLOT(update()));
    // Add component listener to handle frame resizing event
//    this->addComponentListener(
//                    new ComponentAdapter()
//            {
//                public void componentResized(ComponentEvent e)
//                {
//                    scaleImage();
//                }
//            });

}


// Added method to scale the clock digit images to fit the
// size of the display window

/*public*/ void NixieClockFrame::scaleImage() {
  int iconHeight;
  int iconWidth;

  int frameHeight = this->getContentPane()->size().height();
  int frameWidth = this->getContentPane()->size().width();
  if ((double)frameWidth / (double)frameHeight > aspect) {
    iconHeight = frameHeight;
    iconWidth = (int) (iconAspect * iconHeight);
  }
  else {
    //this DOES NOT allow space for the Run/Stop button, if it is
    //enabled.  When the Run/Stop button is enabled, the layout will have to be changed
    iconWidth = (int) (frameWidth / 4.5);
    iconHeight = (int) (iconWidth / iconAspect);
  }
#if 0
  for (int i = 0; i < 10; i++) {
    QImage scaledImage = baseTubes[i]->getImage().getScaledInstance(iconWidth,iconHeight,Image.SCALE_SMOOTH);
    tubes[i].setImage(scaledImage);
  }
  QImage scaledImage = baseColon->getImage().getScaledInstance(iconWidth/2,iconHeight,Image.SCALE_SMOOTH);
  colonIcon->setImage(scaledImage);

//      Ugly hack to force frame to redo the layout.
//      Without this the image is scaled but the label size and position doesn't change.
//      doLayout() doesn't work either
  this->setVisible(false);
//  this->remove(b);
//  this->getContentPane().add(b);
  this->setVisible(true);
#endif
  for (int i = 0; i < 10; i++)
  {
   QImage scaledImage = baseTubes.at(i)->getImage().scaled(23,32);
   NamedIcon* icon = tubes.at(i);
   icon->setImage(scaledImage);

  }
  QImage scaledImage = baseColon->getImage().scaled(12,32);
  colonIcon->setImage(scaledImage);
  return ;
}

//@SuppressWarnings("deprecation")
void NixieClockFrame::update()
{
 QDateTime now = clock->getTime();
 int hours = now.time().hour();
 int minutes = now.time().minute();

 h1->setIcon(tubes[hours/10]);
 h2->setIcon(tubes[hours-(hours/10)*10]);
 m1->setIcon(tubes[minutes/10]);
 m2->setIcon(tubes[minutes-(minutes/10)*10]);
 JmriJFrame::update();
}
//void NixieClockFrame::paint(QGraphicsScene* g)
//{
// QDateTime now = ((SimpleTimebase*)clock)->getTime();
// int hours = now.time().hour();
// int minutes = now.time().minute();
// double x = getLocation().x();
// double y = getLocation().y();

// if(this->g == NULL)
//  this->g = g;
// if(_itemGroup != NULL && _itemGroup->scene() != 0)
// {
//  g->removeItem(_itemGroup);
// }
// _itemGroup = new QGraphicsItemGroup();
// //h1.setIcon(tubes[hours/10]);
// h1 = new JLabel(QPixmap::fromImage(tubes.at(hours/10)->getOriginalImage()));
// h1->setPos(x,y);
// x += h1->boundingRect().width();
// _itemGroup->addToGroup(h1);
// //h2.setIcon(tubes[hours-(hours/10)*10]);
// h2 = new JLabel(QPixmap::fromImage(tubes.at(hours%10)->getOriginalImage()));
// h2->setPos(x,y);
// x += h2->boundingRect().width();
// _itemGroup->addToGroup(h2);
// colon = new JLabel(QPixmap::fromImage(colonIcon->getOriginalImage()));
// colon->setPos(x,y);
// x += colon->boundingRect().width();
// _itemGroup->addToGroup(colon);
// //m1.setIcon(tubes[minutes/10]);
// m1 = new JLabel(QPixmap::fromImage(tubes.at(minutes/10)->getOriginalImage()));
// m1->setPos(x,y);
// x += m1->boundingRect().width();
// _itemGroup->addToGroup(m1);
// //m2.setIcon(tubes[minutes-(minutes/10)*10]);
// m2 = new JLabel(QPixmap::fromImage(tubes.at(minutes%10)->getOriginalImage()));
// m2->setPos(x,y);
// x += m2->boundingRect().width();
// _itemGroup->addToGroup(m2);
// //log->debug(tr("NixieClock Width = %1, height = %2").arg(_itemGroup->boundingRect().width()).arg(_itemGroup->boundingRect().height()));
// g->addItem(_itemGroup);
//}

/*public*/ void NixieClockFrame::dispose() {
    //QWidget::dispose();
}

/**
 * Handle a change to clock properties
 */
/*public*/ void NixieClockFrame:: propertyChange(PropertyChangeEvent* /*e*/) {
    bool now = ((SimpleTimebase*)clock)->getRun();
//    if (now) b.setText("Stop");
//    else b.setText("Run");
}


//private class ButtonListener implements ActionListener {
//    public void actionPerformed(ActionEvent a) {
//        boolean next = !clock.getRun();
//        clock.setRun(next);
//        if (next) b.setText("Stop");
//        else b.setText("Run ");
//    }
//}

/*public*/ QString NixieClockFrame::getClassName()
{
 return "jmri.jmrit.analogclock.NixieClockFrame";
}
