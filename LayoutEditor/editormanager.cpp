#include "editormanager.h"
#include "editor.h"

EditorManager::EditorManager(QObject *parent) : QObject(parent)
{

}
///*public*/ class EditorManager implements InstanceManagerAutoDefault {

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
        return QList<Editor*>(this->editors.toList());
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
        if(!editors.contains(editor))
        {
         this->editors.insert(editor);
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
        return this->editors.remove(editor);
    }
