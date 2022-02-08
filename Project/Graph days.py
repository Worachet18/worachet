from fileinput import hook_compressed
import pandas as pd
from datetime import datetime, timedelta
from random import choices, random
import matplotlib.pyplot as plt
import random

## create random date list
x = random.randint(0,22)
date_diff_days = [0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,21,22,23,24,25,26,27,28,29,30]
dates = [datetime.now().date() - timedelta(days=i) for i in date_diff_days]

## compute repeated times
d = dict()
for date in dates:  
    d[date] = d[date]+1 if date in d else x
df = pd.DataFrame({'date': list(d.keys()),
                  'repeated' : list(d.values())})

df = df.sort_values(['date'])
print(df)
## plot the timeseries data
plt.ylim([0,100])
plt.plot_date(x = df['date'], y = df['repeated'])
labels = [str(i.day)  for i in df['date']]
plt.xticks(ticks=df['date'],labels=labels)
plt.show()