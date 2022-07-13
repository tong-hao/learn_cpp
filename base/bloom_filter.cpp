
#include <algorithm>
#include <cmath>
#include <cstddef>
#include <cstdlib>
#include <iterator>
#include <limits>
#include <string>
#include <vector>

unsigned int SDBMHash(const char *str);
unsigned int RSHash(const char *str);
unsigned int JSHash(const char *str);
unsigned int PJWHash(const char *str);
unsigned int APHash(const char *str);
unsigned int DJBHash(const char *str);
unsigned int ELFHash(const char *str);
unsigned int BKDRHash(const char *str);

unsigned int SDBMHash(const char *str) {
	unsigned int hash = 0;
	while (*str) {
		// equivalent to: hash = 65599*hash + (*str++);
		hash = (*str++) + (hash << 6) + (hash << 16) - hash;
	}
	return (hash & 0x7FFFFFFF);
}

// RS Hash Function
unsigned int RSHash(const char *str) {
	unsigned int b = 378551;
	unsigned int a = 63689;
	unsigned int hash = 0;
	while (*str) {
		hash = hash * a + (*str++);
		a *= b;
	}
	return (hash & 0x7FFFFFFF);
}

// JS Hash Function
unsigned int JSHash(const char *str) {
	unsigned int hash = 1315423911;
	while (*str) {
		hash ^= ((hash << 5) + (*str++) + (hash >> 2));
	}
	return (hash & 0x7FFFFFFF);
}

// P. J. Weinberger Hash Function
unsigned int PJWHash(const char *str) {
	unsigned int BitsInUnignedInt = (unsigned int)(sizeof(unsigned int) * 8);
	unsigned int ThreeQuarters = (unsigned int)((BitsInUnignedInt * 3) / 4);
	unsigned int OneEighth = (unsigned int)(BitsInUnignedInt / 8);
	unsigned int HighBits = (unsigned int)(0xFFFFFFFF)
	                        << (BitsInUnignedInt - OneEighth);
	unsigned int hash = 0;
	unsigned int test = 0;
	while (*str) {
		hash = (hash << OneEighth) + (*str++);
		if ((test = hash & HighBits) != 0) {
			hash = ((hash ^ (test >> ThreeQuarters)) & (~HighBits));
		}
	}
	return (hash & 0x7FFFFFFF);
}

// AP Hash Function
unsigned int APHash(const char *str) {
	unsigned int hash = 0;
	int i;
	for (i = 0; *str; i++) {
		if ((i & 1) == 0) {
			hash ^= ((hash << 7) ^ (*str++) ^ (hash >> 3));
		} else {
			hash ^= (~((hash << 11) ^ (*str++) ^ (hash >> 5)));
		}
	}
	return (hash & 0x7FFFFFFF);
}

// DJB Hash Function
unsigned int DJBHash(const char *str) {
	unsigned int hash = 5381;
	while (*str) {
		hash += (hash << 5) + (*str++);
	}
	return (hash & 0x7FFFFFFF);
}

// ELF Hash Function
unsigned int ELFHash(const char *str) {
	unsigned int hash = 0;
	unsigned int x = 0;
	while (*str) {
		hash = (hash << 4) + (*str++);
		if ((x = hash & 0xF0000000L) != 0) {
			hash ^= (x >> 24);
			hash &= ~x;
		}
	}
	return (hash & 0x7FFFFFFF);
}

// BKDR Hash Function
unsigned int BKDRHash(const char *str) {
	unsigned int seed = 131;  // 31 131 1313 13131 131313 etc..
	unsigned int hash = 0;
	while (*str) {
		hash = hash * seed + (*str++);
	}
	return (hash & 0x7FFFFFFF);
}

#ifndef BLOOMFILTER_H
#define BLOOMFILTER_H

#include <math.h>
#include <stdio.h>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>

#define INT_SIZE 32
#define BUFFER_SIZE 1024

class BloomFilter {
public:
	//样本个数n，期望的失误率p，传入样本的文档路径
	BloomFilter(double errRate, int sampleNum);
	~BloomFilter();
	void filterInit();  //初始化布隆过滤器
	void arrayGenerate(
	    std::string path);  //打开path路径的文档，计算每一行样本到array中
	bool isContain(const char *str);  //查看字符串是否在样本中存在
	void storeArray(std::string path);  //把array存储在指定路径文件path里
	void restoreArray(std::string path);  //把array从指定路径文件path里恢复载入
	int getHashFunNum();  //返回需要的哈希函数的个数k
	int getIntNum();      //返回需要的内存的int数
private:
	int hashtableInit();  //把几个哈希函数加入到hastable中
	std::string path;     //传入样本的文档路径
	double errRate;       //样本失误率p
	int sampleNum;        //样本个数n
	int bitNum;           //需要的二进制位数m
	int intNum;           //需要申请内存的int数
	int hashFunNum;  //需要的哈希函数的个数k,注意计算得到的哈希函数个数k应该<=hashtable.size();
	int *array;      //内存
	std::vector<unsigned int (*)(const char *)>
	    hashtable;  //存放计算字符串哈希值的哈希函数
};
#endif  // BLOOMFILTER_H

BloomFilter::BloomFilter(double errRate, int sampleNum) {
	this->errRate = errRate;
	this->sampleNum = sampleNum;
	this->bitNum =
	    -((this->sampleNum * log(this->errRate)) / (log(2) * log(2)));
	this->hashFunNum = 0.7 * (this->bitNum / this->sampleNum);
	this->intNum = this->bitNum / INT_SIZE + 1;
	array = new int[this->intNum];
}

BloomFilter::~BloomFilter() {
	delete[] array;
}

void BloomFilter::filterInit() {
	hashtableInit();
	if (this->hashFunNum > (int)hashtable.size()) {
		std::cout << "哈希函数不足,请添加" << std::endl;
		return;
	}
}

int BloomFilter::hashtableInit() {
	hashtable.push_back(*PJWHash);
	hashtable.push_back(*JSHash);
	hashtable.push_back(*RSHash);
	hashtable.push_back(*SDBMHash);
	hashtable.push_back(*APHash);
	hashtable.push_back(*DJBHash);
	hashtable.push_back(*BKDRHash);
	hashtable.push_back(*ELFHash);
	return hashtable.size();
}

void BloomFilter::arrayGenerate(std::string path) {
	int hashval;
	std::fstream fs;
	fs.open(path.c_str(), std::ios::in | std::ios::out);
	if (!fs) {
		perror("open file error");
		return;
	}
	fs.seekp(std::ios::beg);
	char buf[BUFFER_SIZE] = {0};
	fs.getline(buf, BUFFER_SIZE);
	while (!fs.eof()) {
		for (int i = 0; i != this->hashFunNum; i++) {
			hashval = hashtable[i](buf);
			hashval = hashval % (this->intNum * INT_SIZE);
			this->array[hashval / INT_SIZE] |= (0x1 << (hashval % INT_SIZE));
		}
		fs.getline(buf, BUFFER_SIZE);
	}
	fs.clear();
	fs.close();
}

bool BloomFilter::isContain(const char *str) {
	int hashval;
	for (int i = 0; i != this->hashFunNum; i++) {
		hashval = hashtable[i](str);
		hashval = hashval % (this->intNum * INT_SIZE);
		if (array[hashval / INT_SIZE] & (0x1 << (hashval % INT_SIZE)))
			continue;
		else
			return false;
	}
	return true;
}

void BloomFilter::storeArray(std::string path) {
	std::fstream fs;
	fs.open(path.c_str(), std::ios::in | std::ios::out);
	if (!fs) {
		fs.open(path.c_str(), std::ios::app | std::ios::in | std::ios::out);
		for (int k = 0; k < this->intNum; k++)
			fs << array[k] << std::endl;
	} else {
		fs.seekp(std::ios::beg);
		for (int k = 0; k < this->intNum; k++)
			fs << array[k] << std::endl;
	}
	fs.clear();
	fs.close();
}

void BloomFilter::restoreArray(std::string path) {
	std::fstream fs;
	fs.open(path.c_str(), std::ios::in | std::ios::out);
	if (!fs) {
		perror("open file error");
		return;
	}
	fs.seekp(std::ios::beg);
	char buf[INT_SIZE] = {0};
	fs.getline(buf, INT_SIZE);
	int i = 0;
	while (!fs.eof()) {
		sscanf(buf, "%d\n", &this->array[i++]);
		fs.getline(buf, INT_SIZE);
	}
	fs.clear();
	fs.close();
}

int BloomFilter::getHashFunNum() {
	return this->hashFunNum;
}

int BloomFilter::getIntNum() {
	return this->intNum;
}

int main() {
	BloomFilter mybloom(0.0001, 10000000000);
	mybloom.filterInit();
	mybloom.arrayGenerate("../tool/redlist.txt");
	std::cout << "intNum:" << mybloom.getIntNum()
	          << ",hashFunNum:" << mybloom.getHashFunNum() << std::endl;
	std::cout << "www.dubai.com在我的集合中吗:"
	          << (mybloom.isContain("www.dubai.com") ? "在" : "不在")
	          << std::endl;
	std::cout << "www.qq.com在我的集合中吗:"
	          << (mybloom.isContain("www.qq.com") ? "在" : "不在") << std::endl;
	mybloom.storeArray("../tool/bloom_array.txt");
	return 0;
}

// link: -lfmt