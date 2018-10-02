#ifndef PORTALITEMPANEL_H
#define PORTALITEMPANEL_H
#include "familyitempanel.h"

class PortalItemPanel : public FamilyItemPanel
{
public:
 /*public*/ PortalItemPanel(DisplayFrame* parentFrame, QString type, QString family, Editor* editor, QWidget* parent = nullptr);
 /*public*/ void init();

private:
 /*private*/ QWidget* makeChangeDefaultIconsPanel();

private slots:
 /*private*/ void setDefaults();


protected:
 /*protected*/ void makeDndIconPanel(QHash<QString, NamedIcon*>* iconMap, QString displayKey);

};

#endif // PORTALITEMPANEL_H
