#!/usr/bin/env python31111
import sys
from io import TextIOWrapper as TextWrapper
import numpy as np
import random 

NMAX = 1000000
XMAX = 3500000
num = np.array([0] * NMAX)

def operation(insert, delete, queue) -> str:
  """"""
  delete += insert
  queue += delete
  
  op = np.random.randint(low=0, high=100)
  if op <= insert:
    return 'A'
  if op <= delete:
    return 'B'
  return 'C'

def random_sequence(data_file: TextWrapper, length, lo, hi, insert, delete, queue) -> None:
  """ generated an unordered sequence of operations """
  for i in range(0, int(length - 1)):
    
    interval = str(np.random.randint(low=lo, high=hi))
    data_file.write(operation(insert, delete, queue) + " " + interval + "\n")

def sorted_sequence(data_file : TextWrapper, length, lo, hi, insert, delete, queue) -> None:
  """ generate an ordered sequence of operations"""
  global num
  for i in range(0, int(length - 1)):
    interval = np.random.randint(low=lo, high=hi)
    num[i] = interval

  num = num[:int(length)]
  num = np.sort(a=num)
  
  for i in range(0,  int(length-1)):
    data_file.write(operation(insert, delete, queue) + " " + str(num[i]) + "\n")

def locality_sequence(data_file: TextWrapper, length, lo, hi, insert, delete, queue, dif) -> None:
  """ generate an unordered sequence of operations, with adjacent elements differening no more than dif"""
  start = np.random.randint(low=lo, high=hi)
  for i in range(0, int(length - 1)):
    interval = np.random.randint(low=start-dif, high=start+dif)
    data_file.write(operation(insert, delete, queue) + " " + str(interval) + "\n")  


def tc1(data_file : TextWrapper) -> None:
  """ random unsorted insertion"""
  data_file.write(str(NMAX) + "\n")
  random_sequence(data_file, NMAX, 0, XMAX, 100, 0, 0)


def tc2(data_file : TextWrapper) -> None:
  """random unsorted & segmented insertion"""
  data_file.write(str(NMAX) + "\n")
  for i in range(0,1000 - 1):
    random_sequence(data_file,NMAX / 1000, (XMAX / 1000) * i, (XMAX / 1000) * (i + 1), 100, 0, 0)

def tc3(data_file : TextWrapper) -> None:
  """sorted and segmented insertion"""
  data_file.write(str(NMAX)+ "\n")
  for i in range(0, 1000-1):
    sorted_sequence(data_file, NMAX / 1000, (XMAX / 1000) * i, (XMAX / 1000) * (i + 1), 100, 0, 0)

def tc4(data_file : TextWrapper) -> None:
  """first 1/3 random insert, last 2/3 random inserted/deletion"""
  data_file.write(str(NMAX) + "\n")
  random_sequence(data_file, NMAX / 3, 0, XMAX, 100, 0, 0)
  random_sequence(data_file, 2 * (NMAX / 3), 0, XMAX, 50, 50, 0)

def tc5(data_file : TextWrapper) -> None:
  """first 1/3 random insert, last 2/3 random local insert/delete"""
  data_file.write(str(NMAX) + "\n")
  random_sequence(data_file, NMAX / 3, 0, XMAX, 100, 0, 0)
  for i in range(0, 1000-1):
    random_sequence(data_file, 2 * (NMAX / 3) / 1000, (XMAX / 1000) * i, (XMAX / 1000) * (i + 1), 50, 50, 0)
  

def tc6(data_file : TextWrapper) -> None:
  """first 1/3 random insert, last 2/3 segment random local insert/delete"""
  data_file.write(str(NMAX) + "\n")
  random_sequence(data_file, NMAX / 3, 0, XMAX, 100, 0, 0)
  for i in range(0, 1000-1):
    sorted_sequence(data_file, 2 * (NMAX / 3) / 1000, (XMAX / 1000) * i, (XMAX / 1000) * (i + 1), 50, 50, 0)
  

def tc7(data_file : TextWrapper) -> None:
  """uniform insert/delete/search, random operation 1/3,1/3,1/3"""
  data_file.write(str(NMAX) + "\n")
  random_sequence(data_file, NMAX, 0, XMAX, 33, 33, 33)

def tc8(data_file : TextWrapper) -> None:
  """uniform insertion/deletion/search, segmented interval operation"""
  data_file.write(str(NMAX) + "\n")
  for i in range(0, 1000-1):
    random_sequence(data_file, NMAX / 1000, (XMAX / 1000) * i, (XMAX / 1000) * (i + 1), 33, 33, 33)

def tc9(data_file : TextWrapper) -> None:
  """uniform insertion/deletion/search, operation interval segmented, adjacent operations"""
  data_file.write(str(NMAX) + "\n")
  for i in range(0, 1000-1):
    locality_sequence(data_file, NMAX / 1000, (XMAX / 1000) * i, (XMAX / 1000) * (i + 1), 33, 33, 33, 10)

def main():
  testcase_num = sys.argv[1]
  testcase_func = "tc" + testcase_num
  data_file_name = "tc" + testcase_num + ".txt"
  data_file = open(file=data_file_name,mode="w")

  random.seed(0)
  print(data_file_name)
  globals()[testcase_func](data_file) # call testcase_ based on name
  data_file.close()


if __name__ == "__main__":
  main()