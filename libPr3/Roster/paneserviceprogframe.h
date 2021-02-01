#ifndef PANESERVICEPROGFRAME_H
#define PANESERVICEPROGFRAME_H
#include "paneprogframe.h"
#include "progservicemodecombobox.h"


class GlobalProgrammerManager;
class ProgModeSelector;
class PaneServiceProgFrame : public PaneProgFrame
{
    Q_OBJECT
public:
    //explicit PaneServiceProgFrame(QWidget *parent = 0);
    /*public*/ PaneServiceProgFrame(DecoderFile* decoderFile, RosterEntry* r, QString name, QString file, Programmer* pProg, QWidget *parent = 0);
    /*public*/ void dispose();
 /*public*/ QString getClassName();

signals:

public slots:
private:
    //ProgModeSelector*  modePane;
    Logger* log;
protected:
    /*protected*/ JPanel *getModePane() override;
 class MyProgServiceModeComboBox : public ProgServiceModeComboBox
 {
   PaneServiceProgFrame* frame;
 public:
   MyProgServiceModeComboBox(PaneServiceProgFrame* frame, QWidget* parent = 0);
  /*public*/ Programmer* getProgrammer();
 protected:
  /*protected*/ QList<GlobalProgrammerManager*> getMgrList() ;
 };
};

#endif // PANESERVICEPROGFRAME_H
