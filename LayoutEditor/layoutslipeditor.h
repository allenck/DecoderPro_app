#ifndef LAYOUTSLIPEDITOR_H
#define LAYOUTSLIPEDITOR_H
#include "layoutturnouteditor.h"
#include "layoutturnout.h"
#include "layouttrackview.h"
#include "layoutslipview.h"

class TestState;
class LayoutSlipEditor : public LayoutTurnoutEditor
{
  Q_OBJECT
 public:
  /*public*/ LayoutSlipEditor(/*@Nonnull*/ LayoutEditor* layoutEditor);
  /*public*/ void editLayoutTrack(/*@Nonnull*/LayoutTrackView* layoutTrackView) override;

  /*public*/ void toggleStateTest();

 private:
  static Logger* log;
  /*private*/ TestState* testPanel;
  // variables for Edit slip Crossing pane
  /*private*/ LayoutSlipView* layoutSlipView = nullptr;
  /*private*/ LayoutSlip* layoutSlip = nullptr;

  /*private*/ JmriJFrame* editLayoutSlipFrame = nullptr;
  /*private*/ QPushButton* editLayoutSlipBlockButton;
  /*private*/ NamedBeanComboBox/*<Turnout>*/* editLayoutSlipTurnoutAComboBox;
  /*private*/ NamedBeanComboBox/*<Turnout>*/* editLayoutSlipTurnoutBComboBox;
  /*private*/ /*final*/ JCheckBox* editLayoutSlipHiddenBox = new JCheckBox(tr("Hide Slip"));
  /*private*/ /*final*/ NamedBeanComboBox/*<Block>*/* editLayoutSlipBlockNameComboBox = new NamedBeanComboBox(
          (AbstractManager*)InstanceManager::getDefault("BlockManager"), nullptr, NamedBean::DisplayOptions::DISPLAYNAME);

  /*private*/ bool editLayoutSlipOpen = false;
  /*private*/ bool editLayoutSlipNeedsRedraw = false;
  /*private*/ bool editLayoutSlipNeedsBlockUpdate = false;
  /*private*/ int testState = LayoutTurnout::UNKNOWN;
  /*private*/ void editLayoutSlipEditBlockPressed(/*ActionEvent a*/);
  /*private*/ void editLayoutSlipDonePressed(/*ActionEvent a*/);
  /*private*/ void editLayoutSlipCancelPressed(/*ActionEvent a*/);
  /*private*/ void drawSlipState(QPainter* g2, int state);

 protected:
  /*protected*/ void drawSlipStatePart1A(QPainter* g2, int state, QPointF A, QPointF B, QPointF C, QPointF D);
  /*protected*/ void drawSlipStatePart1B(QPainter* g2, int state, QPointF A, QPointF B, QPointF C, QPointF D);
  /*protected*/ void drawSlipStatePart2A(QPainter* g2, int state, QPointF A, QPointF B, QPointF C, QPointF D);
  /*protected*/ void drawSlipStatePart2B(QPainter* g2, int state, QPointF A, QPointF B, QPointF C, QPointF D);

  friend class SampleStates;
  friend class TestState;
  friend class LSEWindowListener;
  friend class ActionListenerDone;
  friend class ActionListenerCancel;
};

class SampleStates : public JPanel {
  Q_OBJECT
  LayoutSlipEditor* editor;
 public:
    // Methods, constructors, fields.
    SampleStates(int state, LayoutSlipEditor* editor) {
        //super();
        this->state = state;
     this->editor = editor;
    }
    int state;
public:
    //@Override
    /*public*/ void paintComponent(QPainter* g) override{
        JPanel::paintComponent(g);    // paints background
//        if (g instanceof Graphics2D) {
            editor->drawSlipState( g, state);
//        }
    }
    //@Override
    /*public*/ void paintEvent(QPaintEvent *event)
    {
     QWidget::paintEvent(event);
     QPainter* painter = new QPainter(this);
     editor->drawSlipState(painter, state);
    }
};

class TestState : public JPanel {
Q_OBJECT
  LayoutSlipEditor* editor;
 public:
  TestState(LayoutSlipEditor* editor)
  {
   this->editor = editor;
  }
    //@Override
    /*public*/ void paintComponent(QPainter* g) override{
        JPanel::paintComponent(g);
//        if (g instanceof Graphics2D) {
            editor->drawSlipState( g, editor->testState);
//        }
    }
  /*public*/ void paintEvent(QPaintEvent *event)
  {
   QWidget::paintEvent(event);
   QPainter* painter = new QPainter(this);
   editor->drawSlipState(painter, editor->testState);
  }
};

class LSEWindowListener : public WindowListener
{
  Q_OBJECT
  LayoutSlipEditor* editor;
 public:
  LSEWindowListener(LayoutSlipEditor* editor) {this->editor = editor;}
  /*public*/ void windowClosing(QCloseEvent* e) {
      editor->editLayoutSlipCancelPressed();
  }

};

class ActionListenerDone : public QObject, public ActionListener
{
  Q_OBJECT
    Q_INTERFACES(ActionListener)
  LayoutSlipEditor* editor;
 public:
  ActionListenerDone(LayoutSlipEditor* editor) {this->editor = editor;}
  QObject* self() override {return (QObject*)this;}
 public slots:
  void actionPerformed(JActionEvent */*e*/ = 0) override
  {
   editor->editLayoutSlipDonePressed();
  }
};

class ActionListenerCancel : public QObject, public ActionListener
{
  Q_OBJECT
    Q_INTERFACES(ActionListener)
  LayoutSlipEditor* editor;
 public:
  ActionListenerCancel(LayoutSlipEditor* editor) {this->editor = editor;}
  QObject* self() override {return (QObject*)this;}
 public slots:
  void actionPerformed(JActionEvent */*e*/ = 0) override
  {
   editor->editLayoutSlipCancelPressed();
  }
};
#endif // LAYOUTSLIPEDITOR_H
