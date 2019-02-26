from PythonQt import *
from PythonQt import Jmri
from PythonQt.Jmri import InstanceManager
from PythonQt.Jmri import ProxyTurnoutManager
from PythonQt.Jmri import Turnout
from PythonQt.Jmri import Sensor
from PythonQt.Jmri import NamedBean
from PythonQt.Jmri import SignalHead
from PythonQt.Jmri import FileUtil

turnouts = InstanceManager.getDefault().proxyTurnoutManagerInstance()
sensors = InstanceManager.getDefault().proxySensorManagerInstance()
signals = InstanceManager.getDefault("SignalHeadManager")
masts = InstanceManager.getDefault("SignalMastManager")
lights = InstanceManager.getDefault().proxyLightManagerInstance()
dcc = InstanceManager.getDefault("CommandStation")
reporters = InstanceManager.getDefault().proxyReporterManagerInstance()
memories = InstanceManager.getDefault("MemoryManager")
routes = InstanceManager.getDefault("RouteManager")
blocks = InstanceManager.getDefault("BlockManager")
powermanager = InstanceManager.getDefault("PowerManager")
programmers = InstanceManager.getDefault("ProgrammerManager")
shutdown = InstanceManager.getDefault("ShutDownManager")
audio = InstanceManager.getDefault("AudioManager")
layoutblocks = InstanceManager.getDefault("LayoutBlockManager")
warrants = InstanceManager.getDefault("WarrantManager")
CLOSED = Turnout.CLOSED
THROWN = Turnout.THROWN
CABLOCKOUT = Turnout.CABLOCKOUT
PUSHBUTTONLOCKOUT = Turnout.PUSHBUTTONLOCKOUT
UNLOCKED = Turnout.UNLOCKED
LOCKED = Turnout.LOCKED
ACTIVE = Sensor.ACTIVE
INACTIVE = Sensor.INACTIVE
UNKNOWN = NamedBean.UNKNOWN
INCONSISTENT = NamedBean.INCONSISTENT
DARK = SignalHead.DARK
RED = SignalHead.RED
YELLOW = SignalHead.YELLOW
GREEN = SignalHead.GREEN
LUNAR = SignalHead.LUNAR
FLASHRED = SignalHead.FLASHRED
FLASHYELLOW = SignalHead.FLASHYELLOW
FLASHGREEN = SignalHead.FLASHGREEN
FLASHLUNAR = SignalHead.FLASHLUNAR
#FileUtil = FileUtil.instance()
