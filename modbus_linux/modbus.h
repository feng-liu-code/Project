#ifndef  MODBUS_H
#define  MODBUS_H

#include <vector>
#include <cstdint>
#include <string>
using namespace std;

#define FUNC_READ_HOLDING_REG 0x03 //读保持寄存器
#define FUNC_WRITE_SINGLE_REG 0x06 //写单个寄存器

extern	vector<uint16_t> g_holdint_reg;

/**
 * @brief Modbus 主机指令组包
 * @param slave_addr 从站地址 1~247
 * @param func 功能码
 * @param addr 起始寄存器地址
 * @param val 寄存器数量/值
 * @return 完整报文(含CRC) 
 */
vector<uint8_t> ModbusCmd(uint8_t slave_addr, uint8_t func, uint16_t addr, uint16_t val);

/**
 * @param 从机接收报文并回复
 * @param req 主机请求报文
 * @return 从机回复报文
 */
vector<uint8_t> ModbusResp(const vector<uint8_t>& req);

/**
 * @brief Modbus CRC16校验
 */
uint16_t CRC16(const uint8_t* data, size_t len);

/**
 * @brief 打印16进制报文
 */
void printHex(const string& title, const vector<uint8_t>& data);

#endif