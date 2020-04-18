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

#tup = lambda f: lambda argtup: f(*argtup)

def expr_result(num_data, node_size):
    ''' experiment result in milli second '''
    return yaml.safe_load(
        sp.check_output(
            ['./main', str(int(num_data)), str(int(node_size))],
            universal_newlines=True))

#expr = expr_result(1e3, 50)
#print(expr)

#expr1: same data size, diff node size
from pprint import pprint
def expr1():
    def fixed_data_diff_node_size(
            num_data = int(1e4),
            num_expr = 30,
            #max_node_size = int(2e4)
            max_node_size = int(100)
        ):
        block = max_node_size // num_expr 
        exprs = list(tqdm(
            map(expr_result, 
                F.repeat(num_data, num_expr),
                [1] + [n * block for n in range(1,num_expr)]),
                #[n * block for n in range(1,num_expr)]),
            total = num_expr
        ))
        pprint(exprs)
        return exprs

    num_data = int(1e4)
    exprs = fixed_data_diff_node_size(num_data = num_data)
    with open('fix_nd_%d_diff_ns.yml' % (num_data,), 'w') as f:
        yaml.dump(F.join_with(list, exprs), f)
    with open('fix_nd_%d_diff_ns.yml' % (num_data,)) as f:
        result_dic = yaml.safe_load(f)

    pprint(result_dic)
    x_key = 'node.size'
    y_keys = F.lremove({x_key, 'data.num'}, result_dic.keys())
    y_keys = F.lfilter(lambda s: 'ul' in s, y_keys)
    print(y_keys)

    xs = result_dic[x_key]
    print(xs)
    for key in y_keys:
        plt.plot(xs, result_dic[key], label=key,
                 marker='x' if 'insert' in key else '.',
                 linestyle='-' if 'insert' in key else '--')
     
    plt.xlabel('node size')
    plt.ylabel('milli seconds')
    plt.legend()
    plt.show()

#plt.plot(
#expr2: diff data size, fixed node sizes
def expr2():
    def fixed_node_size_diff_data(
            num_data = int(1e4),
            num_expr = 30,
            #max_node_size = int(2e4)
            max_node_size = int(100)
        ):
        block = max_node_size // num_expr 
        exprs = list(tqdm(
            map(expr_result, 
                F.repeat(num_data, num_expr),
                [1] + [n * block for n in range(1,num_expr)]),
                #[n * block for n in range(1,num_expr)]),
            total = num_expr
        ))
        pprint(exprs)
        return exprs

    num_data = int(1e4)
    exprs = fixed_data_diff_node_size(num_data = num_data)
    with open('fix_ns_%d_diff_nd.yml' % (num_data,), 'w') as f:
        yaml.dump(F.join_with(list, exprs), f)
    with open('fix_ns_%d_diff_nd.yml' % (num_data,)) as f:
        result_dic = yaml.safe_load(f)

    pprint(result_dic)
    x_key = 'node.size'
    y_keys = F.lremove({x_key, 'data.num'}, result_dic.keys())
    y_keys = F.lfilter(lambda s: 'ul' in s, y_keys)
    print(y_keys)

    xs = result_dic[x_key]
    print(xs)
    for key in y_keys:
        plt.plot(xs, result_dic[key], label=key,
                 marker='x' if 'insert' in key else '.',
                 linestyle='-' if 'insert' in key else '--')
     
    plt.xlabel('node size')
    plt.ylabel('milli seconds')
    plt.legend()
    plt.show()

expr1()
#expr2()
