#ifndef CHANGETRACKSFRAME_H
#define CHANGETRACKSFRAME_H
#include "operationsframe.h"
#include "appslib_global.h"


namespace Operations
{
 class LocationEditFrame;
 class Location;
 class APPSLIBSHARED_EXPORT ChangeTracksFrame : public OperationsFrame
 {
  Q_OBJECT
 public:
  ChangeTracksFrame(LocationEditFrame* lef);
 public slots:
  /*public*/ void buttonActionPerformed(QWidget* ae);

 private:
  // radio buttons
  QRadioButton* spurRadioButton;// = new JRadioButton(Bundle.getMessage("Spur"));
  QRadioButton* yardRadioButton;// = new JRadioButton(Bundle.getMessage("Yard"));
  QRadioButton* interchangeRadioButton;// = new JRadioButton(Bundle.getMessage("Interchange"));
  QRadioButton* stagingRadioButton;// = new JRadioButton(Bundle.getMessage("Staging"));

  // major buttons
  QPushButton* saveButton;// = new JButton(Bundle.getMessage("Save"));

  /*private*/ LocationEditFrame* _lef;
  /*private*/ Location* _location;
   Logger* log;
   /*private*/ void changeTracks(QString type);

 };
}
#endif // CHANGETRACKSFRAME_H
