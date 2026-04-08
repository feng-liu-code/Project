#include "modbus.h"
#include <cstdio>
#include <cstring>
#include <iostream>

//模拟从机保持寄存器(1~10)
vector<uint16_t> g_holding_reg = {1,2,3,4,5,6,7,8,9,10};

//CRC计算(modbus 标准)
uint16_t CRC16(const uint8_t* data, size_t len) {
	uint16_t crc = 0xFFFF;
	for(size_t i = 0; i < len; i++) {
		crc ^= data[i];
		for(int j = 0; j < 8; j++) {
			if(crc & 1) {
				crc = (crc >> 1) ^ 0xA001;
			}else {
				crc = crc >> 1;
			}
		}
	}
	return crc;
}

vector<uint8_t> ModbusCmd(uint8_t slave_addr, uint8_t func, uint16_t addr, uint16_t val) {
	vector<uint8_t> buf;
	buf.push_back(slave_addr);
	buf.push_back(func);
	buf.push_back((addr >> 8)& 0xFF);
	buf.push_back(addr & 0xFF);
	buf.push_back((val >> 8)& 0xFF);
	buf.push_back(val & 0xFF);
	uint16_t crc = CRC16(buf.data(), buf.size());
	buf.push_back(crc & 0xFF); //CRC低字节
	buf.push_back((crc >> 8) & 0xFF);
	
	return buf;
}

vector<uint8_t> ModbusResp(const vector<uint8_t>& req) {
	vector<uint8_t> resp;
	if(req.size() < 8) {
		cerr << "[从机] 无效报文长度: " << req.size() << endl;
		return resp;
	}

	size_t data_len = req.size() - 2;
	uint16_t recv_crc = (req[data_len + 1] << 8) | req[data_len];
	uint16_t calc_crc = CRC16(req.data(), data_len);

	if(recv_crc != calc_crc) {
		cerr << "[从机] CRC校验失败!" << endl;
		return resp;
	}

	uint8_t slave_addr = req[0];
	uint8_t func = req[1];
	uint16_t addr = (req[2] << 8) | req[3];
	uint16_t val = (req[4] << 8) | req[5];

	printf("[从机] 解析: 地址=%d, 功能码=0x%02X, 寄存器地址=%d, 值=%d\n", slave_addr, func, addr, val);

	if(func == FUNC_READ_HOLDING_REG) {
		resp.push_back(slave_addr);
		resp.push_back(func);
		resp.push_back(val * 2);

		for(int i = 0; i < val; i++) {
			uint16_t reg_val = g_holding_reg[addr + i];
			resp.push_back((reg_val >> 8) & 0xFF);
			resp.push_back(reg_val & 0xFF);
		}

		uint16_t crc = CRC16(resp.data(), resp.size());
		resp.push_back(crc & 0xFF);
		resp.push_back((crc >> 8) & 0xFF);
	}else if(func == FUNC_WRITE_SINGLE_REG) {
		g_holding_reg[addr] = val;
		resp = req;
		printf("[从机] 写入成功: 地址: %d, 值: %d\n", addr, val);
	}

	return resp;
}

void printHex(const string& title, const vector<uint8_t>& data) {
	printf("%s ", title.c_str());
	for(uint8_t b : data) {
		printf("%02X ", b);
	}
	printf("\n");
}

int main() {
	cout << "===== Modbus RTU 模拟通讯 =====" << endl;
	//主机读保持寄存器(03功能码)
	auto cmd_read = ModbusCmd(1, FUNC_READ_HOLDING_REG, 0, 3);
	printHex("[主机发送]读命令: ", cmd_read);
	auto resp_read = ModbusResp(cmd_read);
	printHex("[从机回复]: ", resp_read);
	printf("\n");

	//主机写单个寄存器(06功能码)
	auto cmd_write = ModbusCmd(1, FUNC_WRITE_SINGLE_REG, 2, 999);
	printHex("[主机发送]写寄存器: ", cmd_write);
	auto resp_write = ModbusResp(cmd_write);
	printHex("[从机回复]: ", resp_write);
	printf("\n");

	//再次读取验证
	auto cmd_check = ModbusCmd(1, FUNC_READ_HOLDING_REG, 0, 3);
	printHex("[主机发送]验证读取: ", cmd_check);
	auto resp_check = ModbusResp(cmd_check);
	printHex("[从机回复]: ", resp_check);
	printf("\n");

	return 0;
}

