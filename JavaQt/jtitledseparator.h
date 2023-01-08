#ifndef JTITLEDSEPARATOR_H
#define JTITLEDSEPARATOR_H

#include "jpanel.h"
#include "gridbaglayout.h"
#include "jseparator.h"
#include "jlabel.h"

class JTitledSeparator : public JPanel
{
 public:
  JTitledSeparator(QString title, QWidget* parent = nullptr);
  /*public*/  QString getTitle();
  /*public*/  void setTitle(QString title);

 private:
  /*private*/ /*final*/ /*static*/ class SeparatorPane : JPanel {

      /*private*/ SeparatorPane() : JPanel(new GridBagLayout, nullptr) {
          //super(new GridBagLayout());
          setOpaque(false);
//          setDoubleBuffered(false);
          ((GridBagLayout*)layout())->addWidget(new JSeparator(), GridBagConstraints(0, 0, 1, 1, 1, 0, GridBagConstraints::CENTER, GridBagConstraints::HORIZONTAL, new Insets(0, 0, 0, 0), 0, 0));
      }
public:
      //@Override
      /*public*/  void setBounds(int x, int y, int w, int h) {
//          JPanel::setBounds(x, y, w, h);
//          doLayout();
      }
    friend class JTitledSeparator;
  };
 private:
  /*private*/ /*final*/ JLabel* label = new JLabel();
    /*private*/ void adjustLook();

};

#endif // JTITLEDSEPARATOR_H
