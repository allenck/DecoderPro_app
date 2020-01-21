#ifndef SETUPEXCELPROGRAMMANIFESTFRAME_H
#define SETUPEXCELPROGRAMMANIFESTFRAME_H
#include "setupexcelprogramframe.h"

namespace Operations
{
 class SetupExcelProgramManifestFrame : public SetupExcelProgramFrame
 {
 public:
  SetupExcelProgramManifestFrame(QWidget* parent = 0);
  /*public*/ void initComponents();
  /*public*/ QString getClassName();

 public slots:
  /*public*/ void buttonActionPerformed(QWidget* ae);
private:
  /*private*/ /*final*/ static Logger* log;// = LoggerFactory::getLogger("SetupExcelProgramManifestFrame");
 };
}
#endif // SETUPEXCELPROGRAMMANIFESTFRAME_H
