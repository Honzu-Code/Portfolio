import requests
from bs4 import BeautifulSoup

response = requests.get("https://allegro.pl/kategoria/wyposazenie-dekoracje-i-ozdoby-9317")

categories = ["Dom i Ogród"]
under_categiories = ["wyposazenie"]


soup = BeautifulSoup(response.text,'html.parser')

prices = soup.findAll('p',{"data-testid" : "ad-price"})

print(prices)
