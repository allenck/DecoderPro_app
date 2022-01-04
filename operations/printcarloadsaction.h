#ifndef PRINTCARLOADSACTION_H
#define PRINTCARLOADSACTION_H

#include "abstractaction.h"
namespace Operations
{
 class CarManager;
 class PrintCarLoadsAction : public AbstractAction
 {
  Q_OBJECT
  public:
  /*public*/ PrintCarLoadsAction(bool preview, QWidget* pWho);

  public slots:
  /*public*/ void actionPerformed(JActionEvent* e = 0)override;

 private:
  CarManager* manager;// = CarManager.instance();
  /**
   * Variable to set whether this is to be printed or previewed
   */
  bool isPreview;
  /*private*/ static QString tabString(QString s, int fieldSize);
  friend class CarLoadPrintOption;
 };
 /*public*/ class CarLoadPrintOption : public QObject
 {
  Q_OBJECT
     static /*final*/ QString TAB;// = "\t"; // NOI18N
     static /*final*/ QString NEW_LINE;// = "\n"; // NOI18N
     PrintCarLoadsAction* parent;
 public:
     // no frame needed for now
     /*public*/ CarLoadPrintOption(PrintCarLoadsAction* parent) ;
 private:
     /*private*/ void printCars();
 };

}
#endif // PRINTCARLOADSACTION_H
