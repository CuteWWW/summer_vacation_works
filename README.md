# summer_vacation_works

## project1

### 原理
生日攻击：通过在hash函数的取值域内随机选择明文，并比较其加密后的密文是否一致，如果一致，则说明产生了hash碰撞，也就是生日攻击。复杂度为O（n^1/2)

### 实现
每次随机选择一对明密文对进行比较，如果有密文相同的情况则成功碰撞，也就是说成功生日攻击。

### 结果
生日攻击虽然降低了攻击方法（相对于穷举）的时间复杂度，但是个概率算法，有可能很快也有可能很慢才得到一对碰撞。经过多次尝试之后，得到了一次较短时间的攻击结果。
本次实验的Iv是8*4*8=256bits
![image](https://github.com/CuteWWW/summer_vacation_works/blob/main/1.png)

## project2

### 原理
通过对某一指定明文不断循环hash,并将每轮hash结果与原hash结果比较，如果一样则碰撞成功。

### 结果
![image](https://github.com/CuteWWW/summer_vacation_works/blob/main/2.png)

## project3

### 原理
针对sm3,sha256的长度扩展攻击，我们可以先对初始明文加密，并利用此密文作为初始向量对扩展明文进行加密，最终得到我们想要的扩展明文加密的密文，将这个密文与（plaintext||padding||extension）加密后的结果进行比较，如果相等，则攻击成功。(注意，由于本.c文件的要求，其sm3加密时对消息的填充不是自动的，第一步对初始明文加密时要先手动填充成plaintext||padding再使用迭代函数，后面也没再填充，也就是说将pad单独拿出来后,**实际上比较的是hash(plaintext||padding||ext,iv） == hash(ext,hash(plaintext||padding,iv))**

### 结果
一.  **验证**  hash(plaintext||padding||ext,iv） == hash(ext,hash(plaintext||padding,iv))

![image](https://github.com/CuteWWW/summer_vacation_works/blob/main/project3/3.1.png)

二.  **验证**  hash(plaintext||padding1||ext||padding3,iv） != hash(ext||padding2,hash(plaintext||padding,iv))  padding 1对应plaintext,2对应ext,3对应plaintext||padding1||ext

![image](https://github.com/CuteWWW/summer_vacation_works/blob/main/project3/3.2.png)

## project5

### 原理

merkle tree 由ralph merkle提出，本质上是用于数据的完整性校验提出的。而所谓的完整性校验，就是检验一下我们的数据是否被恶意篡改或者被伪造过。同时，如果没有Merkle tree,我们的区块链只能通过一个巨大而臃肿的交易记录头来保证交易的可靠性，而通过将这些数据分块存储校验的merkle tree，我们能过更快更便捷的完成交易数据存储与安全性保障。一般意义上来讲，它是哈希大量聚集数据“块”的一种方式，它依赖于将这些数据“块”分裂成较小单位的数据块，每一个bucket块仅包含几个数据“块”，然后取每个bucket单位数据块再次进行哈希，重复同样的过程，直至剩余的哈希总数仅变为一。

![image](https://github.com/CuteWWW/summer_vacation_works/blob/main/project_5/5_2.png)

在最底层，和哈希列表一样，我们把数据分成小的数据块，有相应地哈希和它对应。但是往上走，并不是直接去运算根哈希，而是把相邻的两个哈希合并成一个字符串，然后运算这个字符串的哈希。并且如果存在单个的数据，则直接向上存储，不必再次hash.同时，我们如果想要进行p2p传输，为了验证数据的完整性，也只需要分块验证即可，不需要像hash list那样把整个表进行比对，大大加快了完整性验证效率。

### 实现

我们首先实现一个二维数组，目的是为了存储一个二维的merkle tree,一个维度存储层数，一个维度存储每层的节点。

![image](https://github.com/CuteWWW/summer_vacation_works/blob/main/project_5/5_3.png)

接着我们将数据拆开分别hash,并放入初始叶子节点。然后将他们两两合并hash，向上存入父节点，如果落单直接向上存储，不需要二次hash，重复步骤，直到只剩一个节点为止。

### 结果

![image](https://github.com/CuteWWW/summer_vacation_works/blob/main/project_5/5_4.png)
![image](https://github.com/CuteWWW/summer_vacation_works/blob/main/project_5/5_5.png)

## project6

### 原理

![image](https://github.com/CuteWWW/summer_vacation_works/blob/main/project_6/6_1.png)

本实验的本质是构建一个交互式的零知识证明协议。
首先Alice随机生成一个128bit的大整数记作s,计算其k=2100-1978次hash（sha256)计算并记录第22次hash结果（记作p)与最后的第128次hash结果（记作c),将（p,c)传给Bob。
Bob接收到(p,c)后，将p进行k'=2100-2000次hash(sha256)计算，并记录最后结果为c',比较c与c'是否一致，如果一致，则证明Alice的确年龄大于21岁，且Bob没有得到任何有关Alice具体多少岁的有关信息。

本实验主要通过socket套接字实现交互功能。借用CDSN上的解释，Socket是指套接字，是对网络中不同主机上的应用进程之间进行双向通信的端点的一种抽象。一个套接字就是网络上进程通信的一端，提供了应用层进程利用网络协议交换数据的机制。

![image](https://github.com/CuteWWW/summer_vacation_works/blob/main/project_6/6_2.png)

### 实现

![image](https://github.com/CuteWWW/summer_vacation_works/blob/main/project_6/6_3.png)
![image](https://github.com/CuteWWW/summer_vacation_works/blob/main/project_6/6_4.png)

让Alice担任服务器端，创建socket，设置ip  port,进行监听，准备工作中，使用randint指定成128bit长随机整数，然后计算c与p。当与Bob连接后，发送helloBob与Bob打招呼，Bob接收到招呼后发送想要p,c的请求，Alice逐一发送p,c,然后计算c',并与c进行比较，如果一致，则发送验证成功的消息，然后双方均关闭连接，完成协议。

### 结果

![image](https://github.com/CuteWWW/summer_vacation_works/blob/main/project_6/6_5.png)
![image](https://github.com/CuteWWW/summer_vacation_works/blob/main/project_6/6_6.png)
