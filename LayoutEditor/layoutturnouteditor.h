#ifndef LAYOUTTURNOUTEDITOR_H
#define LAYOUTTURNOUTEDITOR_H
#include "layouttrackeditor.h"
#include "jcheckbox.h"
#include "jcombobox.h"
#include "instancemanager.h"
#include "windowlistener.h"
#include "actionlistener.h"
#include "layouttrackview.h"
#include "layoutturnoutview.h"

class LayoutTurnoutEditor : public LayoutTrackEditor
{
  Q_OBJECT
 public:
  /*public*/ LayoutTurnoutEditor(/*@Nonnull*/ LayoutEditor* layoutEditor);
  /*public*/ void editLayoutTrack(/*@Nonnull*/ LayoutTrackView* layoutTrack) override;


 private:
  static Logger* log;
  /*private*/ void editLayoutTurnoutEditBlockPressed(/*ActionEvent a*/);
  /*private*/ void editLayoutTurnoutDonePressed(/*ActionEvent a*/);
  /*private*/ void editLayoutTurnoutCancelPressed(/*ActionEvent* a*/);

 protected:
  /*protected*/ LayoutTurnoutView* layoutTurnoutView = nullptr;
  /*protected*/ LayoutTurnout* layoutTurnout = nullptr;

  /*protected*/ JmriJFrame* editLayoutTurnoutFrame = nullptr;
  /*protected*/ NamedBeanComboBox/*<Turnout>*/* editLayoutTurnout1stTurnoutComboBox = nullptr;
  /*protected*/ NamedBeanComboBox/*<Turnout>*/* editLayoutTurnout2ndTurnoutComboBox = nullptr;
  /*protected*/ JLabel* editLayoutTurnout2ndTurnoutLabel = nullptr;
  /*protected*/ /*final*/ NamedBeanComboBox/*<Block>*/* editLayoutTurnoutBlockNameComboBox = new NamedBeanComboBox(
          (Manager*)InstanceManager::getDefault("BlockManager"), nullptr, NamedBean::DisplayOptions::DISPLAYNAME);
  /*protected*/ /*final*/ NamedBeanComboBox/*<Block>*/* editLayoutTurnoutBlockBNameComboBox = new NamedBeanComboBox(
          (Manager*)InstanceManager::getDefault("BlockManager"), nullptr, NamedBean::DisplayOptions::DISPLAYNAME);
  /*protected*/ /*final*/ NamedBeanComboBox/*<Block>*/* editLayoutTurnoutBlockCNameComboBox = new NamedBeanComboBox(
          (Manager*)InstanceManager::getDefault("BlockManager"), nullptr, NamedBean::DisplayOptions::DISPLAYNAME);
  /*protected*/ /*final*/ NamedBeanComboBox/*<Block>*/* editLayoutTurnoutBlockDNameComboBox = new NamedBeanComboBox(
          (Manager*)InstanceManager::getDefault("BlockManager"), nullptr, NamedBean::DisplayOptions::DISPLAYNAME);
  /*protected*/ /*final*/ JComboBox/*<String>*/* editLayoutTurnoutStateComboBox = new JComboBox();
  /*protected*/ JCheckBox* editLayoutTurnoutHiddenCheckBox = nullptr;
  /*protected*/ QPushButton* editLayoutTurnoutBlockButton;
  /*protected*/ QPushButton* editLayoutTurnoutBlockBButton;
  /*protected*/ QPushButton* editLayoutTurnoutBlockCButton;
  /*protected*/ QPushButton* editLayoutTurnoutBlockDButton;
  /*protected*/ /*final*/ QCheckBox* editLayoutTurnout2ndTurnoutCheckBox = new QCheckBox(tr("Use Two Physical Addresses"));  // NOI18N
  /*protected*/ /*final*/ QCheckBox* editLayoutTurnout2ndTurnoutInvertCheckBox = new QCheckBox(tr("Invert Second Turnout"));  // NOI18N

  /*protected*/ bool editLayoutTurnoutOpen = false;
  /*protected*/ bool editLayoutTurnoutNeedRedraw = false;
  /*protected*/ bool editLayoutTurnoutNeedsBlockUpdate = false;
  /*protected*/ int editLayoutTurnoutClosedIndex;
  /*protected*/ int editLayoutTurnoutThrownIndex;
  /*protected*/ virtual void extendAddContinuingStateChoice(QWidget* contentPane);
  /*protected*/ virtual void extendBlockBCDSetup(QWidget* contentPane);
  /*protected*/ virtual void configureCheckBoxes(BlockManager* bm);
  /*protected*/ virtual void setUpForEdit();
  /*protected*/ virtual void setUpContinuingSense();
  /*protected*/ virtual void editLayoutTurnoutEditBlockBPressed(/*ActionEvent a*/);
  /*protected*/ virtual void editLayoutTurnoutEditBlockCPressed(/*ActionEvent a*/);
  /*protected*/ virtual void editLayoutTurnoutEditBlockDPressed(/*ActionEvent a*/);
  /*protected*/ virtual void donePressedSecondTurnoutName(QString newName);
  /*protected*/ virtual void setContinuingRouteTurnoutState();
  /*protected*/ virtual void checkBlock234Changed();

  friend class ELTWindowListener;
  friend class ELT_editLayoutTurnoutDonePressed;
  friend class ELT_editLayoutTurnoutCancelPressed;
};

class ELTWindowListener : public WindowListener
{
  Q_OBJECT
  LayoutTurnoutEditor* editor;
 public:
  ELTWindowListener(LayoutTurnoutEditor* editor) {this->editor = editor;}
  /*public*/ void windowClosing(QCloseEvent* e) {
      editor->editLayoutTurnoutCancelPressed();
  }
};

class ELT_editLayoutTurnoutDonePressed : public QObject, public ActionListener
{
 Q_OBJECT
    Q_INTERFACES(ActionListener)
  LayoutTurnoutEditor* editor;
 public:
  ELT_editLayoutTurnoutDonePressed(LayoutTurnoutEditor* editor) {this->editor = editor;}
  QObject* self() override {return (QObject*)this;}
 public slots:
  void actionPerformed(JActionEvent */*e*/ = 0)override
  {
   editor->editLayoutTurnoutDonePressed();
  }
};

class ELT_editLayoutTurnoutCancelPressed : public QObject, public ActionListener
{
  Q_OBJECT
    Q_INTERFACES(ActionListener)
  LayoutTurnoutEditor* editor;
 public:
  ELT_editLayoutTurnoutCancelPressed(LayoutTurnoutEditor* editor) {this->editor = editor;}
  QObject* self() override {return (QObject*)this;}
 public slots:
  void actionPerformed(JActionEvent */*e*/ = 0) override
  {
   editor->editLayoutTurnoutCancelPressed();
  }
};

#endif // LAYOUTTURNOUTEDITOR_H
