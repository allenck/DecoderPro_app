#include "managercombobox.h"
#include "defaultcomboboxmodel.h"
#include "vptr.h"
#include "instancemanager.h"
#include "manager.h"
#include "proxyturnoutmanager.h"
#include "proxyreportermanager.h"
#include "proxylightmanager.h"
/**
 * A JComboBox for a set of Managers for the same type of NamedBean.
 *
 * @author Randall Wood
 * @param <B> the type of NamedBean
 */
///*public*/ class ManagerComboBox<B extends NamedBean> extends JComboBox<Manager<B>> {

    /*public*/ ManagerComboBox::ManagerComboBox(QObject* parent) {
        //this(new QList<Manager/*<B>*/*>());
     this->setManagers(QList<AbstractManager/*<B>*/*>(), nullptr);
    }

    /*public*/ ManagerComboBox::ManagerComboBox(/*@Nonnull*/ QList<AbstractManager/*<B>*/*> list, QObject* parent) {
        //this(list, null);
     this->setManagers(list, nullptr);
    }

    /*public*/ ManagerComboBox::ManagerComboBox(/*@Nonnull*/ QList<AbstractManager/*<B>*/*> list, Manager/*<B>*/* selection, QObject* parent) {
        //super();
//        setRenderer(new ManagerRenderer(getRenderer()));
        // prevent overriding method from being used
        /*ManagerComboBox.*/this->setManagers(list, selection);
    }

    /**
     * Set the list of managers, selecting the first manager in the list.
     *
     * @param list the ,list of managers
     */
    /*public*/ void ManagerComboBox::setManagers(/*@Nonnull*/ QList<AbstractManager/*<B>*/*> list) {
        setManagers(list, nullptr);
    }

    /**
     * Set the list of managers, selecting the passed in manager.
     *
     * @param list      the list of managers
     * @param selection the manager to select; if null, the first manager in the
     *                  list is selected
     */
    /*public*/ void ManagerComboBox::setManagers(/*@Nonnull*/ QList<AbstractManager/*<B>*/*> list, Manager/*<B>*/* selection) {
        //setModel(new DefaultComboBoxModel<Manager*>( QVector<Manager*>(list.toVector())));
        foreach (Manager* m, list) {
         addItem(m->getMemo()->getUserName(), VPtr<Manager>::asQVariant(m));
         vl.append(VPtr<Manager>::asQVariant(m));
        }
        int i=0;
        for(QVariant v : vl)
         setItemData(i++, v, Qt::UserRole);
        if (!list.isEmpty()) {
            if (selection == nullptr) {
                setSelectedIndex(0);
            } else {
                //setSelectedItem(selection->toString());
                setSelectedItem(selection->getMemo()->getUserName());
            }
        }
    }

/*public*/ void ManagerComboBox::setManagers(/*@Nonnull*/ QList<Manager *> list, Manager/*<B>*/* selection)
{
 foreach (Manager* m, list) {
  addItem(m->getMemo()->getUserName(), VPtr<Manager>::asQVariant(m));
  vl.append(VPtr<Manager>::asQVariant(m));
 }
 int i=0;
 for(QVariant v : vl)
  setItemData(i++, v, Qt::UserRole);
 if (!list.isEmpty()) {
     if (selection == nullptr) {
         setSelectedIndex(0);
     } else {
         //setSelectedItem(selection->toString());
         setSelectedItem(selection->getMemo()->getUserName());
     }
 }
}

    /**
     * Set the list of managers to the single passed in manager, and select it.
     *
     * @param manager the manager; if manager is a {@link ProxyManager}, this is
     *                equivalent to calling {@link #setManagers(List, Manager)}
     *                with the results of
     *                {@link ProxyManager#getDisplayOrderManagerList()},
     *                {@link ProxyManager#getDefaultManager()}
     */
    /*public*/ void ManagerComboBox::setManagers(/*@Nonnull*/ Manager/*<B>*/* manager) {
        if (qobject_cast<ProxyManager*>(manager->mself())) {
            AbstractProxyManager/*<B>*/* proxy = (AbstractProxyManager/*<B>*/*) manager->mself();
            setManagers(proxy->getDisplayOrderManagerList(), proxy->getDefaultManager());
//            if(qobject_cast<ProxyTurnoutManager*>(manager->mself()))
//            //setManagers(proxy.getDisplayOrderManagerList(), proxy.getDefaultManager());
//             setManagers(((ProxyTurnoutManager*)manager->mself())->getDisplayOrderManagerList(), ((ProxyTurnoutManager*)manager->mself())->getDefaultManager());
//            if(qobject_cast<ProxySensorManager*>(manager->mself()))
//             setManagers(((ProxySensorManager*)manager->mself())->getDisplayOrderManagerList(), ((ProxySensorManager*)manager->mself())->getDefaultManager());
//            if(qobject_cast<ProxyLightManager*>(manager->mself()))
//             setManagers(((ProxyLightManager*)manager->mself())->getDisplayOrderManagerList(), ((ProxyLightManager*)manager->mself())->getDefaultManager());
//            if(qobject_cast<ProxyReporterManager*>(manager->mself()))
//             setManagers(((ProxyReporterManager*)manager->mself())->getDisplayOrderManagerList(), ((ProxyReporterManager*)manager->mself())->getDefaultManager());
        } else {
            QList<AbstractManager/*<B>*/*> list = QList<AbstractManager/*<B>*/*>();
            list.append((AbstractManager*)manager->mself());
            setManagers(list, manager);
        }
    }

    /**
     * {@inheritDoc}
     */
    //@Override
    /*public*/ Manager/*<B>*/* ManagerComboBox::getSelectedItem() {
        return VPtr<Manager>::asPtr(getItemAt(getSelectedIndex()));
    }

    /*public*/ void ManagerComboBox::setName(QString s)
    {
     setObjectName(s);
    }

//    /*public*/ void ManagerComboBox::setSelectedItem(QString t)
//    {
//     Manager* mgr = (Manager*)InstanceManager::getDefault(t);
//     JComboBox::setSelectedItem(t);
//    }
#if 0
    /*private*/ class ManagerRenderer implements ListCellRenderer<Manager<B>> {

        /*private*/ final ListCellRenderer<? super Manager<B>> renderer;

        /*public*/ ManagerRenderer(ListCellRenderer<? super Manager<B>> renderer) {
            this.renderer = renderer;
        }

        @Override
        /*public*/ Component getListCellRendererComponent(JList<? extends Manager<B>> list, Manager<B> value, int index,
                boolean isSelected, boolean cellHasFocus) {
            JLabel label = (JLabel) renderer.getListCellRendererComponent(list, value, index, isSelected, cellHasFocus);
            if (value != null) {
                label.setText(value.getMemo().getUserName());
            }
            return label;
        }
    }
#endif
