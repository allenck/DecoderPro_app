#include "jsplitbutton.h"
#include <QImage>
#include <QIcon>
#include "bufferedimage.h"
#include <QPainter>
#include <QMouseEvent>
#include <QtMath>
#include <QMenu>
#include "splitbuttonactionlistener.h"


/**
 * An implementation of a "split" button.The left side acts like a normal button, right side has a jPopupMenu attached. <br />
 * This class raises two events.<br />
 * <ol>
 * <li>buttonClicked(e); //when the button is clicked</li>
 * <li>splitButtonClicked(e; //when the split part of the button is clicked) </li>
 * </ol>
 * You need to subscribe to SplitButtonActionListener to handle these events.<br /><br />
 *
 * Use as you wish, but an acknowlegement would be appreciated, ;) <br /><br />
 * <b>Known Issue:</b><br />
 * The 'button part' of the splitbutton is being drawn without the border??? and this is only happening in CDE/Motif and Metal Look and Feels.
 * GTK+ and nimbus works perfect. No Idea why? if anybody could point out the mistake that'd be nice.My email naveedmurtuza[at]gmail.com<br /><br />
 * P.S. The fireXXX methods has been directly plagarized from JDK source code, and yes even the javadocs..;)<br /><br />
 * The border bug in metal L&F is now fixed. Thanks to Hervé Guillaume.
 * @author Naveed Quadri
 */
// /*public*/ class JSplitButton extends JButton implements MouseMotionListener, MouseListener, ActionListener,Serializable {


/**
 * Creates a button with initial text and an icon.
 *
 * @param text  the text of the button
 * @param icon  the Icon image to display on the button
 */
/*public*/ JSplitButton::JSplitButton(QString text, QIcon icon, QWidget *parent)
: JButton(text, icon, parent){
    //super(text, icon);
 common();
//    addMouseMotionListener(this);
//    addMouseListener(this);
//    addActionListener(this);
}

/**
 * Creates a button with text.
 *
 * @param text  the text of the button
 */
/*public*/ JSplitButton::JSplitButton(QString text, QWidget *parent)
 : JButton(text, parent)
{
    //this(text, null);
 common();
}

/**
 * Creates a button with an icon.
 *
 * @param icon  the Icon image to display on the button
 */
/*public*/ JSplitButton::JSplitButton(QIcon icon, QWidget *parent)
 : JButton(icon, parent)
{
    //this("", icon);
 common();
}

/**
 * Creates a button with no set text or icon.
 */
/*public*/ JSplitButton::JSplitButton(QWidget *parent)
 : JButton(parent)
{
    //this("", QIcon());
 common();
}

void JSplitButton::common()
{
 arrowColor = QColor(Qt::black);
 disabledArrowColor = QColor(Qt::gray);
 setMouseTracking(true);
 connect(this, SIGNAL(clicked(bool)), this, SLOT(actionPerformed()));
}

/**
 * Returns the JPopupMenu if set, null otherwise.
 * @return JPopupMenu
 */
/*public*/ QMenu* JSplitButton::getPopupMenu() {
    return popupMenu;
}

/**
 * Sets the JPopupMenu to be displayed, when the split part of the button is clicked.
 * @param popupMenu
 */
/*public*/ void JSplitButton::setPopupMenu(QMenu* popupMenu) {
    this->popupMenu = popupMenu;
    image = QImage(); //to repaint the arrow image

}

/**
 * Returns the separatorSpacing. Separator spacing is the space above and below the separator( the line drawn when you hover your mouse
 * over the split part of the button).
 * @return separatorSpacingimage = null; //to repaint the image with the new size
 */
/*public*/ int JSplitButton::getSeparatorSpacing() {
    return separatorSpacing;
}

/**
 * Sets the separatorSpacing.Separator spacing is the space above and below the separator( the line drawn when you hover your mouse
 * over the split part of the button).
 * @param separatorSpacing
 */
/*public*/ void JSplitButton::setSeparatorSpacing(int separatorSpacing) {
    this->separatorSpacing = separatorSpacing;
}

/**
 * Show the dropdown menu, if attached, even if the button part is clicked.
 * @return true if alwaysDropdown, false otherwise.
 */
/*public*/ bool JSplitButton::isAlwaysDropDown() {
    return alwaysDropDown;
}

/**
 * Show the dropdown menu, if attached, even if the button part is clicked.
 * @param alwaysDropDown true to show the attached dropdown even if the button part is clicked, false otherwise
 */
/*public*/ void JSplitButton::setAlwaysDropDown(bool alwaysDropDown) {
    this->alwaysDropDown = alwaysDropDown;
}

/**
 * Gets the color of the arrow.
 * @return arrowColor
 */
/*public*/ QColor JSplitButton::getArrowColor() {
    return arrowColor;
}

/**
 * Set the arrow color.
 * @param arrowColor
 */
/*public*/ void JSplitButton::setArrowColor(QColor arrowColor) {
    this->arrowColor = arrowColor;
    image = QImage(); //to repaint the image with the new color
}

/**
 *  gets the disabled arrow color
 * @return disabledArrowColor color of the arrow if no popup attached.
 */
/*public*/ QColor JSplitButton::getDisabledArrowColor() {
    return disabledArrowColor;
}

/**
 * sets the disabled arrow color
 * @param disabledArrowColor color of the arrow if no popup attached.
 */
/*public*/ void JSplitButton::setDisabledArrowColor(QColor disabledArrowColor) {
    this->disabledArrowColor = disabledArrowColor;
    image = QImage(); //to repaint the image with the new color
}

/**
 * Splitwidth is the  width of the split part of the button.
 * @return splitWidth
 */
/*public*/ int JSplitButton::getSplitWidth() {
    return splitWidth;
}

/**
 * Splitwidth is the  width of the split part of the button.
 * @param splitWidth
 */
/*public*/ void JSplitButton::setSplitWidth(int splitWidth) {
    this->splitWidth = splitWidth;
}

/**
 * gets the size of the arrow.
 * @return size of the arrow
 */
/*public*/ int JSplitButton::getArrowSize() {
    return arrowSize;
}

/**
 * sets the size of the arrow
 * @param arrowSize
 */
/*public*/ void JSplitButton::setArrowSize(int arrowSize) {
    this->arrowSize = arrowSize;
    image = QImage(); //to repaint the image with the new size
}

/**
 * Gets the image to be drawn in the split part. If none is set, a new image is created with the triangle.
 * @return image
 */
/*public*/ QImage JSplitButton::getImage()
{
 if (!image.isNull()) {
     return image;
 }
 else
 {
  BufferedImage img =  BufferedImage(arrowSize, arrowSize, /*BufferedImage.TYPE_INT_RGB*/QImage::Format_ARGB32_Premultiplied);
  QPainter g(&img);
  //g.setColor(Color.WHITE);
  g.fillRect(0, 0, img.width(), img.height(), QColor(Qt::white) );
  g.setBrush(popupMenu != nullptr ? arrowColor : disabledArrowColor);
  //this creates a triangle facing right >
  //g->fillPolygon(new int[]{0, 0, arrowSize / 2}, new int[]{0, arrowSize, arrowSize / 2}, 3);
  QVector<QPointF> points = QVector<QPointF>() << QPointF(0,0) << QPointF(0,arrowSize ) << QPointF(arrowSize / 2, arrowSize / 2);
  g.drawPolygon(QPolygonF(points));
  //g.dispose();
  g.end();
  //rotate it to face downwards
  img = rotate(img, 90);
  BufferedImage dimg = BufferedImage(img.width(), img.height(), /*BufferedImage.TYPE_INT_ARGB*/QImage::Format_ARGB32_Premultiplied);
  QPainter g2(&dimg);
  //g.setComposite(AlphaComposite.Src);
  g2.drawImage(0,0,(QImage)img);
  //g.dispose();
  //g2.end();
  for (int i = 0; i < dimg.height(); i++)
  {
   for (int j = 0; j < dimg.width(); j++) {
       if (dimg.getRGB(j, i) == QColor(Qt::white).rgb()) {
           dimg.setRGB(j, i, 0x8F1C1C);
       }
   }
  }

  //image = Toolkit.getDefaultToolkit().createImage(dimg.getSource());
  image = dimg;
  return image;
 }
}

/**
 * Sets the image to draw instead of the triangle.
 * @param image
 */
/*public*/ void JSplitButton::setImage(QImage image) {
    this->image = image;
}

/**
 * Gets the disabled image to be drawn in the split part. If no is set, a new image is created with the triangle.
 *
 * @return image
 */
/*public*/ QImage JSplitButton::getDisabledImage()
{
 if (!disabledImage.isNull()) {
     return disabledImage;
 }
 else
 {
  BufferedImage img = BufferedImage(arrowSize, arrowSize, /*BufferedImage::TYPE_INT_RGB*/QImage::Format_ARGB32_Premultiplied);
  QPainter g(&img);
  //g.setColor(Color.WHITE);
  g.fillRect(0, 0, img.width(), img.height(), QColor(Qt::white));
  g.setBrush(disabledArrowColor);
  // this creates a triangle facing right >
  QVector<QPointF> points = QVector<QPointF>() << QPointF(0,0) << QPointF(0,arrowSize ) << QPointF(arrowSize / 2, arrowSize / 2);
  //g.fillPolygon(new int[] { 0, 0, arrowSize / 2 }, new int[] { 0, arrowSize, arrowSize / 2 }, 3);
  g.drawPolygon(QPolygonF(points));
  //g.dispose();
  g.end();
  // rotate it to face downwards
  img = rotate(img, 90);
  BufferedImage dimg = BufferedImage(img.width(), img.height(), /*BufferedImage.TYPE_INT_ARGB*/QImage::Format_ARGB32_Premultiplied);
  QPainter g1(&dimg);
  //g.setComposite(AlphaComposite.Src);
  g1.drawImage(0,0, img);
  //g.dispose();
  g1.end();
  for (int i = 0; i < dimg.height(); i++)
  {
   for (int j = 0; j < dimg.width(); j++) {
       if (dimg.getRGB(j, i) == QColor(Qt::white).rgb()) {
           dimg.setRGB(j, i, 0x8F1C1C);
       }
   }
  }

  //disabledImage = Toolkit.getDefaultToolkit().createImage(dimg.getSource());
  disabledImage = dimg;
  return disabledImage;
 }
}

/**
 * Sets the disabled image to draw instead of the triangle.
 * @param image
 */
/*public*/ void JSplitButton::setDisabledImage(QImage image) {
    this->disabledImage = image;
}

/**
 *
 * @param g
 */
//@Override
/*protected*/ void JSplitButton::paintEvent(QPaintEvent *evt) {
    //super.paintComponent(g);
    JButton::paintEvent(evt);
    QPainter g(this);
    QColor oldColor = g.brush().color();//g.getColor();
    splitRectangle = QRect(width() - splitWidth, 0, splitWidth, height());
    g.translate(splitRectangle.x(), splitRectangle.y());
    int mh = height() / 2;
    int mw = splitWidth / 2;
    // g->drawImage((isEnabled() ? getImage() : getDisabledImage()), mw - arrowSize / 2, mh + 2 - arrowSize / 2, null);
    g.drawImage( mw - arrowSize / 2, mh + 2 - arrowSize / 2, (QImage)(isEnabled() ? getImage() : getDisabledImage()));
    if (onSplit && !alwaysDropDown && popupMenu != nullptr)
    {
     //g.setColor(UIManager.getLookAndFeelDefaults().getColor("Button.background"));
     g.setPen(this->palette().background().color());
     g.drawLine(1, separatorSpacing + 2, 1, height() - separatorSpacing - 2);
     //g.setColor(UIManager.getLookAndFeelDefaults().getColor("Button.shadow"));
     g.setPen(this->palette().shadow().color());
     g.drawLine(2, separatorSpacing + 2, 2, height() - separatorSpacing - 2);
    }
    g.setBrush(oldColor);
    g.translate(-splitRectangle.x(), -splitRectangle.y());
}

/**
 * Rotates the given image with the specified angle.
 * @param img image to rotate
 * @param angle angle of rotation
 * @return rotated image
 */
/*private*/ BufferedImage JSplitButton::rotate(BufferedImage img, int angle) {
    int w = img.width();
    int h = img.height();
    BufferedImage dimg = BufferedImage(w, h, (QImage::Format)img.getType());
    QPainter g(&dimg);
    g.rotate(qDegreesToRadians((float)angle)/*, w / 2, h / 2*/);
    g.drawImage(0,0,img);
    //g.end();
    return dimg;
}

/**
 * Adds an <code>SplitButtonActionListener</code> to the button.
 * @param l the <code>ActionListener</code> to be added
 */
/*public*/ void JSplitButton::addButtonActionListener(ActionListener *l) {
//    listenerList.add("SplitButtonActionListener", l);
 connect(this, SIGNAL(buttonClicked(JActionEvent*)), l, SLOT(buttonClicked(JActionEvent*)) );
}

/**
 * Adds an <code>SplitButtonActionListener</code> to the button.
 * @param l the <code>ActionListener</code> to be added
 */
/*public*/ void JSplitButton::addSplitButtonActionListener(SplitButtonActionListener* l) {
//    listenerList.add("SplitButtonActionListener", l);
 connect(this, SIGNAL(splitButtonClicked(JActionEvent*)), l, SLOT(splitButtonClicked(JActionEvent*)) );
}

/**
 * Removes an <code>SplitButtonActionListener</code> from the button.
 * If the listener is the currently set <code>Action</code>
 * for the button, then the <code>Action</code>
 * is set to <code>null</code>.
 *
 * @param l the listener to be removed
 */
/*public*/ void JSplitButton::removeButtonActionListener(ActionListener* l) {
//    if ((l != nullptr) && (getAction() == l)) {
//        setAction(null);
//    } else {
//        listenerList.remove(SplitButtonActionListener.class, l);
//    }
 disconnect(this, SIGNAL(buttonClicked(JActionEvent*)), l, SLOT(buttonClicked(JActionEvent*)) );
}

/*public*/ void JSplitButton::removeSplitButtonActionListener(SplitButtonActionListener* l) {
//    if ((l != nullptr) && (getAction() == l)) {
//        setAction(null);
//    } else {
//        listenerList.remove(SplitButtonActionListener.class, l);
//    }
 disconnect(this, SIGNAL(splitButtonClicked(JActionEvent*)), l, SLOT(splitButtonClicked(JActionEvent*)) );
}

/**
 *
 * @param e
 */
/*public*/ void JSplitButton::mouseMoved(QMouseEvent* e) {
    if (splitRectangle.contains(e->pos())) {
        onSplit = true;
    }
    else {
        onSplit = false;
    }
    repaint(splitRectangle);
}

/*protected*/ void JSplitButton::mouseMoveEvent(QMouseEvent *e)
{
 mouseMoved(e);
}

/**
 *
 * @param e
 */
/*public*/ void JSplitButton::actionPerformed(JActionEvent* e)
{
 if (popupMenu == nullptr)
 {
     fireButtonClicked(e);
 }
 else if (alwaysDropDown)
 {
     popupMenu->exec( );//width() - (int) popupMenu->sizeHint().width(), height());
     fireButtonClicked(e);
 }
 else if (onSplit)
 {
     popupMenu->exec( ); //width() - (int) popupMenu->sizeHint().width(), height());
     fireSplitbuttonClicked(e);
 }
 else {
     fireButtonClicked(e);
 }
}

/**
 *
 * @param e
 */
/*public*/ void JSplitButton::mouseExited(QMouseEvent* /*e*/) {
    onSplit = false;
    repaint(splitRectangle);
}

// <editor-fold defaultstate="collapsed" desc="Unused Listeners">
#if 0
/*public*/ void mouseDragged(MouseEvent e) {
}

/*public*/ void mouseClicked(MouseEvent e) {
}

/*public*/ void mousePressed(MouseEvent e) {
}

/*public*/ void mouseReleased(MouseEvent e) {
}

/*public*/ void mouseEntered(MouseEvent e) {
}
// </editor-fold>
#endif
/**
 * Notifies all listeners that have registered interest for
 * notification on this event type.  The event instance
 * is lazily created using the <code>event</code>
 * parameter.
 *
 * @param event  the <code>ActionEvent</code> object
 * @see EventListenerList
 */
/*private*/ void JSplitButton::fireButtonClicked(JActionEvent* event) {
 JActionEvent* e = nullptr;

#if 0
    // Guaranteed to return a non-null array
    QVector<EventListener*> listeners = listenerList.getListenerList();
    // Process the listeners last to first, notifying
    // those that are interested in this event
    for (int i = listeners.length() - 2; i >= 0; i -= 2)
    {
//        if (qobject_cast<SplitButtonActionListener*>(listeners[i]))
     {
            // Lazily create the event:
            if (e == nullptr) {
                QString actionCommand = event->getActionCommand();
//                if (actionCommand == "") {
//                    actionCommand = getActionCommand();
//                }
#endif
                e = new JActionEvent(this,
                        JActionEvent::ACTION_PERFORMED,
                        "clicked",
                        0l,//event->getWhen(),
                        0);//event->getModifiers());
#if 0
            }
            ((SplitButtonActionListener*) listeners[i + 1])->buttonClicked(e);
        }
    }
#endif
    emit buttonClicked(e);
}

/**
 * Notifies all listeners that have registered interest for
 * notification on this event type.  The event instance
 * is lazily created using the <code>event</code>
 * parameter.
 *
 * @param event  the <code>ActionEvent</code> object
 * @see EventListenerList
 */
/*private*/ void JSplitButton::fireSplitbuttonClicked(JActionEvent* event) {
 JActionEvent* e = nullptr;
#if 0
    // Guaranteed to return a non-null array
 QVector<EventListener*> listeners = listenerList.getListenerList();
    // Process the listeners last to first, notifying
    // those that are interested in this event
    for (int i = listeners.length() - 2; i >= 0; i -= 2) {
//     if (qobject_cast<SplitButtonActionListener*>(listeners[i]))
     {
            // Lazily create the event:
            if (e == nullptr) {
                QString actionCommand = event->getActionCommand();
                if (actionCommand == "") {
//                    actionCommand = getActionCommand();
                }
#endif
                e = new JActionEvent(this,
                        JActionEvent::ACTION_PERFORMED,
                        "clicked",
                        0l,//event->getWhen(),
                        0);//event->getModifiers());
#if 0
            }
            ((SplitButtonActionListener*) listeners[i + 1])->splitButtonClicked(e);
        }
    }
#endif
    emit splitButtonClicked(e);
}

