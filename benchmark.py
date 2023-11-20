import matplotlib.pyplot as plt
import pandas as pd
import numpy as np
import json
import os

current_path = os.path.dirname(os.path.realpath(__file__))
path = 'benchmark.json'
data = json.load(open('benchmark.json'))

# example: {"line":49,"file":"/home/filippo/github/traction-control-sw/src/main.c","function":"main","time":2},
# group data by file and, for each function and line number, compute the average time and std dev
df = pd.DataFrame(data)
df['file'] = df['file'].str.replace(current_path, '')
df = df.groupby(['file', 'function', 'line']).agg({'time': ['mean', 'std']})
df = df.reset_index()
df.columns = ['file', 'function', 'line', 'mean', 'std']
df = df.sort_values(by=['mean'], ascending=False)
df = df.reset_index()

# plot the results
fig, ax = plt.subplots()
hbars = ax.barh(df.index, df['mean'], xerr=df['std'], align='center', color='green', ecolor='red')
ax.bar_label(hbars, fmt='%.2f')
ax.set_yticks(df.index)
ax.set_yticklabels(df['file'] + ':' + df['function'] + ':' + df['line'].astype(str))
ax.invert_yaxis()
ax.set_xlabel('time (us)')
ax.set_title('Traction Control Benchmark')
plt.show()
