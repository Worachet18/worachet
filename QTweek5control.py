from http import client
from PyQt5 import QtCore, QtGui, QtWidgets

import paho.mqtt.client as mqtt
import json
broker_address='electsut.trueddns.com'
broker_port=27860
client=mqtt.Client("B6214197")
client.connect(broker_address,broker_port)

import sys
app = QtWidgets.QApplication(sys.argv)
MainWindow = QtWidgets.QMainWindow()
from QTweek5 import Ui_MainWindow
class  myledcontrol(Ui_MainWindow):
    def __init__(self) -> None:
        super().setupUi(MainWindow)
        self.gcn()
        self.x='{}'
        self.s=json.loads(self.x)
    def gcn(self):
        self.pushButton.clicked.connect(self.onclick)
        self.pushButton_2.clicked.connect(self.offclick)
    def onclick(self):
        print("ON")
        self.s["LED"]=1
        self.s["state"]="on"
        self.y=json.dumps(self.s)
        client.publish("inno/B6214197/lighting",self.y)
    def offclick(self):
        print("OFF")
        self.s["LED"]=0
        self.s["state"]="off"
        self.y=json.dumps(self.s)
        client.publish("inno/B6214197/lighting",self.y)


if __name__ == "__main__":
    ui=myledcontrol()
    MainWindow.show()
    sys.exit(app.exec_())
