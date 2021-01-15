#ifndef WARRANTTABLEFRAME_H
#define WARRANTTABLEFRAME_H
#include "jmrijframe.h"
#include "windowlistener.h"
#include "liblayouteditor_global.h"
#include "tabledelegates.h"

class QSignalMapper;
class Warrant;
class WarrantTableModel;
class JTextField;
class JDialog;
class LIBLAYOUTEDITORSHARED_EXPORT WarrantTableFrame : public JmriJFrame
{
 Q_OBJECT
public:
 /*public*/ static int _maxHistorySize;// = 30;
 /*public*/ static WarrantTableFrame* getDefault();
 /*public*/ void showWarning(QString msg);
 /*public*/ void mouseClicked(QMouseEvent* event);
 /*public*/ void mousePressed(QMouseEvent* event);
 /*public*/ void mouseEntered(QMouseEvent* event);
 /*public*/ void mouseExited(QMouseEvent* event);
 /*public*/ void mouseReleased(QMouseEvent* event);
 /*public*/ QString getClassName();


signals:

public slots:
 /*public*/ QString runTrain(Warrant* w, int mode);

private:
 static Logger* log;
 /*private*/ JTextField*  _startWarrant;// = new JTextField(30);
 /*private*/ JTextField*  _endWarrant;// = new JTextField(30);
 /*private*/ JDialog*    _concatDialog;
 /*private*/ JTextField*  _status;// = new JTextField(90);
 /*private*/ QList<QString> _statusHistory;// = new ArrayList<String>();
 ///*private*/ JScrollPane _tablePane;
 /*private*/ int _rowHeight;

 /*private*/ WarrantTableModel*     _model;
 /*private*/ static WarrantTableFrame* _instance;
 static QString BLANK;// = "                                                                                                 ";
 ///*private*/ static /*final*/ long serialVersionUID = 8994208663637783635L;
 static /*final*/ QString halt;// = tr("Halt");
 static /*final*/ QString resume;// = tr("Resume");
 static /*final*/ QString abort;// = tr("Abort");
 static /*final*/ QString retry;// = tr("Retry");
 static /*final*/ QStringList controls;// = {halt, resume, retry, abort};
 /*explicit*/ WarrantTableFrame(QWidget *parent = 0);
 Q_INVOKABLE void setStatusText(QString msg, QColor c, bool save);
 QSignalMapper* setColumnMapper;
private slots:
 /*private*/ void haltAllAction();
 /*private*/ void concatenate();
 void on_nxButtonClicked();
protected:
 /*protected*/ static WarrantTableFrame* reset();
 /*protected*/ WarrantTableModel* getModel();
 /*protected*/ void scrollTable();
 /*protected*/ static void nxAction();

protected slots:
 /*protected*/ void concatMenuAction();


friend class CreateNXWarrantActionListener;
friend class WarrantTableAction;
friend class EditWarrantActionListener;
friend class WTWindowListener;
friend class WarrantTableModel;
friend class WarrantFrame;
friend class NXFrame;
friend class Engineer;
friend class RouteBoxCellEditor;
};

class WTWindowListener : public WindowListener
{
 Q_OBJECT
 WarrantTableFrame* frame;
 WTWindowListener(WarrantTableFrame* frame) { this->frame = frame;}
 void windowClosing(QCloseEvent */*e*/) { frame->dispose();}
 friend class WarrantTableFrame;
};

class ControlBoxCellEditor : public JComboBoxEditor
{
  Q_OBJECT
  WarrantTableFrame* frame;
 public:
  ControlBoxCellEditor(QStringList controls, WarrantTableFrame* frame) : JComboBoxEditor(controls, (QObject*)frame) {this->frame = frame;}
  //QWidget *createEditor(QWidget *parent, const QStyleOptionViewItem &option, const QModelIndex &index) const;

};

class RouteBoxCellEditor : public JComboBoxEditor
{
  Q_OBJECT
  WarrantTableFrame* frame;
 public:
  RouteBoxCellEditor(WarrantTableFrame* frame) : JComboBoxEditor((QObject*)frame) {this->frame = frame;}
  QWidget *createEditor(QWidget *parent, const QStyleOptionViewItem &option, const QModelIndex &index) const;
};
#endif // WARRANTTABLEFRAME_H
