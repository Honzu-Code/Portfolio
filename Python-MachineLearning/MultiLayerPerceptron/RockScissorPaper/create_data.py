import pandas as pd
from pathlib import Path

features = ["input","output"]

#paper,scissor,rock
input = [[0,0,1],[0,1,0],[1,0,0],[0,1,0]]
output = [[1,0,0],[0,0,1],[0,1,0],[0,0,1]]

data = {features[0] : input, features[1] : output}

#print(data)

df = pd.DataFrame(data)


df.to_csv("out.csv",index=False)
