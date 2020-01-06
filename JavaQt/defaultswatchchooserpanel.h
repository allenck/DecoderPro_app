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
 /*public*/ QString getTitle();

private:
 SwatchPanel* swatchPanel;
 RecentSwatchPanel* recentSwatchPanel;
 MouseListener* mainSwatchListener;
 MouseListener* recentSwatchListener;
 /*private*/ KeyListener* mainSwatchKeyListener;
 /*private*/ KeyListener* recentSwatchKeyListener;

protected:
 /*protected*/ void buildChooser();
 friend class ColorChooserPanelTest;
 friend class SwatchPanel;
};

class SwatchPanel : public JPanel {
Q_OBJECT
DefaultSwatchChooserPanel* dscp;
public:
 /*public*/ SwatchPanel(DefaultSwatchChooserPanel* dscp) ;
 /*public*/ QColor getSelectedColor() ;
 /*public*/ void paintEvent(QPaintEvent* evt) override;
 /*public*/ QSize getPreferredSize();
 /*public*/ QString getToolTipText(QMouseEvent* e);
 /*public*/ void setSelectedColorFromLocation(int x, int y);
 /*public*/ QColor getColorForLocation( int x, int y );

public slots:
 /*public*/ void mousePressed(QMouseEvent* e);

private:
 /*private*/ int selRow;
 /*private*/ int selCol;
 /*private*/ QColor getColorForCell( int column, int row) ;
private slots:
 void init();

protected:
 virtual /*protected*/ void initValues();
 virtual /*protected*/ void initColors() ;
 /*protected*/ QVector<QColor> colors;
 /*protected*/ QSize swatchSize;
 /*protected*/ QSize numSwatches;
 /*protected*/ QSize gap;
 void mousePressEvent(QMouseEvent*);

};

class RecentSwatchPanel : public SwatchPanel {
 Q_OBJECT
public:
 /*public*/ RecentSwatchPanel(DefaultSwatchChooserPanel* dscp) : SwatchPanel(dscp) {}
 /*public*/ void setMostRecentColor(QColor c);
protected:
 /*protected*/ void initValues();
 /*protected*/ void initColors();
};

class MainSwatchPanel : public SwatchPanel
{
 Q_OBJECT
private:
 /*private*/ QVector<int> initRawValues();
public:
 /*public*/ MainSwatchPanel(DefaultSwatchChooserPanel* dscp) : SwatchPanel(dscp) {}

protected:
 /*protected*/ void initValues();
 /*protected*/ void initColors();

};
#endif // DEFAULTSWATCHCHOOSERPANEL_H
