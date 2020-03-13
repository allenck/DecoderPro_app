#ifndef LAYOUTEDITORHORIZONTALTOOLBARPANEL_H
#define LAYOUTEDITORHORIZONTALTOOLBARPANEL_H
#include "layouteditortoolbarpanel.h"

class LayoutEditorHorizontalToolBarPanel : public LayoutEditorToolBarPanel
{
 Q_OBJECT
public:
 /*public*/ LayoutEditorHorizontalToolBarPanel(/*@Nonnull */LayoutEditor* layoutEditor, QWidget* parent = nullptr);

protected:
 /*protected*/ void layoutComponents() override;

};

#endif // LAYOUTEDITORHORIZONTALTOOLBARPANEL_H
