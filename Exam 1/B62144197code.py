from PyQt5 import QtCore, QtGui, QtWidgets
from B6214197 import Ui_MainWindow
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
        self.val={}
        self.valsld={}
        client.on_message = self.mycallback
        client.subscribe("inno/B6214197/monitoring")
        client.loop_start()
        self.valrh=0
    def gcn(self):
        self.hton.clicked.connect(self.hon)
        self.htoff.clicked.connect(self.hoff)
        self.pmon.clicked.connect(self.pon)
        self.pmoff.clicked.connect(self.poff)
        self.fansld.sliderReleased.connect(self.sld)
    def hon(self):
        print("hon")
        self.val["equipment"]= "heater"
        self.val["state"]= 1
        self.valjson = json.dumps(self.val)
        client.publish("inno/exam01/b6214197/control",self.valjson)
    def hoff(self):
        print("hoff")
        self.val["equipment"]= "heater"
        self.val["state"]= 0
        self.valjson = json.dumps(self.val)
        client.publish("inno/exam01/b6214197/control",self.valjson)
    def pon(self):
        print("pon")
        self.val["equipment"]= "pump"
        self.val["state"]= 1
        self.valjson = json.dumps(self.val)
        client.publish("inno/exam01/b6214197/control",self.valjson)
    def poff(self):
        print("poff")
        self.val["equipment"]= "pump"
        self.val["state"]= 0
        self.valjson = json.dumps(self.val)
        client.publish("inno/exam01/b6214197/control",self.valjson)
    def sld(self):
        self.valsld["fanspeed"]= self.fansld.value()
        self.valsldjson=json.dumps(self.valsld)
        print(self.valsldjson)
        client.publish("inno/exam01/b6214197/fan",self.valsldjson)
    def mycallback(self,client,userdata,message):
        self.valpayload = str(message.payload.decode("utf-8"))
        self.send = json.loads(self.valpayload)
        self.vallevel = self.send["level"]
        self.valtemp = self.send["temp"]
        self.waterlcd.display(self.vallevel)
        self.templcd.display(self.valtemp)
    
if __name__ == "__main__":
    ui = mylab3()
    MainWindow.show()
    sys.exit(app.exec_())