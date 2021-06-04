#include "validatorborder.h"

// /*public*/ class ValidatorBorder extends CompoundBorder {

    //private static final long serialVersionUID = 1L;

/*public*/ ValidatorBorder::ValidatorBorder(/*@javax.annotation.Nonnull*/ Validation* vldtn, Border* border) : CompoundBorder(){
     // <editor-fold defaultstate="collapsed" desc="Compiled Code">
     /* 0: aload_0
      * 1: invokespecial javax/swing/border/CompoundBorder."<init>":()V
      * 4: aload_0
      * 5: aload_1
      * 6: putfield      com/alexandriasoftware/swing/border/ValidatorBorder.validation:Lcom/alexandriasoftware/swing/Validation;
      * 9: aload_0
      * 10: aload_0
      * 11: getfield      com/alexandriasoftware/swing/border/ValidatorBorder.validation:Lcom/alexandriasoftware/swing/Validation;
      * 14: invokevirtual com/alexandriasoftware/swing/Validation.getFont:()Ljava/awt/Font;
      * 17: iconst_1
      * 18: fconst_0
      * 19: invokevirtual java/awt/Font.deriveFont:(IF)Ljava/awt/Font;
      * 22: putfield      com/alexandriasoftware/swing/border/ValidatorBorder.font:Ljava/awt/Font;
      * 25: aload_0
      * 26: aload_2
      * 27: putfield      com/alexandriasoftware/swing/border/ValidatorBorder.outsideBorder:Ljavax/swing/border/Border;
      * 30: aload_0
      * 31: new           com/alexandriasoftware/swing/border/ValidatorBorder$1
      * 34: dup
      * 35: aload_0
      * 36: aload_1
      * 37: invokespecial com/alexandriasoftware/swing/border/ValidatorBorder$1."<init>":(Lcom/alexandriasoftware/swing/border/ValidatorBorder;Lcom/alexandriasoftware/swing/Validation;)V
      * 40: putfield      com/alexandriasoftware/swing/border/ValidatorBorder.insideBorder:Ljavax/swing/border/Border;
      * 43: return
      *  */
     // </editor-fold>
  this->validation = validation;
 }

/*private*/ QFontMetrics getFontMetrics(JComponent* cmpnt) {
 return QFontMetrics(((QWidget*)cmpnt->jself())->font());
}
