#ifndef TRISTATEJCHECKBOX_H
#define TRISTATEJCHECKBOX_H

#include "jcheckbox.h"
#include "actionevent.h"

class TriStateModel;
class Logger;
class TriStateJCheckBox : public JCheckBox
{
 public:
  /**
   * Enum of TriStateJCheckBox state values.
   */
  /*public*/ /*static*/ enum State {
      CHECKED, UNCHECKED, PARTIAL
  };
  TriStateJCheckBox();
  /*public*/ TriStateJCheckBox (QString text);
  /*public*/ void setState(/*@Nonnull*/ State state);
  /*public*/ void setState(QVector<bool> booleanArray);
  /*public*/ State getState();
  /*public*/ void setSelected(bool selected) override;
  /*public*/ int getIconWidth() /*override*/;
  /*public*/ int getIconHeight() /*override*/;
  /*public*/ void paintIcon(QWidget* c, QPainter &g, int x, int y);

 private:
  static Logger* log;
  /*private*/ void initProperties();
  /*private*/ bool arrayDoesNotContainsTrueOrFalse(QVector<bool> booleanArray, bool condition);
  /*private*/ /*final*/ static QIcon icon;// = QIcon();//UIManager.getIcon("CheckBox.icon");
  TriStateModel* model = nullptr;
  void setModel(TriStateModel* model){this->model = model;}
  bool _rolloverEnabled = false;
  void setRolloverEnabled(bool b){_rolloverEnabled = b;}
  bool _opaque = false;
  void setOpaque(bool b) {this->_opaque = b;}
  void paintEvent(QPaintEvent* event) override;

};

/*private*/ /*static*/ class TriStateModel : public QObject //extends JToggleButton.ToggleButtonModel {
{
  Q_OBJECT

 protected:
    /*protected*/ TriStateJCheckBox::State state;
 public:
    /*public*/ TriStateModel(TriStateJCheckBox::State state) {
        this->state = state;
    }

    /**
     * {@inheritDoc}
     */
    //@Override
    /*public*/ bool isSelected() {
        return state == TriStateJCheckBox::State::CHECKED;
    }

    /*public*/ TriStateJCheckBox::State getState() {
        return state;
    }

    /*public*/ void setState(TriStateJCheckBox::State state) {
        this->state = state;
        //fireStateChanged();
   emit stateChanged();
    }

    /**
     * {@inheritDoc}
     */
    //@Override
    /*public*/ void setPressed(bool pressed) {
        if (pressed) {
            state = ( state==TriStateJCheckBox::State::UNCHECKED ? TriStateJCheckBox::State::CHECKED : TriStateJCheckBox::State::UNCHECKED );
            //fireStateChanged();
            emit stateChanged();
//            fireActionPerformed(
//                new ActionEvent(this, ActionEvent.ACTION_PERFORMED,getActionCommand()));
            emit actionPerformed(new JActionEvent(this, JActionEvent::ACTION_PERFORMED,/*getActionCommand()*/""));
        }
    }

    /**
     * {@inheritDoc}
     */
    //@Override
    /*public*/ void setSelected(bool selected) {
        this->state = ( selected ? TriStateJCheckBox::State::CHECKED : TriStateJCheckBox::State::UNCHECKED );
    }
 signals:
  void stateChanged();
  void actionPerformed(JActionEvent*);
};

#endif // TRISTATEJCHECKBOX_H
