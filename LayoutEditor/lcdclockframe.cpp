#include "lcdclockframe.h"
#include "instancemanager.h"
#include "editor.h"
#include "simpletimebase.h"
#include <QStatusBar>
//LcdClockFrame::LcdClockFrame(QWidget *parent) :
//    QWidget(parent)
//{
//}
/**
 * Frame providing a simple clock showing Lcd tubes.
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

/*public*/ LcdClockFrame::LcdClockFrame( QWidget *parent) : JmriJFrame("Lcd Clock", true, true, parent)
{
 //super(Bundle.getMessage("MenuItemLcdClock"));
 log = new Logger("Lcd Clock");
 tubes =  QVector<NamedIcon*>(10, NULL);
 baseTubes =  QVector<NamedIcon*>(10, NULL);
 statusBar()->setVisible(false);
 setWindowTitle("Lcd Clock");
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

 b = new QPushButton();

 //Load the images (these are now the larger version of the original gifs
 for (int i = 0; i < 10; i++)
 {
  baseTubes.replace(i, new NamedIcon(":/resources/icons/misc/LCD/Lcd_" + QString("%1").arg(i) + "b.GIF", ":/resources/icons/misc/LCD/Lcd_" + QString("%1").arg(i) + "b.GIF"));
  tubes.replace(i, new NamedIcon(":/resources/icons/misc/LCD/Lcd_" + QString("%1").arg(i) + "b.GIF", ":/resources/icons/misc/LCD/Lcd_" + QString("%1").arg(i) + "b.GIF"));
 }
 colonIcon = new NamedIcon(":/resources/icons/misc/LCD/Lcd_Colonb.GIF", ":/resources/icons/misc/LCD/Lcd_Colonb.GIF");
 baseColon = new NamedIcon(":/resources/icons/misc/LCD/Lcd_Colonb.GIF", ":/resources/icons/misc/LCD/Lcd_Colonb.GIF");
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
 ((SimpleTimebase*)clock)->addPropertyChangeListener((PropertyChangeListener*)this);
// connect(clock, SIGNAL(propertyChange(PropertyChangeEvent*)), this, SLOT(propertyChange(PropertyChangeEvent*)));
 connect(clock, SIGNAL(minuteTick()), this, SLOT(update()));


 // init GUI
 m1 = new JLabel(tubes.at(0));
 m2 = new JLabel(tubes.at(0));
 h1 = new JLabel(tubes.at(0));
 h2 = new JLabel(tubes.at(0));
 colon = new JLabel(colonIcon);
//    getContentPane().setLayout(new BoxLayout(getContentPane(), BoxLayout.X_AXIS));
    getContentPane()->layout()->addWidget(h1);
    getContentPane()->layout()->addWidget(h2);
    getContentPane()->layout()->addWidget(colon);
    getContentPane()->layout()->addWidget(m1);
    getContentPane()->layout()->addWidget(m2);

    getContentPane()->layout()->addWidget(b = new QPushButton("Stop"));
//    b.addActionListener( new ButtonListener());
//    // since Run/Stop button looks crummy, don't display for now
    b->setVisible(false);

    update();
    pack();

    // request callback to update time
    //((SimpleTimebase*) clock)->addMinuteChangeListener( new PropertyChangeListener());
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
LcdClockFrame::~LcdClockFrame()
{
 delete log;
}

// Added method to scale the clock digit images to fit the
// size of the display window

/*public*/ void LcdClockFrame::scaleImage() {
  int iconHeight;
  int iconWidth;
#if 0
  int frameHeight = this->getContentPane().getSize().height;
  int frameWidth = this->getContentPane().getSize().width;
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
void LcdClockFrame::update()
{
 QDateTime now = clock->getTime();
 int hours = now.time().hour();
 int minutes = now.time().minute();
 h1->setIcon(tubes[hours/10]);
 h2->setIcon(tubes[hours-(hours/10)*10]);
 m1->setIcon(tubes[minutes/10]);
 m2->setIcon(tubes[minutes-(minutes/10)*10]);
 //log->debug(tr("LcdClock Width = %1, height = %2").arg(_itemGroup->boundingRect().width()).arg(_itemGroup->boundingRect().height()));
 JmriJFrame::update();
}

/*public*/ void LcdClockFrame::dispose() {
    //QWidget::dispose();
 JmriJFrame::dispose();
}

/**
 * Handle a change to clock properties
 */
/*public*/ void LcdClockFrame:: propertyChange(PropertyChangeEvent* /*e*/) {
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

/*public*/ QString LcdClockFrame::getClassName()
{
 return "jmri.jmrit.lcdclock.LcdClockFrame";
}
