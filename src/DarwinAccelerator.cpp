/*
 * DarwinAccelerator.cpp
 *
 *  Created on: 2017��10��28��
 *      Author: lambdaji
 */

#include "DarwinAccelerator.h"
#include "city.h"
#include "md5.h"
#include "murmur_hash3.h"
#include <glog/logging.h>
#include "boost/date_time/gregorian/gregorian.hpp"
#include "string"
#include <stdio.h>
#include <iostream>

using namespace boost::gregorian;
//6aa5c5d089cd8f08dd2cd9a4116488cb

void doMD5Hash(const ReqInfo & req_info, RspInfo& rsp_info)
{
	uint32_t layers = 1;
	if(req_info.has_layers())
		layers = req_info.layers();

	uint32_t shuffle = 1;
	if(req_info.has_shuffle())
		shuffle = req_info.shuffle();

	string dt_str = "";
	if(shuffle) {
		date today = boost::gregorian::day_clock::local_day();
	 	dt_str = to_iso_string(today);
	}
	std::cout << layers << "|" << shuffle << "|" << dt_str << "|" << BINS << std::endl;

	char buf[128];
	uint32_t flow_id = 0;

	//auto&& log = COMPACT_GOOGLE_LOG_INFO;
	//log.stream() << req_info.sguid() << "|" << layers << "|";
	for(size_t i = 1; i < layers+1; i++)
	{
		RspInfo_ExpLayerInfo& layer_info = *rsp_info.add_exp_info();
		layer_info.set_exp_layer(i);

		//hash_key
		snprintf(buf, 128, "%s%s%u", req_info.sguid().c_str(), dt_str.c_str(), i);
		MD5 md5;
		md5.update(buf);
		string str = md5.toString().substr(26, 6);
		uint32_t res = hex_to_decimal(str.c_str());
		flow_id = res % BINS + 1;
		layer_info.set_exp_id(flow_id);
		//log.stream() << flow_id;
		std::cout << "layer=" << i << "|" << buf << "|" << flow_id << std::endl;
	}

}


void doMurmurHash(const ReqInfo & req_info, RspInfo& rsp_info)
{
	uint32_t layers = 1;
	if(req_info.has_layers())
		layers = req_info.layers();

	uint32_t shuffle = 1;
	if(req_info.has_shuffle())
		shuffle = req_info.shuffle();

	string dt_str = "";
	if(shuffle) {
		date today = boost::gregorian::day_clock::local_day();
	 	dt_str = to_iso_string(today);
	}

	char buf[128];
	uint32_t flow_id = 0;
	uint32_t mur_val = 0;

	//auto&& log = COMPACT_GOOGLE_LOG_INFO;
	//log.stream() << req_info.sguid() << "|" << layers << "|";
	for(size_t i = 1; i < layers+1; i++)
	{
		RspInfo_ExpLayerInfo& layer_info = *rsp_info.add_exp_info();
		layer_info.set_exp_layer(i);

		//hash_key
		snprintf(buf, 128, "%s%s%u", req_info.sguid().c_str(), dt_str.c_str(), i);
		MurmurHash3_x64_32(buf, 128, MURMUR_SEED, &mur_val);
		flow_id = mur_val % BINS + 1;
		layer_info.set_exp_id(flow_id);
		//log.stream() << flow_id;
	}

}


void doCityHash(const ReqInfo & req_info, RspInfo& rsp_info)
{
	uint32_t layers = 1;
	if(req_info.has_layers())
		layers = req_info.layers();

	uint32_t shuffle = 1;
	if(req_info.has_shuffle())
		shuffle = req_info.shuffle();

	string dt_str = "";
	if(shuffle) {
		date today = boost::gregorian::day_clock::local_day();
	 	dt_str = to_iso_string(today);
	}

	char buf[128];
	uint32_t flow_id = 0;
	uint64_t city_val = 0;
	//auto&& log = COMPACT_GOOGLE_LOG_INFO;
	//log.stream() << req_info.sguid() << "|" << layers << "|";
	for(size_t i = 1; i < layers+1; i++)
	{
		RspInfo_ExpLayerInfo& layer_info = *rsp_info.add_exp_info();
		layer_info.set_exp_layer(i);

		//hash_key
		snprintf(buf, 128, "%s%s%u", req_info.sguid().c_str(), dt_str.c_str(), i);
		city_val = CityHash64(buf,strlen(buf));
		flow_id = city_val % BINS + 1;
		layer_info.set_exp_id(flow_id);
		//log.stream() << flow_id;
	}

}


