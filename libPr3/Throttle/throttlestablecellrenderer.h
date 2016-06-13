#ifndef THROTTLESTABLECELLRENDERER_H
#define THROTTLESTABLECELLRENDERER_H

#include <QObject>

class QTableView;
class NamedIcon;
class RosterIconFactory;
class ThrottlesTableCellRenderer : public QObject
{
    Q_OBJECT
public:
    explicit ThrottlesTableCellRenderer(QObject *parent = 0);
    /*public*/ QWidget* getTableCellRendererComponent(QTableView* jtable, QVariant value, bool bln, bool bln1, int i, int i1);

signals:

public slots:
private:
    /*private*/ static /*final*/ NamedIcon* fwdIcon;// = new ImageIcon("resources/icons/throttles/up-green.png");
    /*private*/ static /*final*/ NamedIcon* bckIcon;// = new ImageIcon("resources/icons/throttles/down-green.png");
    /*private*/ static /*final*/ NamedIcon* estopIcon;// = new ImageIcon("resources/icons/throttles/estop24.png");
    /*private*/ static /*final*/ RosterIconFactory* iconFactory;// =  new RosterIconFactory(32);
    /*final*/ static int height;// = 42;

};

#endif // THROTTLESTABLECELLRENDERER_H
