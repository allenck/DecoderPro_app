#include "jtabbedpane.h"
#include <QTabBar>
#include <QToolButton>
#include <QIcon>

JTabbedPane::JTabbedPane(QWidget* parent) : QTabWidget(parent)
{
 
}

void JTabbedPane::setTabButton(int iTab, QToolButton * button)
{
 tabBar()->setTabButton(iTab, QTabBar::RightSide, button);
}

/**
 * Returns the first tab index with a given <code>title</code>,  or
 * -1 if no tab has this title.
 *
 * @param title the title for the tab
 * @return the first tab index which matches <code>title</code>, or
 *          -1 if no tab has this title
 */
/*public*/ int JTabbedPane::indexOfTab(QString title) {
    for(int i = 0; i < count(); i++) {
        if (tabText(i)==(title == "" ? "" : title)) {
            return i;
        }
    }
    return -1;
}

/**
 * Returns the first tab index with a given <code>icon</code>,
 * or -1 if no tab has this icon.
 *
 * @param icon the icon for the tab
 * @return the first tab index which matches <code>icon</code>,
 *          or -1 if no tab has this icon
 */
/*public*/ int JTabbedPane::indexOfTab(QIcon& icon)
{
 for(int i = 0; i < count(); i++)
 {
  QIcon _tabIcon = tabIcon(i);
  if(!_tabIcon.isNull())
  {
   QByteArray a1;
   QDataStream stream1(&a1, QIODevice::WriteOnly);
   stream1 << _tabIcon;

   QByteArray a2;
   QDataStream stream2(&a2, QIODevice::WriteOnly);
   stream2 << icon;

   if( a1 == a2)
    return i;
  }
 }
 return -1;
}

/**
 * Adds a <code>component</code> and <code>tip</code>
 * represented by a <code>title</code> and/or <code>icon</code>,
 * either of which can be <code>null</code>.
 * Cover method for <code>insertTab</code>.
 *
 * @param title the title to be displayed in this tab
 * @param icon the icon to be displayed in this tab
 * @param component the component to be displayed when this tab is clicked
 * @param tip the tooltip to be displayed for this tab
 *
 * @see #insertTab
 * @see #removeTabAt
 */
/*public*/ void JTabbedPane::addTab(QString title, QIcon icon, QWidget* component, QString tip) {
    insertTab(title, icon, component, tip, count());
}

/**
 * Adds a <code>component</code> represented by a <code>title</code>
 * and/or <code>icon</code>, either of which can be <code>null</code>.
 * Cover method for <code>insertTab</code>.
 *
 * @param title the title to be displayed in this tab
 * @param icon the icon to be displayed in this tab
 * @param component the component to be displayed when this tab is clicked
 *
 * @see #insertTab
 * @see #removeTabAt
 */
/*public*/ void JTabbedPane::addTab(QString title, QIcon icon, QWidget* component) {
    insertTab(title, icon, component, "", count());
}

/**
 * Adds a <code>component</code> represented by a <code>title</code>
 * and no icon.
 * Cover method for <code>insertTab</code>.
 *
 * @param title the title to be displayed in this tab
 * @param component the component to be displayed when this tab is clicked
 *
 * @see #insertTab
 * @see #removeTabAt
 */
/*public*/ void JTabbedPane::addTab(QString title, QWidget* component) {
    insertTab(title, QIcon(), component, "", count());
}

/**
 * Inserts a new tab for the given component, at the given index,
 * represented by the given title and/or icon, either of which may
 * be {@code null}.
 *
 * @param title the title to be displayed on the tab
 * @param icon the icon to be displayed on the tab
 * @param component the component to be displayed when this tab is clicked.
 * @param tip the tooltip to be displayed for this tab
 * @param index the position to insert this new tab
 *       ({@code > 0 and <= getTabCount()})
 *
 * @throws IndexOutOfBoundsException if the index is out of range
 *         ({@code < 0 or > getTabCount()})
 *
 * @see #addTab
 * @see #removeTabAt
 */
/*public*/ void JTabbedPane::insertTab(QString title, QIcon icon, QWidget* component, QString tip, int index) {
    int newIndex = index;

    // If component already exists, remove corresponding
    // tab so that new tab gets added correctly
    // Note: we are allowing component=null because of compatibility,
    // but we really should throw an exception because much of the
    // rest of the JTabbedPane implementation isn't designed to deal
    // with null components for tabs.
    int removeIndex = indexOfComponent(component);
    if (component != nullptr && removeIndex != -1) {
        removeTabAt(removeIndex);
        if (newIndex > removeIndex) {
            newIndex--;
        }
    }
    QTabWidget::insertTab(index,component,icon,title);    //(title,icon,component,tip,index);
    setTabToolTip(index,tip);
}
/**
 * Returns the index of the tab for the specified component.
 * Returns -1 if there is no tab for this component.
 *
 * @param component the component for the tab
 * @return the first tab which matches this component, or -1
 *          if there is no tab for this component
 */
/*public*/ int JTabbedPane::indexOfComponent(QWidget* component) {
    for(int i = 0; i < count(); i++) {
        QWidget* c = getComponentAt(i);
        if ((c != nullptr && c==(component))){
            return i;
        }
    }
    return -1;
}

/**
 * Removes the tab at <code>index</code>.
 * After the component associated with <code>index</code> is removed,
 * its visibility is reset to true to ensure it will be visible
 * if added to other containers.
 * @param index the index of the tab to be removed
 * @exception IndexOutOfBoundsException if index is out of range
 *            {@code (index < 0 || index >= tab count)}
 *
 * @see #addTab
 * @see #insertTab
 */
/*public*/ void JTabbedPane::removeTabAt(int index)
{
 this->removeTab(index);
}

/**
 * Returns the component at <code>index</code>.
 *
 * @param index  the index of the item being queried
 * @return the <code>Component</code> at <code>index</code>
 * @exception IndexOutOfBoundsException if index is out of range
 *            {@code (index < 0 || index >= tab count)}
 *
 * @see #setComponentAt
 */
/*public*/ QWidget* JTabbedPane::getComponentAt(int index) {
    return widget(index);
}

/**
 * Sets the selected index for this tabbedpane. The index must be
 * a valid tab index or -1, which indicates that no tab should be selected
 * (can also be used when there are no tabs in the tabbedpane).  If a -1
 * value is specified when the tabbedpane contains one or more tabs, then
 * the results will be implementation defined.
 *
 * @param index  the index to be selected
 * @exception IndexOutOfBoundsException if index is out of range
 *            {@code (index < -1 || index >= tab count)}
 *
 * @see #getSelectedIndex
 * @see SingleSelectionModel#setSelectedIndex
 * @beaninfo
 *   preferred: true
 * description: The tabbedpane's selected tab index.
 */
/*public*/ void JTabbedPane::setSelectedIndex(int index) {
 setCurrentIndex(index);
}

/*public*/ void JTabbedPane::setEnabledAt(int tabIndex, bool enabled)
{
 QTabWidget::setTabEnabled(tabIndex, enabled);
}
