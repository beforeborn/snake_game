/*
 * Util.cpp
 *
 *  Created on: 2014年4月15日
 *      Author: h3c
 */
/**
 * 交换x，y的值
 */
void  swap(int & x, int &y) {
	x ^= y;
	y ^= x;
	x ^= y;
}

/**
 * 获取数字num转换为二进制后1的数量
 */
int  getOneCount(int num) {
	int count = 0;
	while (num) {
		num = num & (num - 1);
		count++;
	}
	return count;
}

/**
 * 获取数字是否是2的幂
 */
bool  is2Pow(int num) {
//	if (1 == getOneCount(num)) {
//		return true;
//	} else {
//		return false;
//	}
	if (num & (num - 1)) {
		return true;
	} else {
		return false;
	}
}

