#include "namecomponentchooser.h"

NameComponentChooser::NameComponentChooser(QObject *parent) : QObject(parent)
{

}

#if 0
/*public*/ class NameComponentChooser implements ComponentChooser {

    private String name;
    private Operator.StringComparator comparator;

    /*public*/ NameComponentChooser(String name, Operator.StringComparator comparator) {
        // <editor-fold defaultstate="collapsed" desc="Compiled Code">
        /* 0: aload_0
         * 1: invokespecial java/lang/Object."<init>":()V
         * 4: aload_0
         * 5: aload_1
         * 6: putfield      org/netbeans/jemmy/util/NameComponentChooser.name:Ljava/lang/String;
         * 9: aload_0
         * 10: aload_2
         * 11: putfield      org/netbeans/jemmy/util/NameComponentChooser.comparator:Lorg/netbeans/jemmy/operators/Operator$StringComparator;
         * 14: return
         *  */
        // </editor-fold>
    }
#endif
    /*public*/ NameComponentChooser::NameComponentChooser(QString name) {
        // <editor-fold defaultstate="collapsed" desc="Compiled Code">
        /* 0: aload_0
         * 1: aload_1
         * 2: new           org/netbeans/jemmy/operators/Operator$DefaultStringComparator
         * 5: dup
         * 6: iconst_1
         * 7: iconst_1
         * 8: invokespecial org/netbeans/jemmy/operators/Operator$DefaultStringComparator."<init>":(ZZ)V
         * 11: invokespecial org/netbeans/jemmy/util/NameComponentChooser."<init>":(Ljava/lang/String;Lorg/netbeans/jemmy/operators/Operator$StringComparator;)V
         * 14: return
         *  */
        // </editor-fold>
    }
#if 0
    /*public*/ boolean checkComponent(Component component) {
        // <editor-fold defaultstate="collapsed" desc="Compiled Code">
        /* 0: aload_0
         * 1: getfield      org/netbeans/jemmy/util/NameComponentChooser.comparator:Lorg/netbeans/jemmy/operators/Operator$StringComparator;
         * 4: aload_1
         * 5: invokevirtual java/awt/Component.getName:()Ljava/lang/String;
         * 8: aload_0
         * 9: getfield      org/netbeans/jemmy/util/NameComponentChooser.name:Ljava/lang/String;
         * 12: invokeinterface org/netbeans/jemmy/operators/Operator$StringComparator.equals:(Ljava/lang/String;Ljava/lang/String;)Z
         * 17: ireturn
         *  */
        // </editor-fold>
    }

    /*public*/ String getDescription() {
        // <editor-fold defaultstate="collapsed" desc="Compiled Code">
        /* 0: new           java/lang/StringBuilder
         * 3: dup
         * 4: invokespecial java/lang/StringBuilder."<init>":()V
         * 7: ldc           Component having \"
         * 9: invokevirtual java/lang/StringBuilder.append:(Ljava/lang/String;)Ljava/lang/StringBuilder;
         * 12: aload_0
         * 13: getfield      org/netbeans/jemmy/util/NameComponentChooser.name:Ljava/lang/String;
         * 16: invokevirtual java/lang/StringBuilder.append:(Ljava/lang/String;)Ljava/lang/StringBuilder;
         * 19: ldc           \" name.
         * 21: invokevirtual java/lang/StringBuilder.append:(Ljava/lang/String;)Ljava/lang/StringBuilder;
         * 24: invokevirtual java/lang/StringBuilder.toString:()Ljava/lang/String;
         * 27: areturn
         *  */
        // </editor-fold>
    }

    /*public*/ String toString() {
        // <editor-fold defaultstate="collapsed" desc="Compiled Code">
        /* 0: new           java/lang/StringBuilder
         * 3: dup
         * 4: invokespecial java/lang/StringBuilder."<init>":()V
         * 7: ldc           NameComponentChooser{name=
         * 9: invokevirtual java/lang/StringBuilder.append:(Ljava/lang/String;)Ljava/lang/StringBuilder;
         * 12: aload_0
         * 13: getfield      org/netbeans/jemmy/util/NameComponentChooser.name:Ljava/lang/String;
         * 16: invokevirtual java/lang/StringBuilder.append:(Ljava/lang/String;)Ljava/lang/StringBuilder;
         * 19: ldc           , comparator=
         * 21: invokevirtual java/lang/StringBuilder.append:(Ljava/lang/String;)Ljava/lang/StringBuilder;
         * 24: aload_0
         * 25: getfield      org/netbeans/jemmy/util/NameComponentChooser.comparator:Lorg/netbeans/jemmy/operators/Operator$StringComparator;
         * 28: invokevirtual java/lang/StringBuilder.append:(Ljava/lang/Object;)Ljava/lang/StringBuilder;
         * 31: bipush        125
         * 33: invokevirtual java/lang/StringBuilder.append:(C)Ljava/lang/StringBuilder;
         * 36: invokevirtual java/lang/StringBuilder.toString:()Ljava/lang/String;
         * 39: areturn
         *  */
        // </editor-fold>
    }
}
#endif
