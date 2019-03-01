#ifndef ABSTRACTCOLORCHOOSERPANEL_H
#define ABSTRACTCOLORCHOOSERPANEL_H
#include "jpanel.h"

class PropertyChangeListener;
class ColorSelectionModel;
class JColorChooser;
class AbstractColorChooserPanel : public JPanel
{
 Q_OBJECT
public:
 AbstractColorChooserPanel(QWidget* parent = nullptr);
 /*public*/ /*abstract*/ virtual void updateChooser();
 /*public*/ /*abstract*/ virtual QString getDisplayName();
 /*public*/ int getMnemonic();
 /*public*/ int getDisplayedMnemonicIndex();
 /*public*/ /*abstract*/ virtual QIcon getSmallDisplayIcon();
 /*public*/ /*abstract*/ virtual QIcon getLargeDisplayIcon();
 /*public*/ void installChooserPanel(JColorChooser* enclosingChooser);
 /*public*/ void uninstallChooserPanel(JColorChooser* enclosingChooser);
 /*public*/ ColorSelectionModel* getColorSelectionModel();


private:
 /*private*/ /*final*/ PropertyChangeListener* enabledListener;
 /*private*/ JColorChooser* chooser;
 void setSelectedColor(QColor arg0);
 ///*public*/ void paint(Graphics g);
 int getInt(QObject* arg0, int arg1);

protected:
 /*protected*/ /*abstract*/ virtual void buildChooser();
 /*protected*/ QColor getColorFromModel();

};

#endif // ABSTRACTCOLORCHOOSERPANEL_H
