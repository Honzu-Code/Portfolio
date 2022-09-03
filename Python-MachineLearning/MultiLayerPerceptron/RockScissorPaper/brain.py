import numpy as np
import pandas as pd
from sklearn import preprocessing
from sklearn.model_selection import train_test_split
from sklearn.neural_network import MLPClassifier
from sklearn.metrics import accuracy_score

data = pd.read_csv("out.csv")

clf = MLPClassifier(hidden_layer_sizes=(2,),
                    random_state = 5,
                    verbose = False,
                    learning_rate_init = 0.01,
                    max_iter = 1000000
                    )

test_input = [[0,0,1]]
#test_output = [[1,0,0]]

input = [[0,0,1],[0,1,0],[1,0,0]]
output = [[1,0,0],[0,0,1],[0,1,0]]


clf.fit(input,output)

ypred = clf.predict(test_input)

#print(accuracy_score(test_output,ypred))

print("predict of test_input: ", ypred)
print("weights between input and hidden layer",clf.coefs_[0])
print("weights between hidden and output layer",clf.coefs_[1])
