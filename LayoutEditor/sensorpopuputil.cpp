#include "sensorpopuputil.h"
#include "sensoricon.h"

SensorPopupUtil::SensorPopupUtil(Positionable *parent, JComponent* textComp) :
    PositionablePopupUtil(parent, textComp)
{
 this->parent = parent;
}
//class SensorPopupUtil extends PositionablePopupUtil {

//        SensorPopupUtil(Positionable parent, javax.swing.JComponent textComp) {
//            super(parent, textComp);
//        }
//@Override
/*public*/ void SensorPopupUtil::setTextJustificationMenu(QMenu* popup)
{
 if (((PositionableLabel*)parent)->isText())
 {
  PositionablePopupUtil::setTextJustificationMenu(popup);
 }
}
//@Override
/*public*/ void SensorPopupUtil::setTextOrientationMenu(QMenu* popup)
{
if (((PositionableLabel*)parent)->isText()) { PositionablePopupUtil::setTextOrientationMenu(popup); }
}
//@Override
/*public*/ void SensorPopupUtil::setFixedTextMenu(QMenu* popup)
{
if (((PositionableLabel*)parent)->isText()) { PositionablePopupUtil::setFixedTextMenu(popup); }
}
//@Override
/*public*/ void SensorPopupUtil::setTextMarginMenu(QMenu* popup)
{
if (((PositionableLabel*)parent)->isText()) { PositionablePopupUtil::setTextMarginMenu(popup); }
}
//@Override
/*public*/ void SensorPopupUtil::setTextBorderMenu(QMenu* popup)
{
if (((PositionableLabel*)parent)->isText()) { PositionablePopupUtil::setTextBorderMenu(popup); }
}
//@Override
/*public*/ void SensorPopupUtil::setTextFontMenu(QMenu* popup)
{
if (((PositionableLabel*)parent)->isText()) { PositionablePopupUtil::setTextFontMenu(popup); }
}

//@Override
//@SuppressWarnings("fallthrough")
/*protected*/ void SensorPopupUtil::makeColorMenu(QMenu* colorMenu, int type)
{
 QActionGroup* buttonGrp = new QActionGroup(this);
 addColorMenuEntry(colorMenu, buttonGrp, tr("Black"), QColor(Qt::black), type);
 addColorMenuEntry(colorMenu, buttonGrp, tr("DarkGray"),QColor(Qt::darkGray), type);
 addColorMenuEntry(colorMenu, buttonGrp, tr("Gray"),QColor(Qt::gray), type);
 addColorMenuEntry(colorMenu, buttonGrp, tr("LightGray"),QColor(Qt::lightGray), type);
 addColorMenuEntry(colorMenu, buttonGrp, tr("White"),QColor(Qt::white), type);
 addColorMenuEntry(colorMenu, buttonGrp, tr("Red"),QColor(Qt::red), type);
 addColorMenuEntry(colorMenu, buttonGrp, tr("Orange"),QColor(255,165,0), type); // orange
 addColorMenuEntry(colorMenu, buttonGrp, tr("Yellow"),QColor(Qt::yellow), type);
 addColorMenuEntry(colorMenu, buttonGrp, tr("Green"),QColor(Qt::green), type);
 addColorMenuEntry(colorMenu, buttonGrp, tr("Blue"),QColor(Qt::blue), type);
 addColorMenuEntry(colorMenu, buttonGrp, tr("Magenta"),QColor(Qt::magenta), type);
 switch(type)
 {
 case SensorIcon::UNKOWN_BACKGROUND_COLOR :
 case SensorIcon::ACTIVE_BACKGROUND_COLOR :
 case SensorIcon::INACTIVE_BACKGROUND_COLOR :
 case SensorIcon::INCONSISTENT_BACKGROUND_COLOR : addColorMenuEntry(colorMenu, buttonGrp, tr("Clear"), QColor(), type);
 }
 connect(buttonGrp, SIGNAL(triggered(QAction*)), this, SLOT(on_colorMenuEntry_selected(QAction*)));
}

//@Override
/*protected*/ void SensorPopupUtil::addColorMenuEntry(QMenu* menu, QActionGroup* colorButtonGroup,
                   /*final*/ QString name, /*final*/ QColor color, /*final*/ int colorType)
{
 ColorMenuAction* addColorMenuAction = new ColorMenuAction(name, color, colorType, this);
 addColorMenuAction->setCheckable(true);
 colorButtonGroup->addAction(addColorMenuAction);
 menu->addAction(addColorMenuAction);
}

//ActionListener a = new ActionListener() {
//    //final String desiredName = name;
//    /*final*/ QColor desiredColor = color;
//    /*public*/ void actionPerformed(ActionEvent e) {
void SensorPopupUtil::on_colorMenuEntry_selected(ColorMenuAction *act)
{
 QString desiredColor = act->getName();
 int colorType = act->getType();
 QColor color = act->getColor();
 switch (colorType)
 {
 case FONT_COLOR :
  setForeground(desiredColor);
  break;
 case BACKGROUND_COLOR :
  if(!color.isValid())
  {
   ((PositionableLabel*)parent)->setOpaque(false);
   //We need to force a redisplay when going to clear as the area
   //doesn't always go transparent on the first click.
   QPointF p = ((Positionable*)parent)->getLocation();
   int w = ((PositionableLabel*)parent)->getWidth();
   int h = ((PositionableLabel*)parent)->getHeight();
//   QObject* parent = getParent();
//   // force redisplay
//   parent.validate();
//   parent.repaint(p.x,p.y,w,h);
  }
  else
   setBackgroundColor(desiredColor);
  break;
 case BORDER_COLOR :
  setBorderColor(desiredColor);
  break;
 case SensorIcon::UNKNOWN_FONT_COLOR :
  ((SensorIcon*)parent)->setTextUnknown(desiredColor);
  break;
 case SensorIcon::UNKOWN_BACKGROUND_COLOR :
  ((SensorIcon*)parent)->setBackgroundUnknown(desiredColor);
        break;
 case SensorIcon::ACTIVE_FONT_COLOR :
  ((SensorIcon*)parent)->setTextActive(desiredColor);
        break;
 case SensorIcon::ACTIVE_BACKGROUND_COLOR :
  ((SensorIcon*)parent)->setBackgroundActive(desiredColor);
        break;
 case SensorIcon::INACTIVE_FONT_COLOR :
  ((SensorIcon*)parent)->setTextInActive(desiredColor);
        break;
 case SensorIcon::INACTIVE_BACKGROUND_COLOR :
  ((SensorIcon*)parent)->setBackgroundInActive(desiredColor);
        break;
 case SensorIcon::INCONSISTENT_FONT_COLOR :
  ((SensorIcon*)parent)->setTextInconsistent(desiredColor);
        break;
 case SensorIcon::INCONSISTENT_BACKGROUND_COLOR :
  ((SensorIcon*)parent)->setBackgroundInconsistent(desiredColor);
  break;
 default : break;
 }
}
//};
//JRadioButtonMenuItem r = new JRadioButtonMenuItem(name);
//r.addActionListener(a);

//switch (colorType) {
//    case FONT_COLOR:
//        setColorButton(getForeground(), color, r);
//        break;
//    case BACKGROUND_COLOR:
//        setColorButton(getBackground(), color, r);
//        break;
//    case BORDER_COLOR:
//        setColorButton(getBorderColor(), color, r);
//        break;
//    case SensorIcon::UNKOWN_FONT_COLOR:
//        setColorButton(getTextUnknown(), color, r);
//        break;
//    case SensorIcon::UNKOWN_BACKGROUND_COLOR:
//        setColorButton(getBackgroundUnknown(), color, r);
//        break;
//    case SensorIcon::ACTIVE_FONT_COLOR:
//        setColorButton(getTextActive(), color, r);
//        break;
//    case SensorIcon::ACTIVE_BACKGROUND_COLOR:
//        setColorButton(getBackgroundActive(), color, r);
//        break;
//    case SensorIcon::INACTIVE_FONT_COLOR:
//        setColorButton(getTextInActive(), color, r);
//        break;
//    case SensorIcon::INACTIVE_BACKGROUND_COLOR:
//        setColorButton(getBackgroundInActive(), color, r);
//        break;
//    case SensorIcon::INCONSISTENT_FONT_COLOR:
//        setColorButton(getTextInconsistent(), color, r);
//        break;
//    case SensorIcon::INCONSISTENT_BACKGROUND_COLOR:
//     setColorButton(getBackgroundInconsistent(), color, r);
//     break;
//   default : break;
//  }
//  colorButtonGroup.add(r);
//  menu.add(r);
// }
//}
