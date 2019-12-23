#ifndef DEFAULTSWATCHCHOOSERPANEL_H
#define DEFAULTSWATCHCHOOSERPANEL_H
#include "abstractcolorchooserpanel.h"

class SwatchPanel;
class RecentSwatchPanel;
class MouseListener;
class KeyListener;
class DefaultSwatchChooserPanel : public AbstractColorChooserPanel
{
 Q_OBJECT
public:
 DefaultSwatchChooserPanel();
 /*public*/ QString getDisplayName();
 /*public*/ int getMnemonic();
 /*public*/ int getDisplayedMnemonicIndex();
 /*public*/ QIcon getSmallDisplayIcon();
 /*public*/ QIcon getLargeDisplayIcon();
 /*public*/ void installChooserPanel(JColorChooser *enclosingChooser);
 /*public*/ void uninstallChooserPanel(JColorChooser* enclosingChooser);
 /*public*/ void updateChooser();

private:
 SwatchPanel* swatchPanel;
 RecentSwatchPanel* recentSwatchPanel;
 MouseListener* mainSwatchListener;
 MouseListener* recentSwatchListener;
 /*private*/ KeyListener* mainSwatchKeyListener;
 /*private*/ KeyListener* recentSwatchKeyListener;

protected:
 /*protected*/ void buildChooser();

};

class SwatchPanel : public JPanel {
Q_OBJECT

public:
 /*public*/ SwatchPanel() ;
 /*public*/ QColor getSelectedColor() ;
 /*public*/ void paintEvent(QPaintEvent* evt);
 /*public*/ QSize getPreferredSize();
 /*public*/ QString getToolTipText(QMouseEvent* e);
 /*public*/ void setSelectedColorFromLocation(int x, int y);
 /*public*/ QColor getColorForLocation( int x, int y );

private:
 /*private*/ int selRow;
 /*private*/ int selCol;
 /*private*/ QColor getColorForCell( int column, int row) ;

protected:
 /*protected*/ void initValues();
 /*protected*/ void initColors() ;
 /*protected*/ QVector<QColor> colors;
 /*protected*/ QSize swatchSize;
 /*protected*/ QSize numSwatches;
 /*protected*/ QSize gap;
};

class RecentSwatchPanel : public SwatchPanel {
public:
 /*public*/ void setMostRecentColor(QColor c);
protected:
 /*protected*/ void initValues();
 /*protected*/ void initColors();
};

class MainSwatchPanel : public SwatchPanel
{

private:
 /*private*/ QVector<int> initRawValues();

protected:
 /*protected*/ void initValues();
 /*protected*/ void initColors();

};
#endif // DEFAULTSWATCHCHOOSERPANEL_H
