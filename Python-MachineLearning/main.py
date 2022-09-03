from fitLine import fitLine
import matplotlib.pyplot as plt


data_x = [2,3,5,7,9]
data_y = [4,5,7,10,15]

bestLine = fitLine(data_x,data_y)

m,b = bestLine.calculate_line()

fit_line = [1 * m + b,15 * m + b]


def draw_best_fit_Line(data_x,data_y,fitLine):


    plt.plot([1,15],[fitLine[0],fitLine[1]],'bo',linestyle="--")
    plt.scatter(data_x,data_y,s=10,color="red")
    plt.title("Points")

    plt.xlabel("X")
    plt.ylabel("Y")
    plt.show()

if __name__ == '__main__':
    draw_best_fit_Line(data_x,data_y,fit_line)
