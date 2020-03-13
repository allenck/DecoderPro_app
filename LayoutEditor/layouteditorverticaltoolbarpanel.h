#ifndef LAYOUTEDITORVERTICALTOOLBARPANEL_H
#define LAYOUTEDITORVERTICALTOOLBARPANEL_H
#include "layouteditortoolbarpanel.h"

class LayoutEditorVerticalToolBarPanel : public LayoutEditorToolBarPanel
{
 Q_OBJECT
public:
 LayoutEditorVerticalToolBarPanel(LayoutEditor* layoutEditor, QWidget* parent = nullptr);

protected:
 /*protected*/ void layoutComponents() override;

};

#endif // LAYOUTEDITORVERTICALTOOLBARPANEL_H
