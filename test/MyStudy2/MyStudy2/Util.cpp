/*
 * Util.cpp
 *
 *  Created on: 2014��4��15��
 *      Author: h3c
 */
/**
 * ����x��y��ֵ
 */
void  swap(int & x, int &y) {
	x ^= y;
	y ^= x;
	x ^= y;
}

/**
 * ��ȡ����numת��Ϊ�����ƺ�1������
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
 * ��ȡ�����Ƿ���2����
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

