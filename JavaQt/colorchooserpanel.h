#ifndef COLORCHOOSERPANEL_H
#define COLORCHOOSERPANEL_H
#include "abstractcolorchooserpanel.h"

class PropertyChangeEvent;
class JComponent;
class JLabel;
class JTextField;
class DiagramComponent;
class ColorModel;
class ColorPanel;
class ColorChooserPanel : public AbstractColorChooserPanel
{
 Q_OBJECT
public:
 ColorChooserPanel(ColorModel* model);
 /*public*/ void setEnabled(bool enabled);
 /*public*/ void updateChooser();
 /*public*/ QString getDisplayName();
 /*public*/ int getMnemonic();
 /*public*/ int getDisplayedMnemonicIndex();
 /*public*/ QIcon getSmallDisplayIcon();
 /*public*/ QIcon getLargeDisplayIcon();

public slots:
 /*public*/ void propertyChange(PropertyChangeEvent* event);

private:
 /*private*/ static /*final*/ int MASK;// = 0xFF000000;
 /*private*/ /*final*/ ColorModel* model;
 /*private*/ /*final*/ ColorPanel* panel;
 /*private*/ /*final*/ DiagramComponent* slider;
 /*private*/ /*final*/ DiagramComponent* diagram;
 /*private*/ /*final*/ /*JFormattedTextField*/JTextField* text;
 /*private*/ /*final*/ JLabel* label;
 /*private*/ static void setEnabled(/*Container*/QWidget *container, bool enabled);
 /*private*/ static void setInheritsPopupMenu(JComponent* component, bool value);
 QSize sizeHint() {return QSize(100,100);}

protected:
 /*protected*/ void buildChooser();

 friend class ColorChooserPanelTest;
};

#endif // COLORCHOOSERPANEL_H
