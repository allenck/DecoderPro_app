#include "positionablepopuputil.h"
#include <QVector>
#include "jlabel.h"
#include <QLineEdit>
#include "positionablelabel.h"
#include "QButtonGroup"
#include <QSignalMapper>
#include "coordinateedit.h"
#include <QPainter>
#include "jtextfield.h"
#include <QPalette>
#include <editor.h>
#include "positionablejpanel.h"
#include "colorutil.h"
#include <QPalette>
#include <QBrush>
#include "lineborder.h"
#include "compoundborder.h"
#include "borderfactory.h"
#include "jmricolorchooser.h"
#include "textitempanel.h"

//PositionablePopupUtil::PositionablePopupUtil(QObject *parent) :
//    QObject(parent)
//{
//}
/**
 * <p>
 * This class handles text attributes for Positionables. Font size, style and
 * color. Margin size and color, Border size and color, Fixed sizes.
 * Justification.
 * </p>
 *
 * moved from PositionableLabel
 *
 * @author Pete Cressman copyright (C) 2010
 */
///*public*/ class PositionablePopupUtil {

/*public*/ PositionablePopupUtil::PositionablePopupUtil(Positionable* parent, QWidget* textComp)
{
 init();
 _parent = parent;
 //if (textComp instanceof JLabel)
 if(qobject_cast<JLabel*>(textComp)!= NULL)
 {
  _textType = LABEL;
 }
 else
 if(dynamic_cast<JTextField*>(textComp)!= NULL)
 {
  _textType = TEXTFIELD;
 }
 else
 {
  _textType = JCOMPONENT;
 }
 _textComponent = textComp;
_self= this;\
 debug = log->isDebugEnabled();
 if(_textComponent != NULL)
 {
//  defaultForeground = ((PositionableLabel*)_textComponent)->getForeground();
  //defaultBackground = ((JTextField*)_textComponent)->getBackground();
  //defaultBackground = ((PositionableLabel*)_textComponent)->getBackground();
//  defaultBackground = ((PositionableIcon*)_textComponent)->getBackground();
 }
 if(_parent != NULL)
  defaultBorderColor = (_parent)->getBackground();
 else
  defaultBorderColor = QColor(Qt::black);
 _propertiesUtil = new PositionablePropertiesUtil(_parent);
}

/*public*/ PositionablePopupUtil* PositionablePopupUtil::clone(Positionable* parent, QWidget* textComp)
{
 PositionablePopupUtil* util = new PositionablePopupUtil(parent, textComp);
 util->setJustification(getJustification());
 util->setHorizontalAlignment(getJustification());
 util->setFixedWidth(getFixedWidth());
 util->setFixedHeight(getFixedHeight());
 util->setMargin(getMargin());
 util->setBorderSize(getBorderSize());
 util->setBorderColor(getBorderColor());
 util->setFont(getFont()/*.deriveFont(getFontStyle())*/);
 util->setFontSize(getFontSize());
 util->setOrientation(getOrientation());
 util->setBackgroundColor(getBackground());
 util->setForeground(getForeground());
 util->setHasBackground(hasBackground());     // must do this AFTER setBackgroundColor

 return util;
}

/*public*/ QString PositionablePopupUtil::toString() {
    return _parent->getNameString()+": fixedWidth= "+QString("%1").arg(fixedWidth)+", fixedHeight= "+QString("%1").arg(fixedHeight)+
             ", margin= "+QString("%1").arg(margin)+", borderSize= "+QString("%1").arg(borderSize);
}

void PositionablePopupUtil::init()
{
 log = new Logger("PositionalPopupUtil");
 setObjectName("PositionalPopupUtil");
 debug = false;
 fixedWidth=0;
 fixedHeight=0;
 margin=0;
 borderSize=0;
 borderColor=QColor(Qt::black);
 borderMargin = BorderFactory::createEmptyBorder(0, 0, 0, 0);
 outlineBorder = BorderFactory::createEmptyBorder(0, 0, 0, 0);

 italic = NULL;
 bold = NULL;
 _showBorder = true;
 justification=CENTRE; //Default is always Centre
 orientation = HORIZONTAL;
 editAdditionalMenu = new QVector<QMenu*>();
 viewAdditionalMenu = new QVector<QMenu*>();
 _textComponent = NULL;
}

/****************************************************************************************/



/*public*/ void PositionablePopupUtil::propertyUtil(QMenu* popup)
{
//    JMenuItem edit = new JMenuItem("Properties");
//    edit.addActionListener(new ActionListener() {
//        /*public*/ void actionPerformed(ActionEvent e) { _propertiesUtil.display(); }
//    });
 QAction* propertiesAction = new QAction(tr("Properties"),this);
 connect(propertiesAction, &QAction::triggered, [=]{
  _propertiesUtil->display();
         });
 popup->addAction(propertiesAction);
}

/*public*/ void PositionablePopupUtil::setFixedTextMenu(QMenu* popup) {
    QMenu* edit = new QMenu(tr("Edit Fixed Size..."));
    if (getFixedWidth()==0)
        edit->addAction(new QAction(tr("Width= Auto"),this));
    else
        edit->addAction(new QAction(tr("Width= ") + QString("%1").arg(_parent->maxWidth()),this));

    if (getFixedHeight()==0)
        edit->addAction(new QAction(tr("Height= Auto"),this));
    else
        edit->addAction(new QAction(tr("Height= ") + QString("%1").arg(_parent->maxHeight()),this));

    edit->addAction(CoordinateEdit::getFixedSizeEditAction((Positionable*)_parent, this));
    popup->addMenu(edit);
}

/*public*/ void PositionablePopupUtil::setTextMarginMenu(QMenu* popup) {
    QMenu* edit = new QMenu(tr("Edit Margin..."));
    if((fixedHeight==0)||(fixedWidth==0))
    {
     edit->addAction(new QAction("Margin= " + QString("%1").arg(getMargin()),this));
//     QAction* act = _parent->cEdit->getMarginEditAction((Positionable*)_parent, this);
//     edit->addAction(act);
     edit->addAction(CoordinateEdit::getMarginEditAction(_parent,this));
    }
    popup->addMenu(edit);
}

/*public*/ void PositionablePopupUtil::setBackgroundMenu(QMenu* popup)
{
    QAction* edit = new QAction(("Background Color"));
    //edit.addActionListener((ActionEvent event) ->
    connect(edit, &QAction::triggered, [=]
    {
        QColor desiredColor = JmriColorChooser::showDialog((QWidget*)_textComponent,
                             tr("Background Color"),
                             getBackground());
        if (!desiredColor.isValid() ) {
           setBackgroundColor(desiredColor);
       }
    });

    popup->addAction(edit);
}

/*public*/ void PositionablePopupUtil::setTextBorderMenu(QMenu* popup) {
    QMenu* edit = new QMenu(tr("Edit Border..."));
    edit->addAction(new QAction("Border Size= " + QString("%1").arg(borderSize),this));
    QAction* act = CoordinateEdit::getBorderEditAction((Positionable*)_parent,this);
    edit->addAction(act);
    QAction* colorMenu = new QAction(tr("Border Color"), this);
    //colorMenu.addActionListener((ActionEvent event) -> {
    connect(colorMenu, &QAction::triggered, [=]{
        QColor desiredColor = JmriColorChooser::showDialog(_textComponent,
                             tr("Border Color"),
                             defaultBorderColor);
        if (!desiredColor.isValid() ) {
           setBorderColor(desiredColor);
       }
    });
    edit->addAction(colorMenu);
    popup->addMenu(edit);
}

/*public*/ void PositionablePopupUtil::setTextFontMenu(QMenu* popup) {
    QMenu* edit = new QMenu(tr("Edit Font.."));
    edit->addMenu(makeFontSizeMenu());
    edit->addMenu(makeFontStyleMenu());
    QAction* colorMenu = new QAction(tr("Font Color"),this);
    connect(colorMenu, SIGNAL(triggered(bool)), this, SLOT(onSetTeaxtFontColor()));
    edit->addAction(colorMenu);
    popup->addMenu(edit);
}

void PositionablePopupUtil::onSetTeaxtFontColor()
{
 QColor desiredColor = JmriColorChooser::showDialog((QWidget*)_textComponent,
                      tr("Border Color"),
                      defaultBorderColor);
 if (desiredColor.isValid()) {
    setBorderColor(desiredColor);
}

}
/*public*/ int PositionablePopupUtil::getMargin()
{
    return margin;
}
/*public*/ void PositionablePopupUtil::setMargin(int m)
{
    margin = m;
    if (_parent->isOpaque()) {
        borderMargin = new LineBorder(getBackground(), m);
    } else {
        borderMargin = BorderFactory::createEmptyBorder(m, m, m, m);
    }
    if (_showBorder) {
        _parent->setBorder(new CompoundBorder(outlineBorder, borderMargin));
    }
    _parent->updateSize();
}

/*public*/ int PositionablePopupUtil::getFixedWidth() {
    return fixedWidth;
}
/*public*/ void PositionablePopupUtil::setFixedWidth(int w) {
    fixedWidth = w;
    if (log->isDebugEnabled()) log->debug("setFixedWidth()="+QString("%1").arg(getFixedWidth()));
   _parent->updateSize();
}
/*public*/ int PositionablePopupUtil::getFixedHeight() {
    return fixedHeight;
}
/*public*/ void PositionablePopupUtil::setFixedHeight(int h) {
    //Q_ASSERT(h > 0);
    fixedHeight = h;
    if (log->isDebugEnabled()) log->debug("setFixedHeight()="+QString("%1").arg(getFixedHeight()));
    _parent->updateSize();
}
/*public*/ void PositionablePopupUtil::setFixedSize(int w, int h) {
    fixedWidth = w;
    fixedHeight = h;
    if (log->isDebugEnabled()) log->debug(tr("setFixedSize()=")+"("+QString("%1").arg(getFixedWidth())+","+QString("%1").arg(getFixedHeight())+")");
    _parent->updateSize();
}

/*public*/ void PositionablePopupUtil::setBorderSize(int border){
    borderSize = border;

    if(borderColor.isValid()){
        outlineBorder = new LineBorder(borderColor, borderSize);
        _parent->setBorder(new CompoundBorder(outlineBorder, borderMargin));
        //setHorizontalAlignment(CENTRE);
    }
    _parent->updateSize();
}

/*public*/ void PositionablePopupUtil::setBorder(bool set) {
    _showBorder = set;
    if (set) {
        if(borderColor.isValid()){
            outlineBorder = new LineBorder(borderColor, borderSize);
            _parent->setBorder(new CompoundBorder(outlineBorder, borderMargin));
         }
    } else {
        _parent->setBorder(NULL);
    }
}

/*public*/ int PositionablePopupUtil::getBorderSize() {
    return borderSize;
}

/*public*/ void PositionablePopupUtil::setBorderColor(QColor border){
    borderColor = border;
    if(borderColor.isValid() && _showBorder){
        outlineBorder = new LineBorder(borderColor, borderSize);
        _parent->setBorder(new CompoundBorder(outlineBorder, borderMargin));
    }
}

/*public*/ QColor PositionablePopupUtil::getBorderColor()
{
 if (!borderColor.isValid())
 {
  borderColor = _parent->getBackground();
 }
 return borderColor;
}

/*public*/ void PositionablePopupUtil::setForeground(QColor c)
{
    if(_textComponent == NULL ) return;
   //((PositionableLabel*) _textComponent)->setForeground(c);
    if(qobject_cast<JLabel*>(_textComponent)!= NULL)
     ((PositionableLabel*)_textComponent)->setForeground(c);
    else
     if(qobject_cast<JTextField*>(_textComponent)!= NULL)
         ((JTextField*)_textComponent)->setForeground(c);

    _parent->updateSize();
}

/*public*/ QColor PositionablePopupUtil::getForeground() {
    if(_textComponent == NULL ) return QColor();
    if(qobject_cast<JLabel*>(_textComponent)!= NULL)
     return ((PositionableLabel*)_textComponent)->getForeground();
//    if(qobject_cast<JTextField*>(_textComponent)!= NULL)
//        return ((JTextField*)_textComponent)->getForeground();
    return QColor();
}

/*public*/ void PositionablePopupUtil::setBackgroundColor(QColor color)
{
 if(_textComponent == NULL ) return;
 //if(qobject_cast<DragDecoratorLabel*>(_textComponent)!=NULL) return;
 if(!color.isValid())
 {
  if(qobject_cast<PositionableLabel*>(_textComponent)!=NULL)
  {
   ((PositionableLabel*)_textComponent)->setOpaque(false);
   if(qobject_cast<JLabel*>(_textComponent)!= NULL)
    ((JLabel*)_textComponent)->setBackground(color);
   else
    if(qobject_cast<JTextField*>(_textComponent)!= NULL)
        ((JTextField*)_textComponent)->setBackground(color);

  }
  _parent->setOpaque(false);
 }
 else
 {
  if(qobject_cast<PositionableLabel*>(_textComponent)!= NULL)
  {
   ((PositionableLabel*)_textComponent)->setOpaque(true);
   //((PositionableLabel*)_textComponent)->setBackgroundColor(color);
   QColor oldC = ((JLabel*)_textComponent)->getBackground();
   if(qobject_cast<JLabel*>(_textComponent)!= NULL && oldC!= color)
    ((JLabel*)_textComponent)->setBackground(color);
   else
    if(qobject_cast<JTextField*>(_textComponent)!= NULL)
        ((JTextField*)_textComponent)->setBackground(color);
  }
         //     ((JTextField*)_textComponent)->setOpaque(true);
//     ((JTextField*)_textComponent)->setBackground(color);

//  _parent->setOpaque(true);
//  _parent->setBackground(color);
 }
 setMargin(margin);  //This rebuilds margin and sets it colour.
 _parent->updateSize();
}

/*public*/ void PositionablePopupUtil::setHasBackground(bool set) {
    _hasBackground = set;
    //if (_textComponent instanceof PositionableJPanel)
    if(qobject_cast<PositionableJPanel*>(_textComponent) != NULL)
    {
        ((Positionable*)_textComponent)->setOpaque(_hasBackground);
    }
    if (!_hasBackground) {
        _parent->setOpaque(false);
        ((Positionable*)_textComponent)->setOpaque(false);
    }
}
/*public*/ void PositionablePopupUtil::setSuppressRecentColor(bool b) {
       _suppressRecentColor = b;
   }
/*public*/ bool PositionablePopupUtil::hasBackground() {
    return _hasBackground;
}

/*public*/ QColor PositionablePopupUtil::getBackground()
{
 QColor c = ((PositionableLabel*)_textComponent)->getBackground();
 if (!c.isValid()) {
     c = QColor(Qt::white);
 }
 if (!_hasBackground) {
     // make sure the alpha value is set to 0
     c = ColorUtil::setAlpha(c,0);
 }
 return c;

}

/*protected*/ QMenu* PositionablePopupUtil::makeFontSizeMenu()
{
    QMenu* sizeMenu = new QMenu("Font Size");
    QActionGroup* buttonGrp = new QActionGroup(this);
    addFontMenuEntry(sizeMenu, buttonGrp, 6);
    addFontMenuEntry(sizeMenu, buttonGrp, 8);
    addFontMenuEntry(sizeMenu, buttonGrp, 10);
    addFontMenuEntry(sizeMenu, buttonGrp, 11);
    addFontMenuEntry(sizeMenu, buttonGrp, 12);
    addFontMenuEntry(sizeMenu, buttonGrp, 14);
    addFontMenuEntry(sizeMenu, buttonGrp, 16);
    addFontMenuEntry(sizeMenu, buttonGrp, 20);
    addFontMenuEntry(sizeMenu, buttonGrp, 24);
    addFontMenuEntry(sizeMenu, buttonGrp, 28);
    addFontMenuEntry(sizeMenu, buttonGrp, 32);
    addFontMenuEntry(sizeMenu, buttonGrp, 36);
    connect(buttonGrp, SIGNAL(triggered(QAction*)), this, SLOT(on_setFontSize(QAction*)));
    return sizeMenu;
}
void PositionablePopupUtil::on_setFontSize(QAction *act)
{
 int size = act->data().toInt();
 setFontSize((float)size);
}

void PositionablePopupUtil::addFontMenuEntry(QMenu* menu, QActionGroup* fontButtonGroup, const int size)
{
// QRadioButton* r = new QRadioButton(""+QString("%1").arg(size));
//    r.addActionListener(new ActionListener() {
//        final float desiredSize = size+0.f;
//        /*public*/ void actionPerformed(ActionEvent e) {
//            setFontSize(desiredSize);
//        }
//    });
    // TODO:
//    fontButtonGroup->add(r);
//    if (_textComponent->getFont().getSize() == size) r.setSelected(true);
//    else r.setSelected(false);
//    menu.add(r);
 QAction* act = new QAction(QString("%1").arg(size),this);
 act->setCheckable(true);
 if(((PositionableLabel*)_textComponent)->getFont().pointSize() == size)
  act->setChecked(true);
 act->setData(size);
 menu->addAction(act);
 fontButtonGroup->addAction(act);
}

/*public*/ void PositionablePopupUtil::setFont(QFont font) {
    if(_textComponent == NULL) return;
    ((PositionableLabel*)_textComponent)->setFont(font);
    _parent->updateSize();
}

/*public*/ QFont PositionablePopupUtil::getFont()
{
 if(_textComponent == NULL) return QFont();
 if(qobject_cast<PositionableLabel*> (_textComponent))
  return ((PositionableLabel*)_textComponent)->getFont();
 //return ((Positionable*)_textComponent)->getFont();
 return _textComponent->font();
}

/*public*/ void PositionablePopupUtil::setFontSize(float newSize)
{
 //_textComponent.setFont(jmri.util.FontUtil.deriveFont(getFont(), newSize));
 if(_textComponent == nullptr)
  return;
 QFont f;
 if(qobject_cast<JTextField*>(_textComponent) || qobject_cast<QLabel*>(_textComponent))
  f = _textComponent->font();
 else
  f = ((PositionableLabel*)_textComponent)->getFont();
 f.setPointSizeF(newSize);
 _textComponent->setFont(f);
 _parent->updateSize();
 ///_parent.getEditor().setAttributes(_self, _parent);
}

/*public*/ int PositionablePopupUtil::getFontSize()
{
 if(_textComponent == NULL) return 0;
   if(qobject_cast<PositionableLabel*>(_textComponent))
    return((PositionableLabel*)_textComponent)->getFont().pointSize();
 return (_textComponent)->font().pointSize();
}

void PositionablePopupUtil::setItalic()
{
 if (debug)
  log->debug("When style item selected italic state is "+italic->isChecked());
 if (italic->isChecked()) setFontStyle(QFont::StyleItalic);
 else setFontStyle(QFont::StyleNormal);
 //_parent->_editor->addToTarget(_parent);
}
void PositionablePopupUtil::setBold()
{
 if (debug)
  log->debug("When style item selected bold state is "+bold->isChecked());
 if (bold->isChecked()) setFontStyle(QFont::Bold, 0);
 else setFontStyle(0, QFont::Bold);
}

/*protected*/ QMenu* PositionablePopupUtil::makeFontStyleMenu()
{
    QMenu* styleMenu = new QMenu(tr("Font Style"));
//    styleMenu.add(italic = newStyleMenuItem(new AbstractAction(tr("Italic")) {
//        /*public*/ void actionPerformed(ActionEvent e) {
//            if (debug)
//                log->debug("When style item selected "+((QString)getValue(NAME))
//                            +" italic state is "+italic.isSelected());
//            if (italic.isSelected()) setFontStyle(Font.ITALIC, 0);
//            else setFontStyle(0, Font.ITALIC);
//        }
//      }, Font.ITALIC));
    italic = new QAction(tr("Italic"),this);
    styleMenu->addAction(italic);
    connect(italic, SIGNAL(triggered()), this, SLOT(on_italicAction_triggered()));

//    styleMenu.add(bold = newStyleMenuItem(new AbstractAction(tr("Bold")) {
//        /*public*/ void actionPerformed(ActionEvent e) {
//            if (debug)
//                log->debug("When style item selected "+((QString)getValue(NAME))
//                            +" bold state is "+bold.isSelected());
//            if (bold.isSelected()) setFontStyle(Font.BOLD, 0);
//            else setFontStyle(0, Font.BOLD);
//        }
//      }, Font.BOLD));
    bold = new QAction(tr("Bold"),this);
    styleMenu->addAction(bold);
    connect(bold, SIGNAL(triggered()), this, SLOT(on_boldAction_triggered()));

     return styleMenu;
}

/*public*/ void PositionablePopupUtil::setFontStyle(int style)
{
 //((PositionableLabel*)_textComponent)->setFont(deriveFont(_textComponent->getFont(),style));
 //((PositionableLabel*)_textComponent)->getFont().setStyle((QFont::Style)style);
 QFont f = ((PositionableLabel*)_textComponent)->getFont();
 f.setStyle((QFont::Style)style);
 ((PositionableLabel*)_textComponent)->setFont(f);
 _parent->updateSize();
}
void PositionablePopupUtil::setFontWeight(int weight)
{
 //((PositionableLabel*)_textComponent)->getFont().setWeight(weight);
 QFont f = ((PositionableLabel*)_textComponent)->getFont();
 f.setWeight((QFont::Weight)weight);
 ((PositionableLabel*)_textComponent)->setFont(f);
 _parent->updateSize();
}

/*public*/ void PositionablePopupUtil::setFontStyle(int addStyle, int dropStyle)
{
 //int styleValue = (((PositionableLabel*)_textComponent)->getFont().style() & ~dropStyle) | addStyle;
 //int styleValue = (((JTextField*)_textComponent)->font().style() & ~dropStyle) | addStyle;
 QFont f = ((PositionableLabel*)_textComponent)->font();
 int style = 0; // Convert Qt QFont style & weight to Java Font style
 if(f.style() == QFont::StyleNormal && f.weight() == QFont::Normal)
  style = 0;
 else if(style == QFont::StyleNormal && f.weight() == QFont::Bold)
  style = 1;
 else if(style == QFont::StyleItalic && f.weight() == QFont::Normal)
  style = 2;
 else if(style == QFont::StyleItalic && f.weight() == QFont::Bold)
  style = 3;
 int styleValue = (style & ~dropStyle) | addStyle;
 if (debug)
  log->debug("setFontStyle: addStyle="+QString("%1").arg(addStyle)+", dropStyle= "+QString("%1").arg(dropStyle)
                    +", net styleValue is "+QString("%1").arg(styleValue));
 if (bold != NULL) bold->setChecked( (styleValue & 1) != 0);
 if (italic != NULL) italic->setChecked( (styleValue & 2) != 0);
  //((PositionableLabel*)_textComponent)->setFont(deriveFont(((PositionableLabel*)_textComponent)->getFont(),styleValue));
// ((PositionableLabel*)_textComponent)->getFont().setStyle((QFont::Style)styleValue);
 //QFont f = ((JTextField*)_textComponent)->font();
 //f.setPointSize(8);
 //f.setStyle((QFont::Style)styleValue);
 switch (styleValue)
 {
 default:
 case 0:
   f.setStyle(QFont::StyleNormal);
   f.setWeight(QFont::Normal);
   break;
 case 1:
  f.setStyle(QFont::StyleNormal);
  f.setWeight(QFont::Bold);
  break;
 case 2:
  f.setStyle(QFont::StyleItalic);
  f.setWeight(QFont::Normal);
  break;
 case 3:
  f.setStyle(QFont::StyleItalic);
  f.setWeight(QFont::Bold);
  break;
 }

 if(qobject_cast<PositionableLabel*>(_textComponent) != NULL)
  ((PositionableLabel*)_textComponent)->setFont(f);
    //setSize(getPreferredSize().width, getPreferredSize().height);
 _parent->updateSize();
}

/*public*/ int PositionablePopupUtil::getFontStyle() {
//    return ((PositionableLabel*)_textComponent)->getFont().getStyle();
 QFont f = ((JTextField*)_textComponent)->font();
 int style = 0; // Convert Qt QFont style & weight to Java Font style
 if(f.style() == QFont::StyleNormal && f.weight() == QFont::Normal)
  style = 0;
 else if(style == QFont::StyleNormal && f.weight() == QFont::Bold)
  style = 1;
 else if(style == QFont::StyleItalic && f.weight() == QFont::Normal)
  style = 2;
 else if(style == QFont::StyleItalic && f.weight() == QFont::Bold)
  style = 3;
 return style; // Java style!
}

/*protected*/ QAction* PositionablePopupUtil::newStyleMenuItem(QAction* a, int /*mask*/)
{
    // next two lines needed because JCheckBoxMenuItem(AbstractAction) not in 1.1.8
//    JCheckBoxMenuItem c = new JCheckBoxMenuItem((QString)a.getValue(AbstractAction.NAME));
//    c.addActionListener(a);
//    if (debug) log->debug("When creating style item "+((QString)a.getValue(AbstractAction.NAME))
//                                        +" mask was "+mask+" state was "+_textComponent.getFont().getStyle());
//    if ( (mask & _textComponent.getFont().getStyle()) == mask ) c.setSelected(true);
//    return c;
  QAction* newStyleMenuItemAction = new QAction(a->text(), this);
  newStyleMenuItemAction->setCheckable(true);
  return newStyleMenuItemAction;
}
#if 0
/*protected*/ void PositionablePopupUtil::makeColorMenu(QMenu* colorMenu, int type)
{
 saveType = type;
 QActionGroup* buttonGrp = new QActionGroup(this);
 addColorMenuEntry(colorMenu, buttonGrp, tr("Black"), QColor(Qt::black), type);
 addColorMenuEntry(colorMenu, buttonGrp, tr("DarkGray"),QColor(Qt::darkGray), type);
 addColorMenuEntry(colorMenu, buttonGrp, tr("Gray"),QColor(Qt::gray), type);
 addColorMenuEntry(colorMenu, buttonGrp, tr("LightGray"),QColor(Qt::lightGray), type);
 addColorMenuEntry(colorMenu, buttonGrp, tr("White"),QColor(Qt::white), type);
 addColorMenuEntry(colorMenu, buttonGrp, tr("Red"),QColor(Qt::red), type);
 addColorMenuEntry(colorMenu, buttonGrp, tr("Orange"),QColor(255,170,0), type);
 addColorMenuEntry(colorMenu, buttonGrp, tr("Yellow"),QColor(Qt::yellow), type);
 addColorMenuEntry(colorMenu, buttonGrp, tr("Green"),QColor(Qt::green), type);
 addColorMenuEntry(colorMenu, buttonGrp, tr("Blue"),QColor(Qt::blue), type);
 addColorMenuEntry(colorMenu, buttonGrp, tr("Magenta"),QColor(Qt::magenta), type);
 if (type == BACKGROUND_COLOR)
 {
  addColorMenuEntry(colorMenu, buttonGrp, tr("Clear"), QColor(Qt::transparent), type);
 }
 connect(buttonGrp, SIGNAL(triggered(QAction*)), this,SLOT(on_colorMenuItemSelected(QAction*)));
}
void PositionablePopupUtil::on_colorMenuItemSelected(QAction *act)
{
 int type = act->data().toInt();
 QColor desiredColor = _propertiesUtil->colorStringToColor(act->text());
 switch(type)
 {
 case FONT_COLOR:
  ((PositionableLabel*)_textComponent)->setForeground(desiredColor);
  act->setChecked(true);
  if(qobject_cast<PositionableLabel*>(_parent))
  {
   if(_parent->isIcon())
  _parent->setIcon( _parent->makeTextOverlaidIcon(_parent->getUnRotatedText(), _parent->getIcon()));
  }
  break;
 case BACKGROUND_COLOR:
  if(!desiredColor.isValid())
  {
   ((PositionableLabel*)_textComponent)->setOpaque(false);
     _parent->setOpaque(false);
     //We need to force a redisplay when going to clear as the area
     //doesn't always go transparent on the first click.
     QPointF p = _parent->getLocation();
     int w = _parent->getWidth();
     int h = _parent->getHeight();
#if 0 // TODO:
     Container parent = _parent.getParent();
     // force redisplay
     setMargin(margin);  //This rebuilds margin and clears it colour.
     parent.validate();
     parent.repaint(p.x,p.y,w,h);

#endif
  }
  else
   setBackgroundColor(desiredColor);
  break;
 case BORDER_COLOR :
  setBorderColor(desiredColor);
  break;
 }
 _parent->_editor->addToTarget(_parent);
}


/*protected*/ void PositionablePopupUtil::addColorMenuEntry(QMenu* menu, QActionGroup* colorButtonGroup, const QString name, QColor color, const int colorType)
{
//    ActionListener a = new ActionListener() {
//        //final QString desiredName = name;
//        Color desiredColor;
//        /*public*/ void actionPerformed(ActionEvent e) {
//            switch (colorType){
//                case FONT_COLOR :
//                    _textComponent.setForeground(desiredColor);
//                    break;
//                case BACKGROUND_COLOR :
//                    if(desiredColor==NULL){
//                        _textComponent.setOpaque(false);
//                        _parent.setOpaque(false);
//                        //We need to force a redisplay when going to clear as the area
//                        //doesn't always go transparent on the first click.
//                        Point p = _parent.getLocation();
//                        int w = _parent.getWidth();
//                        int h = _parent.getHeight();
//                        Container parent = _parent.getParent();
//                        // force redisplay
//                        setMargin(margin);  //This rebuilds margin and clears it colour.
//                        parent.validate();
//                        parent.repaint(p.x,p.y,w,h);
//                    }
//                    else
//                        setBackgroundColor(desiredColor);
//                    break;
//                case BORDER_COLOR :
//                    setBorderColor(desiredColor);
//                    break;
//            }
//        }
//        ActionListener init (Color c) {
//            desiredColor = c;
//            return this;
//        }
//    }.init(color);
//    JRadioButtonMenuItem r = new JRadioButtonMenuItem(name);
//    r.addActionListener(a);

//    if (debug) log->debug("setColorButton: colorType="+colorType);
//    switch (colorType) {
//        case FONT_COLOR:
//            if (color==NULL) { color = defaultForeground; }
//            setColorButton(_textComponent.getForeground(), color, r);
//            break;
//        case BACKGROUND_COLOR:
//            if (color==NULL) { color = defaultBackground; }
//            setColorButton(_textComponent.getBackground(), color, r);
//            break;
//        case BORDER_COLOR:
//            if (color==NULL) { color = defaultBorderColor; }
//            setColorButton(getBorderColor(), color, r);
//    }
//    colorButtonGroup.add(r);
//    menu.add(r);
  QAction* act = new QAction(getColourIcon(color), name, this);
  act->setCheckable(true);
  switch (colorType)
  {
   case FONT_COLOR:
    //if (!color.isValid() { color = defaultForeground; }
    //setColorButton(_textComponent.getForeground(), color, r);
    if(((PositionableLabel*)_textComponent)->getForeground()== color)
     act->setChecked(true);
    break;
   case BACKGROUND_COLOR:
    //if (color==NULL) { color = defaultBackground; }
    //setColorButton(_textComponent.getBackground(), color, r);
    if(((PositionableLabel*)_textComponent)->getBackground() == color)
     act->setChecked(true);
    break;
   case BORDER_COLOR:
    //if (color==NULL) { color = defaultBorderColor; }
    //setColorButton(getBorderColor(), color, r);
    if(getBorderColor() == color)
     act->setChecked(true);
    break;
 }
 act->setData(colorType);
 colorButtonGroup->addAction(act);
 menu->addAction(act);
}

/*protected*/ void PositionablePopupUtil::setColorButton(QColor color, QColor buttonColor, QRadioButton* r)
{
// if (debug)
//        log->debug("setColorButton: color="+color+" (RGB= "+(color==NULL?"":color.getRGB())+
//                  ") buttonColor= "+buttonColor+" (RGB= "+(buttonColor==NULL?"":buttonColor.getRGB())+")");
 if (buttonColor.isValid())
 {
  if (color.isValid() && buttonColor.name() == color.name())
  {
   r->setChecked(true);
  }
  else r->setChecked(false);
 }
 else
 {
  if (!color.isValid())  r->setChecked(true);
  else  r->setChecked(false);
 }
}
#endif
/*public*/ void PositionablePopupUtil::copyItem(QMenu* popup){
    QAction*  edit = new QAction("Copy", this);
//    edit.addActionListener(new ActionListener() {
//        /*public*/ void actionPerformed(ActionEvent e) { _parent.getEditor().copyItem(_parent); }
//    });
//    connect(edit, SIGNAL(triggered()), _parent->getEditor(), SLOT(copyItem()));
    popup->addAction(edit);
}
/*************** Justification ************************/

/*public*/ void PositionablePopupUtil::setTextJustificationMenu(QMenu* popup)
{
 QMenu* justMenu = new QMenu("Justification");
 addJustificationMenuEntry(justMenu, LEFT);
 addJustificationMenuEntry(justMenu, RIGHT);
 addJustificationMenuEntry(justMenu, CENTRE);
 popup->addMenu(justMenu);
}



/*public*/ void PositionablePopupUtil::setJustification(int just)
{
 log->debug("setJustification: justification="+QString("%1").arg(just));
 justification=just;
 setHorizontalAlignment(justification);
 _parent->updateSize();
}

/*public*/ void PositionablePopupUtil::setJustification(QString just){
    log->debug("setJustification: justification="+QString("%1").arg(just));
    if (just==("right"))
        justification=RIGHT;
    else if (just==("centre"))
        justification=CENTRE;
    else
        justification=LEFT;
    setHorizontalAlignment(justification);
    _parent->updateSize();
}

/*public*/ int PositionablePopupUtil::getJustification()
{
 if(debug) log->debug("getJustification: justification="+QString("%1").arg(justification));
    return justification;
}

void PositionablePopupUtil::addJustificationMenuEntry(QMenu* menu, const int just)
{
 QActionGroup* justButtonGroup = new QActionGroup(this);
 QAction* r;
 switch(just)
 {
  case LEFT :
   r = new QAction(tr("LEFT"), this);
   r->setData(LEFT);
   break;
  case RIGHT:
   r = new QAction(tr("RIGHT"),this);
   r->setData(RIGHT);
   break;
  case CENTRE:
   r = new QAction(tr("CENTER"),this);
   r->setData(CENTRE);
   break;
  default :
   r = new QAction("LEFT",this);
   r->setData(LEFT);
 }
 r->setCheckable(true);
//    r.addActionListener(new ActionListener() {
//        //final int justification = just;
//        /*public*/ void actionPerformed(ActionEvent e) { setJustification(just); }
//    });
 justButtonGroup->addAction(r);
 if (justification == just) r->setChecked(true);
 else r->setChecked(false);
 menu->addAction(r);
}

/*public*/ void PositionablePopupUtil::setHorizontalAlignment(int alignment)
{
 if (_textType == LABEL)
 {
  switch (alignment)
  {
  case LEFT :
   ((JLabel*)_textComponent)->setHorizontalAlignment(JLabel::LEFT);
                            break;
        case RIGHT :    ((JLabel*)_textComponent)->setHorizontalAlignment(JLabel::RIGHT);
                            break;
        case CENTRE :   ((JLabel*)_textComponent)->setHorizontalAlignment(JLabel::CENTER);
                            break;
        default     :   ((JLabel*)_textComponent)->setHorizontalAlignment(JLabel::CENTER);
        }
    }
//    else if (_textType == TEXTFIELD) {
//        switch (alignment){
//            case LEFT :     ((JTextField)_textComponent).setHorizontalAlignment(JTextField.LEFT);
//                            break;
//            case RIGHT :    ((JTextField)_textComponent).setHorizontalAlignment(JTextField.RIGHT);
//                            break;
//            case CENTRE :   ((JTextField)_textComponent).setHorizontalAlignment(JTextField.CENTER);
//                            break;
//            default     :   ((JTextField)_textComponent).setHorizontalAlignment(JTextField.CENTER);
//        }
//    }
}

/*public*/ QString PositionablePopupUtil::getText()
{
 if (_textType == LABEL)
 {
  //return ((JLabel*)_textComponent)->getText();
     return ((PositionableLabel*)_textComponent)->getUnRotatedText();
 }
 else if (_textType == TEXTFIELD) {
        return ((QLineEdit*)_textComponent)->text();
    }
    return NULL;
}


/*public*/ int PositionablePopupUtil::getOrientation(){
    return orientation;
}

/*public*/ void PositionablePopupUtil::setOrientation(int ori){
    orientation=ori;
    _parent->updateSize();
}

/*public*/ void PositionablePopupUtil::setOrientation(QString ori){
    if(ori==("vertical_up"))
        setOrientation(VERTICAL_UP);
    else if(ori==("vertical_down"))
        setOrientation(VERTICAL_DOWN);
    else
        setOrientation(HORIZONTAL);
}

/*public*/ void PositionablePopupUtil::setTextOrientationMenu(QMenu* popup)
{
 QMenu* oriMenu = new QMenu("Orientation");
 QActionGroup* justButtonGroup = new QActionGroup(this);
 addOrientationMenuEntry(oriMenu, justButtonGroup, HORIZONTAL);
 addOrientationMenuEntry(oriMenu, justButtonGroup, VERTICAL_UP);
 addOrientationMenuEntry(oriMenu, justButtonGroup, VERTICAL_DOWN);
 popup->addMenu(oriMenu);
 connect(justButtonGroup, SIGNAL(triggered(QAction*)), this, SLOT(on_setTextOrientation_triggered(QAction*)));
}

void PositionablePopupUtil::addOrientationMenuEntry(QMenu* menu, QActionGroup* justButtonGroup, const int ori)
{
 QAction* r;
 switch(ori)
 {
 case HORIZONTAL :
  r = new QAction(tr("Horizontal"), this);
  r->setData(HORIZONTAL);
  break;
 case VERTICAL_UP:
  r = new QAction(tr("Vertical Up"), this);
  r->setData(VERTICAL_UP);
  break;
 case VERTICAL_DOWN:
  r = new QAction("Vertical Down", this);
  r->setData(VERTICAL_DOWN);
  break;
 default :
  r = new QAction("Horizontal",this);
  r->setData(HORIZONTAL);
 }
 r->setCheckable(true);

//    r.addActionListener(new ActionListener() {
//        /*public*/ void actionPerformed(ActionEvent e) { setOrientation(ori); }
//    });
 justButtonGroup->addAction(r);
 if (orientation == ori) r->setChecked(true);
 else r->setChecked(false);
 menu->addAction(r);
}
void PositionablePopupUtil::on_setTextOrientation_triggered(QAction *act)
{
 int ori = act->data().toInt();
 setOrientation(ori);
}

/**
*  Add a menu item to be displayed when the popup menu is called for
*  when in edit mode.
*/
/*public*/ void PositionablePopupUtil::addEditPopUpMenu(QMenu* menu)
{
 if(!editAdditionalMenu->contains(menu))
 {
  editAdditionalMenu->append(menu);
 }
}

/**
*  Add a menu item to be displayed when the popup menu is called for
*  when in view mode.
*/
/*public*/ void PositionablePopupUtil::addViewPopUpMenu(QMenu* menu)
{
 if(!viewAdditionalMenu->contains(menu))
 {
  viewAdditionalMenu->append(menu);
 }
}

/**
*  Add the menu items to the edit popup menu
*/
/*public*/ void PositionablePopupUtil::setAdditionalEditPopUpMenu(QMenu* popup)
{
 if(editAdditionalMenu == NULL ||editAdditionalMenu->isEmpty())
  return;
 popup->addSeparator();
 foreach (QMenu* mi, *editAdditionalMenu)
 {
  popup->addMenu(mi);
 }
}

/**
*  Add the menu items to the view popup menu
*/
/*public*/ void PositionablePopupUtil::setAdditionalViewPopUpMenu(QMenu* popup)
{
 if(viewAdditionalMenu->isEmpty())
  return;
 foreach(QMenu* mi, *viewAdditionalMenu)
 {
  popup->addMenu(mi);
 }
}
void PositionablePopupUtil::on_italicAction_triggered()
{
   // TODO:
}
void PositionablePopupUtil::on_boldAction_triggered()
{
  // TODO:
}

//    static org.apache.log4j.Logger log = org.apache.log4j.Logger.getLogger(PositionablePopupUtil.class.getName());
//}
const QIcon PositionablePopupUtil::getColourIcon(QColor color)
{
 Q_ASSERT(color.isValid());
 int ICON_DIMENSION = 10;
// BufferedImage image = new BufferedImage(ICON_DIMENSION, ICON_DIMENSION,
// BufferedImage.TYPE_INT_RGB);
 QImage resultImage = QImage(ICON_DIMENSION,ICON_DIMENSION,QImage::Format_ARGB32_Premultiplied);

// Graphics g = image.getGraphics();
 QPainter painter(&resultImage);
//   // set completely transparent
// g.setColor(color);
// g.fillRect(0,0, ICON_DIMENSION,ICON_DIMENSION);
 QBrush brBkgnd = QBrush(QColor(color), Qt::SolidPattern);
//eRect.adjust(0, -3.0, 0, 0);
 painter.fillRect(resultImage.rect(), brBkgnd);
 painter.end();
// ImageIcon icon = new ImageIcon(image);
 QIcon icon =  QIcon(QPixmap::fromImage(resultImage));
 return icon;
}
