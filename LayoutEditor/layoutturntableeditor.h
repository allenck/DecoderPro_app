#ifndef LAYOUTTURNTABLEEDITOR_H
#define LAYOUTTURNTABLEEDITOR_H
#include "layouttrackeditor.h"
#include "jcheckbox.h"
#include "jtextfield.h"
#include "titledborder.h"
#include "jmrijframe.h"
#include "turnout.h"
#include "instancemanager.h"
#include "decimalformat.h"
#include "actionlistener.h"
#include "windowlistener.h"
#include <QPushButton>
#include <QScrollArea>

class RayTrack;
class LayoutTurntable;
class LevelXing;
class LayoutTurntableEditor : public LayoutTrackEditor
{
  Q_OBJECT
 public:
  /*public*/ LayoutTurntableEditor(/*@Nonnull*/ LayoutEditor* layoutEditor);
  /*public*/ void editLayoutTrack(/*@Nonnull*/ LayoutTrackView* layoutTrack) override;

 private:
  static Logger* log;
  // variables for Edit Turntable pane
  /*private*/ LayoutTurntable* layoutTurntable = nullptr;

  /*private*/ JmriJFrame* editLayoutTurntableFrame = nullptr;
  /*private*/ /*final*/ JTextField* editLayoutTurntableRadiusTextField = new JTextField(8);
  /*private*/ /*final*/ JTextField* editLayoutTurntableAngleTextField = new JTextField(8);
  /*private*/ /*final*/ NamedBeanComboBox/*<Block>*/* editLayoutTurntableBlockNameComboBox = new NamedBeanComboBox(
           (BlockManager*)InstanceManager::getDefault("BlockManager"), nullptr, NamedBean::DisplayOptions::DISPLAYNAME);
  /*private*/ QPushButton* editLayoutTurntableSegmentEditBlockButton;

  /*private*/ JPanel* editLayoutTurntableRayPanel;
  /*private*/ QPushButton* editLayoutTurntableAddRayTrackButton;
  /*private*/ JCheckBox* editLayoutTurntableDccControlledCheckBox;

  /*private*/ QString editLayoutTurntableOldRadius = "";
  /*private*/ bool editLayoutTurntableOpen = false;
  /*private*/ bool editLayoutTurntableNeedsRedraw = false;

  /*private*/ /*final*/ QList<Turnout*> turntableTurnouts = QList<Turnout*>();
  /*private*/ void updateRayPanel();
  /*private*/ void saveRayPanelDetail();

 private slots:
  /*private*/ void editLayoutTurntableEditBlockPressed(/*ActionEvent a*/);
  /*private*/ void addRayTrackPressed(/*ActionEvent a*/);
  /*private*/ void editLayoutTurntableDonePressed(/*ActionEvent a*/);
  /*private*/ void turntableEditCancelPressed(/*ActionEvent a*/);

  friend class ELTTFWindowListener;
  friend class LTTE_editLayoutTurntableDonePressed;
  friend class LTTE_turntableEditCancelPressed;
  friend class TurntableRayPanel;
};

class ELTTFWindowListener : public WindowListener
{
  Q_OBJECT
  LayoutTurntableEditor* editor;
 public:
  ELTTFWindowListener(LayoutTurntableEditor* editor) {this->editor = editor;}
  /*public*/ void windowClosing(QCloseEvent* e) override {
      editor->turntableEditCancelPressed();
  }

};

/*public*/ class TurntableRayPanel : public JPanel {
 Q_OBJECT
  LayoutTurntableEditor* editor;
    // variables for Edit Turntable ray pane
    /*private*/ RayTrack* rayTrack = nullptr;
    /*private*/ /*final*/ JPanel* rayTurnoutPanel;
    /*private*/ /*final*/ NamedBeanComboBox/*<Turnout>*/* turnoutNameComboBox;
    /*private*/ /*final*/ TitledBorder* rayTitledBorder;
    /*private*/ /*final*/ JComboBox/*<String>*/* rayTurnoutStateComboBox;
    /*private*/ /*final*/ JLabel* rayTurnoutStateLabel;
    /*private*/ /*final*/ JTextField* rayAngleTextField;
    /*private*/ /*final*/ QVector<int> rayTurnoutStateValues = QVector<int>{Turnout::CLOSED, Turnout::THROWN};
    /*private*/ /*final*/ DecimalFormat* twoDForm = new DecimalFormat("#.00");
public:
    /**
     * constructor method.
     * @param rayTrack the single ray track to edit.
     */
    /*public*/ TurntableRayPanel(/*@Nonnull*/ RayTrack* rayTrack, LayoutTurntableEditor* editor);
 private:
    /*private*/ void _delete();
    /*private*/ void updateDetails();
    /*private*/ void showTurnoutDetails();
  friend class LayoutTurntableEditor;
};

class LTTE_editLayoutTurntableDonePressed : public QObject, public ActionListener
{
  Q_OBJECT
    Q_INTERFACES(ActionListener)
  LayoutTurntableEditor* editor;
public:
  LTTE_editLayoutTurntableDonePressed(LayoutTurntableEditor* editor) {this->editor = editor;}
  void actionPerformed(JActionEvent */*e*/ = 0) override
  {
   editor->editLayoutTurntableDonePressed();
  }
};

class LTTE_turntableEditCancelPressed : public QObject, public ActionListener
{
  Q_OBJECT
    Q_INTERFACES(ActionListener)
  LayoutTurntableEditor* editor;
public:
  LTTE_turntableEditCancelPressed(LayoutTurntableEditor* editor) {this->editor = editor;}
  void actionPerformed(JActionEvent */*e*/ = 0)override
  {
   editor->turntableEditCancelPressed();
  }
};
#endif // LAYOUTTURNTABLEEDITOR_H
