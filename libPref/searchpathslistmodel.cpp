#include "searchpathslistmodel.h"
#include "profilemanager.h"
#include "rosterentry.h"

//SearchPathsListModel::SearchPathsListModel(QObject *parent) :
//    AbstractListModel(parent)
//{
//}
/**
 *
 * @author rhwood
 */
///*public*/ class SearchPathsListModel extends AbstractListModel {

    /**
     *
     */
//	/*private*/ static final long serialVersionUID = 6765348859634258763L;

/*public*/ SearchPathsListModel::SearchPathsListModel(QObject *parent) :
    AbstractListModel(parent)
{
 ProfileManager::getDefault()->addPropertyChangeListener(ProfileManager::SEARCH_PATHS, new PropertyChangeListener());
    //connect(ProfileManager::getDefault(), SIGNAL(indexedPropertyChange(IndexedPropertyChangeEvent*)), this, SLOT(propertyChange(IndexedPropertyChangeEvent*)));

}
//    @Override
/*public*/ void SearchPathsListModel::propertyChange(IndexedPropertyChangeEvent* evt)
{
//  if (evt instanceof IndexedPropertyChangeEvent
//                && evt.getSource().equals(ProfileManager.getDefault()))
 if(qobject_cast<IndexedPropertyChangeEvent*>(evt) != NULL && evt->getSource() == ProfileManager::getDefault())
 {
  if (evt->getOldValue() == QVariant())
  {
   fireIntervalAdded(((IndexedPropertyChangeEvent*) evt)->getIndex(), ((IndexedPropertyChangeEvent*) evt)->getIndex());
  }
  else if (evt->getNewValue() == QVariant())
  {
   fireIntervalRemoved(((IndexedPropertyChangeEvent*) evt)->getIndex(), ((IndexedPropertyChangeEvent*) evt)->getIndex());
  }
  fireContentsChanged(((IndexedPropertyChangeEvent*) evt)->getIndex(), ((IndexedPropertyChangeEvent*) evt)->getIndex());
 }
}

//@Override
/*public*/ int SearchPathsListModel::getSize()
{
 return ProfileManager::getDefault()->getSearchPaths().length();
}
int SearchPathsListModel::rowCount(const QModelIndex &/*parent*/) const
{
 return ProfileManager::getDefault()->getSearchPaths().length();
}
//@Override
/*public*/ QVariant SearchPathsListModel::data(const QModelIndex &index, int role) const
{
 if(role == Qt::DisplayRole)
 {
  return ProfileManager::getDefault()->getSearchPaths(index.row())->getPath();
 }
 return QVariant();
}

/*private*/ void SearchPathsListModel::fireContentsChanged(int index0, int index1)
{
 AbstractListModel::fireContentsChanged(this, index0, index1);
}

/*private*/ void SearchPathsListModel::fireIntervalAdded(int index0, int index1)
{
 AbstractListModel::fireIntervalAdded(this, index0, index1);
}

/*private*/ void SearchPathsListModel::fireIntervalRemoved(int index0, int index1)
{
 AbstractListModel::fireIntervalRemoved(this, index0, index1);
}
