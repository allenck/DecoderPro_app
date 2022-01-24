#ifndef JTEXTPANE_H
#define JTEXTPANE_H

#include <jeditorpane.h>
#include <QObject>

class JTextPane : public JEditorPane
{
  Q_OBJECT
 public:
  JTextPane(QWidget* parent =0);
  /*public*/ void setEditable(bool b);
};

#endif // JTEXTPANE_H
