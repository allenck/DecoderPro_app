#ifndef MEMORYITEMPANEL_H
#define MEMORYITEMPANEL_H
#include "tableitempanel.h"
#include "dragjcomponent.h"

class MemoryIconDragJComponent;
class ItemPalette;
class ChangeEvent;
class MemoryComboIcon;
class MemorySpinnerIcon;
class MemoryInputIcon;
class MemoryIcon;
class QSpinBox;
class MemoryItemPanel : public TableItemPanel
{
    Q_OBJECT
public:
    //explicit MemoryItemPanel(QWidget *parent = 0);
    enum Type { READONLY, READWRITE, SPINNER, COMBO };
    /*public*/ MemoryItemPanel(DisplayFrame* parentFrame, QString type, QString family, PickListModel* model, Editor* editor, QWidget *parent = 0);
    /*public*/ void init() override;

signals:

public slots:
    /*public*/ void stateChanged(/*ChangeEvent* e = 0*/);
    /*public*/ void valueChanged(/*ListSelectionEvent e*/);

private:
    QSpinBox* _spinner;
    /**
    *  CENTER Panel
    */
    MemoryIcon*      	_readMem;
    MemoryInputIcon* 	_writeMem;
    QWidget*			_writePanel;
    MemorySpinnerIcon*   _spinMem;
    MemoryComboIcon* 	_comboMem;
    /*private*/ QWidget* makeDragIcon(QWidget* mem, Type type);
    Logger* log;

protected:
    /*protected*/ QWidget* instructions();
    /*protected*/ void initIconFamiliesPanel() override;
    /*protected*/ void makeDndIconPanel(QMap<QString, NamedIcon*>* iconMap, QString displayKey) override;
    /*protected*/ MemoryIconDragJComponent* getDragger(DataFlavor* flavor, Type type, QWidget *comp );
friend class MemoryIconDragJComponent;
};

/*protected*/ class MemoryIconDragJComponent :public DragJComponent
{
    Q_OBJECT
    MemoryItemPanel::Type _memType;
    MemoryItemPanel* self;
public:
    /*public*/ MemoryIconDragJComponent(DataFlavor* flavor, MemoryItemPanel::Type type, QWidget *comp, QWidget* parent = 0);
    /*public*/ QObject* getTransferData(DataFlavor* flavor) throw (UnsupportedFlavorException,IOException);
    QByteArray mimeData();
};

#endif // MEMORYITEMPANEL_H
