#ifndef CONVERTDIALOG_H
#define CONVERTDIALOG_H
#include "jdialog.h"
#include "indicatortoitempanel.h"
#include "indicatoritempanel.h"

class Positionable;
class CircuitBuilder;
class PositionableLabel;
class OBlock;
class FamilyItemPanel;
class DisplayFrame;
class ConvertDialog : public JDialog
{
 Q_OBJECT
public:
 ConvertDialog(CircuitBuilder* cb, PositionableLabel* pos, OBlock* block, QWidget *parent = nullptr);

private:
 /*private*/ CircuitBuilder* _parent;
 /*private*/ PositionableLabel* _pos;
 FamilyItemPanel* _panel;
 DisplayFrame* _filler;
 /*private*/ void displayIcons();
 /*private*/ void convertTO(OBlock* block);
 /*private*/ void convertSeg(OBlock* block);
 /*private*/ void finishConvert(Positionable* pos, OBlock* block);

 friend class CDIndicatorTOItemPanel;
 friend class CDIndicatorItemPanel;
};

class CDIndicatorTOItemPanel : public IndicatorTOItemPanel
{
 Q_OBJECT
 ConvertDialog* cd;
public:
 CDIndicatorTOItemPanel(DisplayFrame* parentFrame, QString type, QString family, PickListModel* model, Editor* editor, ConvertDialog* cd)
  : IndicatorTOItemPanel(parentFrame, type, family, model, editor, cd)
 {this->cd = cd;}
protected:
    //@Override
    /*protected*/ void showIcons() {
         IndicatorTOItemPanel::showIcons();
         cd->displayIcons();
    }
    //@Override
    /*protected*/ void hideIcons() {
        IndicatorTOItemPanel::hideIcons();
        cd->displayIcons();
    }
};

class CDIndicatorItemPanel : public IndicatorItemPanel
{
 Q_OBJECT
 ConvertDialog* cd;
public:
 CDIndicatorItemPanel(DisplayFrame* parentFrame, QString type, QString family, Editor* editor, ConvertDialog* cd)
  : IndicatorItemPanel(parentFrame, type, family,editor, cd)
 {
  this->cd = cd;
 }
protected:
 //@Override
 /*protected*/ void showIcons() {
     IndicatorItemPanel::showIcons();
     cd->displayIcons();
 }
 //@Override
 /*protected*/ void hideIcons() {
     IndicatorItemPanel::hideIcons();
     cd->displayIcons();
 }
};

#endif // CONVERTDIALOG_H
