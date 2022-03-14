#ifndef IMPORTLOGIXFRAME_H
#define IMPORTLOGIXFRAME_H

#include <jmrijframe.h>
#include <QRadioButton>
#include "jcheckbox.h"
#include "jbutton.h"

class ImportLogixFrame : public JmriJFrame
{
 public:
  ImportLogixFrame(QWidget* parent = nullptr);
  /*public*/  void initComponents()override;
  /*public*/  void initMinimumSize(QSize dimension);

 private:
  static Logger* log;
  //    /*private*/ static final int panelWidth700 = 700;
  //    /*private*/ static final int panelHeight500 = 500;

  /*private*/ QRadioButton* _whichLogix_All;
  /*private*/ QRadioButton* _whichLogix_AllActive;
  /*private*/ QRadioButton* _whichLogix_Selected;
  /*private*/ QRadioButton* _whatToDo_Nothing;
  /*private*/ QRadioButton* _whatToDo_Disable;
  /*private*/ QRadioButton* _whatToDo_Delete;
  /*private*/ JCheckBox* _includeSystemLogixs;

  /*private*/ JButton* _importLogix;
  /*private*/ JButton* _cancelDone;

  /*private*/ static /*final*/ QString SYSLOGIX;// = ((LogixManager*)InstanceManager::getDefault("LogixManager")).getSystemNamePrefix() + ":SYS";
  /*private*/ static /*final*/ QString RTXLOGIX;// = "RTX";
  /*private*/ static /*final*/ QString USSLOGIX;// = "USS CTC:OsIndicator";
  /*private*/ void doImport();

};

#endif // IMPORTLOGIXFRAME_H
