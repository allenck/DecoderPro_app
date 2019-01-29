#ifndef RPSITEMPANEL_H
#define RPSITEMPANEL_H
#include "familyitempanel.h"
#include "dragjlabel.h"

class QLabel;
class RPSItemPanel : public FamilyItemPanel
{
public:
 /*public*/ RPSItemPanel(DisplayFrame* parentFrame, QString type, QString family, Editor* editor);


private:
 static Logger* log;

protected:
 /*protected*/ void makeDndIconPanel(QMap<QString, NamedIcon *> *iconMap, QString displayKey);
 /*protected*/ DragJLabel *getDragger(DataFlavor* flavor, QMap<QString, NamedIcon*>* map, NamedIcon* icon);
 friend class RPSIconDragJLabel;
};

class RPSIconDragJLabel : public DragJLabel
{
  Q_OBJECT
  QMap<QString, NamedIcon*>* iconMap;
  RPSItemPanel* rpsItemPanel;
 public:
  /*public*/ RPSIconDragJLabel(DataFlavor* flavor, QMap<QString, NamedIcon*>* map, NamedIcon* icon, RPSItemPanel* rpsItemPanel) ;
  /*public*/ bool isDataFlavorSupported(DataFlavor* flavor);
  /*public*/ QVariant getTransferData(DataFlavor* flavor) throw (UnsupportedFlavorException, IOException);
};

#endif // RPSITEMPANEL_H
