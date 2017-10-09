# -*- coding: utf-8 -*-
"""
Created on Thu Feb 09 18:12:17 2017

@author: Chengbang
"""

import numpy as np
import matplotlib.pyplot as pl
import matplotlib
import math
import pandas as pd
import random
import pickle
import csv
from scipy import signal, fft,fftpack

row = 4
col = 4

N = 160
fs1 = 10
fs2 = 20
fs3 = 30
fs4 = 40
fs5 = 50
fs6 = 60
n1 = [2*math.pi*fs1*t/N for t in range(N)]
n2 = [2*math.pi*fs2*t/N for t in range(N)]
n3 = [2*math.pi*fs3*t/N for t in range(N)]
n4 = [2*math.pi*fs4*t/N for t in range(N)]
n5 = [2*math.pi*fs5*t/N for t in range(N)]
n6 = [2*math.pi*fs6*t/N for t in range(N)]

axis_x = np.linspace(0,1,num=N)

myfont = matplotlib.font_manager.FontProperties(fname='c:\\windows\\Fonts\\arial.ttf')

#频率为10Hz的正弦信号
x1 = [math.sin(i) for i in n1]
pl.subplot(321)
pl.plot(axis_x,x1)
pl.title(u'10Hz', fontproperties=myfont)
pl.axis('tight')

#频率为20Hz的正弦信号
x2 = [math.sin(i) for i in n2]
pl.subplot(322)
pl.plot(axis_x,x2)
pl.title(u'20Hz', fontproperties=myfont)
pl.axis('tight')

#频率为30Hz的正弦信号
x3 = [math.sin(i) for i in n3]
pl.subplot(323)
pl.plot(axis_x,x3)
pl.title(u'30Hz', fontproperties=myfont)
pl.axis('tight')

#频率为40Hz的正弦信号
x4 = [math.sin(i) for i in n4]
pl.subplot(324)
pl.plot(axis_x,x4)
pl.title(u'40Hz', fontproperties=myfont)
pl.axis('tight')

#50Hz
x5 = [math.sin(i) for i in n5]
pl.subplot(325)
pl.plot(axis_x,x5)
pl.title(u'50Hz', fontproperties=myfont)
pl.axis('tight')

#60Hz
x6 = [math.sin(i) for i in n6]
pl.subplot(326)
pl.plot(axis_x,x6)
pl.title(u'60Hz', fontproperties=myfont)
pl.axis('tight')

#直流偏置
xs = []
for i in range(len(x1)):
    xs.append(((x1[i] + x2[i] + x3[i] + x4[i] + x5[i] + x6[i])/6)*0.01)


f = open("sinsignalmulti.txt","wb")
np.savetxt(f,xs,"%f",',',',\r\n')
f.close()

#频谱绘制

xf = np.fft.fft(xs)

xf_abs = np.fft.fftshift(abs(xf))
axis_xf = np.linspace(-N/2,N/2-1,num=len(xf))
pl.figure()
pl.title(u'raw data', fontproperties=myfont)
pl.plot(axis_xf,xf_abs)
pl.axis('tight')
pl.xlim(0,65)

pl.show()
