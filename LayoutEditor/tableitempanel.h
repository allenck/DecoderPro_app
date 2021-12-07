#ifndef TABLEITEMPANEL_H
#define TABLEITEMPANEL_H
#include "familyitempanel.h"
#include "dragjlabel.h"

class ListSelectionEvent;
class DisplayFrame;
class JDialog;
class QItemSelection;
class TIconDragJLabel;
class JTable;
class JTextField;
class PickListModel;
class ActionListener;
class NamedBean;
class TableItemPanel : public FamilyItemPanel
{
    Q_OBJECT
public:
    //explicit TableItemPanel(QWidget *parent = 0);
    /*public*/ TableItemPanel(DisplayFrame* parentFrame, QString  type, QString family, PickListModel* model, Editor* editor, QWidget *parent = 0);
    /*public*/ void init();
    /*public*/ void init(ActionListener* doneAction, QMap<QString, NamedIcon*>* iconMap);
    /*public*/ NamedBean* getTableSelection();
    /*public*/ void setSelection(NamedBean* bean) ;

signals:

public slots:
    void OnSelectionChanged(const QItemSelection & selected, const QItemSelection & deselected );
    void cancelPressed(/*ActionEvent e*/);
    /*public*/ void valueChanged(ListSelectionEvent *e);

private:
    int ROW_HEIGHT;
    //JScrollPane _scrollPane;
    JDialog*     _addTableDialog = nullptr;
    JTextField*  _sysNametext;// = new JTextField();
    JTextField*  _userNametext;// = new JTextField();
    QPushButton* _addTableButton;
private:
    Logger* log;

protected:
    /*protected*/ JTable*    _table = nullptr;
    /*protected*/ PickListModel* _model = nullptr;
    /*protected*/ virtual QWidget* initTablePanel(PickListModel* model, Editor* editor);
    /*protected*/ void addToTable();
    /*protected*/ NamedBean* getNamedBean();

protected slots:
    /*protected*/ void makeAddToTableWindow();
    /*protected*/ DragJLabel* getDragger(DataFlavor* flavor, QMap<QString, NamedIcon*>* map, NamedIcon* icon);

friend class SignalHeadItemPanel;
friend class TIconDragJLabel;
friend class SignalMastItemPanel;
friend class SMIconDragJLabel;
friend class MultiSensorItemPanel;
friend class MSIconDragJLabel;
friend class ITOIconDragJLabel;
friend class AddTableActionListener;
};

/*protected*/ class TIconDragJLabel :public DragJLabel
{
 Q_OBJECT
 TableItemPanel* self;
 QMap<QString, NamedIcon*>* iMap;
public:
 /*public*/ TIconDragJLabel(DataFlavor* flavor, QMap<QString, NamedIcon *> *map, NamedIcon *icon, TableItemPanel* self);
 /*public*/ bool isDataFlavorSupported(DataFlavor* flavor) ;
 /*public*/ QObject* getTransferData(DataFlavor* flavor) throw (UnsupportedFlavorException,IOException) ;
 QByteArray mimeData();
};

class AddTableActionListener : public QObject, public ActionListener
{
    Q_OBJECT
    Q_INTERFACES(ActionListener)
    TableItemPanel* parent;
public:
    AddTableActionListener(TableItemPanel* parent);
    QObject* self() override {return (QObject*)this;}
  public slots:

    void actionPerformed(JActionEvent *e = 0)override;
};

class AtCancelListener : public QObject, public ActionListener
{
  TableItemPanel* tip;
  Q_OBJECT
  Q_INTERFACES(ActionListener)
public:
  AtCancelListener(TableItemPanel* tip);
  QObject* self() override {return (QObject*)this;}
public slots:
  /*public*/ void actionPerformed(JActionEvent* =0)override ;
};

#endif // TABLEITEMPANEL_H
