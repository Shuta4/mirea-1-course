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
CUM_VALUE = 'CumSumValue'
LN_CUM_VALUE = 'LnCumSumValue'
PROD_DIV_SUM = "y'/y"
LN_PROD_DIV_SUM = "ln(y'/y)"

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


def get_ln(data_col):
    return data_col.apply(lambda x: log(x) if x > 0 else 0)

def main():
    plt.style.use('seaborn-whitegrid')

    data = pd.read_csv('coal-production-by-country.csv')
    data[VALUE] = data['Coal production (TWh)']
    data[LN_VALUE] = get_ln(data[VALUE])
    data = data[data['Code'] == 'USA']
    make_plot(data, "ln(Coal production)", column_y=LN_VALUE, marker='.')
    data = data[data[YEAR] >= 1960]
    data = data.reset_index(drop=True)
    data = data.iloc[::-1]
    data[CUM_VALUE] = data[VALUE].cumsum()
    data[LN_CUM_VALUE] = get_ln(data[CUM_VALUE])
    data[PROD_DIV_SUM] = [v / s for v, s in zip(data[VALUE], data[CUM_VALUE])]
    data[LN_PROD_DIV_SUM] = get_ln(data[PROD_DIV_SUM])

    make_plot(data, "Coal production (TWh)", marker='.')
    make_plot(data, "Coal production", column_y=LN_VALUE, ylabel='ln(y)', marker='.')
    plt.xlim(data[YEAR].max(), data[YEAR].min())

    make_plot(data, "Anamorphose", column_y=LN_PROD_DIV_SUM, ylabel="ln(y' / y)", marker='.')
    plt.xlim(data[YEAR].max(), data[YEAR].min())
    plt.plot(
            [data.iloc[5][YEAR], data.iloc[-1][YEAR]],
            [data.iloc[5][LN_PROD_DIV_SUM], data.iloc[-1][LN_PROD_DIV_SUM]],
            color='orange')


    make_plot(data, "Logistics", column_y=LN_PROD_DIV_SUM, column_x=LN_CUM_VALUE, ylabel="ln(y' / y)", xlabel="ln(y)", marker='.')

    plt.plot(
            [data[LN_CUM_VALUE].min(), data[LN_CUM_VALUE].max()],
            [data[LN_PROD_DIV_SUM].max(), data[LN_PROD_DIV_SUM].min()],
            color='orange')


    plt.show()


if __name__ == '__main__':
    main()
