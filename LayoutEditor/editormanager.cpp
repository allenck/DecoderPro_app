#include "editormanager.h"
#include "editor.h"
#include "vptr.h"
#include "class.h"

EditorManager::EditorManager(QObject *parent) : Bean(parent)
{

}
///*public*/ class EditorManager implements InstanceManagerAutoDefault {

/*public*/ /*static*/ /*final*/ QString EditorManager::EDITORS = "editors";
/*public*/ /*static*/ /*final*/ QString EditorManager::TITLE = "title";
/**
 * Add an editor to this manager.
 *
 * @param editor the editor to add
 */
/*public*/ void EditorManager::add(/*@Nonnull*/ Editor* editor) {
    //bool result = set.insert(editor);
    QSet<Editor*>::iterator it = set.insert(editor);
    //if (result)
//    if(it)
//    {
//        fireIndexedPropertyChange(EDITORS, set.size(), QVariant(), VPtr<Editor>::asQVariant(editor));
//        editor->addPropertyChangeListener(TITLE, this);
//    }
}

/**
 * Check if an editor is in the manager.
 *
 * @param editor the editor to check for
 * @return true if this manager contains an editor with name; false
 * otherwise
 */
/*public*/ bool EditorManager::contains(/*@Nonnull*/ Editor* editor) {
    return set.contains(editor);
}
/**
 * Check if an editor with the specified name is in the manager.
 *
 * @param name the name to check for
 * @return true if this manager contains an editor with name; false
 * otherwise
 */
/*public*/ bool EditorManager::contains(QString name) {
    return get(name) != nullptr;
}

/**
 * Get all managed editors. This set is sorted by the title of the editor.
 *
 * @return the set of all editors
 */
//@Nonnull
/*public*/ QSet<Editor*> EditorManager::getAll() {
    return QSet<Editor*>(set);
}
#if 1
/**
 * Get all managed editors that implement the specified type. This set is
 * sorted by the title of the editor.
 *
 * @param <T> the specified type
 * @param type the specified type
 * @return the set of all editors of the specified type
 */
//@Nonnull
/*public*/ /*<T extends Editor>*/ QSet<Editor*> EditorManager::getAll(/*@Nonnull Class<T>*/QString type) {
//    return set.stream()
//            .filter(e -> type.isAssignableFrom(e.getClass()))
//            .map(type::cast)
//            .collect(Collectors.toCollection(() -> new TreeSet<>(Comparator.comparing(Editor::getTitle))));
 QSet<Editor*> myset = QSet<Editor*>();
 for( Editor* e : set)
 {
  Class* clazz = (Class*)e;
  if(clazz->isAssignableFrom(type))
   myset.insert(e);
 }
 return myset;
}
#endif
/**
 * Get the editor with the given name.
 *
 * @param name the name of the editor
 * @return the editor with the given name or null if no editor by that name
 * exists
 */
//@CheckForNull
/*public*/ Editor* EditorManager::get(/*@Nonnull*/ QString name) {
    //return getAll().stream().filter(e -> e.getTitle().equals(name)).findFirst().orElse(null);
    foreach (Editor* e, getAll()) {
        if(e->getTitle() == name)
            return e;
    }
    return nullptr;
}

/**
 * Get the editor with the given name and type.
 *
 * @param <T> the type of the editor
 * @param type the type of the editor
 * @param name the name of the editor
 * @return the editor with the given name or null if no editor by that name
 * exists
 */
//@CheckForNull

/*public*/ /*<T extends Editor>*/ QObject* EditorManager::get(/*@Nonnull*/ QString type, /*@Nonnull*/ QString name) {
//    return type.cast(set.stream()
//            .filter(e -> e.getClass().isAssignableFrom(type) && e.getTitle().equals(name))
//            .findFirst().orElse(null));
 Class* obj = Class::forName(type);
return (QObject*)obj;
}
#if 0
    /*private*/ /*final*/ SortedSet<Editor> editors = new TreeSet<>(new Comparator<Editor>() {

        @Override
        /*public*/ int compare(Editor o1, Editor o2) {
            return o1.getTitle().compareTo(o2.getTitle());
        }
    });
#endif
    /**
     * Get a List of the currently-existing Editor objects. The returned list is
     * a copy made at the time of the call, so it can be manipulated as needed
     * by the caller.
     *
     * @return a List of Editors
     */
    /*synchronized*/ /*public*/ QList<Editor *> EditorManager::getEditorsList() {
        return QList<Editor*>(this->set.toList());
    }
#if 0
    /**
     * Get a list of currently-existing Editor objects that are specific
     * sub-classes of Editor.
     * <p>
     * The returned list is a copy made at the time of the call, so it can be
     * manipulated as needed by the caller.
     *
     * @param type the Class the list should be limited to.
     * @return a List of Editors.
     */
    @SuppressWarnings("unchecked")
    synchronized /*public*/ <T extends Editor> List<T> getEditorsList(@Nonnull Class<T> type) {
        List<T> result = new ArrayList<>();
        for (Editor e : this.getEditorsList()) {
            if (type.isInstance(e)) {
                result.add((T) e);
            }
        }
        return result;
    }
#else
     /*public*/ QList<Editor*> EditorManager::getEditorsList(QString type)
     {
      QList<Editor*> result = QList<Editor*>();
      for (Editor* e : this->getEditorsList()) {
          if (e->metaObject()->className() == type) {
              result.append( e);
          }
      }
      return result;

     }
#endif
    /**
     * Get an Editor of a particular name. If more than one exists, there's no
     * guarantee as to which is returned.
     *
     * @param name the editor to get
     * @return the first matching Editor or null if no matching Editor could be
     *         found
     */
    /*public*/ Editor* EditorManager::getEditor(QString name) {
        for (Editor* e : this->getEditorsList()) {
            if (e->getTitle() == (name)) {
                return e;
            }
        }
        return nullptr;
    }

    /**
     * Add an Editor to the set of Editors. This only changes the set of Editors
     * if the Editor is not already in the set.
     *
     * @param editor the editor to add
     * @return true if the set was changed; false otherwise
     */
    /*public*/ bool EditorManager::addEditor(/*@Nonnull*/ Editor* editor) {
        if(!set.contains(editor))
        {
         this->set.insert(editor);
         return true;
        }
        return false;
    }

    /**
     * Add an Editor from the set of Editors. This only changes the set of
     * Editors if the Editor is in the set.
     *
     * @param editor the editor to remove
     * @return true if the set was changed; false otherwise
     */
    /*public*/ bool EditorManager::removeEditor(/*@Nonnull*/ Editor* editor) {
        return this->set.remove(editor);
    }
/**
 * Remove an editor from this manager.
 *
 * @param editor the editor to remove
 */
/*public*/ void EditorManager::remove(/*@Nonnull*/ Editor* editor) {
    bool result = set.remove(editor);
    if (result) {
        fireIndexedPropertyChange(EDITORS, set.size(), VPtr<Editor>::asQVariant(editor), QVariant());
        editor->removePropertyChangeListener(TITLE, (PropertyChangeListener*)this);
    }
}
