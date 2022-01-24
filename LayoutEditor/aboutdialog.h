#ifndef ABOUTDIALOG_H
#define ABOUTDIALOG_H

#include <jdialog.h>
#include "jframe.h"

class AboutDialog : public JDialog
{
 public:
  /*public*/ AboutDialog(JFrame* frame, bool modal);


 private:
  static Logger* log;

 protected:
  /*protected*/ JPanel* namePane();
  /*protected*/ QString checkCopyright(QString name);
  /*protected*/ JPanel* infoPane();
  /*protected*/ void addCenteredComponent(JComponent* c, JPanel* p);

};

#endif // ABOUTDIALOG_H
