import ccxt
import csv
import datetime
import time

# Initialize Binance exchange
exchange = ccxt.binance()

# Define the symbols you want to track
symbols = [
    'BTC/USDT', 'ETH/USDT', 'BNB/USDT', 'XRP/USDT', 'LTC/USDT',
    'ADA/USDT', 'DOGE/USDT', 'DOT/USDT', 'BCH/USDT', 'LINK/USDT',
    'XLM/USDT', 'SOL/USDT', 'TRX/USDT', 'ETC/USDT', 'FIL/USDT'
]

# Open CSV file for appending and reading
with open('live_data.csv', mode='a+', newline='') as file:
    writer = csv.writer(file)

    while True:
        try:
            # Get the current timestamp for this minute
            current_minute_timestamp = datetime.datetime.now().replace(second=0, microsecond=0)

            for _ in range(60):  # Iterate for each second in the minute
                for symbol in symbols:
                    # Fetch the order book for the specified symbol
                    order_book = exchange.fetch_order_book(symbol)
                    
                    # Get the highest bid
                    bid = order_book['bids'][0] if len(order_book['bids']) > 0 else [None, None]
                    bid_price = bid[0]
                    bid_amount = bid[1]
                    
                    # Get the lowest ask
                    ask = order_book['asks'][0] if len(order_book['asks']) > 0 else [None, None]
                    ask_price = ask[0]
                    ask_amount = ask[1]

                    # Write bid data to CSV
                    writer.writerow([current_minute_timestamp.strftime('%Y/%m/%d %H:%M:%S'), symbol, 'bid', bid_price, bid_amount])
                    
                    # Write ask data to CSV
                    writer.writerow([current_minute_timestamp.strftime('%Y/%m/%d %H:%M:%S'), symbol, 'ask', ask_price, ask_amount])
                    
                    # Flush the file buffer to ensure data is written
                    file.flush()

                # Update timestamp for the next minute
                current_minute_timestamp += datetime.timedelta(minutes=1)
                # Sleep for 1 second to keep the loop running every second
                time.sleep(1)
            
        except Exception as e:
            print(f"An error occurred: {e}")
            break
