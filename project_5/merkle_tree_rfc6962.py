import math

import random
import time
import string

import hashlib
import json

def merkle_tree(str):
    # 首先我们创建一个二维序列，一个维度存储树的层，一个存储树每层的节点
    mt = [[]]
    #接着开始考虑将数据逐步放到树中,树的高度为叶子节点数量取log向上取整加一（注意不是所有的树都可以这样，而是在这种特殊情况下，是满二叉树或者少一个叶子）
    n=len(str)
    depth=math.ceil(math.log(n,2))+1

    #然后对将hash后的单位数据存到叶子中
    mt[0]=[(hashlib.sha256(i.encode())).hexdigest() for i in str]

    #接着不断两两相加hash向上得到父节点，如果最后一个为单个则直接自己Hash
    for i in range(1, depth):
        l = math.floor(len(mt[i - 1]) / 2)#通过mt[i-1]得到本层节点数l

        mt.append(
            [(hashlib.sha256(mt[i - 1][2 * j].encode() + mt[i - 1][2 * j + 1].encode())).hexdigest() for
             j in range(0, l)])
        if len(mt[i - 1]) % 2 == 1:
            mt[i].append(mt[i - 1][-1])#[-1]是取最后一个元素，因为已经Hash过了，不需要再hash

    return mt


print("现在举个例子：",merkle_tree(["h","e","l","l","o"]))
