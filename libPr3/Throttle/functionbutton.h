#ifndef FUNCTIONBUTTON_H
#define FUNCTIONBUTTON_H
#include "jtogglebutton.h"
#include "logger.h"
#include "jcomponent.h"

class QDomDocument;
class JActionEvent;
class QDomElement;
class FunctionListener;
class FunctionButton : public JToggleButton, public JComponent
{
    Q_OBJECT
  Q_INTERFACES(JComponent)
public:
    explicit FunctionButton(QWidget *parent = 0);
    /*public*/ static int getButtonHeight();
    /*public*/ static int getButtonWidth();
    /*public*/ void setIdentity(int id);
    /*public*/ int getIdentity();
    /*public*/ void setKeyCode(int key);
    /*public*/ bool checkKeyCode(int keycode);
    /*public*/ void setState(bool isOn);
    /*public*/ bool getState();
    /*public*/ void setIsLockable(bool isLockable);
    /*public*/ bool getIsLockable();
    /*public*/ void setDisplay(bool displayed);
    /*public*/ bool getDisplay();
    /*public*/ void setDirty(bool dirty);
    /*public*/ bool isDirty();
    /*public*/ QString getButtonLabel() ;
    /*public*/ void setButtonLabel(QString label);
    /*public*/ void setText(QString s);
    /*public*/ void updateLnF();
    /*public*/ void changeState(bool newState);
    /*public*/ void setFunctionListener(FunctionListener* l);
    /*public*/ void addFunctionListener(FunctionListener* l);
    /*public*/ void removeFunctionListener(FunctionListener* l);
//    class PopupListener : public QObject
//    {
        /**
         * If the event is the popup trigger, which is dependent on
         * the platform, present the popup menu. Otherwise change
         * the state of the function depending on the locking state
         * of the button.
         * @param e The MouseEvent causing the action.
         */
        /*public*/ void mousePressEvent(QMouseEvent* e);
        /*public*/ void mouseReleaseEvent(QMouseEvent* e);
//    };

    /*public*/ QDomElement getXml();
    /*public*/ void setXml(QDomElement e);
    /*public*/ void setIconPath(QString fnImg);
    /*public*/ QString getIconPath();
    /*public*/ void setSelectedIconPath(QString fnImg);
    /*public*/ QString getSelectedIconPath();
    /*public*/ bool isImageOK();
    /*public*/ bool isSelectedImageOK();
    static int BUT_HGHT;// = 30;
    static int BUT_WDTH;// = 56;
    /*final*/ static int BUT_IMG_SIZE;// = 45;
    QObject* jself() {return (QObject*)this;}
    /*public*/ void setEnabled(bool b) override {QWidget::setEnabled(b);}
    /*public*/ bool isOpaque() override {return true;}
    /*public*/ QColor getForeground() override {return Qt::black;}
    /*public*/ QColor getBackground() override {return Qt::lightGray;}
    /*public*/ void setBackground(QColor) override {}
    /*public*/ void setOpaque(bool) override {}
    /*public*/ QFont getFont() override {return QWidget::font();}
    /*public*/ void setFont(QFont) override {}
    /*public*/ Border* getBorder() override {return nullptr;}
    /*public*/ void setBorder(Border*) override {}

signals:
    void notifyFunctionStateChanged(int identity, bool isOn);
    void notifyFunctionLockableChanged(int identity, bool isLockable);

public slots:
    /*public*/ void popactionPerformed(JActionEvent* e = 0);

private:
    /*private*/ QList<FunctionListener*> listeners;// = new QList<FunctionListener>();
    /*private*/ int identity; // F0, F1, etc?
    /*private*/ bool isOn;
    /*private*/ bool isLockable = true;
    /*private*/ bool isDisplayed = true;
    /*private*/ bool dirty = false;
    /*private*/ bool _isImageOK = false;
    /*private*/ bool _isSelectedImageOK = false;
    /*private*/ int actionKey;
    /*private*/ QString buttonLabel;
    /*private*/ QMenu* popup;
    /*private*/ QString iconPath;
    /*private*/ QString selectedIconPath;
    void init();
    NamedIcon* unSelectedIcon;
    NamedIcon* selectedIcon;

    static    QPushButton* sample;// = new QPushButton(" Light ");
    /*private*/ bool checkFile(QString name);
 Logger* log;

};

#endif // FUNCTIONBUTTON_H
