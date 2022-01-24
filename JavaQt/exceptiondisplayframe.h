#ifndef EXCEPTIONDISPLAYFRAME_H
#define EXCEPTIONDISPLAYFRAME_H

#include "jdialog.h"
#include <QObject>
#include "jpanel.h"
#include "jbutton.h"
#include "jtextarea.h"
#include "jlabel.h"
#include "exceptioncontext.h"

class ExceptionDisplayFrame : public JDialog
{
 public:
  ExceptionDisplayFrame(ExceptionContext* context, /*@CheckForNull*/ QWidget* owner = nullptr);
  ExceptionDisplayFrame(Exception* ex, /*@CheckForNull*/ QWidget* owner = nullptr);

 private:
  /*private*/  JPanel* contentPane;
  JTextArea* stackTraceTextArea;
  /*private*/  JPanel* buttonPanel;
  /*private*/  JButton* copyButton;
  /*private*/  JButton* closeButton;

  /*private*/  JLabel* stackTraceLabel;
  /*private*/  JButton* showDetailsButton;
  /*private*/  JPanel* panel;
  /*private*/  JPanel* panel_2;
  /*private*/  JLabel* lblNewLabel;
  /*private*/  JLabel* lblNewLabel_2;

  // New stuff
  /*private*/  JTextArea* operationTextArea;
  /*private*/  JTextArea* messageTextArea;
  /*private*/  JTextArea* hintTextArea;
  /*private*/  JPanel* summaryPanel;
  /*private*/  JPanel* panel_4;
  /*private*/  JLabel* lblNewLabel_3;
  /*private*/  JLabel* lblNewLabel_4;
  /*private*/  JTextArea* summaryTextArea2;

  /*private*/  JPanel* panel_5;
  /*private*/  JLabel* lblNewLabel_5;
  /*private*/  JTextArea* typeTextArea;

  /*private*/  JPanel* panel_6;
  /*private*/  JLabel* lblNewLabel_6;
  /*private*/  JTextArea* toStringTextArea;

  /*private*/  JPanel* panel_7;
  /*private*/  JLabel* lblNewLabel_7;
  /*private*/  JTextArea* causeTextArea;

  /*private*/  JPanel* detailsPanel;
  /*private*/  JLabel* lblNewLabel_1;

  /*private*/  /*final*/ /*transient*/ ExceptionContext* context;
  /*private*/  void initComponents();

};

#endif // EXCEPTIONDISPLAYFRAME_H
