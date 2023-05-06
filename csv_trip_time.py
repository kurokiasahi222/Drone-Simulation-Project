import pandas as pd

def trip_time(file_name):
    df = pd.read_csv(file_name)
    undelivered_robots = df[(df["type"]=='robot') & (df["delivered"] == 0)]
    return undelivered_robots["totalTime"].max()

file = input("Enter CSV File Name: ")
print(trip_time(file))