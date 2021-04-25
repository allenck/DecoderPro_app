#ifndef SWITCHBOARDEDITOR_H
#define SWITCHBOARDEDITOR_H
#include "editor.h"
#include "jpanel.h"
#include "jspinner.h"
#include "jbutton.h"
#include "jtextarea.h"

class NamedBeanHandleManager;
class BeanSwitch;
class QGroupBox;
class JTextArea;
class QComboBox;
class QCheckBox;
class JLabel;
class SwitchboardEditor : public Editor
{
 Q_OBJECT
public:
 SwitchboardEditor(QWidget* parent = nullptr);
 ~SwitchboardEditor();
 /*public*/ SwitchboardEditor(QString name, QWidget* parent = nullptr);


 /*public*/ QString getSwitchType();
 /*public*/ QString getSwitchTypeName();
 /*public*/ void setSwitchType(QString prefix);
 /*public*/ QString getSwitchManu();
 /*public*/ void setSwitchManu(QString manuPrefix);
 /*public*/ QString getSwitchShape();
 /*public*/ void setSwitchShape(QString switchShape);
 /*public*/ void setBoardToolTip(QString tip);
 /*public*/ int getColumns();
 /*public*/ void setColumns(int cols);
 /*public*/ void loadComplete();
 /*public*/ void initView();
 /*public*/ JmriJFrame* makeFrame(QString name);
 /*public*/ QList<BeanSwitch*> getSwitches();
 /*public*/ void setNextLocation(Positionable* obj);
 /*public*/ void setDefaultTextColor(QString color);
 /*public*/ QString getDefaultTextColor();
 /*public*/ QColor getDefaultTextColorAsColor();
 /*public*/ void setDefaultBackgroundColor(QColor color);
 /*public*/ QColor getDefaultBackgroundColor();
 /*public*/ void setAllEditable(bool edit);
 /*public*/ void setUseGlobalFlag(bool set);
 /*public*/ void setTitle();
 /*public*/ void setHideUnconnected(bool state);
 /*public*/ bool getHideUnconnected();
 /*public*/ void resetDirty();
 /*public*/ void setDirty(bool val);
 /*public*/ void setDirty();
 /*public*/ bool isDirty();
 /*public*/ void setPanelMenuRangeMin(int rangemin);
 /*public*/ void setPanelMenuRangeMax(int rangemax);
 /*public*/ int getPanelMenuRangeMin();
 /*public*/ int getPanelMenuRangeMax();
 /*public*/ void setScroll(int state);
 /*public*/ void setScroll(QString strState);
 /*public*/ void keyPressEvent(QKeyEvent *event);
// /*public*/ void windowClosing(QCloseEvent* e);
// /*public*/ void showEvent(QShowEvent *event);
 /*public*/ QString getClassName();
 /*public*/ QList<NamedBeanUsageReport*> getUsageReport(NamedBean* bean);
 /*public*/ int getTileSize(); //tmp synchronized

public slots:
 /*public*/ void updatePressed();
 void onOpenEditor();
 void onUpdateButton();
 void onAddAction();
 void onHideConnectedBox();

private:
 void common();
 /*private*/ /*final*/ static Logger* log;// = LoggerFactory::getLogger("SwitchboardEditor");
 /*private*/ QMenu* _editorMenu;
 /*private*/ QList<Positionable*> _secondSelectionGroup;
 /*private*/ bool panelChanged;// = false;
 /*private*/ JPanel* navBarPanel;// = nullptr;
 QVBoxLayout* thisLayout;
 // Switchboard items
 ImageIcon* iconPrev;// = new ImageIcon(":resources/icons/misc/gui3/LafLeftArrow_m.gif");
 /*private*/ /*final*/ JLabel* prev;// = new JLabel(iconPrev);
 ImageIcon* iconNext = new ImageIcon(":resources/icons/misc/gui3/LafRightArrow_m.gif");
 /*private*/ /*final*/ JLabel* next;// = new QLabel(iconNext);
 /*private*/ int rangeMin;// = 1;
 /*private*/ int rangeMax;// = 24;
 /*private*/ int _range;// = rangeMax - rangeMin;
 /*private*/ /*final*/ QSpinBox* minSpinner;// = new QSpinBox(new SpinnerNumberModel(rangeMin, rangeMin, rangeMax, 1));
 /*private*/ /*final*/ QSpinBox* maxSpinner;// = new QSpinBox(new SpinnerNumberModel(rangeMax, rangeMin, rangeMax, 1));
 /*private*/ /*final*/ QCheckBox* hideUnconnected;// = new JCheckBox(tr("CheckBoxHideUnconnected"));
 /*private*/ TargetPane* switchboardLayeredPane; // JLayeredPane
 static /*final*/ QString TURNOUT;// = tr("BeanNameTurnout");
 static /*final*/ QString SENSOR;// = tr("BeanNameSensor");
 static /*final*/ QString LIGHT;// = tr("BeanNameLight");
 /*private*/ /*final*/ QStringList beanTypeStrings;// = {TURNOUT, SENSOR, LIGHT};
 /*private*/ QComboBox* beanTypeList;
 /*private*/ QChar beanTypeChar;
 QSpinBox* columns;// = new QSpinBox(new SpinnerNumberModel(8, 1, 16, 1));
 /*private*/ /*final*/ QStringList switchShapeStrings;// = {
//     tr("Buttons"),
//     tr("Sliders"),
//     tr("Keys"),
//     tr("Symbols")
// };
 int currRow, currCol;

 /*private*/ QComboBox* switchShapeList;
 /*private*/ /*final*/ QStringList beanManuPrefixes;//= new ArrayList<>();
 /*private*/ QComboBox* beanManuNames;
 /*private*/ QGroupBox* border;
 /*private*/ /*final*/ QString interact;// = tr("SwitchboardInteractHint");
 /*private*/ /*final*/ QString noInteract;// = tr("SwitchboardNoInteractHint");


 /*private*/ QString typePrefix;
 /*private*/ QString type;

 // editor items (adapted from LayoutEditor toolbar)
 /*private*/ QWidget* editToolBarPanel;// = null;
 /*private*/ QScrollArea* editToolBarScroll;// = null;
 /*private*/ QWidget* editorContainer;// = null;
 /*private*/ QColor defaultTextColor;// = QColor(Qt::black);
 /*private*/ bool _hideUnconnected = false;
 /*private*/ bool _autoItemRange = true;
 /*private*/ int rows = 4; // matches initial autoRows pref for default pane size
 /*private*/ /*final*/ float cellProportion = 1.0f; // TODO analyse actual W:H per switch type/shape: worthwhile?
 /*private*/ int _tileSize = 100;
 /*private*/ int _iconSquare = 75;
 /*private*/ /*final*/ JSpinner* rowsSpinner = new JSpinner(new SpinnerNumberModel(rows, 1, 25, 1));
 /*private*/ /*final*/ JButton* updateButton = new JButton(tr("Update"));
 // number of rows displayed on switchboard, disabled when autoRows is on
 /*private*/ /*final*/ JTextArea* help2 = new JTextArea(tr("Greyed out buttons are not connected to layout."));
 /*private*/ /*final*/ JTextArea* help3 = new JTextArea(tr("Empty Switchboard (uncheck [%1] to fix).").arg(tr("Hide unconnected switches")));
 // saved state of options when panel was loaded or created
 /*private*/ /*transient*/ bool savedEditMode = true;
 /*private*/ /*transient*/ bool savedControlLayout = true; // menu option to turn this off
 /*private*/ int height = 100;
 /*private*/ /*final*/ int width = 100;
 /*private*/ /*final*/ QAction* controllingBox;// = new JCheckBoxMenuItem(tr("CheckBoxControlling"));
 /*private*/ /*final*/ QAction* hideUnconnectedBox;// = new JCheckBoxMenuItem(Bundle.getMessage("CheckBoxHideUnconnected"));
 /*private*/ /*final*/ QAction*  showToolTipBox;// = new JCheckBoxMenuItem(tr("CheckBoxShowTooltips"));
 /*private*/ /*final*/ QAction* scrollBoth;// = new JRadioButtonMenuItem(tr("ScrollBoth"));
 /*private*/ /*final*/ QAction* scrollNone;// = new JRadioButtonMenuItem(tr("ScrollNone"));
 /*private*/ /*final*/ QAction* scrollHorizontal;// = new JRadioButtonMenuItem(tr("ScrollHorizontal"));
 /*private*/ /*final*/ QAction* scrollVertical;// = new JRadioButtonMenuItem(tr("ScrollVertical"));

 // Action commands
 /*private*/ static QString LAYER_COMMAND;// = "layer";
 /*private*/ static QString MANU_COMMAND;// = "manufacturer";
 /*private*/ static QString SWITCHTYPE_COMMAND;// = "switchshape";
 /*private*/ void makeFileMenu();
 /**
  * List of names/labels of all switches currently displayed. Refreshed
  * during {@link #updatePressed()}
  */
 /*private*/ /*final*/ QStringList switchlist;// = new ArrayList<>();
 /*private*/ void addSwitchRange(int rangeMin, int rangeMax, int beanType, QString manuPrefix, int switchShape) ;
 /*private*/ QGroupBox* createControlPanel();
 /*private*/ void setupEditorPane();
 QGridLayout* switchboardLayeredPaneLayout;
 QScrollArea* scrollArea;
 QMenu* editMenu;

private slots:
 void onControllingBox();
 void onHideUnconnected(bool bChecked);
 void onHideUnConnectedBox(bool bChecked);
 void onStoreIndexItem();
 void onShowToolTipBox();
 void onBackground();
 void onTextColor();
 void onDeleteItem();
 void onEditItem();
 void onCloseEditor();

protected:
 /*protected*/ void init(QString name);
 /*protected*/ QMenuBar* _menuBar;
 /*protected*/ QMenu* _editMenu;
 /*protected*/ QMenu* _fileMenu;
 /*protected*/ QMenu* _optionMenu;
 /*protected*/ Manager* getManager(QChar typeChar);
 /*protected*/ void makeOptionMenu();
 /**
  * List with copies of BeanSwitch objects currently displayed to display on
  * Web Server. Created by {@link #getSwitches()}
  */
 /*protected*/ QList<BeanSwitch*> _switches;// = new ArrayList<>();
 /*protected*/ void setSecondSelectionGroup(QList<Positionable*> list);
 /*protected*/ BeanSwitch* getSwitch(QString sName);
 /*protected*/ void copyItem(Positionable* p);
 /*protected*/ void showPopUp(Positionable* p, QMouseEvent* event);
 /*protected*/ QList<Positionable*>* getSelectionGroup();
 /*protected*/ void targetWindowClosingEvent(QCloseEvent* e);

 friend class BeanSwitch;
 friend class SwitchboardEditorXml;
};

#endif // SWITCHBOARDEDITOR_H
