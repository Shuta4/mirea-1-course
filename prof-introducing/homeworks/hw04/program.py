from matplotlib import pyplot as plt
import numpy as np
import pandas as pd
import datetime as dt
from math import log
import math
from scipy.interpolate import interp1d


DATE = 'Date'
PRICE = 'Price'
LN_PRICE = 'LnPrice'
D_DATE = 'dDate'
LN_DATE = 'lnDate'
INDEX = 'index'


def make_plot(data, func, title, column_date=DATE, column_value=PRICE):
    plt.figure()
    plt.plot(data[column_date], data[column_value].apply(lambda x: func(x)))
    plt.xlabel('Years')
    plt.ylabel('Value')
    plt.title(title)


def make_counts_plot(data):
    plt.figure()
    data = data.round({PRICE: 2})
    series = data.value_counts(subset=[PRICE], sort=False)
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
    ln_data = data[PRICE].apply(lambda x: log(x))
    rank = ln_data.rank()
    plt.plot(rank, ln_data)
    plt.xlabel('Rank')
    plt.ylabel('Value')
    plt.title('Ranked')


def date_half(date1, date2):
    ts1 = date1.timestamp()
    ts2 = date2.timestamp()
    ts = abs(ts1 - ts2) / 2
    return dt.datetime.fromtimestamp(min(ts1, ts2) + ts)


def make_vertical(x, min_y, max_y, *args, text='', **kwargs):
    plt.plot([x, x], [min_y, max_y], *args, **kwargs)
    if text != '':
        plt.text(x, min_y - 0.1, text)


def recursive_verticals(date1, date2, min_y, max_y, level, max_level, *args, **kwargs):
    half = date_half(date1, date2)
    make_vertical(half, min_y, max_y, *args, **kwargs)
    if level == max_level:
        return
    recursive_verticals(date1, half, min_y, max_y, level + 1, max_level, *args, **kwargs)
    recursive_verticals(date2, half, min_y, max_y, level + 1, max_level, *args, **kwargs)


def main():
    data = pd.read_csv('eur-usd-monthly-1975-2022.csv')
    data[DATE] = data[DATE].apply(lambda x: pd.to_datetime(x))

    data.sort_values(DATE, ascending=True)

    print('Creating plots...')
    plt.style.use('seaborn-whitegrid')
    make_plot(data, lambda x: x, "$")
    #make_plot(data, lambda x: log(x), "ln$")

    data[LN_PRICE] = data[PRICE].apply(lambda x: log(x))
    price_max = data[LN_PRICE].max()
    price_min = data[LN_PRICE].min()

    date_max = [date for price, date in zip(data[LN_PRICE], data[DATE]) if price == price_max][0]
    date_min = [date for price, date in zip(data[LN_PRICE], data[DATE]) if price == price_min][0]
    half = date_half(date_min, date_max)

    #make_vertical(date_min, price_min, price_max, 'r')
    #make_vertical(date_max, price_min, price_max, 'r')
    #recursive_verticals(date_min, date_max, price_min, price_max, 1, 3, color='orange')

    make_plot(data, lambda x: log(x), "ln$")

    start = [d for p, d in zip(data[LN_PRICE], data[DATE])
            if p == min(p for p, d in zip(data[LN_PRICE], data[DATE])
                if d.year < 1980) and d.year < 1980][0]
    start_ts = start.timestamp()

    d_date = start_ts - data[DATE].min().timestamp()

    e1_ts = start_ts + d_date * math.e
    e1 = dt.datetime.fromtimestamp(e1_ts)

    e2_ts = start_ts + d_date * math.e**2 - (15 + 5 * 30) * 86400
    e2 = dt.datetime.fromtimestamp(e2_ts)

    e3_ts = start_ts + d_date * math.e**3
    e3 = dt.datetime.fromtimestamp(e3_ts)

    T_k = e2_ts - start_ts

    e2_T_k_ts = e2_ts + T_k
    e2_T_k = dt.datetime.fromtimestamp(e2_T_k_ts)

    e3_ts = e2_T_k_ts + T_k
    e3 = dt.datetime.fromtimestamp(e3_ts)

    ee_ts = start_ts + d_date * math.e**math.e
    ee = dt.datetime.fromtimestamp(ee_ts)

    x0_ts = e3_ts - (e3_ts - start_ts) / 19 * 20
    x0 = dt.datetime.fromtimestamp(x0_ts)



    make_vertical(start, price_min, price_max, color='orange', text='1')
    make_vertical(e1, price_min, price_max, color='red', text='e')
    make_vertical(e2, price_min, price_max, color='red', text='e^2')
    make_vertical(e3, price_min, price_max, color='red', text='e^3')
    make_vertical(ee, price_min, price_max, color='red', text='e^e')
    make_vertical(x0, price_min, price_max, color='orange', text='0')
    make_vertical(e2_T_k, price_min, price_max, color='orange')

    plt.show()


if __name__ == '__main__':
    main()
