#ifndef PORTALITEMPANEL_H
#define PORTALITEMPANEL_H
#include "familyitempanel.h"

class PortalItemPanel : public FamilyItemPanel
{
 Q_OBJECT
public:
 /*public*/ PortalItemPanel(DisplayFrame* parentFrame, QString type, QString family, Editor* editor, QWidget* parent = nullptr);
 /*public*/ void init();

private:
 /*private*/ QWidget* makeChangeDefaultIconsPanel();

private slots:
 /*private*/ void setDefaults();


protected:
 /*protected*/ void makeDndIconPanel(QMap<QString, NamedIcon *> *iconMap, QString displayKey);

};

#endif // PORTALITEMPANEL_H
