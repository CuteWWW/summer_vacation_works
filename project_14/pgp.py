#开始先导入gmssl模块
import math

import base64

import random


from gmssl import sm3, func


from gmssl import sm2, sm4



from gmssl.sm4 import CryptSM4, SM4_ENCRYPT, SM4_DECRYPT




def MOD(m, n):
    if math.isinf(m):
        return float('inf')
    else:
        return m % n




def MODMULT(a, b, n):
    if b == 0:
        r = float('inf')
    elif a == 0:
        r = 0
    else:
        t = bin(n - 2).replace('0b', '')
        y = 1
        i = 0
        while i < len(t):
            y = (y ** 2) % n
            if t[i] == '1':
                y = (y * b) % n
            i += 1
        r = (y * a) % n
    return r


def ADD(P, Q, a, p):
    if (math.isinf(P[0]) or math.isinf(P[1])) and (~math.isinf(Q[0]) and ~math.isinf(Q[1])):
        Z = Q
    elif (~math.isinf(P[0]) and ~math.isinf(P[1])) and (math.isinf(Q[0]) or math.isinf(Q[1])):
        Z = P
    elif (math.isinf(P[0]) or math.isinf(P[1])) and (math.isinf(Q[0]) or math.isinf(Q[1])):
        Z = [float('inf'), float('inf')]
    else:
        if P != Q:
            l = MODMULT(Q[1] - P[1], Q[0] - P[0], p)
        else:
            l = MODMULT(3 * P[0] ** 2 + a, 2 * P[1], p)
        X = MOD(l ** 2 - P[0] - Q[0], p)
        Y = MOD(l * (P[0] - X) - P[1], p)
        Z = [X, Y]
    return Z

def MULT(k, P, a, p):
    tmp = bin(k).replace('0b', '')
    l = len(tmp) - 1
    Z = P
    if l > 0:
        k = k - 2 ** l
        while l > 0:
            Z = ADD(Z, Z, a, p)
            l -= 1
        if k > 0:
            Z = ADD(Z, MULT(k, P, a, p), a, p)
    return Z



def keygen(a, p, n, G):
    # 私钥d

    d = random.randint(1, n - 2)
    # 公钥k

    k = MULT(d, G, a, p)
    return d, k


def pgp_enc(m, k):
    # padding
    l = 16
    n = len(m)
    if n % l != 0:
        num = l - (n % l)
    else:
        num = 0
    m = m + ('\0' * num)
    # str->bytes
    m = str.encode(m)
    k = str.encode(k)
    print("原文：\n", base64.b16encode(m))
    print("\n密钥：\n", base64.b16encode(k))

    # 使用SM4算法对消息进行加密
    SM4 = CryptSM4()
    SM4.set_key(k, SM4_ENCRYPT)
    c1 = SM4.crypt_ecb(m)

    # 使用SM2算法对密钥进行加密
    c2 = sm2_crypt.encrypt(k)
    print("密文：", base64.b16encode(c1))
    print("加密密钥：", base64.b16encode(c2))
    return c1, c2


def pgp_dec(c1, c2):
    k = sm2_crypt.decrypt(c2)
    SM4 = CryptSM4()
    SM4.set_key(k, SM4_DECRYPT)
    m = SM4.crypt_ecb(c1)

    print("\n解密密钥：\n", base64.b16encode(k))
    print("\n明文：\n", base64.b16encode(m))


if __name__ == '__main__':
    p = 0xFFFFFFFEFFBFCDAABDDDEAACBCBBAFEEAFFFFFFF00000000FFFFFFFFFFFFFFFF

    a = 0xFFFFFFFEFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF00000000FFFFFFFFFFFFFFFC

    b = 0x28E9FA9E9D9F5E344D5A9E4BCF6509A7F39789F515AB8F92DDBCBD414D940E93

    n = 0xFFFFFFFEFFFFFFFFFFFFFFFFFFFFFFFF7203DF6B21C6052B53BBF40939D54123

    x = 0x32C4AE2C1F1981195F9904466A39C9948FE30BBFF2660BE1715A4589334C74C7

    y = 0xBC3736A2F4F6779C59BDCEE36B692153D0A9877CC62A474002DF32E52139F0A0

    g = [x, y]
    [d, k] = keygen(a, p, n, g)

    sk = hex(d)[2:]
    pk = hex(k[0])[2:] + hex(k[1])[2:]

    sm2_crypt = sm2.CryptSM2(public_key=pk, private_key=sk)

    m = "ABCDEG"

    k = hex(random.randint(2 ** 127, 2 ** 128))[2:]

    r1, r2 = pgp_enc(m, k)
    pgp_dec(r1, r2)