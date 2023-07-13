# summer_vacation_works

## project1

### 原理
生日攻击：通过在hash函数的取值域内随机选择明文，并比较其加密后的密文是否一致，如果一致，则说明产生了hash碰撞，也就是生日攻击。复杂度为O（n^1/2)

### 实现
每次随机选择一对明密文对进行比较，如果有密文相同的情况则成功碰撞，也就是说成功生日攻击。

### 结果
生日攻击虽然降低了攻击方法（相对于穷举）的时间复杂度，但是个概率算法，有可能很快也有可能很慢才得到一对碰撞。经过很多次尝试之后，终于得到了一次较短时间的攻击结果。
本次实验的Iv是8*4*8=256bits
