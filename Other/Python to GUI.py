from PyQt5 import QtCore, QtGui, QtWidgets
from lab3 import Ui_MainWindow
import sys
import json
import paho.mqtt.client as mqtt
import time
import pyqtgraph as pg
import numpy as np
 
broker_address="electsut.trueddns.com"
broker_port=27860
client = mqtt.Client("B6222932_1")
client.connect(broker_address,broker_port)
 
app = QtWidgets.QApplication(sys.argv)
MainWindow = QtWidgets.QMainWindow()
class mylab3(Ui_MainWindow):
    def __init__(self) -> None:
        super().setupUi(MainWindow)
        self.gcn()
    def gcn(self):
        pass
if __name__ == "__main__":
    ui = mylab3()
    MainWindow.show()
    sys.exit(app.exec_())