#ifndef LAYOUTEDITORFLOATINGTOOLBARPANEL_H
#define LAYOUTEDITORFLOATINGTOOLBARPANEL_H
#include "layouteditortoolbarpanel.h"

class JTabbedPane;
class LayoutEditorFloatingToolBarPanel : public LayoutEditorToolBarPanel
{
 Q_OBJECT
public:
 /*public*/ LayoutEditorFloatingToolBarPanel(/*@Nonnull*/ LayoutEditor* layoutEditor);
 /*public*/ JTabbedPane* getfloatEditTabsPane();

public slots:
 void onTabBar(int);

private:
 /*private*/ /*transient*/ JPanel* floatEditTabsPanel;
 /*private*/ /*transient*/ JTabbedPane* floatEditTabsPane;
 JPanel* floatEditTurnout;
 QVBoxLayout* floatEditTurnoutLayout;
 JPanel* floatEditTrack;
 QVBoxLayout* floatEditTrackLayout;

protected:
 /*protected*/ void setupComponents();
 /*protected*/ void layoutComponents();

};

#endif // LAYOUTEDITORFLOATINGTOOLBARPANEL_H
