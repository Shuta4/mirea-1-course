from matplotlib import pyplot as plt
import pandas as pd
import datetime as dt
from math import log


def download_data(code, years):
    ts_end = int(dt.datetime.now().timestamp())
    ts_start = ts_end - years * 365 * 86400

    data = pd.read_csv(f"https://query1.finance.yahoo.com/v7/finance/download/{code}?period1={ts_start}&period2={ts_end}&interval=1d&events=history&includeAdjustedClose=true", sep=',')
    data = data.drop('Volume', axis='columns')
    data = data.dropna()
    data['Date'] = data['Date'].apply(lambda x: pd.to_datetime(x))
    return data


def make_plot(data, func, title):
    plt.figure()
    plt.plot(data['Date'], data['Close'].apply(lambda x: func(x)))
    plt.xlabel('Years')
    plt.ylabel('Value')
    plt.title(title)


def main():
    code = input('Code >> ')
    years = int(input('Years >> '))

    print('Downloading data...')
    data = download_data(code, years)
    max_value = data['Close'].max()
    min_value = data['Close'].min()

    print('Creating plots...')
    plt.style.use('seaborn-whitegrid')
    make_plot(data, lambda x: x, "$")
    make_plot(data, lambda x: log(x), "ln$")
    make_plot(data, lambda x: log(x / max_value), "ln(\$/\$max)")
    make_plot(data, lambda x: log(x / min_value), "ln(\$/\$min)")

    plt.show()


if __name__ == '__main__':
    main()
