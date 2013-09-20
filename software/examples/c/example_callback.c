
#include <stdio.h>

#include "ip_connection.h"
#include "bricklet_moisture.h"

#define HOST "localhost"
#define PORT 4223
#define UID "XYZ" // Change to your UID

// Callback function for moisture value 
void cb_moisture(uint16_t moisture, void *user_data) {
	(void)user_data; // avoid unused parameter warning

	printf("Moisture Value: %d\n", moisture);
}

int main() {
	// Create IP connection
	IPConnection ipcon;
	ipcon_create(&ipcon);

	// Create device object
	Moisture m;
	moisture_create(&m, UID, &ipcon); 

	// Connect to brickd
	if(ipcon_connect(&ipcon, HOST, PORT) < 0) {
		fprintf(stderr, "Could not connect\n");
		exit(1);
	}
	// Don't use device before ipcon is connected

	// Set Period for moisture callback to 1s (1000ms)
	// Note: The moisture callback is only called every second if the 
	//       moisture value has changed since the last call!
	moisture_set_moisture_callback_period(&m, 1000);

	// Register moisture callback to function cb_moisture
	moisture_register_callback(&m,
	                           MOISTURE_CALLBACK_MOISTURE,
	                           (void *)cb_moisture,
	                           NULL);

	printf("Press key to exit\n");
	getchar();
	ipcon_destroy(&ipcon); // Calls ipcon_disconnect internally
}