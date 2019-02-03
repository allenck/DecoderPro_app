#include "analogclock2display.h"
#include "namedicon.h"
#include "editor.h"
#include "instancemanager.h"
#include "QPolygonF"
#include "coordinateedit.h"
#include "simpletimebase.h"

//AnalogClock2Display::AnalogClock2Display(QWidget *parent) :
//    PositionableJComponent(parent)
//{
//}
/**
 * <p>An Analog Clock for displaying in a panel</p>
 *
 * <p>Time code copied in part from code for the Nixie clock by Bob Jacobsen </p>
 *
 * @author  Howard G. Penny - Copyright (C) 2005
 * @version $Revision: 22320 $
 */
///*public*/ class AnalogClock2Display extends PositionableJComponent {

/*public*/ AnalogClock2Display::AnalogClock2Display(Editor* editor, QObject *parent) :
    PositionableIcon("Clock", editor, (Positionable*)parent) //PositionableJComponent(editor, parent)
{
 //super(editor);
 log = new Logger("AnalogClock2Display");
 clock = static_cast<Timebase*>(InstanceManager::getDefault("Timebase"));

 rate = (int) ((SimpleTimebase*)clock)->userGetRate();

 common();
}
AnalogClock2Display::~AnalogClock2Display()
{
 SimpleTimebase* t = (SimpleTimebase*)clock;
 disconnect(t, SIGNAL(minuteTick()), this, SLOT(update()));

 delete log;
 delete jmriIcon;
 delete scaledIcon;
 delete clockIcon;
 delete hourHand;
 delete minuteHand;
 delete _iconMap;
}

/*public*/ Positionable* AnalogClock2Display::deepClone()
{
 AnalogClock2Display* pos = new AnalogClock2Display(_editor);
 return finishClone((Positionable*)pos);
}

/*public*/ Positionable* AnalogClock2Display::finishClone(Positionable* p)
{
 AnalogClock2Display* pos = (AnalogClock2Display*)p;
 pos->setScale(getScale());
 //return PositionableJComponent::finishClone(pos);
 return PositionableLabel::finishClone((Positionable*)pos);
}

void AnalogClock2Display::common()
{
 hourX << -12 << -11 << -25 << -10 << -10 << 0 << 10 << 10 << 25 << 11 << 12;
 hourY << -31 << -163 << -170 << -211 << -276 << -285 << -276 << -211 << -170 << -163 << -31;
 minuteX << -12 << -11 << -24 << -11 << -11 << 0 << 11 << 11 << 24 << 11 << 12;
 minuteY<< -31<< -261<< -266<< -314<< -381<< -391<< -381<< -314<< -266<< -261<< -31;
 scaledHourX = QVector<int>(hourX.size());
 scaledHourY = QVector<int> (hourY.size());
 scaledMinuteX = QVector<int> (minuteX.size());
 scaledMinuteY = QVector<int> (minuteY.size());
 rotatedHourX = QVector<int> (hourX.size());
 rotatedHourY = QVector<int> (hourY.size());
 rotatedMinuteX = QVector<int> (minuteX.size());
 rotatedMinuteY = QVector<int> (minuteY.size());
 // Load the JMRI logo and clock face
 // Icons are the original size version kept for to allow for mulitple resizing
 // and scaled Icons are the version scaled for the panel size
 jmriIcon = new NamedIcon(":/resources/logo.gif", "resources/logo.gif");
 scaledIcon = new NamedIcon(":/resources/logo.gif", "resources/logo.gif");
 clockIcon = new NamedIcon(":/resources/clock2.gif", "resources/clock2.gif");
 logo = jmriIcon->getImage();
 clockFace = clockIcon->getImage();
 runMenu = NULL;
 // Create an unscaled set of hands to get the original size (height)to use
 // in the scaling calculations
 QVector<QPointF> ptHour;
 for(int i=0; i < 11; i++)
  ptHour.append(QPoint(hourX.at(i), hourY.at(i)));
 //QPolygonF* pHour = new QPolygonF(ptHour);
 hourHand = new QGraphicsPolygonItem(QPolygonF(ptHour),0);
 hourHeight = hourHand->boundingRect().size().height();
 QVector<QPointF> ptMinute;
 for(int i=0; i < 11; i++)
  ptMinute.append(QPoint(minuteX.at(i), minuteY.at(i)));
 //QPolygonF* pMinute = new QPolygonF(ptminute);
 minuteHand = new QGraphicsPolygonItem(QPolygonF(ptMinute));
 minuteHeight = minuteHand->boundingRect().size().height();

 amPm = "AM";
 _itemGroup = NULL;
 g =NULL;
 _bVisible = true;
 _icon = true;
 _text = false;
 _namedIcon = clockIcon;
 _iconMap = new QMap <QString, NamedIcon*>();

    // request callback to update time
//    clock->addMinuteChangeListener(new PropertyChangeListener()
//    {
//        /*public*/ void propertyChange(java.beans.PropertyChangeEvent e) {
//            update();
//        }
//    });
//    connect(clock, SIGNAL(minuteTick()), this, SLOT(update()));
    // request callback to update changes in properties
//    clock->addPropertyChangeListener(new java.beans.PropertyChangeListener() {
//        /*public*/ void propertyChange(java.beans.PropertyChangeEvent e) {
//            update();
//        }
//    });
 SimpleTimebase* t = (SimpleTimebase*)clock;
 connect(t, SIGNAL(minuteTick()), this, SLOT(update()));
 setSize(clockIcon->getIconHeight()); // set to default size
}


/*public*/ int AnalogClock2Display::getFaceWidth() {return faceSize;}
/*public*/ int AnalogClock2Display::getFaceHeight() {return faceSize;}

/*public*/ bool AnalogClock2Display::setScaleMenu(QMenu* popup)
{
 popup->addAction(new QAction("Fast Clock", this));
 QMenu* rateMenu = new QMenu("Clock rate");
 rateButtonGroup = new QActionGroup(this);
 mapper = new QSignalMapper(this);
 addRateMenuEntry(rateMenu, 1);
 addRateMenuEntry(rateMenu, 2);
 addRateMenuEntry(rateMenu, 4);
 addRateMenuEntry(rateMenu, 8);
 popup->addMenu(rateMenu);
 runMenu = new QAction(getRun() ? "Stop" : "Start",this);
//    runMenu->addActionListener(act = new QAction() {
//        /*public*/ void actionPerformed(ActionEvent e) {
//            setRun(!getRun());
//            update();
//        }
//    });
 connect(runMenu, SIGNAL(triggered()), this, SLOT(actActivated()));
 connect(mapper, SIGNAL(mapped(int)), this, SLOT(rateChange(int)));
 popup->addAction(runMenu);
 CoordinateEdit edit;
 popup->addAction(CoordinateEdit::getScaleEditAction((Positionable*)this, &edit));

 return true;
}

void AnalogClock2Display::actActivated() // SLOT[]
{
    setRun(!getRun());
    update();
}

/*public*/ QString AnalogClock2Display::getNameString() {
    return "Clock";
}

/*public*/ void AnalogClock2Display::setScale(double scale) {
    if (scale==1.0) {
        common();
        return;
    }
    //AffineTransform t = AffineTransform.getScaleInstance(scale, scale);
    int w = (int)qCeil(scale*clockIcon->getIconWidth());
    int h = (int)qCeil(scale*clockIcon->getIconHeight());
    //clockIcon.transformImage(w, h, t, null);
    clockIcon->reduceTo(w,h,100);
    w = (int)qCeil(scale*scaledIcon->getIconWidth());
    h = (int)qCeil(scale*scaledIcon->getIconHeight());
    //scaledIcon.transformImage(w, h, t, null);
    scaledIcon->reduceTo(w,h,100);
    w = (int)qCeil(scale*jmriIcon->getIconWidth());
    h = (int)qCeil(scale*jmriIcon->getIconHeight());
    //jmriIcon.transformImage(w, h, t, null);
    jmriIcon->reduceTo(w, h, 20);
    setSize(clockIcon->getIconHeight());
    scale *= getScale();
    //PositionableJComponent::setScale(scale);
    PositionableLabel::setScale(scale);
}

void AnalogClock2Display::addRateMenuEntry(QMenu* menu, /*final*/ int newrate)
{
 //JRadioButtonMenuItem button = new JRadioButtonMenuItem("" + newrate + ":1");
 QAction* button = new QAction(QString("%1:1").arg(newrate), this);
//    button.addActionListener(new ActionListener() {
//        final int r = newrate;
//        /*public*/ void actionPerformed(ActionEvent e) {
//            try {
//                clock.userSetRate(r);
//                rate = r;
//            }
//            catch (TimebaseRateException t) {
//                log.error("TimebaseRateException for rate= "+r+". "+t);
//            }
//        }
//    });

 rateButtonGroup->addAction(button);
 mapper->setMapping(button,newrate);
 connect(button, SIGNAL(triggered()), mapper, SLOT(map()));
 button->setCheckable(true);
 if (rate == newrate)
 {
  button->setChecked(true);
 }
 else
 {
  button->setChecked(false);
 }
 menu->addAction(button);
}
void AnalogClock2Display::rateChange(int rate) // SLOT[]
{
((SimpleTimebase*) clock)->userSetRate(rate);
 this->rate = rate;
}

/*public*/ void AnalogClock2Display::paint(QGraphicsScene* g)
{
 this->g = g;
 // overridden Paint method to draw the clock
 //g.translate(centreX, centreY);
 if(_itemGroup != NULL && _itemGroup->scene() != 0)
 {
  g->removeItem(_itemGroup);
 }
 _itemGroup = new MyGraphicsItemGroup();
 _itemGroup->setName("analogClock");

 QPointF locHands = QPointF(getLocation().x() + clockFace.width()/2, getLocation().y()+ clockFace.height()/2);

 // Draw the clock face
 //g.drawImage(clockFace, -faceSize / 2, -faceSize / 2, faceSize, faceSize, this);
 QGraphicsPixmapItem* itemFace = new QGraphicsPixmapItem(QPixmap::fromImage(clockFace));
 itemFace->setPos(getLocation());
 _itemGroup->addToGroup(itemFace);

 // Draw the JMRI logo
 //    g.drawImage(scaledLogo, -logoWidth / 2, -faceSize / 4, logoWidth,
 //                logoHeight, this);
// QGraphicsPixmapItem* itemLogo = new QGraphicsPixmapItem(QPixmap::fromImage(logo));
// itemLogo->setPos(getLocation());
// itemGroup->addToGroup(itemLogo);

 // Draw hour hand rotated to appropriate angle
 // Calculation mimics the AffineTransform class calculations in Graphics2D
 // Grpahics2D and AffineTransform not used to maintain compatabilty with Java 1.1.8
 QVector<QPointF> ptMinute;
 QVector<QPointF> ptHour;
 for (int i = 0; i < scaledMinuteX.size(); i++)
 {
  rotatedMinuteX[i] = (int) ( scaledMinuteX[i] *
                              qCos(toRadians(minuteAngle)) -
                              scaledMinuteY[i] *
                              qSin(toRadians(minuteAngle)));
  rotatedMinuteY[i] = (int) ( scaledMinuteX[i] *
                              qSin(toRadians(minuteAngle)) +
                              scaledMinuteY[i] *
                              qCos(toRadians(minuteAngle)));
  ptMinute.append(QPointF(rotatedMinuteX[i],rotatedMinuteY[i]));
 }
 scaledMinuteHand = new QGraphicsPolygonItem(QPolygonF(ptMinute));
 scaledMinuteHand->setPos(locHands);
 _itemGroup->addToGroup(scaledMinuteHand);
 for (int i = 0; i < scaledHourX.size(); i++)
 {
  rotatedHourX[i] = (int) ( scaledHourX[i] *
                            qCos(toRadians(hourAngle)) -
                            scaledHourY[i] *
                            qSin(toRadians(hourAngle)));
  rotatedHourY[i] = (int) ( scaledHourX[i] *
                            qSin(toRadians(hourAngle)) +
                            scaledHourY[i] *
                            qCos(toRadians(hourAngle)));
  ptHour.append((QPointF(rotatedHourX[i], rotatedHourY[i])));
 }
 scaledHourHand = new QGraphicsPolygonItem(QPolygonF(ptHour));
 scaledHourHand->setPos(locHands);
 _itemGroup->addToGroup(scaledHourHand);

//    g.fillPolygon(scaledHourHand);
 scaledHourHand->setBrush(QBrush(QColor(Qt::black)));
//    g.fillPolygon(scaledMinuteHand);
 scaledMinuteHand->setBrush(QBrush(QColor(Qt::black)));

 // Draw AM/PM indicator in slightly smaller font than hour digits
 int amPmFontSize = (int) ( faceSize * .075);
 if (amPmFontSize < 1)
 {
  amPmFontSize = 1;
 }
 QFont amPmSizedFont =  QFont("Serif", amPmFontSize, QFont::Bold);
 //g.setFont(amPmSizedFont);
 //FontMetrics amPmFontM = g.getFontMetrics(amPmSizedFont);

 //g.drawQString(amPm, -amPmFontM.stringWidth(amPm) / 2, faceSize / 5);
 QGraphicsTextItem* textItem = new QGraphicsTextItem(amPm);
 textItem->setFont(amPmSizedFont);
 QRectF bounds = textItem->boundingRect();
 QPointF locAmPm = QPointF(locHands.x()-bounds.width()/2, locHands.y()+ bounds.height()/2);
 textItem->setPos(locAmPm);
 _itemGroup->addToGroup(textItem);
 if(_itemGroup && _itemGroup->scene())
  log->warn(tr("item already has been added %1 %2").arg(__FILE__).arg(__LINE__));
 g->addItem(_itemGroup);

}

// Method to convert degrees to radians
// Math.toRadians was not available until Java 1.2
double AnalogClock2Display::toRadians(double degrees) {
    double qPI = 3.14159265359;
    return degrees / 180.0 *qPI;
}

// Method to provide the cartesian x coordinate given a radius and angle (in degrees)
int AnalogClock2Display::dotX(double radius, double angle) {
    int xDist;
    xDist = (int) qRound(radius * qCos(toRadians(angle)));
    return xDist;
}

// Method to provide the cartesian y coordinate given a radius and angle (in degrees)
int AnalogClock2Display::dotY(double radius, double angle) {
    int yDist;
    yDist = (int) qRound(radius * qSin(toRadians(angle)));
    return yDist;
}

// Method called on resizing event - sets various sizing variables
// based on the size of the resized panel and scales the logo/hands
/*private*/ void AnalogClock2Display::scaleFace() {
    panelHeight = this->getSize().height();
    panelWidth = this->getSize().width();
    if (panelHeight > 0 && panelWidth > 0)
    {
        size = qMin(panelHeight, panelWidth);
    }
    faceSize = size;
    if (faceSize == 0) {
        faceSize = 1;
    }

    // Had trouble getting the proper sizes when using Images by themselves so
    // use the NamedIcon as a source for the sizes
    int logoScaleWidth = faceSize / 6;
    int logoScaleHeight = (int) ( (float) logoScaleWidth *
                                 (float) jmriIcon->getIconHeight() /
                                 jmriIcon->getIconWidth());
    //scaledLogo = logo.getScaledInstance(logoScaleWidth, logoScaleHeight,
//                                        Image::SCALE_SMOOTH);
    scaledLogo = logo.scaled(logoScaleWidth, logoScaleHeight);
    scaledIcon->setImage(scaledLogo);
    logoWidth = scaledIcon->getIconWidth();
    logoHeight = scaledIcon->getIconHeight();

    scaleRatio = faceSize / 2.7 / minuteHeight;
    QVector<QPointF> ptHour;
    QVector<QPointF> ptMinute;
    for (int i = 0; i < minuteX.size(); i++)
    {
        scaledMinuteX[i] = (int) ( minuteX[i] * scaleRatio);
        scaledMinuteY[i] = (int) ( minuteY[i] * scaleRatio);
        ptMinute << QPointF(scaledMinuteX[i], scaledMinuteY[i]);
        scaledHourX[i] = (int) ( hourX[i] * scaleRatio);
        scaledHourY[i] = (int) ( hourY[i] * scaleRatio);
        ptHour << QPointF(scaledHourX[i], scaledHourY[i]);
    }
    scaledHourHand = new QGraphicsPolygonItem(QPolygonF(ptHour));
    scaledMinuteHand = new QGraphicsPolygonItem(QPolygonF(ptMinute));

    if (panelHeight > 0 && panelWidth > 0) {
        centreX = panelWidth / 2;
        centreY = panelHeight / 2;
    }
    else {
        centreX = centreY = size / 2;
    }
    return;
}

/*public*/ void AnalogClock2Display::setSize(int x) {
    size = x;
    //PositionableJComponent::setSize(x, x);
    PositionableLabel::setSize(x, x);
    scaleFace();
}

/* This needs to be updated if resizing becomes an option */
/*public*/ void AnalogClock2Display::resize() {
    int panelHeight = this->getSize().height();
    int panelWidth = this->getSize().width();
    size = qMin(panelHeight, panelWidth);
    scaleFace();
}


//@SuppressWarnings("deprecation")
/*public*/ void AnalogClock2Display::update()
{
    QDateTime now = ((SimpleTimebase*)clock)->getTime();
    if (runMenu != NULL) {
        runMenu->setText(getRun() ? "Stop" : "Start");
    }
    int hours = now.time().hour();
    int minutes = now.time().minute();
    minuteAngle = minutes * 6.;
    hourAngle = hours * 30. + 30. * minuteAngle / 360.;
    if (hours < 12) {
        amPm = "AM " + QString("%1").arg((int) ((SimpleTimebase*)clock)->userGetRate()) + ":1";
    }
    else {
        amPm = "PM " + QString("%1").arg((int) ((SimpleTimebase*)clock)->userGetRate()) + ":1";
    }
    if (hours == 12 && minutes == 0) {
        amPm = "Noon";
    }
    if (hours == 0 && minutes == 0) {
        amPm = "Midnight";
    }
    //repaint();
    if(g != NULL)
     paint(g);
}

/*public*/ bool AnalogClock2Display::getRun() {
    return ((SimpleTimebase*)clock)->getRun();
}

/*public*/ void AnalogClock2Display::setRun(bool next) {
    ((SimpleTimebase*)clock)->setRun(next);
}

void AnalogClock2Display::cleanup() {
}

/*public*/ void AnalogClock2Display::dispose() {
    rateButtonGroup = NULL;
    runMenu = NULL;
    SimpleTimebase* t = (SimpleTimebase*)clock;
    disconnect(t, SIGNAL(minuteTick()), this, SLOT(update()));

}
//static org.apache.log4j.Logger log = org.apache.log4j.Logger.getLogger(AnalogClock2Display.class.getName());
//}
void AnalogClock2Display::propertyChange(PropertyChangeEvent *)
{
 update();
}

/*public*/ bool AnalogClock2Display::updateScene()
{
 update();
 return true;
}
