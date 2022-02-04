# import json
# data={}
# data["John"]= 50.3
# data["Marry"]=75.8
# data["Boy"]=65.2
# data["Kethy"]=77.4
# data["Brian"]=83.4
# datajson = json.dumps(data)
# print(datajson)

# data1={}
# data1["name"]="john"
# data1["age"]=35
# data1["phone"]= "0992111111"
# data1["car"]=["toyota","nissan"]
# data1["nationality"]="USA"
# data1json=json.dumps(data1)
# print(data1json)


import paho.mqtt.client as mqtt
import time
import json
broker_address="electsut.trueddns.com"  
broker_port=27860
client = mqtt.Client("B6214197") 
client.connect(broker_address,broker_port)
def on_message(client, userdata, message):
    print("topic = ",message.topic)
    print("Payload = ",str(message.payload.decode("utf-8")))
    print("Qos = ",message.qos)
    myPL = str(message.payload.decode("utf-8"))
    if myPL == "system_stop" :
        client.disconnect()
data={}
data["John"] = 50.3
data["Marry"] = 75.8
data["Boy"] = 65.2
data["Kethy"] = 77.4
data["Brian"] = 83.4
datajson=json.dumps(data)
data1={}
data1["name"] = "john"
data1["age"] = 35
data1["phone"] = "099211111"
data1["car"] = ["ford","toyota","nissan"]
data1["pet"] = ["cat","dog"]
data1["nationality"] = "USA"
datajson1 = json.dumps(data1)
###publish
client.publish("inno/b6214197/323",datajson)
client.publish("inno/b6214197/323",datajson1)

client.on_message= on_message 
###subscribe>>>on_message or callback
client.subscribe("inno/b6214197/324")
client.loop_start() #start the loop
time.sleep(10) # wait
client.loop_stop() #stop the loop
