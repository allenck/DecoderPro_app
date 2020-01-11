#ifndef COLORCHOOSERPANEL_H
#define COLORCHOOSERPANEL_H
#include "abstractcolorchooserpanel.h"

class ChangeEvent;
class QColorDialog;
class PropertyChangeEvent;
class JComponent;
class QLabel;
class JTextField;
class DiagramComponent;
class ColorModel;
class ColorPanel;
class ColorChooserPanel : public AbstractColorChooserPanel
{
 Q_OBJECT
public:
 ColorChooserPanel();
 /*public*/ void setEnabled(bool enabled);
 /*public*/ void updateChooser();
 /*public*/ QString getDisplayName();
 /*public*/ int getMnemonic();
 /*public*/ int getDisplayedMnemonicIndex();
 /*public*/ QIcon getSmallDisplayIcon();
 /*public*/ QIcon getLargeDisplayIcon();
 /*public*/ void installChooserPanel(JColorChooser *enclosingChooser);
 /*public*/ QString getTitle();

public slots:
 /*public*/ void propertyChange(PropertyChangeEvent* event);
 /*public*/ void colorSelected(QColor);
 /*public*/ void stateChanged(ChangeEvent*);

private:
 /*private*/ static /*final*/ int MASK;// = 0xFF000000;
 /*private*/ /*final*/ ColorModel* model;
 /*private*/ /*final*/ ColorPanel* panel;
 /*private*/ /*final*/ DiagramComponent* slider;
 /*private*/ /*final*/ DiagramComponent* diagram;
 /*private*/ /*final*/ /*JFormattedTextField*/JTextField* text;
 /*private*/ /*final*/ QLabel* label;
 /*private*/ static void setEnabled(/*Container*/QWidget *container, bool enabled);
 /*private*/ static void setInheritsPopupMenu(JComponent* component, bool value);
 QSize sizeHint() {return QSize(100,100);}
 bool bInit = false;
 QColorDialog* dialog;

protected:
 /*protected*/ void buildChooser();

 friend class ColorChooserPanelTest;
};

#endif // COLORCHOOSERPANEL_H
