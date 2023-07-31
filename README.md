# summer_vacation_works

**所有的实验报告均在此**

**目前已经完成project 1,2,3,5,6,9,11,17**

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

## project9

### 原理

![image](https://github.com/CuteWWW/summer_vacation_works/blob/main/project_9/9_2.png)

因为DES的加密密钥空间太小容易被攻破，而三重DES又可以被中间相遇攻击所克制，所以，AES是现在流行使用的高级对称加密算法。AES采用分组密码的工作模式，每128bit为一组进行加密，而密钥也是128bit的，在加密过程中，使用了扩散与混淆的手法，包括轮密钥加、字节替换、行变换、列混淆等，并且一般要进行10轮加密函数（当然，如果密钥长度不同，加密轮数也不同），充分使得加密过程更加安全可靠，减小了攻击者破解AES算法的可能性。

![image](https://github.com/CuteWWW/summer_vacation_works/blob/main/project_9/9_9.png)
![image](https://github.com/CuteWWW/summer_vacation_works/blob/main/project_9/9_17.png)

SM4是国密算法中的对称加密函数，同样使用128bit的分组与密钥长度，但是轮密钥长度仅有32bit，并且总的加密轮数也达到了32轮。

### 实现

![image](https://github.com/CuteWWW/summer_vacation_works/blob/main/project_9/9_4.png)
![image](https://github.com/CuteWWW/summer_vacation_works/blob/main/project_9/9_5.png)

首先是密钥扩展函数，我们将128bit的原始密钥输入函数，函数自动将其拆分进4*4的单位为字节的矩阵，然后通过公式迭代推导下一轮的密钥，一共可以得到11个128bit密钥，除了一个初始密钥，剩下的按顺序为第一轮、第二轮......的轮密钥。然后将密钥倒序赋值给另一个数组，得到加密轮密钥。接着，是轮密钥加函数，将对应部分的密钥与明文进行异或即可。

![image](https://github.com/CuteWWW/summer_vacation_works/blob/main/project_9/9_6.png)
![image](https://github.com/CuteWWW/summer_vacation_works/blob/main/project_9/9_3.png)

接着是字节替换，我们通过对应位置字节（前四位对应S盒行值，后四位对应S盒列值）找到相应的S盒数据进行替换。

![image](https://github.com/CuteWWW/summer_vacation_works/blob/main/project_9/9_7.png)
![image](https://github.com/CuteWWW/summer_vacation_works/blob/main/project_9/9_8.png)

最后是行变换和列混淆，列混淆使用矩阵右乘，且为异或相乘。

通过加密函数将明文按照128bit进行分割，按照ECB的工作模式进行加密。解密过程则是使用上述过程的逆过程与逆函数实现。

![image](https://github.com/CuteWWW/summer_vacation_works/blob/main/project_9/9_10.png)
![image](https://github.com/CuteWWW/summer_vacation_works/blob/main/project_9/9_11.png)

以上是s盒，fk,ck的构成。

![image](https://github.com/CuteWWW/summer_vacation_works/blob/main/project_9/9_12.png)
![image](https://github.com/CuteWWW/summer_vacation_works/blob/main/project_9/9_13.png)
![image](https://github.com/CuteWWW/summer_vacation_works/blob/main/project_9/9_14.png)
这是T函数 T'函数 RK函数。

![image](https://github.com/CuteWWW/summer_vacation_works/blob/main/project_9/9_15.png)

加密过程如图

### 结果
AES
![image](https://github.com/CuteWWW/summer_vacation_works/blob/main/project_9/9_1.png)
SM4
![image](https://github.com/CuteWWW/summer_vacation_works/blob/main/project_9/9_16.png)

## project11

### 原理

![image](https://github.com/CuteWWW/summer_vacation_works/blob/main/project_11/11_2.png)
![image](https://github.com/CuteWWW/summer_vacation_works/blob/main/project_11/11_3.png)
![image](https://github.com/CuteWWW/summer_vacation_works/blob/main/project_11/11_4.png)

sm2是国产基于椭圆曲线的签名算法。
其基础参数一般如下：
![image](https://github.com/CuteWWW/summer_vacation_works/blob/main/project_11/11_5.png)

然后是其他步骤
![image](https://github.com/CuteWWW/summer_vacation_works/blob/main/project_11/11_5.png)
![image](https://github.com/CuteWWW/summer_vacation_works/blob/main/project_11/11_6.png)
![image](https://github.com/CuteWWW/summer_vacation_works/blob/main/project_11/11_7.png)
![image](https://github.com/CuteWWW/summer_vacation_works/blob/main/project_11/11_8.png)
![image](https://github.com/CuteWWW/summer_vacation_works/blob/main/project_11/11_9.png)
![image](https://github.com/CuteWWW/summer_vacation_works/blob/main/project_11/11_10.png)

参考文献：https://blog.csdn.net/u013137970/article/details/84573200

### 结果
![image](https://github.com/CuteWWW/summer_vacation_works/blob/main/project_11/11_1.png)

## project14

### 原理
![image](https://github.com/CuteWWW/summer_vacation_works/blob/main/project_14/14_2.png)

Pretty Good Privacy（PGP）是一个加密程序，为数据通信提供加密隐私和身份验证。PGP 用于对文本、电子邮件、文件、目录和整个磁盘分区进行签名、加密和解密，并提高电子邮件通信的安全性。PGP加密使用散列，数据压缩，对称密钥加密，最后是公钥加密的串行组合。其中最关键的是两种形式的加密的组合：对称密钥加密(Symmetric Cryptography)和非对称密钥加密(Asymmetric cryptography)。在实现PGP加密的过程中，首先使用对称密钥加密算法对原始数据进行加密。对称密钥加密算法包括DES、AES、Blowfish等，这些算法能够快速地加密和解密数据，但是需要发送方和接收方之间共享密钥。为了避免在网络上传输密钥，PGP使用了公钥加密算法。公钥加密算法是一种使用不同的密钥加密和解密的算法，其中公钥用于加密，而私钥用于解密。公钥加密算法包括RSA、DSA等，这些算法具有极高的安全性，但是加密和解密速度比对称密钥加密算法慢得多。PGP将对称密钥加密，并使用接收方的公钥进行加密。这种方式可以保证密钥的安全性，同时可以确保只有接收方可以解密对称密钥，从而保护了数据的机密性。接收方使用自己的私钥对加密的对称密钥进行解密，然后使用对称密钥对数据进行解密。这种方式既可以保护数据的安全性，也可以提高加解密的速度。

### 结果

![image](https://github.com/CuteWWW/summer_vacation_works/blob/main/project_14/14_1.png)

## project17

**存储方式** Firefox使用的是“登录管理器”来存储和管理用户的密码信息，而谷歌使用的是“密码管理器”。这两种存储方式在数据结构和加密算法上可能会有所不同。

**自动填充** Firefox的记住密码功能可以自动填充登录表单，用户只需点击用户名输入框，浏览器会自动弹出已保存的用户名列表供选择。而谷歌浏览器在输入用户名时会自动匹配已保存的用户名，并在用户名输入框下方显示下拉列表，用户可以选择其中的用户名进行自动填充。

**同步功能** 谷歌浏览器的记住密码功能可以通过用户的Google账号进行同步，使得在不同设备上使用同一个账号登录时能够自动填充密码。而Firefox则需要通过Firefox账号进行同步，但同步功能的实现可能会有一些差异。

**安全性** Firefox和谷歌浏览器在密码存储和加密方面都有一定的安全措施，但具体实现可能会有所不同。谷歌浏览器的密码管理器支持使用主密码进行加密，而Firefox的登录管理器也有一些安全措施来保护用户的密码信息。

总体来说，Firefox和谷歌浏览器的记住密码插件在实现上有一些细微的差别，包括存储方式、自动填充、同步功能和安全性等方面。用户可以根据自己的需求和偏好选择适合自己的浏览器和插件。
