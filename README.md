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

