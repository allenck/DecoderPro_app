#ifndef NEWPANELEDITOR_H
#define NEWPANELEDITOR_H
#include "editor.h"

class QComboBox;
class Logger;
class QCheckBox;
class NewPanelEditor : public Editor
{
 Q_OBJECT
public:
 NewPanelEditor(QWidget* parent = nullptr);

 /*public*/ NewPanelEditor(QString name, QWidget* parent);
 /*public*/ JmriJFrame* makeFrame(QString name);
 /*public*/ void initView();
 /*public*/ void putItem(Positionable* l);
 /*public*/ void setRemoveMenu(Positionable* p, QMenu* popup);
 /*public*/ void setBackgroundMenu(QMenu* popup);

 /*public*/ void windowClosing(QCloseEvent* e);

public slots:
 void onStoreIndexItem();
 void onOpenEditor();
 void onDeletePanel();
 void onAddLoco();
 void onAddLocoRoster();
 void onRemoveMarkers();
 void onLabelAdd();
 void onRename();
 /*public*/ void mousePressed(QGraphicsSceneMouseEvent* event);
 /*public*/ void mouseReleased(QGraphicsSceneMouseEvent* event);
 /*public*/ void mouseDragged(QGraphicsSceneMouseEvent* event);
 /*public*/ void mouseMoved(QGraphicsSceneMouseEvent* event);
 /*public*/ void mouseClicked(QGraphicsSceneMouseEvent* event);
 /*public*/ void mouseEntered(QGraphicsSceneMouseEvent* event);
 /*public*/ void mouseExited(QGraphicsSceneMouseEvent* event);
 void onEdit();


 /*public*/ void itemStateChanged(/*ItemEvent e*/);


private:
  /*private*/ /*final*/ static Logger* log;// = LoggerFactory.getLogger(PanelEditor.class);

  /*private*/ /*final*/ JTextField* nextX;// = new JTextField("0", 4);
  /*private*/ /*final*/ JTextField* nextY;// = new JTextField("0", 4);

  /*private*/ /*final*/ QCheckBox* editableBox;// = new JCheckBox(tr("CheckBoxEditable"));
  /*private*/ /*final*/ QCheckBox* positionableBox;// = new JCheckBox(tr("CheckBoxPositionable"));
  /*private*/ /*final*/ QCheckBox* controllingBox;// = new JCheckBox(tr("CheckBoxControlling"));
  ///*private*/ JCheckBox showCoordinatesBox = new JCheckBox(tr("CheckBoxShowCoordinates"));
  /*private*/ /*final*/ QCheckBox* showTooltipBox;// = new JCheckBox(tr("CheckBoxShowTooltips"));
  /*private*/ /*final*/ QCheckBox* hiddenBox;// = new JCheckBox(tr("CheckBoxHidden"));
  /*private*/ /*final*/ QCheckBox* menuBox;// = new JCheckBox(tr("CheckBoxMenuBar"));
  /*private*/ /*final*/ QLabel* scrollableLabel;// = new JLabel(tr("ComboBoxScrollable"));
  /*private*/ /*final*/ QComboBox* scrollableComboBox;// = new JComboBox<>();

  /*private*/ /*final*/ QPushButton* labelAdd;// = new JButton(tr("ButtonAddText"));
  /*private*/ /*final*/ JTextField* nextLabel;// = new JTextField(10);

  /*private*/ QComboBox * _addIconBox;
 /*static*/ class ComboBoxItem {

     /*private*/ /*final*/ QString name;
     /*private*/ QString bundleName;
 protected:
     /*protected*/ ComboBoxItem(QString n);
     /*protected*/ QString getName();
 public:
     /*public*/ QString toString();
  friend class NewPanelEditor;
  friend class AddItemPopupActionListener;

 };

 /*private*/ bool delayedPopupTrigger;
 /*private*/ void amendSelectionGroup(Positionable* p);
 /*private*/ void removeMultiItems();
 /*private*/ void setMultiItemsPositionableMenu(QMenu* popup);


private slots:
 /*private*/ void hiddenCheckBoxListener();

protected:
 /*protected*/ void init(QString name);
 /*protected*/ void targetWindowClosingEvent(QCloseEvent* e);
 /*protected*/ void setNextLocation(Positionable* obj);
 /*protected*/ void showPopUp(Positionable* p, QGraphicsSceneMouseEvent* event);
 /*protected*/ void copyItem(Positionable* p);
 /*protected*/ bool addItemViaMouseClick = false;
 /*protected*/ bool pasteItemFlag = false;
 /*protected*/ QList<Positionable*>* _multiItemCopyGroup = nullptr;  // items gathered inside fence
 /*protected*/ void showAddItemPopUp(/*final*/ QGraphicsSceneMouseEvent* event, QMenu* popup);
 /*protected*/ void addItemPopUp(/*final*/ ComboBoxItem* item, QMenu* menu);
 /*protected*/ void pasteItem(QGraphicsSceneMouseEvent* e);
 /*protected*/ void pasteItemPopUp(/*final*/ QGraphicsSceneMouseEvent* event);
 /*protected*/ void backgroundPopUp(QGraphicsSceneMouseEvent* event);
 /*protected*/ void showMultiSelectPopUp(/*final*/ QGraphicsSceneMouseEvent* event, Positionable* p);

protected slots:
 void onCopy();
 friend class AddItemPopupActionListener;
};
class PEWindowListener : public WindowListener
{
 QHash<QString, JFrameItem*>* iconAdderFrames;
 NewPanelEditor* panel;
public:
 PEWindowListener(NewPanelEditor* panel);
 //@Override
 /*public*/ void windowClosing(QCloseEvent* e);
 PEWindowListener* init(QHash<QString, JFrameItem*>* f);
};
class AddItemPopupActionListener : public ActionListener
{
 Q_OBJECT
 ///*final*/ QString desiredName = name;
 NewPanelEditor* panel;
 NewPanelEditor::ComboBoxItem* selected;
public:
 AddItemPopupActionListener(NewPanelEditor* panel) { this->panel = panel;}
public slots:
 /*public*/ void actionPerformed(ActionEvent* e = nullptr) {
     panel->addItemViaMouseClick = true;
     panel->getIconFrame(selected->getName());
 }

 AddItemPopupActionListener* init(NewPanelEditor::ComboBoxItem* i) {
  selected = i;
  return this;
 }

};
#endif // NEWPANELEDITOR_H
