#ifndef LEVELXINGEDITOR_H
#define LEVELXINGEDITOR_H
#include "layoutturntableeditor.h"
#include "levelxingview.h"

class LevelXingView;
class LevelXing;
class LevelXingEditor : public LayoutTurntableEditor
{
  Q_OBJECT
 public:
  /*public*/ LevelXingEditor(/*@Nonnull*/ LayoutEditor* layoutEditor);
  /*public*/ void editLayoutTrack(LevelXing* levelXing);


 private:
  // variables for Edit Track Segment pane
  /*private*/ LevelXingView* levelXingView;
  /*private*/ LevelXing* levelXing;

  // variables for Edit Level Crossing pane
  /*private*/ JmriJFrame* editLevelXingFrame = nullptr;
  /*private*/ /*final*/ JCheckBox* editLevelXingHiddenCheckBox = new JCheckBox(tr("Hide Crossing"));  // NOI18N

  /*private*/ /*final*/ NamedBeanComboBox/*<Block>*/* editLevelXingBlock1NameComboBox = new NamedBeanComboBox(
          (Manager*)InstanceManager::getDefault("BlockManager"), nullptr, NamedBean::DisplayOptions::DISPLAYNAME);
  /*private*/ /*final*/ NamedBeanComboBox/*<Block>*/* editLevelXingBlock2NameComboBox = new NamedBeanComboBox(
          (Manager*)InstanceManager::getDefault("BlockManager"), nullptr, NamedBean::DisplayOptions::DISPLAYNAME);
  /*private*/ QPushButton *editLevelXingBlock1Button;
  /*private*/ QPushButton* editLevelXingBlock2Button;

  /*private*/ bool editLevelXingOpen = false;
  /*private*/ bool editLevelXingNeedsRedraw = false;
  /*private*/ bool editLevelXingNeedsBlockUpdate = false;

 private slots:
  /*private*/ void editLevelXingBlockACPressed(/*ActionEvent a*/);
  /*private*/ void editLevelXingBlockBDPressed(/*ActionEvent a*/);
  /*private*/ void editLevelXingDonePressed(/*ActionEvent a*/);
  /*private*/ void editLevelXingCancelPressed(/*ActionEvent a*/);


  friend class ELXWindowListener;
  friend class LXEeditLevelXingDonePressed;
  friend class LXEeditLevelXingCancelPressed;
};

class ELXWindowListener : public WindowListener
{
  Q_OBJECT
  LevelXingEditor* editor;
 public:
  ELXWindowListener(LevelXingEditor* editor) {this->editor = editor;}
  /*public*/ void windowClosing(QCloseEvent* e) {
      editor->editLevelXingCancelPressed();
  }

};

class LXEeditLevelXingDonePressed : public QObject, public ActionListener
{
  Q_OBJECT
    Q_INTERFACES(ActionListener)
  LevelXingEditor* editor;
 public:
  LXEeditLevelXingDonePressed(LevelXingEditor* editor) {this->editor = editor;}
  QObject* self() override {return (QObject*)this;}
public slots:
  void actionPerformed(JActionEvent */*e*/ = 0) override
  {
  editor->editLevelXingDonePressed();
 }
};

class LXEeditLevelXingCancelPressed : public QObject, public ActionListener
{
  Q_OBJECT
    Q_INTERFACES(ActionListener)
  LevelXingEditor* editor;
 public:
  LXEeditLevelXingCancelPressed(LevelXingEditor* editor) {this->editor = editor;}
  QObject* self() override {return (QObject*)this;}
public slots:
  void actionPerformed(JActionEvent */*e*/ = 0)override
  {
  editor->editLevelXingCancelPressed();
 }
};

#endif // LEVELXINGEDITOR_H
