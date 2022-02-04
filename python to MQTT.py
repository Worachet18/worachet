
import paho.mqtt.client as mqtt
import time
import json
broker_address="electsut.trueddns.com" 
broker_port=27860
client = mqtt.Client("B6214197") 
client.connect(broker_address,broker_port)
def callback(client, userdata, message):
    print("topic = ",message.topic)
    print("Payload = ",str(message.payload.decode("utf-8")))
    print("Qos = ",message.qos)
    myPL = str(message.payload.decode("utf-8"))
    if myPL == "system_stop" :
        client.disconnect()

##client.publish("inno/b6214197/323",datajson)


client.on_message= callback
##client.subscribe("inno/b6214197/324")
client.loop_start() #start the loop
time.sleep(10) # wait
client.loop_stop() #stop the loop