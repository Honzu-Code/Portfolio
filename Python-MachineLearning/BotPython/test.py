#from selenium import webdriver
#import requests
#from bs4 import BeautifulSoup
import pandas as pd
from data import Data as dt

pd = pd.read_csv("BTC-USD.csv")

data = dt(open_price=pd["Open"],close_price=pd["Close"],high_price=pd["High"],low_price=pd["Low"])

data.show()

#url = "http://www.python.org"

#res = requests.get(url)

#print(res.content)

#driver = webdriver.Firefox()
#driver.get("http://www.python.org")

#driver.close()





