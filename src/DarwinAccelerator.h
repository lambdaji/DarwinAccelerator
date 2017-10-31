/*
 * DarwinAccelerator.h
 *
 *  Created on: 2017Äê10ÔÂ28ÈÕ
 *      Author: lambdaji
 */

#ifndef DARWINACCELERATOR_H_
#define DARWINACCELERATOR_H_

#include "expinfo.pb.h"
using namespace DarwinProto;


#define MURMUR_SEED 0x3c074a61
#define BINS 1000

class DarwinAccelerator
{
public:
	DarwinAccelerator();
	~DarwinAccelerator();
	void doMD5Hash(const ReqInfo & req_info, RspInfo& rsp_info);
	void doMurmurHash(const ReqInfo & req_info, RspInfo& rsp_info);
	void doCityHash(const ReqInfo & req_info, RspInfo& rsp_info);
};

static int32_t hex_table[] = { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
		0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
		0, 0, 0, 0, 0, 0, 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 0, 0, 0, 0, 0, 0, 0, 10,
		11, 12, 13, 14, 15, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
		0, 0, 0, 0, 0, 0, 0, 0, 0, 10, 11, 12, 13, 14, 15 };

inline int32_t hex_to_decimal(const char* hex_str) {
	char ch;
	int32_t ret = 0;
	while (ch = *hex_str++) {
		ret = (ret << 4) | hex_table[ch];
	}
	return ret;
}

#endif /* DARWINACCELERATOR_H_ */
