#include "portallist.h"
#include "loggerfactory.h"
#include "oblock.h"
#include "portal.h"
#include "editframe.h"
#include "vptr.h"

PortalList::PortalList(QObject *parent)
{

}
/**
 *
 * @author Pete Cressman Copyright: Copyright (c) 2014
 *
 */
///*public*/ class PortalList extends JList<Portal> {


    PortalList::PortalList(OBlock* block, EditFrame* parent) {
        //super();
        _portalListModel = new PortalListModel(block, parent);
        setModel(_portalListModel);
//        setCellRenderer(new PortalCellRenderer());
        resize(QSize(300, 120));
        setVisibleRowCount(5);
    }

    void PortalList::dataChange() {
        _portalListModel->dataChange();
    }
#if 0
    private static class PortalCellRenderer extends JLabel implements ListCellRenderer<Portal>{

        @Override
        /*public*/ Component getListCellRendererComponent(
                JList<? extends Portal> list, // the list
                Portal value, // value to display
                int index, // cell index
                boolean isSelected, // is the cell selected
                boolean cellHasFocus) // does the cell have focus
        {
            String s = value.getDescription();
            setText(s);
            if (isSelected) {
                setBackground(list.getSelectionBackground());
                setForeground(list.getSelectionForeground());
            } else {
                setBackground(list.getBackground());
                setForeground(list.getForeground());
            }
            setEnabled(list.isEnabled());
            setFont(list.getFont());
            setOpaque(true);
            return this;
        }
    }
#endif
//    static class PortalListModel extends AbstractListModel<Portal> implements PropertyChangeListener {

//        OBlock _homeBlock;
//        private EditFrame _parent;
//        List<Portal> _list = new ArrayList<>();

        PortalListModel::PortalListModel(OBlock* block, EditFrame* parent) {
            _homeBlock = block;
            _parent = parent;
            _homeBlock->addPropertyChangeListener((PropertyChangeListener*)this);
            makeList();
        }

        /*private*/ void PortalListModel::makeList() {
            for (Portal* p : _list) {
                p->removePropertyChangeListener((PropertyChangeListener*)this);
            }
            _list = _homeBlock->getPortals();
            for (Portal* p : _list) {
                p->addPropertyChangeListener((PropertyChangeListener*)this);
            }
        }

        //@Override
        /*public*/ int PortalListModel::getSize() const{
            return _homeBlock->getPortals().size();
        }

        int PortalListModel::rowCount(const QModelIndex &parent) const
        {
         return _homeBlock->getPortals().size();
        }

        //@Override
        /*public*/ QVariant PortalListModel::getElementAt(int index) const{
            if (index < getSize()) {
                return VPtr<Portal>::asQVariant(_homeBlock->getPortals().at(index));
            }
            return QVariant();
        }

        QVariant PortalListModel::data(const QModelIndex &index, int role) const
        {
         return (getElementAt(index.row()));
        }

        /*public*/ void PortalListModel::dataChange() {
            fireContentsChanged(this, 0, 0);
        }

        /*public*/ void PortalListModel::propertyChange(PropertyChangeEvent* e) {
            QObject* source = e->getSource();
            QString property = e->getPropertyName();
            if (log->isDebugEnabled()) {
                log->debug(tr("property = %1 source= %2").arg(property).arg(source->metaObject()->className()));
            }
            if (qobject_cast<OBlock*>(source) && property == ("deleted")) {
                _homeBlock->removePropertyChangeListener((PropertyChangeListener*)this);
                _parent->closingEvent(true);
            } else {
                makeList();
                fireContentsChanged(this, 0, 0);
                if (property == ("signalChange") || property ==("NameChange")) {
                    _parent->clearListSelection();
                }
            }
        }
//    }
    /*private*/ /*final*/ /*static*/ Logger* PortalList::log = LoggerFactory::getLogger("PortalList");
    /*private*/ /*final*/ /*static*/ Logger* PortalListModel::log = LoggerFactory::getLogger("PortalListModel");

