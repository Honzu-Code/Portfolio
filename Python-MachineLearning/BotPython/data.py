import pandas as pd
from dataclasses import dataclass
import numpy as np
from talipp.indicators import EMA,SMA,Stoch,WMA,RSI

@dataclass
class Data:
    open: []
    close: []
    high: []
    low: []

    def __init__(self,open_price,close_price,high_price,low_price):
        self.open = np.array(open_price.to_numpy())
        self.close = np.array(close_price.to_numpy())
        self.high = np.array(high_price.to_numpy())
        self.low = np.array(low_price.to_numpy())

    def show(self):
        print(f"open: {self.open}\n")
        print(f"close: {self.close}\n")
        print(f"high: {self.high}\n")
        print(f"low: {self.low}\n")

    def rsi_play(self,period,index_start,index_end):
        if(RSI(period,close[index_start:index_end] >= 75)
           return "sell"
        else if(RSI(period,close[index_start:index_end] <= 25))
           return "buy"
        else:
           return "none"

array = [1,2,3,4,5,4,7,8,9]
print("SMA: ",SMA(4,array))
print("EMA: ",EMA(3,array))
print("WMA: ",WMA(4,array))
print("RSI: ",RSI(4,array))

