#ifndef SPLITBUTTONCOLORCHOOSERPANEL_H
#define SPLITBUTTONCOLORCHOOSERPANEL_H
#include "abstractcolorchooserpanel.h"

class ChangeEvent;
class ActionEvent;
class JLabel;
class JSplitButton;
class SplitButtonColorChooserPanel : public AbstractColorChooserPanel
{
 Q_OBJECT
public:
 SplitButtonColorChooserPanel(QWidget *parent = nullptr);
 /*public*/ void updateChooser();
 /*public*/ QString getDisplayName();

public slots:
 void buttonClicked(ActionEvent*);
 void splitButtonClicked(ActionEvent*e);
 void stateChanged(ChangeEvent*);

private:
 ///*private*/ JLabel* swatch = nullptr;
 /*private*/ JSplitButton* setButton = nullptr;
 /*private*/ static /*final*/ int ICON_DIMENSION;// = 20;

protected:
 /*protected*/ void buildChooser();

 friend class ColorChooserPanelTest;
};

#endif // SPLITBUTTONCOLORCHOOSERPANEL_H
