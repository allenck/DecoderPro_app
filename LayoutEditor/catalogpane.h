#ifndef CATALOGPANE_H
#define CATALOGPANE_H

#include <QWidget>
#include <QLabel>
#include "jtree.h"
#include <QBoxLayout>

class NamedIcon;
class Logger;
class CatalogPane : public QWidget
{
 Q_OBJECT
public:
 explicit CatalogPane(QWidget *parent = nullptr);
 /*public*/ NamedIcon* getSelectedIcon();

signals:

public slots:

private:
 /*private*/ /*final*/ static Logger* log;// = LoggerFactory::getLogger("CatalogPane");
 QLabel* preview;// = new JLabel();
 JTree* dTree;
 friend class CPTreeSelectionListener;
 friend class CP2TreeSelectionListener;
};

class CPTreeSelectionListener : public TreeSelectionListener
{
 Q_OBJECT
 CatalogPane* cp;
public:
 CPTreeSelectionListener(CatalogPane* cp);
public slots:
 /*public*/ void valueChanged(TreeSelectionEvent* e);

};

class CP2TreeSelectionListener : public TreeSelectionListener
{
 Q_OBJECT
 CatalogPane* cp;
public:
 CP2TreeSelectionListener(CatalogPane* cp);
public slots:
 /*public*/ void valueChanged(TreeSelectionEvent* e);

};

#endif // CATALOGPANE_H
