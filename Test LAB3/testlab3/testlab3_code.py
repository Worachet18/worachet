from PyQt5 import QtCore, QtGui, QtWidgets
from testlab3 import Ui_MainWindow
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
        self.time()
        self.gcn()
        self.valrh=0
        self.val={}
        client.on_message = self.mycallback
        client.subscribe("inno/b6214197/lab03/sensor")
        client.loop_start()
        self.mygraph=pg.PlotWidget(self.centralwidget)
        self.mygraph.setGeometry(QtCore.QRect(325,251,431,281))
        self.x1 = np.arange(100)
        self.y1= np.arange(100)
        self.dataline= self.mygraph.plot()
    def gcn(self):
        self.pushButton.clicked.connect(self.on18)
        self.pushButton_2.clicked.connect(self.off18)
        self.pushButton_3.clicked.connect(self.on19)
        self.pushButton_4.clicked.connect(self.off19)
        self.verticalSlider.sliderReleased.connect(self.sld)
        self.verticalSlider_2.sliderReleased.connect(self.sld2)     
    def on18(self):
        print("on18")
        self.val["LED"]=1
        self.val["state"]="on"
        self.valdump = json.dumps(self.val)
        client.publish("inno/b6214197/lab03/lighting",self.valdump)
    def off18(self):
        print("off18")
        self.val["LED"]=1
        self.val["state"]="off"
        self.valdump = json.dumps(self.val)
        client.publish("inno/b6214197/lab03/lighting",self.valdump)
    def on19(self):
        print("on19")
        self.val["LED"]= 2 
        self.val["state"]="on"
        self.valdump = json.dumps(self.val)
        client.publish("inno/b6214197/lab03/lighting",self.valdump)
    def off19(self):
        print("off19")
        self.val["LED"]= 2 
        self.val["state"]="off"
        self.valdump = json.dumps(self.val)
        client.publish("inno/b6214197/lab03/lighting",self.valdump)
    def sld(self):
        print("sld")
        self.val["PWM"]= 1
        self.val["val"]= self.verticalSlider.value()
        self.valdump = json.dumps(self.val)
        client.publish("inno/b6214197/lab03/pwm",self.valdump)
    def sld2(self):
        print("sld")
        self.val["PWM"]= 2
        self.val["val"]= self.verticalSlider_2.value()
        self.valdump = json.dumps(self.val)
        client.publish("inno/b6214197/lab03/pwm",self.valdump)
    def mycallback(self,client,userdata,message):
        self.valpayload = str(message.payload.decode("utf-8"))
        self.send = json.loads(self.valpayload)
        self.sensorval = self.send["sensor"]
        self.vall = self.send["val"]
        print(self.vall)
        if self.sensorval == "temp" :
            self.label_5.setNum(self.vall)
        if self.sensorval == "humid" :
            self.label_6.setNum(self.vall)

    def autoplot(self):
        self.x1=np.append(self.x1[1:], self.x1[-1]+1)
        self.y1=np.append(self.y1[1:],self.valrh)
        self.dataline.setData(self.x1,self.y1)
    def time(self):
        self.mytm1=QtCore.QTimer()
        self.mytm1.timeout.connect(self.autoplot)
        self.mytm1.setInterval(10)
        self.mytm1.start()


if __name__ == "__main__":
    ui = mylab3()
    MainWindow.show()
    sys.exit(app.exec_())