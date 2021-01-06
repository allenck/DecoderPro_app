#ifndef TABLEFRAMES_H
#define TABLEFRAMES_H
#include "jmrijframe.h"
#include "jinternalframe.h"
#include <QItemDelegate>
#include <QItemEditorFactory>
#include <QComboBox>
#include "libtables_global.h"
#include "pathturnouttablemodel.h"
#include "jdesktoppane.h"
#include "windowadapter.h"
#include "warranttableaction.h"


class InternalFrameEvent;
class OBlock;
class BlockPathTableModel;
class QMdiArea;
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
 /*public*/ OBlockTableModel* getOblockTableModel() ;
 /*public*/ PortalTableModel* getPortalTableModel();
 /*public*/ BlockPortalTableModel* getPortalXRefTableModel();
 /*public*/ BlockPathTableModel* getBlockPathTableModel(OBlock* block);
 /*public*/ SignalTableModel* getSignalTableModel();
 /*public*/ void initComponents();
  /*public*/ QMenuBar* addMenus(QMenuBar* mBar);
 /*public*/ QMenu *getPrintMenuItems(JTable* oBlockTable, JTable* portalTable, JTable* signalTable, JTable* blockPortalTable);
 /*public*/ QMenu* getOptionMenu();
 /*public*/ QMenu* getTablesMenu();
 ///*public*/ void windowClosing(QCloseEvent* e);
  /*public*/ QString toString() {return getTitle();}
 /*public*/ void internalFrameClosing(InternalFrameEvent* e);
 /*public*/ void internalFrameClosed(InternalFrameEvent* e);
 /*public*/ void internalFrameOpened(InternalFrameEvent* e);
 /*public*/ void internalFrameIconified(InternalFrameEvent* e) ;
 /*public*/ void internalFrameActivated(InternalFrameEvent* e);
 /*public*/ void internalFrameDeiconified(InternalFrameEvent* e) ;
 /*public*/ void internalFrameDeactivated(InternalFrameEvent* e);
 /*public*/ QString getClassName() {return "jmri.jmrit.beantable.oblock.TableFrames";}
  static int ROW_HEIGHT;
  /*public*/ void openPathTurnoutEditPane(QString pathTurnoutName);
  /*public*/ /*static*/ class BlockPathJPanel : public JPanel {
      BlockPathTableModel* blockPathModel;
  public:
      BlockPathJPanel(QString title, QWidget* parent=nullptr) : JPanel(parent) {
          //super();
          JPanel::setObjectName(title);
      }

      BlockPathTableModel* getModel() {
          return blockPathModel;
      }

      void setModel(BlockPathTableModel* model, QString blockName) {
          blockPathModel = model;
          setObjectName(blockName);
      }
  };
  /*public*/ void openBlockPathPane(QString blockSystemName, QString editorTabName);

signals:

public slots:
private:
 /*private*/ static QString _oblockPrefix;
 /*private*/ /*final*/ static QString portalPrefix;// = "IP";
 /*private*/ QString _title;
 static Logger* log;
 void common(QString);
 QMdiArea* mdiArea = nullptr;
 JTable* _oBlockTable = nullptr;
 OBlockTableModel* _oBlockModel = nullptr;
 JTable* _portalTable = nullptr;
 PortalTableModel* _portalModel = nullptr;
 JTable* _blockPortalTable = nullptr;
 BlockPortalTableModel* _blockPortalXRefModel = nullptr;
 JTable* _signalTable = nullptr;
 SignalTableModel* _signalModel = nullptr;

 /*private*/ /*final*/ bool _tabbed; // updated from prefs (restart required)
 /*private*/ bool pathEdit = false;

 /*private*/ JmriJFrame* desktopframe = nullptr;
 /*private*/ JDesktopPane* _desktop = nullptr;
 JInternalFrame* _blockTableFrame = nullptr;
 JInternalFrame* _portalTableFrame = nullptr;
 JInternalFrame* _blockPortalXRefFrame = nullptr;
 JInternalFrame* _signalTableFrame = nullptr;

 bool _showWarnings;// = true;
 QAction* _showWarnItem;
 QMenu* _openMenu;
 QMap<QString, JInternalFrame*> _blockPathMap;// = new HashMap<String, JInternalFrame>();
 QMap<QString, JInternalFrame*> _pathTurnoutMap;// = new HashMap<String, JInternalFrame>();
 QSignalMapper* warningMapper;
 void showPopup(QMouseEvent* me);
 // /*private*/ void errorCheck();
 QMenu* tablesMenu;
 void addCloseListener(JmriJFrame* desktop);
 /*private*/ void createDesktop();
 /*private*/ QString getTitle() override;
 /*private*/ void setTitle(QString title) override;
 /*private*/ void showHideFrame(JInternalFrame* frame, QAction* menu, QString menuName);
 /*private*/ QString oblockPrefix();
 /*private*/ QAction* openBlock;
 /*private*/ QAction* openPortal;
 /*private*/ QAction* openXRef;
 /*private*/ QAction* openSignal;
 /*public*/ void mousePressEvent(QMouseEvent* me); // for macOS, Linux


private slots:
 /*private*/ void setShowWarnings(QString cmd);

protected:
 /*protected*/ static /*final*/ QString SET_CLOSED;// = jmri.InstanceManager.turnoutManagerInstance().getClosedText();
 /*protected*/ static /*final*/ QString SET_THROWN;// = jmri.InstanceManager.turnoutManagerInstance().getThrownText();
 /*protected*/ void openBlockPathFrame(QString sysName);
 /*protected*/ QString makePathTurnoutName(QString blockSysName, QString pathName);
 /*protected*/ void disposeBlockPathFrame(OBlock* block);
 /*protected*/ int verifyWarning(QString message);
 /*protected*/ JmriJFrame* getDesktopFrame();
 /*protected*/ void importBlocks() throw (IllegalArgumentException);
 /*protected*/ void updateOBlockTablesMenu();
 /*protected*/ JInternalFrame* buildFrame(AbstractTableModel* tableModel, QString title, QString prompt);
 /*protected*/ JTable* makeOBlockTable(OBlockTableModel* model);
 /*protected*/ bool openOBlockEditor(QString blockSystemName, QString tabname);
 /*protected*/ BlockPathJPanel* makeBlockPathEditPanel(OBlock* block);
 /*protected*/ void setPathEdit(bool edit);
 /*protected*/ bool isPathEdit();
 /*protected*/ JPanel* makeBlockPathTablePanel(BlockPathTableModel* _model);
 /*protected*/ JTable* makeBlockPathTable(BlockPathTableModel* _model);
 /*protected*/ JTable* makePathTurnoutTable(PathTurnoutTableModel* model);
 /*protected*/ void openPathTurnoutFrame(QString pathTurnoutName);
 /*protected*/ void openPathTurnoutEditor(QString pathTurnoutName);
 /*protected*/ JTable* makeBlockPortalTable(BlockPortalTableModel* model);
 /*protected*/ JTable* makePortalTable(PortalTableModel* model);
 /*protected*/ JTable* makeSignalTable(SignalTableModel* model);
 /*protected*/ bool openPathEditor(/*@Nonnull*/ QString blockName, /*@CheckForNull*/ QString pathName, BlockPathTableModel* bpmodel);

 /**
  * ********************* Path-Turnout JPanel class for _tabbed *****************
  */
 /*protected*/ /*static*/ class PathTurnoutJPanel : public JPanel {

     /**
      * Remember the tableModel
      */
     PathTurnoutTableModel* pathTurnoutModel;

     PathTurnoutJPanel(QString pathname) {
         //super();
         this->setObjectName(pathname);
     }

     PathTurnoutTableModel* getModel() {
         return pathTurnoutModel;
     }

     void setModel(PathTurnoutTableModel* model) {
         pathTurnoutModel = model;
     }
     friend class TableFrames;
     friend class BlockPathEditFrame;
 };
 // ********************* Path-Turnout Frame class for _desktop ****************
 /*protected*/ /*static*/ class PathTurnoutFrame : public JInternalFrame {

     /**
      * Remember the tableModel
      */
     PathTurnoutTableModel* pathTurnoutModel;

     PathTurnoutFrame(QString title, bool resizable, bool closable,
             bool maximizable, bool iconifiable) : JInternalFrame(title, resizable, closable, maximizable, iconifiable){
         //super(title, resizable, closable, maximizable, iconifiable);
     }

     PathTurnoutTableModel* getModel() {
         return pathTurnoutModel;
     }

     void setModel(PathTurnoutTableModel* model) {
         pathTurnoutModel = model;
     }
     friend class TableFrames;
 };
 // ***************** Block-Path Frame class for _desktop **************************
 /*protected*/ /*static*/ class BlockPathFrame : public JInternalFrame {

     BlockPathTableModel* blockPathModel;
public:
     BlockPathFrame(QString title, bool resizable, bool closable,
                    bool maximizable, bool iconifiable): JInternalFrame(title, resizable, closable, maximizable, iconifiable){
         //super(title, resizable, closable, maximizable, iconifiable);
     }

     BlockPathTableModel* getModel() {
         return blockPathModel;
     }

     void setModel(BlockPathTableModel* model, QString blockName) {
         blockPathModel = model;
         setName(blockName);
     }
     friend class TableFrames;
 };
 /*protected*/ BlockPathFrame* makeBlockPathFrame(OBlock* block);
 /*protected*/ PathTurnoutFrame* makePathTurnoutFrame(OBlock* block, QString pathName);
 /*protected*/ PathTurnoutJPanel* makePathTurnoutPanel(/*@Nonnull*/ OBlock* block, /*@CheckForNull*/ QString pathName);
 /*protected*/ void addTurnoutPane(OPath* path, PathTurnoutTableModel* pathTurnoutModel);

friend class OBlockTableModel;
friend class BlockPathTableModel;
friend class PortalTableModel;
friend class TFCloseWindowListener;
friend class BlockPathEditFrame;
friend class BPEFCloseListener;

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

/**
 * ********************* PathTurnoutFrame *****************************
 */
/*protected*/ /*static*/ class PathTurnoutFrame : public JInternalFrame {
 Q_OBJECT
    /**
     *
     */
    PathTurnoutTableModel* pathTurnoutModel;
public:

    PathTurnoutFrame(QString title, bool resizable, bool closable,
            bool maximizable, bool iconifiable)
     :         JInternalFrame(title, resizable, closable, maximizable, iconifiable)

    {
        //super(title, resizable, closable, maximizable, iconifiable);
    }

    void init(OPath* path) {
        pathTurnoutModel = new PathTurnoutTableModel(path, this);
    }

    PathTurnoutTableModel* getModel() {
        return pathTurnoutModel;
    }
    void setEnabled(bool b) override {setEnabled(b);}
    bool isOpaque() {return true;}
    QColor getForeground()  {return Qt::black;}
    QColor getBackground() {return Qt::lightGray;}
    void setBackground(QColor){return;}
    void setOpaque(bool) {}
    QFont getFont() {return font();}
    void setFont(QFont f) {QWidget::setFont(f);}
    QObject* jself() {(QObject*)this;}
    void setBorder(Border* b) {}
    Border* getBorder() {return nullptr;}
};

class TFCloseWindowListener : public WindowAdapter
{
  Q_OBJECT
  TableFrames* tf;
  JmriJFrame* desktop;
 public:
  TFCloseWindowListener(JmriJFrame* desktop, TableFrames* tf)
  {
   this->tf = tf;
   this->desktop = desktop;
  }
  //@Override
  /*public*/ void windowClosing(QCloseEvent* e) {
      WarrantTableAction::getDefault()->errorCheck();
      desktop->setDefaultCloseOperation(JFrame::HIDE_ON_CLOSE);
      // closing instead of hiding removes name from Windows menu.handle menu to read Show...
      tf->log->debug(tr("windowClosing: %1").arg(tf->toString()));
      desktop->dispose();
  }
};


#endif // TABLEFRAMES_H
