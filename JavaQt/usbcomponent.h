#ifndef USBCOMPONENT_H
#define USBCOMPONENT_H
#include <QString>


/*public*/ /*static*/ class POV {
#if 0
    /*public*/ static /*final*/ float OFF = 0.0F;
    /*public*/ static /*final*/ float CENTER = 0.0F;
    /*public*/ static /*final*/ float UP_LEFT = 0.125F;
    /*public*/ static /*final*/ float UP = 0.25F;
    /*public*/ static /*final*/ float UP_RIGHT = 0.375F;
    /*public*/ static /*final*/ float RIGHT = 0.5F;
    /*public*/ static /*final*/ float DOWN_RIGHT = 0.625F;
    /*public*/ static /*final*/ float DOWN = 0.75F;
    /*public*/ static /*final*/ float DOWN_LEFT = 0.875F;
    /*public*/ static /*final*/ float LEFT = 1.0F;
#endif
    /*public*/ POV() {
        // <editor-fold defaultstate="collapsed" desc="Compiled Code">
        /* 0: aload_0
         * 1: invokespecial java/lang/Object."<init>":()V
         * 4: return
         *  */
        // </editor-fold>
    }
}; // end class POV

/*public*/ /*interface*/class UsbComponent
{
public:
 /*public*/ /*static*/ class Identifier
 {
  /*private*/ /*final*/ QString name;

 public:
  /*public*/ /*static*/ class Key /*: public Identifier*/ {
  enum KEYS
  {
    VOID,
    ESCAPE,
    _1,
    _2,
    _3,
    _4,
    _5,
    _6,
    _7,
    _8,
    _9,
    _0,
    MINUS,
    EQUALS,
    BACK,
    TAB,
    Q,
    W,
    E,
    R,
    T,
    Y,
    U,
    I,
    O,
    P,
    LBRACKET,
    RBRACKET,
    RETURN,
    LCONTROL,
    A,
    S,
    D,
    F,
    G,
    H,
    J,
    K,
    L,
    SEMICOLON,
    APOSTROPHE,
    GRAVE,
    LSHIFT,
    BACKSLASH,
    Z,
    X,
    C,
    V,
    B,
    N,
    M,
    COMMA,
    PERIOD,
    SLASH,
    RSHIFT,
    MULTIPLY,
    LALT,
    SPACE,
    CAPITAL,
    F1,
    F2,
    F3,
    F4,
    F5,
    F6,
    F7,
    F8,
    F9,
    F10,
    NUMLOCK,
    SCROLL,
    NUMPAD7,
    NUMPAD8,
    NUMPAD9,
    SUBTRACT,
    NUMPAD4,
    NUMPAD5,
    NUMPAD6,
    ADD,
    NUMPAD1,
    NUMPAD2,
    NUMPAD3,
    NUMPAD0,
    DECIMAL,
    F11,
    F12,
    F13,
    F14,
    F15,
    KANA,
    CONVERT,
    NOCONVERT,
    YEN,
    NUMPADEQUAL,
    CIRCUMFLEX,
    AT,
    COLON,
    UNDERLINE,
    KANJI,
    STOP,
    AX,
    UNLABELED,
    NUMPADENTER,
    RCONTROL,
    NUMPADCOMMA,
    DIVIDE,
    SYSRQ,
    RALT,
    PAUSE,
    HOME,
    UP,
    PAGEUP,
    LEFT,
    RIGHT,
    END,
    DOWN,
    PAGEDOWN,
    INSERT,
    DELETE,
    LWIN,
    RWIN,
    APPS,
    POWER,
    SLEEP,
    UNKNOWN
  };
  protected:
      /*protected*/ Key(QString name) {
          // <editor-fold defaultstate="collapsed" desc="Compiled Code">
          /* 0: aload_0
           * 1: aload_1
           * 2: invokespecial net/java/games/input/Component$Identifier."<init>":(Ljava/lang/String;)V
           * 5: return
           *  */
          // </editor-fold>
      }
  }; // end class Key
  Identifier() {}

  /*public*/ QString getName() {
      // <editor-fold defaultstate="collapsed" desc="Compiled Code">
      /* 0: aload_0
       * 1: getfield      net/java/games/input/Component$Identifier.name:Ljava/lang/String;
       * 4: areturn
       *  */
      // </editor-fold>
  }

  /*public*/ QString toString() {
      // <editor-fold defaultstate="collapsed" desc="Compiled Code">
      /* 0: aload_0
       * 1: getfield      net/java/games/input/Component$Identifier.name:Ljava/lang/String;
       * 4: areturn
       *  */
      // </editor-fold>
  }
 protected:
  /*protected*/ Identifier(QString name) {
      // <editor-fold defaultstate="collapsed" desc="Compiled Code">
      /* 0: aload_0
       * 1: invokespecial java/lang/Object."<init>":()V
       * 4: aload_0
       * 5: aload_1
       * 6: putfield      net/java/games/input/Component$Identifier.name:Ljava/lang/String;
       * 9: return
       *  */
      // </editor-fold>
   }
 }; // end class Identifier



 /*public*/ /*static*/ class Button : public Identifier
 {
 public:
 #if 0
     /*public*/ static /*final*/ Button _0;
     /*public*/ static /*final*/ Button _1;
     /*public*/ static /*final*/ Button _2;
     /*public*/ static /*final*/ Button _3;
     /*public*/ static /*final*/ Button _4;
     /*public*/ static /*final*/ Button _5;
     /*public*/ static /*final*/ Button _6;
     /*public*/ static /*final*/ Button _7;
     /*public*/ static /*final*/ Button _8;
     /*public*/ static /*final*/ Button _9;
     /*public*/ static /*final*/ Button _10;
     /*public*/ static /*final*/ Button _11;
     /*public*/ static /*final*/ Button _12;
     /*public*/ static /*final*/ Button _13;
     /*public*/ static /*final*/ Button _14;
     /*public*/ static /*final*/ Button _15;
     /*public*/ static /*final*/ Button _16;
     /*public*/ static /*final*/ Button _17;
     /*public*/ static /*final*/ Button _18;
     /*public*/ static /*final*/ Button _19;
     /*public*/ static /*final*/ Button _20;
     /*public*/ static /*final*/ Button _21;
     /*public*/ static /*final*/ Button _22;
     /*public*/ static /*final*/ Button _23;
     /*public*/ static /*final*/ Button _24;
     /*public*/ static /*final*/ Button _25;
     /*public*/ static /*final*/ Button _26;
     /*public*/ static /*final*/ Button _27;
     /*public*/ static /*final*/ Button _28;
     /*public*/ static /*final*/ Button _29;
     /*public*/ static /*final*/ Button _30;
     /*public*/ static /*final*/ Button _31;
     /*public*/ static /*final*/ Button _32;
     /*public*/ static /*final*/ Button _33;
     /*public*/ static /*final*/ Button _34;
     /*public*/ static /*final*/ Button _35;
     /*public*/ static /*final*/ Button _36;
     /*public*/ static /*final*/ Button _37;
     /*public*/ static /*final*/ Button _38;
     /*public*/ static /*final*/ Button _39;
     /*public*/ static /*final*/ Button _40;
     /*public*/ static /*final*/ Button _41;
     /*public*/ static /*final*/ Button _42;
     /*public*/ static /*final*/ Button _43;
     /*public*/ static /*final*/ Button _44;
     /*public*/ static /*final*/ Button _45;
     /*public*/ static /*final*/ Button _46;
     /*public*/ static /*final*/ Button _47;
     /*public*/ static /*final*/ Button _48;
     /*public*/ static /*final*/ Button _49;
     /*public*/ static /*final*/ Button TRIGGER;
     /*public*/ static /*final*/ Button THUMB;
     /*public*/ static /*final*/ Button THUMB2;
     /*public*/ static /*final*/ Button TOP;
     /*public*/ static /*final*/ Button TOP2;
     /*public*/ static /*final*/ Button PINKIE;
     /*public*/ static /*final*/ Button BASE;
     /*public*/ static /*final*/ Button BASE2;
     /*public*/ static /*final*/ Button BASE3;
     /*public*/ static /*final*/ Button BASE4;
     /*public*/ static /*final*/ Button BASE5;
     /*public*/ static /*final*/ Button BASE6;
     /*public*/ static /*final*/ Button DEAD;
     /*public*/ static /*final*/ Button A;
     /*public*/ static /*final*/ Button B;
     /*public*/ static /*final*/ Button C;
     /*public*/ static /*final*/ Button X;
     /*public*/ static /*final*/ Button Y;
     /*public*/ static /*final*/ Button Z;
     /*public*/ static /*final*/ Button LEFT_THUMB;
     /*public*/ static /*final*/ Button RIGHT_THUMB;
     /*public*/ static /*final*/ Button LEFT_THUMB2;
     /*public*/ static /*final*/ Button RIGHT_THUMB2;
     /*public*/ static /*final*/ Button SELECT;
     /*public*/ static /*final*/ Button MODE;
     /*public*/ static /*final*/ Button LEFT_THUMB3;
     /*public*/ static /*final*/ Button RIGHT_THUMB3;
     /*public*/ static /*final*/ Button TOOL_PEN;
     /*public*/ static /*final*/ Button TOOL_RUBBER;
     /*public*/ static /*final*/ Button TOOL_BRUSH;
     /*public*/ static /*final*/ Button TOOL_PENCIL;
     /*public*/ static /*final*/ Button TOOL_AIRBRUSH;
     /*public*/ static /*final*/ Button TOOL_FINGER;
     /*public*/ static /*final*/ Button TOOL_MOUSE;
     /*public*/ static /*final*/ Button TOOL_LENS;
     /*public*/ static /*final*/ Button TOUCH;
     /*public*/ static /*final*/ Button STYLUS;
     /*public*/ static /*final*/ Button STYLUS2;
     /*public*/ static /*final*/ Button UNKNOWN;
     /*public*/ static /*final*/ Button BACK;
     /*public*/ static /*final*/ Button EXTRA;
     /*public*/ static /*final*/ Button FORWARD;
     /*public*/ static /*final*/ Button LEFT;
     /*public*/ static /*final*/ Button MIDDLE;
     /*public*/ static /*final*/ Button RIGHT;
     /*public*/ static /*final*/ Button SIDE;
 #endif
     /*public*/ Button(QString name) {
         // <editor-fold defaultstate="collapsed" desc="Compiled Code">
         /* 0: aload_0
          * 1: aload_1
          * 2: invokespecial net/java/games/input/Component$Identifier."<init>":(Ljava/lang/String;)V
          * 5: return
          *  */
         // </editor-fold>
     }
 }; // end class Button

 /*public*/ /*static*/ class Axis : public Identifier {
 public:
 #if 0
     /*public*/ static /*final*/ Axis X;
     /*public*/ static /*final*/ Axis Y;
     /*public*/ static /*final*/ Axis Z;
     /*public*/ static /*final*/ Axis RX;
     /*public*/ static /*final*/ Axis RY;
     /*public*/ static /*final*/ Axis RZ;
     /*public*/ static /*final*/ Axis SLIDER;
     /*public*/ static /*final*/ Axis SLIDER_ACCELERATION;
     /*public*/ static /*final*/ Axis SLIDER_FORCE;
     /*public*/ static /*final*/ Axis SLIDER_VELOCITY;
     /*public*/ static /*final*/ Axis X_ACCELERATION;
     /*public*/ static /*final*/ Axis X_FORCE;
     /*public*/ static /*final*/ Axis X_VELOCITY;
     /*public*/ static /*final*/ Axis Y_ACCELERATION;
     /*public*/ static /*final*/ Axis Y_FORCE;
     /*public*/ static /*final*/ Axis Y_VELOCITY;
     /*public*/ static /*final*/ Axis Z_ACCELERATION;
     /*public*/ static /*final*/ Axis Z_FORCE;
     /*public*/ static /*final*/ Axis Z_VELOCITY;
     /*public*/ static /*final*/ Axis RX_ACCELERATION;
     /*public*/ static /*final*/ Axis RX_FORCE;
     /*public*/ static /*final*/ Axis RX_VELOCITY;
     /*public*/ static /*final*/ Axis RY_ACCELERATION;
     /*public*/ static /*final*/ Axis RY_FORCE;
     /*public*/ static /*final*/ Axis RY_VELOCITY;
     /*public*/ static /*final*/ Axis RZ_ACCELERATION;
     /*public*/ static /*final*/ Axis RZ_FORCE;
     /*public*/ static /*final*/ Axis RZ_VELOCITY;
     /*public*/ static /*final*/ Axis POV;
     /*public*/ static /*final*/ Axis UNKNOWN;
     /*public*/ static /*final*/ Axis _0;
     /*public*/ static /*final*/ Axis _1;
     /*public*/ static /*final*/ Axis _2;
     /*public*/ static /*final*/ Axis _3;
     /*public*/ static /*final*/ Axis _4;
     /*public*/ static /*final*/ Axis _5;
     /*public*/ static /*final*/ Axis _6;
     /*public*/ static /*final*/ Axis _7;
     /*public*/ static /*final*/ Axis _8;
     /*public*/ static /*final*/ Axis _9;
     /*public*/ static /*final*/ Axis _10;
     /*public*/ static /*final*/ Axis _11;
     /*public*/ static /*final*/ Axis _12;
     /*public*/ static /*final*/ Axis _13;
     /*public*/ static /*final*/ Axis _14;
     /*public*/ static /*final*/ Axis _15;
     /*public*/ static /*final*/ Axis _16;
     /*public*/ static /*final*/ Axis _17;
     /*public*/ static /*final*/ Axis _18;
     /*public*/ static /*final*/ Axis _19;
     /*public*/ static /*final*/ Axis _20;
     /*public*/ static /*final*/ Axis _21;
     /*public*/ static /*final*/ Axis _22;
     /*public*/ static /*final*/ Axis _23;
     /*public*/ static /*final*/ Axis _24;
     /*public*/ static /*final*/ Axis _25;
     /*public*/ static /*final*/ Axis _26;
     /*public*/ static /*final*/ Axis _27;
     /*public*/ static /*final*/ Axis _28;
     /*public*/ static /*final*/ Axis _29;
 #endif
     /*protected*/ Axis(QString name) {
         // <editor-fold defaultstate="collapsed" desc="Compiled Code">
         /* 0: aload_0
          * 1: aload_1
          * 2: invokespecial net/java/games/input/Component$Identifier."<init>":(Ljava/lang/String;)V
          * 5: return
          *  */
         // </editor-fold>
     }

 }; // end class Axis

    /*public*/ virtual Identifier* getIdentifier() {return NULL;}

    /*public*/ virtual bool isRelative() {return false;}

    /*public*/ virtual bool isAnalog() {return false;}

    /*public*/ virtual float getDeadZone() {return 0.0;}

    /*public*/ virtual float getPollData() {return 0.0;}

    /*public*/ virtual QString getName() {return "";}
};

#endif // USBCOMPONENT_H
