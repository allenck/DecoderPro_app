#ifndef TABLEFRAMES_H
#define TABLEFRAMES_H
#include "jmrijframe.h"
#include "jinternalframe.h"
#include <QItemDelegate>
#include <QItemEditorFactory>
#include <QComboBox>
#include "libtables_global.h"

class InternalFrameEvent;
class OBlock;
class BlockPathTableModel;
class BlockPathFrame;
class QMdiArea;
//class JDesktopPane;
class QSignalMapper;
class JInternalFrame;
class SignalTableModel;
class BlockPortalTableModel;
class PortalTableModel;
class OBlockTableModel;
class JTable;
class LIBTABLESSHARED_EXPORT TableFrames : public JmriJFrame
{
 Q_OBJECT
public:
 explicit TableFrames(QWidget *parent = 0);
 /*public*/ static /*final*/ int STRUT_SIZE;// = 10;
 /*public*/ TableFrames(QString actionName, QWidget *parent = 0);
 /*public*/ void initComponents();
 /*public*/ void windowClosing(QCloseEvent* e);
 /*public*/ QString toString();
 /*public*/ void internalFrameClosing(InternalFrameEvent* e);
 /*public*/ void internalFrameClosed(InternalFrameEvent* e);
 /*public*/ void internalFrameOpened(InternalFrameEvent* e);
 /*public*/ void internalFrameIconified(InternalFrameEvent* e) ;
 /*public*/ void internalFrameActivated(InternalFrameEvent* e);
 /*public*/ void internalFrameDeiconified(InternalFrameEvent* e) ;
 /*public*/ void internalFrameDeactivated(InternalFrameEvent* e);

signals:

public slots:
private:
 static int ROW_HEIGHT;
 void common();
 QMdiArea* mdiArea;
 JTable* _oBlockTable;
 OBlockTableModel* _oBlockModel;
 JTable* _portalTable;
 PortalTableModel* _portalModel;
 JTable* _blockPortalTable;
 BlockPortalTableModel* _blockPortalXRefModel;
 JTable* _signalTable;
 SignalTableModel* _signalModel;

// JTable* _blockTablePane;
// JTable* _portalTablePane;
// JTable* _signalTablePane;

 //JDesktopPane* _desktop;
 JInternalFrame* _blockTableFrame;
 JInternalFrame* _portalTableFrame;
 JInternalFrame* _blockPortalXRefFrame;
 JInternalFrame* _signalTableFrame;

 bool _showWarnings;// = true;
 QAction* _showWarnItem;
 QMenu* _openMenu;
 QMap<QString, JInternalFrame*> _blockPathMap;// = new HashMap<String, JInternalFrame>();
 QMap<QString, JInternalFrame*> _PathTurnoutMap;// = new HashMap<String, JInternalFrame>();
 Logger* log;
 QSignalMapper* warningMapper;
 void showPopup(QMouseEvent* me);
 /*private*/ void errorCheck();
 static /*private*/ void setActionMappings(JTable* table);

private slots:
 /*private*/ void setShowWarnings(QString cmd);
 void  on_openBlock_triggered();
 void on_openPortal_triggered();
 void on_openXRef_triggered();
 void on_openSignal_triggered();
protected:
 /*protected*/ void openBlockPathFrame(QString sysName);
 /*protected*/ /*final*/ SignalTableModel* getSignalModel();
 /*protected*/ /*final*/ BlockPortalTableModel* getXRefModel();
 /*protected*/ void updateOpenMenu();
 /*protected*/ QString makePathTurnoutName(QString blockSysName, QString pathName);
// /*protected*/ /*final*/ JTable* getBlockTablePane() ;
// /*protected*/ /*final*/ JTable* getPortalTablePane() ;
// /*protected*/ /*final*/ JTable* getSignalTablePane();
 /*protected*/ /*final*/ OBlockTableModel* getBlockModel();
 /*protected*/ /*final*/ PortalTableModel* getPortalModel();
 /*protected*/ JInternalFrame* makeBlockFrame();
 /*protected*/ JInternalFrame* makePortalFrame();
 /*protected*/ JInternalFrame* makeBlockPortalFrame();
 /*protected*/ JInternalFrame* makeSignalFrame();
 /*protected*/ BlockPathFrame* makeBlockPathFrame(OBlock* block);
 /*protected*/ void openPathTurnoutFrame(QString pathTurnoutName);
 /*protected*/ JInternalFrame* makePathTurnoutFrame(OBlock* block, QString pathName);

friend class OBlockTableModel;
friend class BlockPathTableModel;
};

/*static*/ class BlockPathFrame : public JInternalFrame
{
 Q_OBJECT
    /**
     *
     */
   // private static /*final*/ long serialVersionUID = 1917299755191589427L;
    BlockPathTableModel* blockPathModel;
public:
    /*public*/ BlockPathFrame(QString title, bool resizable, bool closable,
            bool maximizable, bool iconifiable) ;
    /*public*/ void init(OBlock* block, TableFrames* parent) ;
    /*public*/ BlockPathTableModel* getModel() ;
};

class MyBooleanRenderer : public QItemDelegate
{
 Q_OBJECT
 QString _trueValue;
 QString _falseValue;
 QSignalMapper* _mapper;
public:
 MyBooleanRenderer(QString trueValue, QString falseValue, QSignalMapper* mapper)
 {
  _trueValue = trueValue;
  _falseValue = falseValue;
  _mapper = mapper;
 }
 QWidget *createEditor(QWidget *parent, const QStyleOptionViewItem &option, const QModelIndex &index) const
{
 //QLabel* editor = new QLabel(parent);
  QItemEditorFactory* factory = new QItemEditorFactory;

  QWidget* editor = factory->createEditor(QVariant::Bool, parent);
  QComboBox* cb = (QComboBox*)editor;
  cb->clear();
  cb->addItem(_falseValue);
  cb->addItem(_trueValue);

 if(_mapper != NULL)
 {
  QModelIndex* pIndex = new QModelIndex(index);
  _mapper->setMapping(editor,(QObject*)pIndex);

  connect(editor, SIGNAL(clicked()), _mapper, SLOT(map()));
 }
 return editor;
}

void setEditorData(QWidget *editor, const QModelIndex &index) const
{
 QComboBox *cb = static_cast<QComboBox*>(editor);
 //label->setStyleSheet("QLabel { background-color : red; color : blue; }");
 bool value = index.model()->data(index, Qt::DisplayRole).toBool();
 if(value)
  cb->setCurrentIndex(1);
 else
  cb->setCurrentIndex(0);
}
void setModelData(QWidget *editor, QAbstractItemModel *model, const QModelIndex &index) const
{
 QComboBox* cb = (QComboBox*)editor;
 int ix = cb->currentIndex();
 model->setData(index,(ix ==1));

}
 void updateEditorGeometry(QWidget *editor, const QStyleOptionViewItem &option, const QModelIndex &index) const
 {
  editor->setGeometry(option.rect);
 }

};

#endif // TABLEFRAMES_H
