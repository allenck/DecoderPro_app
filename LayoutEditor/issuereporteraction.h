#ifndef ISSUEREPORTERACTION_H
#define ISSUEREPORTERACTION_H

#include <abstractaction.h>

class IssueReporterAction : public AbstractAction
{
 public:
  explicit IssueReporterAction(QWidget *parent = nullptr);
  /*public*/ void actionPerformed(JActionEvent* e = 0);
};

#endif // ISSUEREPORTERACTION_H
