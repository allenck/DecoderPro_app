#ifndef SENSORICON_H
#define SENSORICON_H
#include "positionableicon.h"
#include "namedbeanhandle.h"
#include "sensor.h"
#include <QTimer>
#include "logger.h"
#include "actionlistener.h"
#include "liblayouteditor_global.h"

class JActionEvent;
class TableItemPanel;
class NamedIcon;
class Editor;
class LIBLAYOUTEDITORSHARED_EXPORT SensorIcon : public PositionableIcon
{
    Q_OBJECT
public:
    //explicit SensorIcon(QObject *parent = 0);
    static const /*public*/ int UNKNOWN_FONT_COLOR =      0x03;
    static const /*public*/ int UNKOWN_BACKGROUND_COLOR =    0x04;
    static const /*public*/ int ACTIVE_FONT_COLOR =          0x05;
    static const /*public*/ int ACTIVE_BACKGROUND_COLOR =    0x06;
    static const /*public*/ int INACTIVE_FONT_COLOR =        0x07;
    static const /*public*/ int INACTIVE_BACKGROUND_COLOR =  0x08;
    static const /*public*/ int INCONSISTENT_FONT_COLOR =        0x0A;
    static const /*public*/ int INCONSISTENT_BACKGROUND_COLOR =  0x0B;
    /*public*/ SensorIcon(Editor* editor);
    /*public*/ SensorIcon(NamedIcon* s, Editor* editor) ;
    /*public*/ SensorIcon(QString s, Editor* editor);
    /*public*/ Positionable* deepClone() override;
    /*public*/ Positionable* finishClone(Positionable* p) override;
    /**
     * Attached a named sensor to this display item
     * @param pName System/user name to lookup the sensor object
     */
    /*public*/ void setSensor(QString pName);
    /**
     * Attached a named sensor to this display item
     * @param s the Sensor
     */
    /*public*/ void setSensor(NamedBeanHandle<Sensor*>* s);


    /**
     * Drive the current state of the display from the state of the
     * turnout.
     */
    /*public*/ void displayState(int state);
    // Original text is used when changing between icon and text, this allows for a undo when reverting back.
    QString originalText;
    /*public*/ void setOriginalText(QString s) ;
    /*public*/ QString getOriginalText();
    /*public*/ void setText(QString s);
    /*public*/ Sensor* getSensor();
    /*public*/ NamedBean* getNamedBean() override;
    /*public*/ NamedBeanHandle <Sensor*>* getNamedSensor();
    void makeIconMap();
    /**
    * Place icon by its bean state name key found in jmri.NamedBeanBundle.properties
    * That is, by its localized bean state name
    */
    /*public*/ void setIcon(QString name, NamedIcon* icon);
    /**
    * Get icon by its localized bean state name
    */
    /*public*/ NamedIcon* getIcon(QString state);
    /*public*/ NamedIcon* getIcon(int state);
    /*public*/ QString getFamily();
    /*public*/ void setFamily(QString family);
    /**
     * Get current state of attached sensor
     * @return A state variable from a Sensor, e.g. Sensor.ACTIVE
     */
    int sensorState();
    /*public*/ QString getNameString() override;
    /*public*/ bool getMomentary();

    /*public*/ bool buttonLive();
    /*public*/ void dispose() override;
    /*public*/ void setTextActive(QColor color);
    /*public*/ QColor getTextActive();
    /*public*/ void setTextInActive(QColor color);
    /*public*/ QColor getTextInActive();
    /*public*/ void setTextUnknown(QColor color);
    /*public*/ QColor getTextUnknown();
    /*public*/ void setTextInconsistent(QColor color);
    /*public*/ QColor getTextInconsistent();
    /*public*/ void setBackgroundActive(QColor color);
    /*public*/ QColor getBackgroundActive();
    /*public*/ void setBackgroundInActive(QColor color);
    /*public*/ QColor getBackgroundInActive();
    /*public*/ void setBackgroundUnknown(QColor color);
    /*public*/ QColor getBackgroundUnknown();
    /*public*/ void setBackgroundInconsistent(QColor color);
    /*public*/ QColor getBackgroundInconsistent();
    /*public*/ QString getActiveText();
    /*public*/ void setActiveText(QString i);
    /*public*/ QString getInactiveText();
    /*public*/ void setInactiveText(QString i);
    /*public*/ QString getInconsistentText();
    /*public*/ void setInconsistentText(QString i);
    /*public*/ QString getUnknownText();
    QMenu* stateMenu(const QString name, int state);
    /*public*/ void setUnknownText(QString i) ;
    //void changeLayoutSensorType();
    /*synchronized*/ /*public*/ void flashSensor(int tps, int state1, int state2);
    /*synchronized*/ /*public*/ void stopFlash();
    /*public*/ bool showPopUp(QMenu* popup) override;
    /*public*/ bool setTextEditMenu(QMenu* popup) override;
    /*public*/ void sensorTextEdit(QString name);
    /*public*/ bool setEditItemMenu(QMenu* popup) override;
    /*public*/ bool setEditIconMenu(QMenu* popup) override;
    /*public*/ bool updateScene() override;

signals:
    
public slots:
    // update icon as state of turnout changes
//    /*public*/ void propertyChange(PropertyChangeEvent* e);
    //void propertyChange(QString propertyName, int old, int now);
    void propertyChange(PropertyChangeEvent* e);

 void changeLayoutSensorType();
 /*public*/ void doMousePressed(QGraphicsSceneMouseEvent* e) override;
 /*public*/ void doMouseReleased(QGraphicsSceneMouseEvent* e) override;
 /*public*/ void doMouseClicked(QGraphicsSceneMouseEvent* e) override;
 /*public*/ void setMomentary(bool m);
 void on_editSensorItemAction_triggered();

private:
 Logger* log;
 void common();
 // the associated Sensor object
 /*private*/ NamedBeanHandle<Sensor*>* namedSensor;
 /*private*/ void setAttributes();
 bool momentary;// = false;
 // The code below here is from the layoutsensoricon.

 QColor textColorActive;// = QColor(Qt::black);
 //Color clear = new Color(238,238,238);
 QString activeText;
 QString inactiveText;
 QString inconsistentText;
 QString unknownText;
 QColor textColorInActive;// = QColor(Qt::black);
 QColor textColorUnknown;// = QColor(Qt::black);
 QColor textColorInconsistent;// = QColor(Qt::black);
 QColor backgroundColorActive = nullptr;
 QColor backgroundColorInActive = nullptr;
 QColor backgroundColorUnknown = nullptr;
 QColor backgroundColorInconsistent = nullptr;
 int flashStateOn = -1;
 int flashStateOff = -1;
 bool flashon = false;
 //ActionListener taskPerformer;
 QTimer* flashTimer = nullptr;
 Editor* editor;
 void updateSensor();
 void updateItem();
 TableItemPanel* _itemPanel = nullptr;
 bool bRightButton = false;
 int _state = 0;

private slots:
 void on_timeout();
 void on_setSensorTextAction();

protected:
 /*protected*/ QHash <QString, int>* _name2stateMap;       // name to state
 /*protected*/ QHash <int, QString>* _state2nameMap;       // state to name
 /*protected*/ QMap<QString, NamedIcon*>* cloneMap(QMap<QString, NamedIcon*>* map, SensorIcon* pos);
 /*protected*/ void editItem();
protected slots:
 /*protected*/ void edit()override;

 friend class Editor;
 friend class UpdateActionListener;
 friend class EditActionListener;

};
class UpdateActionListener : public ActionListener
{
 Q_OBJECT
 SensorIcon* parent;
public:
 UpdateActionListener(SensorIcon* parent);
 /*public*/ void actionPerformed(JActionEvent* a = 0) override;
};
class EditActionListener : public ActionListener
{
 Q_OBJECT
 SensorIcon* parent;
public:
 EditActionListener(SensorIcon* parent);
 /*public*/ void actionPerformed(JActionEvent* a = 0);
};

#endif // SENSORICON_H
