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
class JSpinner;
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
    JSpinner* _spinner = nullptr;
    /**
    *  CENTER Panel
    */
    MemoryIcon*      	_readMem = nullptr;
    MemoryInputIcon* 	_writeMem = nullptr;
    MemorySpinnerIcon*   _spinMem = nullptr;
    MemoryComboIcon* 	_comboMem = nullptr;
    /*private*/ JPanel* makeDragIcon(QWidget* mem, Type type);
    Logger* log;

protected:
    /*protected*/ JPanel *instructions();
    /*protected*/ void initIconFamiliesPanel() override;
    /*protected*/ void makeDndIconPanel(QMap<QString, NamedIcon*>* iconMap, QString displayKey) override;
    /*protected*/ MemoryIconDragJComponent* getDragger(DataFlavor* flavor, MemoryItemPanel::Type type, QSize dim );

friend class MemoryIconDragJComponent;
};

/*protected*/ class MemoryIconDragJComponent :public DragJComponent
{
    Q_OBJECT
    MemoryItemPanel::Type _memType;
    MemoryItemPanel* self;
public:
    /*public*/ MemoryIconDragJComponent(DataFlavor* flavor, MemoryItemPanel::Type type, QSize dim, QWidget* parent = 0);
    /*public*/ QObject* getTransferData(DataFlavor* flavor) throw (UnsupportedFlavorException,IOException);
    QByteArray mimeData() override;
};

#endif // MEMORYITEMPANEL_H
