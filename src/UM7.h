#ifndef UM7_H
#define UM7_H

#if defined(ARDUINO) && ARDUINO >= 100
#include "Arduino.h"
#else
#include "WProgram.h"
#endif

#include <stdlib.h>

// UM7_CREG_MISC_SETTINGS 0x08
#define UM7_MAG_ENABLED     (1 << 0)      // The magnetometer will be used in state updates
#define UM7_Q_ENABLED       (1 << 1)      // The sensor will run in quaternion mode rather than Euler angle mode
#define UM7_ZG_ENABLED      (1 << 2)      // The sensor will attempt to measure the rate gyro bias on startup
#define UM7_PPS_ENABLED     (1 << 8)      // Use the TX2 pin on the IO expansion header as the PPS input from an external GPS module

class UM7{
public:
	short roll, pitch, yaw, roll_rate, pitch_rate, yaw_rate;
	
	UM7();
	
	bool encode(byte c);
	
private:

	int state;
	
	enum {STATE_ZERO,STATE_S,STATE_SN,STATE_SNP,STATE_PT,STATE_DATA,STATE_CHK1,STATE_CHK0};
	
	byte packet_type;
	byte address;
	bool packet_is_batch;
	byte batch_length;
	bool packet_has_data;
	byte data[30];
	byte data_length;
	byte data_index;

	byte checksum1;		// First byte of checksum
	byte checksum0;		// Second byte of checksum

	unsigned short checksum10;			// Checksum received from packet
	unsigned short computed_checksum;	// Checksum computed from bytes received
	
	bool checksum(void);
	
	void save(void);
};

#endif
