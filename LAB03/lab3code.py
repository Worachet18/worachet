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
        self.val={}
        self.valsld={}
        self.valsld1={}
        client.on_message = self.mycallback
        client.subscribe("inno/b6214197/lab03/sensor")
        client.loop_start()
        self.valrh=0
        self.time()
        
        self.mygraph=pg.PlotWidget(self.centralwidget)
        self.mygraph.setGeometry(QtCore.QRect(200,270,261,141))
        self.x1 = np.arange(100)
        self.y1= np.arange(100)
        self.dataline= self.mygraph.plot()
        self.mygraph.setYRange(0,100)

    def gcn(self):
        self.on18.clicked.connect(self.onclick18)
        self.off18.clicked.connect(self.offclick18)
        self.on19.clicked.connect(self.onclick19)
        self.off19.clicked.connect(self.offclick19)
        self.slider12.sliderReleased.connect(self.fslider12)
        self.slider14.sliderReleased.connect(self.fslider14)




    def autoplot(self):
        self.x1=np.append(self.x1[1:], self.x1[-1]+1)
        self.y1=np.append(self.y1[1:],self.valrh)
        self.dataline.setData(self.x1,self.y1)
    def time(self):
        self.mytm1=QtCore.QTimer()
        self.mytm1.timeout.connect(self.autoplot)
        self.mytm1.setInterval(10)
        self.mytm1.start()






    def onclick18(self):
        print("onclick18")
        self.val["LED"]=1
        self.val["state"]="on"
        self.valjson = json.dumps(self.val)
        client.publish("inno/b6214197/lab03/lighting",self.valjson)
    def offclick18(self):
        print("offclick18")
        self.val["LED"]=1
        self.val["state"]="off"
        self.valjson = json.dumps(self.val)
        client.publish("inno/b6214197/lab03/lighting",self.valjson)
    def onclick19(self):
        print("onclick19")
        self.val["LED"]=2
        self.val["state"]="on"
        self.valjson = json.dumps(self.val)
        client.publish("inno/b6214197/lab03/lighting",self.valjson)
    def offclick19(self):
        print("offclick19")
        self.val["LED"]=2
        self.val["state"]="off"
        self.valjson = json.dumps(self.val)
        client.publish("inno/b6214197/lab03/lighting",self.valjson)
    def fslider12(self):
        self.valsld["pwm"]=1
        self.valsld["val"]= self.slider12.value()
        self.valsldjson=json.dumps(self.valsld)
        print(self.valsldjson)
        client.publish("inno/b6214197/lab03/pwm",self.valsldjson)
    def fslider14(self):
        self.valsld["pwm"]=2
        self.valsld["val"]= self.slider14.value()
        self.valsldjson=json.dumps(self.valsld)
        print(self.valsldjson)
        client.publish("inno/b6214197/lab03/pwm",self.valsldjson)

    def mycallback(self,client,userdata,message):
        self.valpayload = str(message.payload.decode("utf-8"))
        self.send = json.loads(self.valpayload)
        self.sensorval = self.send["sensor"]
        self.val12 = self.send["val"]
        if self.sensorval == "temp":
            self.realtimetemp.display(self.val12)
        if self.sensorval == "humid":
            self.valrh = self.val12
            self.realtimerh.display(self.val12)

if __name__ == "__main__":
    ui = mylab3()
    MainWindow.show()
    sys.exit(app.exec_())