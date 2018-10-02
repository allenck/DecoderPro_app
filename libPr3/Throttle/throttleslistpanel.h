#ifndef THROTTLESLISTPANEL_H
#define THROTTLESLISTPANEL_H

#include <QWidget>
#include <QtXml>

class JTable;
class ThrottlesTableModel;
class ThrottlesListPanel : public QWidget
{
    Q_OBJECT
public:
 explicit ThrottlesListPanel(QWidget *parent = 0);
 /*public*/ ThrottlesTableModel* getTableModel();
 /*public*/ QDomElement getXml();
 /*public*/ void setXml(QDomElement tlp);

signals:

public slots:
 void On_jbNewClicked();
 void On_preferencesClicked();
 void On_throttleFramesClicked(QModelIndex);

private:
 /*private*/ ThrottlesTableModel* throttleFramesLM;
 /*private*/ JTable* throttleFrames;
 /*private*/ void initGUI();
 QDomDocument doc;
};

#endif // THROTTLESLISTPANEL_H
