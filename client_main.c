/*
 *
 *  GattLib - GATT Library
 *
 *  Copyright (C) 2016-2017  Olivier Martin <olivier@labapart.org>
 *
 *
 *  This program is free software; you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation; either version 2 of the License, or
 *  (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with this program; if not, write to the Free Software
 *  Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA
 *
 */

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <wiringPi.h>

#include "gattlib.h"

#define BUTTON_PIN0 0
#define BUTTON_PIN1 4

typedef enum { READ, WRITE} operation_t;
operation_t g_operation;

static uuid_t g_uuid;
long int value_data;
volatile int eventCounter = 0;

static void usage(char *argv[]) {
	printf("%s <device_address>\n", argv[0]);
}

void myirq1(gatt_connection_t* connection) {
	value_data = strtol("0x6162", NULL, 0);
	ret = gattlib_write_char_by_uuid(connection, &g_uuid, value_data, sizeof(value_data));
	assert(ret == 0);
}

int main(int argc, char *argv[]) {
	uint8_t buffer[100];
	int i, ret;
	size_t len;
	gatt_connection_t* connection;

	if ((argc != 2)) {
		usage(argv);
		return 1;
	}
	// add the uuid
	if (gattlib_string_to_uuid("", strlen("") + 1, &g_uuid) < 0) {
		usage(argv);
		return 1;
	}
	//connect
	connection = gattlib_connect(NULL, argv[1], BDADDR_LE_PUBLIC, BT_SEC_LOW, 0, 0);
	if (connection == NULL) {
		fprintf(stderr, "Fail to connect to the bluetooth device.\n");
		return 1;
	}
	//set up wiringPi
	if (wiringPiSetup () < 0) {
		fprintf (stderr, "Unable to setup wiringPi: %s\n", strerror (errno));
		return 1;
	}
	pinMode(BUTTON_PIN0, INPUT);
	//待測試,因為原本的按鈕模組就有拉電阻了
	pullUpDnControl (BUTTON_PIN0, PUD_UP);
	
	if ( wiringPiISR (BUTTON_PIN0, INT_EDGE_FALLING, &myirq1) < 0 ) {
		fprintf (stderr, "Unable to setup ISR: %s\n", strerror (errno));
		return 1;
	}
	gattlib_disconnect(connection);
	return 0;
}

