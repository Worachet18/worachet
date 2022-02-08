import paho.mqtt.client as mqtt
from time import sleep
broker_address="electsut.trueddns.com"
broker_port=27860
client = mqtt.Client("B62141971") ##client ต้องไม่ตรงกัน 
client.connect(broker_address,broker_port)

def on_message(client,userdata,message):
    print("message receive=",str(message.payload.decode()))
    print("Topic receive=",message.topic)
    PL=str(message.payload.decode())
    if PL=='stop_loop'
client.on_message=on_message
client.publish("B6214197/python_mqtt","hello")
client.subscribe("B6214197/python_sub")
client.loop_start()
sleep(5) ##วินาที
client.loop_stop()
##client.loop_forever(timeout=10) ##มันจะรันไปเรื่อยๆ