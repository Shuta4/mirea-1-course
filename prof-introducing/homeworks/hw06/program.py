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
    data = data[data['Code'] == 'USA']
    data[LN_VALUE] = get_ln(data[VALUE])
    make_plot(data, "ln(Coal production)", column_y=LN_VALUE, marker='.')
    data = data[data[YEAR] >= 1994]
    data = data[data[YEAR] <= 2020]
    data = data.reset_index(drop=True)
    for i in range(13):
        data.loc[i, VALUE] = data.iloc[-i - 1][VALUE]
        data.loc[i, LN_VALUE] = data.iloc[-i - 1][LN_VALUE]

    data[CUM_VALUE] = data[VALUE].cumsum()
    data[LN_CUM_VALUE] = get_ln(data[CUM_VALUE])
    data[PROD_DIV_SUM] = [v / s for v, s in zip(data[VALUE], data[CUM_VALUE])]
    data[LN_PROD_DIV_SUM] = get_ln(data[PROD_DIV_SUM])

    make_plot(data, "Coal production (TWh)", marker='.')
    make_plot(data, "Coal production", column_y=LN_VALUE, ylabel='ln(y)', marker='.')
    make_plot(data, "Coal", column_y=LN_CUM_VALUE, ylabel="ln(y)", marker='.')

    make_plot(data, "Logistics", column_y=LN_PROD_DIV_SUM, column_x=CUM_VALUE,
              ylabel="ln(y' / y)", xlabel="y", marker='.')

    logistics_x1 = data[CUM_VALUE].min()
    logistics_x2 = data[CUM_VALUE].max()
    logistics_y1 = data[LN_PROD_DIV_SUM].max()
    logistics_y2 = data[LN_PROD_DIV_SUM].min()

    plt.plot([logistics_x1, logistics_x2],
             [logistics_y1, logistics_y2], color='orange')

    make_plot(data, "Logistics", column_y=LN_PROD_DIV_SUM, column_x=LN_CUM_VALUE,
              ylabel="ln(y' / y)", xlabel="ln(y)", marker='.')

    ln_logistics_x1 = data[LN_CUM_VALUE].min()
    ln_logistics_x2 = data[LN_CUM_VALUE].max()
    ln_logistics_y1 = data[LN_PROD_DIV_SUM].max()
    ln_logistics_y2 = data[LN_PROD_DIV_SUM].min()

    plt.plot([ln_logistics_x1, ln_logistics_x2],
             [ln_logistics_y1, ln_logistics_y2], color='orange')

    plt.show()


if __name__ == '__main__':
    main()
