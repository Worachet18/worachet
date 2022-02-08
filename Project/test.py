from tracemalloc import stop
import pandas as pd 
import csv
import os
from datetime import date
from datetime import datetime
from datetime import time
import numpy as np
import random

minute=00
hour=00
days=7
mount=1
year=2022
randtemp = random.randint(25,28)
randhumid = random.randint(60,80)

try:
    os.makedirs("c:/poject/test")
except FileExistsError:
    pass  

# day,mount,year,hour,minute,secone,temp,humid

os.chdir("c:/poject/test")
with open('testpjinno.csv','a',newline="") as f:
    mv = csv.writer(f)
    # mv.writerow(['day','mount','year','hour','minute','secone','temp','humid'])
    
    while mount<3 :
        days = 1
        while days<31 :
            hour = 0
            while hour<24 :
                minute = 0
                while minute<60 :
                    for i in range(1):
                        mv.writerow([days,mount,year,hour,minute,00,random.randint(25,28),random.randint(60,80)])
                        mv.writerow([days,mount,year,hour,minute,30,random.randint(25,28),random.randint(60,80)])
                    minute = minute+1
                hour = hour+1
            days = days+1
        mount = mount+1
        
        
        


