
import matplotlib.pyplot as plt
from scipy import signal, fft, fftpack
import numpy as np

def dataFFT(data, sampleRate, fftSize):
    outputData = np.fft.fft(data) / (fftSize / 2)
    outputData = outputData[range(fftSize / 2)]

    frq = np.fft.fftfreq(fftSize) * sampleRate
    frq = frq[range(fftSize / 2)]
    return frq, outputData

fftSize = 160
sampleRate = 160

f1 = open('bandpass.txt', 'r')
f2 = open('sinsignalmulti.txt', 'r')
data1 = []
data2 = []
for line in f1:
    data1.append(float(line))

for line in f2:
    temp = line.split(',')
    data2.append(float(temp[0]))

plt.figure(1)
plt.subplot(211)
plt.plot(data1)
plt.subplot(212)
plt.plot(data2)

plt.figure(2)
plt.subplot(311)
frq, fftData1 = dataFFT(data1, sampleRate, fftSize)
plt.plot(frq, abs(fftData1))
plt.subplot(312)
frq, fftData2 = dataFFT(data2, sampleRate, fftSize)
plt.plot(frq, abs(fftData2))
plt.subplot(313)
b, a = signal.butter(8, [10/(0.5*sampleRate), 40/(0.5*sampleRate)], 'bandpass')
filteredData = signal.filtfilt(b,a,data2)
frq, fftData3 = dataFFT(filteredData, sampleRate, fftSize)
plt.plot(frq, abs(fftData3))


plt.show()
