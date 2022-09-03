import numpy as np
from dataclasses import dataclass

@dataclass
class fitLine:
    x_Points: list
    y_Points: list

    def __init__(self,x_array,y_array):
        self.x_Points = x_array
        self.y_Points = y_array

    def calculate_line(self):
        sum_x = np.sum(self.x_Points)
        sum_y = np.sum(self.y_Points)
        sum_x2 = np.sum(np.multiply(self.x_Points,self.x_Points))
        sum_y2 = np.sum(np.multiply(self.y_Points,self.y_Points))
        sum_xy = np.sum(np.multiply(self.x_Points,self.y_Points))

        m = (len(self.x_Points) * sum_xy - sum_x * sum_y) / \
        (len(self.x_Points) * sum_x2 - sum_x ** 2)

        b = (sum_y - m * sum_x) / len(self.x_Points)
        print(m)
        return m,b
