from matplotlib import pyplot as plt
import numpy as np
import pandas as pd
import datetime as dt
from math import log
import math
from scipy.interpolate import interp1d


YEAR = 'Year'
VALUE = 'Value'
LN_VALUE = 'LnValue'
R = 'R'


def make_plot(data, title, column_x=YEAR, column_y=VALUE, xlabel='Years', ylabel='Value', **kwargs):
    plt.figure()
    plt.plot(data[column_x], data[column_y], **kwargs)
    plt.xlabel(xlabel)
    plt.ylabel(ylabel)
    plt.title(title)


def make_counts_plot(data):
    plt.figure()
    data = data.round({VALUE: 2})
    series = data.value_counts(subset=[VALUE], sort=False)
    x = series.to_list()
    y = [x[0] for x in series.keys()]

    ynew = np.linspace(min(y), max(y), num=500, endpoint=True)
    cubic = interp1d(y, x, kind='cubic')

    plt.plot(cubic(ynew), ynew)
    plt.xlabel('Count')
    plt.ylabel('Value')
    plt.title('Value counts')


def make_rank_plot(data):
    plt.figure()
    ln_data = data[VALUE].apply(lambda x: log(x))
    rank = ln_data.rank()
    plt.plot(rank, ln_data)
    plt.xlabel('Rank')
    plt.ylabel('Value')
    plt.title('Ranked')


def make_vertical(x, min_y, max_y, *args, text='', **kwargs):
    plt.plot([x, x], [min_y, max_y], *args, **kwargs)
    if text != '':
        plt.text(x, min_y - 0.1, text)


def make_horizontal(min_x, max_x, y, *args, text='', **kwargs):
    plt.plot([min_x, max_x], [y, y], *args, **kwargs)
    if text != '':
        plt.text(min_x - 0.1, y, text)


def recursive_verticals(date1, date2, min_y, max_y, level, max_level, *args, **kwargs):
    half = date_half(date1, date2)
    make_vertical(half, min_y, max_y, *args, **kwargs)
    if level == max_level:
        return
    recursive_verticals(date1, half, min_y, max_y, level + 1, max_level, *args, **kwargs)
    recursive_verticals(date2, half, min_y, max_y, level + 1, max_level, *args, **kwargs)


def normal_distribution(values, mu, sigma):
    return [1 / (sigma * (2 * math.pi) ** 0.5)
            * math.e ** (-0.5 * ((x - mu) / sigma) ** 2)
            for x in values]


def ln_normal_distribution(values, mu, sigma):
    x_minus_mu_power_2 = [(x - mu) ** 2 for x in values]
    y = [-log(sigma * (2 * math.pi) ** 0.5) - x / (2 * sigma ** 2)
         for x in x_minus_mu_power_2]
    return (x_minus_mu_power_2, y)


def plot_normal_distribution(mu, sigma):
    x = np.linspace(mu - 3 * sigma, mu + 3 * sigma, 100)
    plt.figure()
    plt.plot(x, normal_distribution(x, mu, sigma))
    plt.title('Normal Distribution')


def plot_ln_normal_distribution(mu, sigma):
    x, y = ln_normal_distribution(np.linspace(mu - 3 * sigma, mu + 3 * sigma, 100), mu, sigma)
    plt.figure()
    plt.plot(x, y)
    plt.title('Ln(Normal Distribution)')


def get_ln(data_col):
    return data_col.apply(lambda x: log(x) if x > 0 else 0)


def main():
    plt.style.use('seaborn-v0_8-whitegrid')

    data = pd.read_csv('../coal-production-by-country.csv')
    data = data[data['Code'] == 'USA']
    data = data.reset_index(drop=True)

    data[VALUE] = data['Coal production (TWh)']
    data[LN_VALUE] = get_ln(data[VALUE])

    make_plot(data, "Coal production (TWh)", marker='.')
    make_plot(data, "Coal production", column_y=LN_VALUE, ylabel='ln(y)', marker='.')

    t = 5
    size = data.index.size

    data[R] = [data.loc[i - t, VALUE] * data.loc[i + t, VALUE] / data.loc[i, VALUE] ** 2 if t <= i and i < size - t else None for i in range(size)]

    make_plot(data, "R", column_y=R, marker='.')

    plt.figure()
    plt.hist(data[R], orientation='horizontal', bins=20)

    mu = data[VALUE].median()
    sigma = 0.2
    plot_normal_distribution(mu, sigma)
    plot_ln_normal_distribution(mu, sigma)

    plt.show()


if __name__ == '__main__':
    main()
