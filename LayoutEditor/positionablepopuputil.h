#ifndef POSITIONABLEPOPUPUTIL_H
#define POSITIONABLEPOPUPUTIL_H

#include <QObject>
#include "positionable.h"
#include <QRadioButton>
#include "positionablepropertiesutil.h"
#include <QFont>
#include <QMenu>
#include "logger.h"
#include "positionablelabel.h"

class PositionablePropertiesUtil;
class PositionablePopupUtil : public QObject
{
    Q_OBJECT
public:
 //explicit PositionablePopupUtil(QObject *parent = 0);
    /*public*/ PositionablePopupUtil(Positionable* parent, QObject* textComp);
    /*public*/ PositionablePopupUtil* clone(Positionable* parent, QObject* textComp);
    /*public*/ QString toString();
    static const /*public*/ int FONT_COLOR =             0x00;
    static const /*public*/ int BACKGROUND_COLOR =       0x01;
    static const /*public*/ int BORDER_COLOR =           0x02;
    static const /*public*/ int MIN_SIZE = 5;
    /*public*/ void propertyUtil(QMenu* popup);
    /*public*/ void setFixedTextMenu(QMenu* popup);
    /*public*/ void setTextMarginMenu(QMenu* popup);
    /*public*/ void setBackgroundMenu(QMenu* popup);
    /*public*/ void setTextBorderMenu(QMenu* popup);
    /*public*/ void setTextFontMenu(QMenu* popup) ;
    /*public*/ int getMargin();
    /*public*/ void setMargin(int m);
    /*public*/ int getFixedWidth();
    /*public*/ void setFixedWidth(int w);
    /*public*/ int getFixedHeight();
    /*public*/ void setFixedHeight(int h);
    /*public*/ void setFixedSize(int w, int h);
    /*public*/ void setBorderSize(int border);
    /*public*/ void setBorder(bool set);
    /*public*/ int getBorderSize();
    /*public*/ void setBorderColor(QColor border);
    /*public*/ QColor getBorderColor();
    /*public*/ void setForeground(QColor c);
    /*public*/ QColor getForeground();
    /*public*/ void setBackgroundColor(QColor color);
    /*public*/ QColor getBackground();
    /*public*/ void setFont(QFont font);
    /*public*/ QFont getFont();
    /*public*/ void setFontSize(float newSize);
    /*public*/ int getFontSize();
    void setItalic();
    void setBold() ;
    /*protected*/ QMenu* makeFontStyleMenu();
    /*public*/ void setFontStyle(int style);
    void setFontWeight(int weight);
    /*public*/ void setFontStyle(int addStyle, int dropStyle);
    /*public*/ int getFontStyle();
    /*protected*/ void makeColorMenu(QMenu* colorMenu, int type);
    /*protected*/ void addColorMenuEntry(QMenu* menu, QActionGroup* colorButtonGroup, const QString name, QColor color, const int colorType);
    /*protected*/ void setColorButton(QColor color, QColor buttonColor, QRadioButton* r);
    /*public*/ void copyItem(QMenu* popup);
    static /*public*/ const int LEFT   = 0x00;
    static /*public*/ const int RIGHT  = 0x02;
    static /*public*/ const int CENTRE = 0x04;
    /*public*/ void setTextJustificationMenu(QMenu* popup) ;
    /*public*/ void setJustification(int just);
    /*public*/ void setJustification(QString just);
    /*public*/ int getJustification();
    void addJustificationMenuEntry(QMenu* menu, const int just);
    /*public*/ void setHorizontalAlignment(int alignment);
    /*public*/ QString getText() ;
    /*public*/ const static int HORIZONTAL = 0x00;
    /*public*/ const static int VERTICAL_UP =0x01;
    /*public*/ const static int VERTICAL_DOWN =0x02;
    /*public*/ int getOrientation();
//    /*public*/ void setOrientation(int ori);
    /*public*/ void setOrientation(QString ori);
    /*public*/ void setTextOrientationMenu(QMenu* popup) ;
    void addOrientationMenuEntry(QMenu* menu, QActionGroup* justButtonGroup, const int ori);
    /**
    *  Add a menu item to be displayed when the popup menu is called for
    *  when in edit mode.
    */
    /*public*/ void addEditPopUpMenu(QMenu* menu);
    /**
    *  Add a menu item to be displayed when the popup menu is called for
    *  when in view mode.
    */
    /*public*/ void addViewPopUpMenu(QMenu* menu);
    /**
    *  Add the menu items to the edit popup menu
    */
    /*public*/ void setAdditionalEditPopUpMenu(QMenu* popup);
    /**
    *  Add the menu items to the view popup menu
    */
    /*public*/ void setAdditionalViewPopUpMenu(QMenu* popup);
    const QIcon getColourIcon(QColor color);


signals:
    
public slots:
 /*public*/ void setOrientation(int ori);
 void on_setFontSize(QAction* act);
 void on_colorMenuItemSelected(QAction* act);
 void on_actionMarginEdit_triggered();
 void on_actionGetFixedSizeEdit_triggered();
 void on_setTextOrientation_triggered(QAction* act);

private:
 /*private*/ bool debug;// = false;
 void init();
 /*private*/ int fixedWidth;//=0;
 /*private*/ int fixedHeight;//=0;
 /*private*/ int margin;//=0;
 /*private*/ int borderSize;//=0;
 /*private*/ QColor borderColor;//=null;
// /*private*/ Border borderMargin;// = BorderFactory.createEmptyBorder(0, 0, 0, 0);
// /*private*/ Border outlineBorder;// = BorderFactory.createEmptyBorder(0, 0, 0, 0);

 QAction* italic;// = null;
 QAction* bold;// = null;
 /*private*/ bool _showBorder;// = true;
 /*private*/ int justification;//=CENTRE; //Default is always Centre
 /*private*/ int orientation;// = HORIZONTAL;
 QVector<QMenu*>* editAdditionalMenu;// = new QVector<QMenu*>(0);
 QVector<QMenu*>* viewAdditionalMenu;// = new QVector<QMenu*>(0);
 int saveType;

 Logger* log;
private slots:
 void on_italicAction_triggered();
 void on_boldAction_triggered();
 void display();

protected:
 /*protected*/ QObject* _textComponent;    // closest ancestor for JLabel and JTextField
 /*protected*/ int _textType;                // JComponent does not have text, used for casting
 /*protected*/ Positionable* _parent;
 /*protected*/ PositionablePropertiesUtil* _propertiesUtil;
 /*private*/ QColor defaultForeground;
 /*private*/ QColor defaultBackground;
 /*private*/ QColor defaultBorderColor;
 /*protected*/ static const int LABEL = 1;
 /*protected*/ static const int TEXTFIELD = 2;
 /*protected*/ static const int JCOMPONENT = 3;
 /*protected*/ QMenu* makeFontSizeMenu();
 void addFontMenuEntry(QMenu* menu, QActionGroup* fontButtonGroup, const int size);
 /*protected*/ QAction* newStyleMenuItem(QAction* a, int mask);
 friend class PositionablePropertiesUtil;
};

#endif // POSITIONABLEPOPUPUTIL_H
