from colorama import Fore, Back, Style
import matplotlib.pyplot as plt
import numpy as np
import math
import os
import copy
from tqdm import tqdm as tqdm

from data_parser import DataParser
from weight_parser import WeightsParser

class LinearRegression:
    __WEIGHTS_FILE = 'weights.dat'
    __ALPHA = 0.001
    __EPOCHES = 5000
    __BATCH_SIZE = 50
    __TRAINING_PATH = 'TrainingPlots/'

    def __init__(self, filename, mode= 'file'):
        if  mode == 'file':
            parser = DataParser(filename)
            self.data = parser.data
            self.headers = parser.headers
            self.theta_0 = 0.0
            self.theta_1 = 0.0
            self.prev_mse = 0.0

    def estimatePrice(self, mileage):
        return ((self.theta_0 + (self.theta_1 * float(mileage))))

    def mean_square_error(self, data):
        tmp_summ = 0.0

        for i in range(data.shape[0]):
            tmp_summ += (self.estimatePrice(data[i, 0]) - float(data[i, 1])) ** 2
        return (tmp_summ / data.shape[0])

    def get_gradient0(self, X_batch, y_batch):
        tmp_summ = 0.0

        for i in range(len(X_batch)):
            tmp_summ += (self.estimatePrice(X_batch[i]) - float(y_batch[i]))
        return (tmp_summ / len(X_batch))

    def get_gradient1(self, X_batch, y_batch):
        tmp_summ = 0.0

        for i in range(len(X_batch)):
            tmp_summ += (self.estimatePrice(X_batch[i]) - float(y_batch[i])) * X_batch[i]
        return (tmp_summ / len(X_batch))

    def standardize(self, iner_data, mode):
        if mode == 'train':
            self.min_parametr = iner_data[:, 0].min()
            self.max_parametr = iner_data[:, 0].max()
            self.min_target = iner_data[:, 1].min()
            self.max_target = iner_data[:, 1].max()

        for i in range(self.data.shape[0]):
            iner_data[i, 0] = (iner_data[i, 0] - self.min_parametr)/(self.max_parametr - self.min_parametr)
            iner_data[i, 1] = (iner_data[i, 1] - self.min_target)/(self.max_target - self.min_target)

    def generate_batches(self, X, y, batch_size):
        assert len(X) == len(y)
        np.random.seed(42)
        perm = np.random.permutation(len(X))

        X_inner, y_inner = X[perm], y[perm]
        for i in range(X_inner.shape[0] // batch_size):
            yield tuple((X_inner[i * batch_size: (i + 1) * batch_size], y_inner[i * batch_size: (i + 1) * batch_size]))

    def save_img(self, loss_value):
        try:
            os.stat(self.__TRAINING_PATH)
        except:
            os.mkdir(self.__TRAINING_PATH)

        fig, ax = plt.subplots()
        ax.plot(range(len(loss_value)), loss_value)
        ax.set_xlabel('Epoha')
        ax.set_ylabel('Loss')
        ax.set_title('Training Loss')
        fig.savefig(self.__TRAINING_PATH + 'Training Loss.png')

        fig, ax = plt.subplots()
        ax.scatter(self.data[:, 0], self. data[:, 1])
        ax.set_xlabel('Mileage, km')
        ax.set_ylabel('Price')
        ax.set_title('Data')
        fig.savefig(self.__TRAINING_PATH + 'Data plot.png')

        fig, ax = plt.subplots()
        ax.scatter(self.data[:, 0], self.data[:, 1])
        mileage = np.linspace(self.min_parametr, self.max_parametr, 100)
        price = np.array([self.estimatePrice(km) for km in mileage])
        ax.plot(mileage, price)
        ax.set_xlabel('Mileage, km')
        ax.set_ylabel('Price')
        ax.set_title('Data with line')
        fig.savefig(self.__TRAINING_PATH + 'Data with line.png')

    def __save_weights_file(self):
        with open(self.__WEIGHTS_FILE, 'w') as weights_file:
            weights_file.write('%f ' % self.theta_0)
            weights_file.write('%f ' % self.theta_1)
        print('Saved model parameters in ' + Fore.CYAN + self.__WEIGHTS_FILE + Fore.RESET + '\n')

    def train_model(self):
        iner_data = np.array(self.data, dtype=np.float)
        self.standardize(iner_data, 'train')
        prev_mse = self.mean_square_error(iner_data)
        history = []

        for _ in tqdm(range(self.__EPOCHES)):
            for X_batch, y_batch in self.generate_batches(X=iner_data[:, 0], y=iner_data[:, 1], batch_size=2):
                tmp_theta_0 = self.get_gradient0(X_batch, y_batch)
                tmp_theta_1 = self.get_gradient1(X_batch, y_batch)
                self.theta_0 -= self.__ALPHA * tmp_theta_0
                self.theta_1 -= self.__ALPHA * tmp_theta_1

                history.append(self.mean_square_error(iner_data))
            cur_mse = self.mean_square_error(iner_data)
            if np.abs(prev_mse - cur_mse) < 1e-10:
                break
            prev_mse = copy.deepcopy(cur_mse)

        self.theta_1 = (self.max_target - self.min_target) * self.theta_1 / (self.max_parametr - self.min_parametr)
        self.theta_0 = self.min_target + ((self.max_target - self.min_target) * self.theta_0) + self.theta_1 * (1 - self.min_parametr)

        self.save_img(history)
        self.__save_weights_file()

    def predict_data(self):
        if os.path.exists(self.__WEIGHTS_FILE):
            parser = WeightsParser(self.__WEIGHTS_FILE)
            self.theta_0 = parser.tet[0]
            self.theta_1 = parser.tet[1]
        else:
            self.theta_0 = 0
            self.theta_1 = 0

        for i in range(self.data.shape[0]):
            print('Car mileage = ' +  str(self.data[i, 0]) + Fore.MAGENTA + ' LR price = ' + str(self.estimatePrice(self.data[i, 0])) + Fore.GREEN + ' Real price = ' + str(self.data[i, 1]) + Fore.RESET)

    def predict_data_value(self):
        if os.path.exists(self.__WEIGHTS_FILE):
            parser = WeightsParser(self.__WEIGHTS_FILE)
            self.theta_0 = parser.tet[0]
            self.theta_1 = parser.tet[1]
        else:
            self.theta_0 = 0
            self.theta_1 = 0

        print('Car mileage = ')
        meliage = input()

        print('Car mileage = ' + meliage + Fore.MAGENTA + ' LR price = ' + str(self.estimatePrice(int(meliage))) + Fore.RESET)































    # def generate_batches(self, X, y):
    #     assert len(X) == len(y)
    #
    #     batch_size = self.__BATCH_SIZE
    #     np.random.seed(42)
    #     perm = np.random.permutation(len(X))
    #     X_inner, y_inner = X[perm], y[perm]
    #     for i in range(X_inner.shape[0] // batch_size):
    #         yield tuple((X_inner[i * batch_size: (i + 1) * batch_size], y_inner[i * batch_size: (i + 1) * batch_size]))
    #
    # def logit(self, x, w):
    #     return np.dot(x, w)
    #
    # def sigmoid(self, h):
    #     return 1. / (1 + np.exp(-h))
    #
    # def fit(self, X, y):
    #     n, k = X.shape
    #     np.random.seed(42)
    #     # self.w = np.random.randn(k + 1)
    #     self.w = np.random.randn(k)
    #
    #     # X_train = np.concatenate((np.ones((n, 1)), X), axis=1)
    #     X_train = X
    #     loss_per_epoha = []
    #     for _ in range(self.__EPOCHES):
    #         losses = []
    #         for X_batch, y_batch in self.generate_batches(X=X_train, y=y):
    #             predictions = self.sigmoid(self.logit(X_batch, self.w))
    #             self.w -= self.__ALPHA * self.get_grad(X_batch, y_batch, predictions)
    #             losses.append(self.__loss(y_batch, predictions))
    #         loss_per_epoha.append(np.sum(losses) / len(losses))
    #         if abs(losses[-1] - losses[-2]) < 1e-6:
    #             break
    #     return loss_per_epoha, self.w
    #
    # def __loss(self, y, p):
    #     p = np.clip(p, 1e-10, 1 - 1e-10)
    #     return -np.mean(y * np.log(p) + (1 - y) * np.log(1 - p))
    #
    # def get_grad(self, X_batch, y_batch, predictions):
    #     grad = np.dot(X_batch.T, (predictions - y_batch)) / X_batch.shape[0]
    #
    #     prom_v = np.sign(self.w)
    #     prom_v[0] = 0
    #     grad += self.__L1_coef * prom_v
    #
    #     prom_v = copy.deepcopy(self.w)
    #     prom_v[0] = 0
    #     grad += self.__L2_coef * 2 * prom_v
    #     return grad
    #
    # def save_loss_img(self, fac_name, loss_value):
    #     fig, ax = plt.subplots()
    #     ax.plot(range(len(loss_value)), loss_value)
    #     ax.set_xlabel('Epoha')
    #     ax.set_ylabel('Loss')
    #     ax.set_title(fac_name)
    #     filename = self.__TRAINING_LOSS_PATH + '%s' % (fac_name) + '.png'
    #     fig.savefig(filename)
    #
    # def train_faculty(self, faculty_name, feahers, label):
    #     print(Style.BRIGHT + Fore.BLUE + 'Running gradient descent to determine ' + faculty_name)
    #     losses, faculti_w = self.fit(X=feahers, y=np.where(label == faculty_name, 1, 0))
    #     self.save_loss_img(faculty_name, losses)
    #     return faculti_w
    #
    # def __save_weights_file(self):
    #     with open(self.__WEIGHTS_FILE, 'w') as weights_file:
    #         for mean in self.__mean:
    #             weights_file.write('%f ' % mean)
    #         weights_file.write('\n')
    #         for std in self.__std:
    #             weights_file.write('%f ' % std)
    #         weights_file.write('\n')
    #         for row in self.faculty_w:
    #             # print(row)
    #             for num in row:
    #                 weights_file.write('%f ' % num)
    #             weights_file.write('\n')
    #     print('Saved model parameters in ' + Fore.CYAN + self.__WEIGHTS_FILE + Fore.RESET + '\n')
    #
    # def train_model(self, filename):
    #     print(Style.BRIGHT + 'Data parsing from file = ' + Fore.MAGENTA + filename + Fore.RESET + Style.RESET_ALL)
    #     dt_analize = DataAnalyzer(filename)
    #     feahers = np.array(dt_analize.data[:, 9:], dtype=np.float64)
    #
    #     print(Style.BRIGHT + 'Data normalization' + Fore.MAGENTA)
    #     mask = ~np.isnan(feahers).any(axis=1)
    #     feahers = feahers[mask]
    #     label = dt_analize.data[:, list(dt_analize.headers).index('Hogwarts House')][mask]
    #     # print("Dataset size = ", feahers.shape)
    #     for i in range(feahers.shape[1]):
    #         mean = mean_(feahers[:, i])
    #         self.__mean.append(mean)
    #         std = std_(feahers[:, i])
    #         self.__std.append(std)
    #         for j in range(feahers.shape[0]):
    #             feahers[j, i] =  (feahers[j, i] - mean) / std
    #     print()
    #
    #     try:
    #         os.stat(self.__TRAINING_LOSS_PATH)
    #     except:
    #         os.mkdir(self.__TRAINING_LOSS_PATH)
    #
    #     print(Style.BRIGHT + 'Training Log_Regression for data in ' + Fore.MAGENTA + filename + Fore.RESET + Style.RESET_ALL)
    #     Gryffindor_w = self.train_faculty('Gryffindor', feahers, label)
    #     Hufflepuff_w = self.train_faculty('Hufflepuff', feahers, label)
    #     Ravenclaw_w = self.train_faculty('Ravenclaw', feahers, label)
    #     Slytherin_w = self.train_faculty('Slytherin', feahers, label)
    #     self.faculty_w = [Gryffindor_w, Hufflepuff_w, Ravenclaw_w, Slytherin_w]
    #     self.__save_weights_file()
    #
    # def __save_answer(self, predictions):
    #     with open(self.__ANSWER_FILE, 'w') as answer_file:
    #         answer_file.write('Index,Hogwarts House' + '\n')
    #         indices = range(len(predictions))
    #         for i, prediction in zip(indices, predictions):
    #             answer_file.write('%d,%s\n' % (i, prediction))
    #     print('Saved predictions in ' + Fore.CYAN + self.__ANSWER_FILE + Fore.RESET + '\n')
    #
    # def predict_model(self, weights_file, data_file):
    #     parser = WeightsParser(weights_file)
    #     self.__mean = parser.mean
    #     self.__std = parser.std
    #     self.__w = np.array(parser.w)
    #
    #     dt_analize = DataAnalyzer(data_file)
    #     feahers = np.array(dt_analize.data[:, 9:], dtype=np.float64)
    #     for i in range(feahers.shape[1]):
    #         for j in range(feahers.shape[0]):
    #             feahers[j, i] = (feahers[j, i] - self.__mean[i]) / self.__std[i]
    #
    #     print(feahers.shape, self.__w.shape)
    #
    #     house_percent = self.sigmoid(np.dot(feahers, self.__w.T))
    #     predictions = np.argmax(house_percent, axis=1)
    #     predictions = predictions.tolist()
    #     predictions = [self.__LABELS[index] for index in predictions]
    #     self.__save_answer(predictions)












