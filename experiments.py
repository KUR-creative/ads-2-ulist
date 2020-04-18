'''
node size
linked list .vs. unrolled linked list

insert/remove from front
insert/remove from back

insert/remove random position
'''

import subprocess as sp
import sys

import yaml
import matplotlib.pyplot as plt
import funcy as F
from tqdm import tqdm

def expr_result(num_data, node_size):
    ''' experiment result in milli second '''
    return yaml.safe_load(
        sp.check_output(
            #['./main', str(int(num_data)), str(int(node_size))],
            ['./main', str(num_data), str(node_size)],
            universal_newlines=True))

expr = expr_result(1e3, 50)
print(expr)
