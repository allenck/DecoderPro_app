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
 /*public*/ void setColorTransparencySelectionEnabled(bool b);
 /*public*/ bool isColorTransparencySelectionEnabled();
 /*public*/ QString toString();

private:
 /*private*/ /*final*/ PropertyChangeListener* enabledListener = nullptr;
 /*private*/ JColorChooser* chooser = nullptr;
 void setSelectedColor(QColor color);
 ///*public*/ void paint(Graphics g);
 int getInt(QVariant key, int defaultValue);

protected:
 /*protected*/ /*abstract*/ virtual void buildChooser();
 /*protected*/ QColor getColorFromModel();

 friend class SwatchPanel;
 friend class JColorChooser;
};

#endif // ABSTRACTCOLORCHOOSERPANEL_H
