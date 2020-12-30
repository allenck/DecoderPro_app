#ifndef BEANSWITCH_H
#define BEANSWITCH_H
#include "jpanel.h"
#include "namedbeanhandle.h"
#include "bufferedimage.h"
#include "actionlistener.h"

class JTextField;
class JmriJFrame;
class QMenu;
class JActionEvent;
class Turnout;
class Sensor;
class Light;
class IconSwitch;
class QPushButton;
class SwitchboardEditor;
class NamedBean;
class NamedBeanHandleManager;
class Logger;
class BeanSwitch : public JPanel
{
 Q_OBJECT
public:
 /*public*/ BeanSwitch(int index, NamedBean* bean, QString switchName, int shapeChoice, SwitchboardEditor* editor);
 ~BeanSwitch();
 /*public*/ NamedBean* getNamedBean();
 /*public*/ void setNamedBean(/*@Nonnullptr*/ NamedBean* bean);
 /*public*/ Turnout* getTurnout();
 /*public*/ Sensor* getSensor();
 /*public*/ Light* getLight();
 /*public*/ int getType();
 /*public*/ QString getInactiveText();
 /*public*/ QString getActiveText();
 /*public*/ QString getUnknownText();
 /*public*/ QString getInconsistentText();
 /*public*/ QString getToolTip();
 /*public*/ void displayState(int state);
 /*public*/ /*final*/ bool isIcon();
 /*public*/ /*final*/ bool isText();

 /*public*/ void setTristate(bool set);
 /*public*/ bool getTristate();
 /*public*/ bool getMomentary();
 /*public*/ void setMomentary(bool m);
 /*public*/ QString getNameString();
 /*public*/ void operate(QMouseEvent* e, QString name);
 /*public*/ void setBackgroundColor(QColor bgcolor);
 /*public*/ void setInverted(bool set);
 /*public*/ bool getInverted();
 /*public*/ bool showPopUp(QMouseEvent* e);

public slots:
 /*public*/ void propertyChange(PropertyChangeEvent* e);
 /*public*/ void actionPerformed(JActionEvent* e);
 void mouseClicked(QMouseEvent* e = nullptr);
 /*public*/ void doMouseClicked(QMouseEvent* e);
 void mousePressed(QMouseEvent*);
 void onConnectNewLabel();
 void renameBean();
 /*public*/ void setBeanInverted(bool set);
 void mouseExited(QMouseEvent* e);


signals:
 void mouseMove(QMouseEvent* e);
 void mouseRelease(QMouseEvent* e);
 void mousePress(QMouseEvent* e);
 void mouseDoubleClick(QMouseEvent* e);

private:
 /*private*/ /*final*/ static Logger* log;// = LoggerFactory::getLogger("BeanSwitch");
 /*private*/ QPushButton* beanButton;
 ///*private*/ /*final*/ bool connected = false;
 /*private*/ int _shape;
 /*private*/ QString _label;
 /*private*/ QString _uname = "unconnected";
 // the associated Bean object
 /*private*/ NamedBean* _bname;
 /*private*/ QObject* namedBean = nullptr; // could be Turnout, Sensor or Light
 /*private*/ IconSwitch* beanIcon;
 /*private*/ IconSwitch* beanKey;
 /*private*/ IconSwitch* beanSymbol;
 /*private*/ QString beanManuPrefix;
 /*private*/ QChar beanTypeChar;
 /*private*/ float opac;// = 0.5f;
 /*private*/ SwitchboardEditor* _editor;
 /*private*/ bool tristate = false;
 bool momentary = false;
// int turnoutState();


 QString rootPath;// = "resources/icons/misc/switchboard/";
 QString iconOffPath;// = rootPath + "appslide-off-s.png";
 QString iconOnPath;// = rootPath + "appslide-on-s.png";
 QString keyOffPath;// = rootPath + "markl-off-s.png";
 QString keyOnPath;// = rootPath + "markl-on-s.png";
 QString symbolOffPath; // = rootPath + "T-off-s.png"; // default for Turnout, replace T by S or L
 QString symbolOnPath; // = rootPath + "T-on-s.png";
 void mouseMoveEvent(QMouseEvent* e);
 void mouseReleaseEvent(QMouseEvent* event);
 void mousePressEvent(QMouseEvent* event);
 void mouseDoubleClickEvent(QMouseEvent* event);
 void cleanup();
 void alternateOnClick();
 /*private*/ bool inverted = false;
 int turnoutState();
 QMenu* switchPopup;
 QAction* connectNewMenu;// = new JMenuItem(tr("ConnectNewMenu", "..."));
 QAction* editItem = nullptr;
 QAction* invertItem = nullptr;
 void addEditUserName(QMenu* popup);
 void addInvert(QMenu* popup);
 JmriJFrame* addFrame;// = nullptr;
 JTextField* sysName;// = new JTextField(12);
 JTextField* userName;// = new JTextField(15);
 void handleCreateException(QString sysName);


protected:
 /*protected*/ QString switchLabel;
 /*protected*/ QString switchTooltip;
 /*protected*/ bool _text;
 /*protected*/ bool _icon = false;
 /*protected*/ bool _control = false;
 /*protected*/ QString _state;
 /*protected*/ QString stateClosed;// = tr("StateClosedShort");
 /*protected*/ QString stateThrown;// = tr("StateThrownShort");

 /*protected*/ NamedBeanHandleManager* nbhm;// = InstanceManager::getDefault(jmri."NamedBeanHandleManager");
 /*protected*/ void connectNew(QString systemName);
 ///*protected*/ void paintComponent(QPainter* g);

protected slots:
 /*protected*/ void cancelAddPressed(JActionEvent* e = nullptr);
 /*protected*/ void okAddPressed(JActionEvent* e = nullptr);

 friend class IconSwitch;
 friend class OkActionListener;
 friend class CancelActionListener;
};

/**
 * Class to display individual bean state switches on a JMRI Switchboard
 * using 2 image files.
 */
/*public*/ class IconSwitch : public JPanel {
Q_OBJECT
    /*private*/ BufferedImage* image = nullptr;
    /*private*/ BufferedImage* image1 = nullptr;
    /*private*/ BufferedImage* image2 = nullptr;
    /*private*/ QString tag = "tag";
    /*private*/ int labelX = 16;
    /*private*/ int labelY = 53;
    BeanSwitch* bs = nullptr;

public:
    /*public*/ IconSwitch(QString filepath1, QString filepath2, BeanSwitch* bs) ;
 void paintEvent(QPaintEvent *e);

signals:
 void mouseMove(QMouseEvent* e);
 void mouseRelease(QMouseEvent* e);
 void mousePress(QMouseEvent* e);
 void mouseDoubleClick(QMouseEvent* e);

private:
 void mouseMoveEvent(QMouseEvent* e);
 void mouseReleaseEvent(QMouseEvent* event);
 void mousePressEvent(QMouseEvent* event);
 void mouseDoubleClickEvent(QMouseEvent* event);

 protected:
    /*protected*/ void setOpacity(float);
    /*protected*/ void showSwitchIcon(int stateIndex);
    /*protected*/ void setImage1(QString newImagePath);
    /*protected*/ void setLabel(QString text);
    /*protected*/ void positionLabel(int x, int y);
    /*protected*/ void paintComponent(QPainter* g) ;
 friend class BeanSwitch;
};

class OkActionListener : public ActionListener
{
 Q_OBJECT
 BeanSwitch* bs;
public:
 OkActionListener(BeanSwitch* bs) {this->bs = bs;}
public slots:
 void actionPerformed()
 {
  bs->okAddPressed();
 }
};

class CancelActionListener : public ActionListener
{
 Q_OBJECT
 BeanSwitch* bs;
public:
 CancelActionListener(BeanSwitch* bs) {this->bs = bs;}
public slots:
 void actionPerformed()
 {
  bs->cancelAddPressed();
 }
};

#endif // BEANSWITCH_H
