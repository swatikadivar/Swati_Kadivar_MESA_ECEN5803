#define MAIN
#include "shared.h"
//#include "mbed.h"
#include <math.h>
#include <stdio.h>

//uint32_t arr[1000] = {0, 32767, 33590, 34413, 35235, 36056, 36874, 37690, 38502, 39311, 40116, 40916, 41711, 42500, 43284, 44060, 44830, 45591, 46345, 47090, 47826, 48553, 49269, 49976, 50671, 51355, 52027, 52687, 53335, 53969, 54591, 55198, 55791, 56370, 56933, 57482, 58015, 58532, 59032, 59516, 59984, 60434, 60866, 61281, 61677, 62056, 62416, 62757, 63079, 63383, 63666, 63931, 64175, 64400, 64605, 64790, 64954, 65098, 65222, 65325, 65408, 65470, 65511, 65532, 65532, 65511, 65470, 65408, 65325, 65222, 65098, 64954, 64790, 64605, 64400, 64175, 63931, 63666, 63383, 63079, 62757, 62416, 62056, 61677, 61281, 60866, 60434, 59984, 59516, 59032, 58532, 58015, 57482, 56933, 56370, 55791, 55198, 54591, 53969, 53335, 52687, 52027, 51355, 50671, 49976, 49269, 48553, 47826, 47090, 46345, 45591, 44830, 44060, 43284, 42500, 41711, 40916, 40116, 39311, 38502, 37690, 36874, 36056, 35235, 34413, 33590, 32767, 31944, 31121, 30299, 29478, 28660, 27844, 27032, 26223, 25418, 24618, 23823, 23034, 22250, 21474, 20704, 19943, 19189, 18444, 17708, 16981, 16265, 15558, 14863, 14179, 13507, 12847, 12199, 11565, 10943, 10336, 9743, 9164, 8601, 8052, 7519, 7002, 6502, 6018, 5550, 5100, 4668, 4253, 3857, 3478, 3118, 2777, 2455, 2151, 1868, 1603, 1359, 1134, 929, 744, 580, 436, 312, 209, 126, 64, 23, 2, 2, 23, 64, 126, 209, 312, 436, 580, 744, 929, 1134, 1359, 1603, 1868, 2151, 2455, 2777, 3118, 3478, 3857, 4253, 4668, 5100, 5550, 6018, 6502, 7002, 7519, 8052, 8601, 9164, 9743, 10336, 10943, 11565, 12199, 12847, 13507, 14179, 14863, 15558, 16265, 16981, 17708, 18444, 19189, 19943, 20704, 21474, 22250, 23034, 23823, 24618, 25418, 26223, 27032, 27844, 28660, 29478, 30299, 31121, 31944, 32767, 33590, 34413, 35235, 36056, 36874, 37690, 38502, 39311, 40116, 40916, 41711, 42500, 43284, 44060, 44830, 45591, 46345, 47090, 47826, 48553, 49269, 49976, 50671, 51355, 52027, 52687, 53335, 53969, 54591, 55198, 55791, 56370, 56933, 57482, 58015, 58532, 59032, 59516, 59984, 60434, 60866, 61281, 61677, 62056, 62416, 62757, 63079, 63383, 63666, 63931, 64175, 64400, 64605, 64790, 64954, 65098, 65222, 65325, 65408, 65470, 65511, 65532, 65532, 65511, 65470, 65408, 65325, 65222, 65098, 64954, 64790, 64605, 64400, 64175, 63931, 63666, 63383, 63079, 62757, 62416, 62056, 61677, 61281, 60866, 60434, 59984, 59516, 59032, 58532, 58015, 57482, 56933, 56370, 55791, 55198, 54591, 53969, 53335, 52687, 52027, 51355, 50671, 49976, 49269, 48553, 47826, 47090, 46345, 45591, 44830, 44060, 43284, 42500, 41711, 40916, 40116, 39311, 38502, 37690, 36874, 36056, 35235, 34413, 33590, 32767, 31944, 31121, 30299, 29478, 28660, 27844, 27032, 26223, 25418, 24618, 23823, 23034, 22250, 21474, 20704, 19943, 19189, 18444, 17708, 16981, 16265, 15558, 14863, 14179, 13507, 12847, 12199, 11565, 10943, 10336, 9743, 9164, 8601, 8052, 7519, 7002, 6502, 6018, 5550, 5100, 4668, 4253, 3857, 3478, 3118, 2777, 2455, 2151, 1868, 1603, 1359, 1134, 929, 744, 580, 436, 312, 209, 126, 64, 23, 2, 2, 23, 64, 126, 209, 312, 436, 580, 744, 929, 1134, 1359, 1603, 1868, 2151, 2455, 2777, 3118, 3478, 3857, 4253, 4668, 5100, 5550, 6018, 6502, 7002, 7519, 8052, 8601, 9164, 9743, 10336, 10943, 11565, 12199, 12847, 13507, 14179, 14863, 15558, 16265, 16981, 17708, 18444, 19189, 19943, 20704, 21474, 22250, 23034, 23823, 24618, 25418, 26223, 27032, 27844, 28660, 29478, 30299, 31121, 31944, 32767, 33590, 34413, 35235, 36056, 36874, 37690, 38502, 39311, 40116, 40916, 41711, 42500, 43284, 44060, 44830, 45591, 46345, 47090, 47826, 48553, 49269, 49976, 50671, 51355, 52027, 52687, 53335, 53969, 54591, 55198, 55791, 56370, 56933, 57482, 58015, 58532, 59032, 59516, 59984, 60434, 60866, 61281, 61677, 62056, 62416, 62757, 63079, 63383, 63666, 63931, 64175, 64400, 64605, 64790, 64954, 65098, 65222, 65325, 65408, 65470, 65511, 65532, 65532, 65511, 65470, 65408, 65325, 65222, 65098, 64954, 64790, 64605, 64400, 64175, 63931, 63666, 63383, 63079, 62757, 62416, 62056, 61677, 61281, 60866, 60434, 59984, 59516, 59032, 58532, 58015, 57482, 56933, 56370, 55791, 55198, 54591, 53969, 53335, 52687, 52027, 51355, 50671, 49976, 49269, 48553, 47826, 47090, 46345, 45591, 44830, 44060, 43284, 42500, 41711, 40916, 40116, 39311, 38502, 37690, 36874, 36056, 35235, 34413, 33590, 32767, 31944, 31121, 30299, 29478, 28660, 27844, 27032, 26223, 25418, 24618, 23823, 23034, 22250, 21474, 20704, 19943, 19189, 18444, 17708, 16981, 16265, 15558, 14863, 14179, 13507, 12847, 12199, 11565, 10943, 10336, 9743, 9164, 8601, 8052, 7519, 7002, 6502, 6018, 5550, 5100, 4668, 4253, 3857, 3478, 3118, 2777, 2455, 2151, 1868, 1603, 1359, 1134, 929, 744, 580, 436, 312, 209, 126, 64, 23, 2, 2, 23, 64, 126, 209, 312, 436, 580, 744, 929, 1134, 1359, 1603, 1868, 2151, 2455, 2777, 3118, 3478, 3857, 4253, 4668, 5100, 5550, 6018, 6502, 7002, 7519, 8052, 8601, 9164, 9743, 10336, 10943, 11565, 12199, 12847, 13507, 14179, 14863, 15558, 16265, 16981, 17708, 18444, 19189, 19943, 20704, 21474, 22250, 23034, 23823, 24618, 25418, 26223, 27032, 27844, 28660, 29478, 30299, 31121, 31944, 32767, 33590, 34413, 35235, 36056, 36874, 37690, 38502, 39311, 40116, 40916, 41711, 42500, 43284, 44060, 44830, 45591, 46345, 47090, 47826, 48553, 49269, 49976, 50671, 51355, 52027, 52687, 53335, 53969, 54591, 55198, 55791, 56370, 56933, 57482, 58015, 58532, 59032, 59516, 59984, 60434, 60866, 61281, 61677, 62056, 62416, 62757, 63079, 63383, 63666, 63931, 64175, 64400, 64605, 64790, 64954, 65098, 65222, 65325, 65408, 65470, 65511, 65532, 65532, 65511, 65470, 65408, 65325, 65222, 65098, 64954, 64790, 64605, 64400, 64175, 63931, 63666, 63383, 63079, 62757, 62416, 62056, 61677, 61281, 60866, 60434, 59984, 59516, 59032, 58532, 58015, 57482, 56933, 56370, 55791, 55198, 54591, 53969, 53335, 52687, 52027, 51355, 50671, 49976, 49269, 48553, 47826, 47090, 46345, 45591, 44830, 44060, 43284, 42500, 41711, 40916, 40116, 39311, 38502, 37690, 36874, 36056, 35235, 34413, 33590, 32767, 31944, 31121, 30299, 29478, 28660, 27844, 27032, 26223, 25418, 24618, 23823, 23034, 22250, 21474, 20704, 19943, 19189, 18444, 17708, 16981, 16265, 15558, 14863, 14179, 13507, 12847, 12199, 11565, 10943, 10336, 9743, 9164, 8601, 8052, 7519, 7002, 6502, 6018, 5550, 5100, 4668, 4253, 3857, 3478, 3118, 2777, 2455, 2151, 1868, 1603, 1359, 1134, 929, 744, 580, 436, 312, 209, 126, 64, 23, 2, 2, 23, 64, 126, 209, 312, 436, 580, 744, 929, 1134, 1359, 1603, 1868, 2151, 2455, 2777, 3118, 3478, 3857, 4253, 4668, 5100, 5550, 6018, 6502, 7002, 7519, 8052, 8601, 9164, 9743, 10336, 10943, 11565, 12199, 12847, 13507, 14179, 14863, 15558, 16265, 16981, 17708, 18444, 19189, 19943, 20704, 21474, 22250, 23034, 23823, 24618, 25418, 26223, 27032, 27844, 28660, 29478, 30299, 31121};
uint32_t arr[1000];

AnalogIn adc(A0);
DigitalOut PWM3(PTE30);
DigitalOut PWM4(PTE31);


Timer tick;             //  Creates a timer interrupt using mbed methods
 /****************      ECEN 5803 add code as indicated   ***************/
                // Add code to control red, green and blue LEDs here
                                                    

uint16_t calculate_flow(uint8_t freq, uint8_t temp){
	//float flow=0.0;
	
	//float viscosity = eq10(temp);		// passing arg in celcius
	//float density = eq9(temp);			// passing arg in celcius
	
	uint32_t density = (uint32_t)(1000 * (1 - (((temp + 288.9414) / (508929.2 * (temp + 68.12963))) * ((temp - 3.9863) * (temp - 3.9863)))));
	uint32_t viscosity = (uint32_t)(2.4 * 0.00001 * pow(10, (247.8/((temp + 273.15)-140)))); /// Optimizing it as value comes close to zero.
	
	//printf("density = %d viscosity = %d\n\r",density,viscosity);
	
	//float v=0;
	
	//float pid_m = 0.07366;
	//float d_m = 0.0127;
	
	//float pid_i = 2.9;
	//float d_i = 0.5;
	
	//float Re_const = ((density * 0.07366)/viscosity);		// it should be float Re = (density * v * pid_m)/viscosity;
		
	//float st_const = freq * 0.0127;		// it should be st = (freq * d_m)/ v;
	//printf("re_const = %f, st_const = %f\n\r", Re_const, st_const);
	
	// reducing equations 2-8 into just velocity variable based equations.
	// 0.072 v^2 - ( (0.273 * Re_const  + 1.072)/Re_const ) * v + 0.258 =0;
	//     v^2 - ((3.79 * Re_const + 14.89)/Re_const) * v + 3.58 = 0;
	// a * x^2 +  b *v + c = 0;
	// finding roots of above equation...
	
	// a = 1;
	float b = ((-1)*(3.79 * ((density * 0.07366)) + 14.89)/((density * 0.07366)));
	// c = 3.58;
	//printf("b = %5.2f \n\r", b);
	
	uint16_t root_x = (uint16_t)(((-1) * b) + sqrt((b*b) - (14.32)))/2;
	uint16_t root_y = (uint16_t)(((-1) * b) - sqrt((b*b) - (14.32)))/2;
	
	//printf("x = %d y = %d\n\r", root_x, root_y);
	
	if(root_y > root_x) 
		//v = root_x;
		return (uint16_t)(2.45 * root_x * (2.9 * 2.9) * 3.281);
	else
		//v = root_y;
		return (uint16_t)(2.45 * root_y * (2.9 * 2.9) * 3.281);
	//printf(" root_x= %f, root_y = %f\n\r",root_x, root_y);
	
	//flow = 2.45 * v * (2.9 * 2.9) * 3.281;
	//printf("flow = %f\n\r", flow);
	//return flow;
}

void adc_init(uint8_t res)
{
	// Enable clocks
	SIM->SCGC6 |= SIM_SCGC6_ADC0_MASK;	// ADC 0 clock

	// Configure ADC
	ADC0->CFG1 = 0; // Reset register

	ADC0->CFG1 |= (ADC_CFG1_MODE( res )  |  	// 16 bits mode
				  ADC_CFG1_ADICLK(0)|	// Input Bus Clock (20-25 MHz out of reset (FEI mode))
				  ADC_CFG1_ADIV(1)) ;	// Clock divide by 2 (10-12.5 MHz)

	ADC0->SC3 = 0; // Reset SC3

	ADC0->SC1[0] |= ADC_SC1_ADCH(31); // Disable module
}


uint16_t adc_read(uint16_t ch)
{
	//ADC0_SC1A = (ch & ADC_SC1_ADCH_MASK) | (ADC0_SC1A & (ADC_SC1_AIEN_MASK | ADC_SC1_DIFF_MASK));     // Write to SC1A to start conversion
	ADC0->SC1[0] = ch & ADC_SC1_ADCH_MASK; //Write to SC1A to start conversion
	while(ADC0->SC2 & ADC_SC2_ADACT_MASK); 	 // Conversion in progress
	while(!(ADC0->SC1[0] & ADC_SC1_COCO_MASK)); // Run until the conversion is complete
	return ADC0->R[0];
}

uint8_t freq_detect(uint32_t *data) //size = 999
{
    bool is_pos = false;
    uint16_t i = 0, size = 999;
    uint16_t zero_cross = 0;
    if(data[0] > 0)
    {
        is_pos = true;
    }
    
    while(size--) {
        int value = data[++i];
        if(is_pos && value > 32767)
        {
            is_pos = false;
            zero_cross++;
        }
        else if(!is_pos && value <= 32767)
        {
            is_pos = true;
            zero_cross++;
        }
    }
    
    return (uint8_t)((zero_cross/2)*10);   
}

int main() {

	uint16_t flow=0;
	//tick.attach(&timer0, 0.0001);
	tick.start();
    while (true) {
       uint8_t temp = (uint8_t) (25-((adc_read(26)/20)-716)/2);                  //Calculate temp in Celsius                     
      wait(2);
				uint8_t freq = freq_detect(arr);
			  flow = calculate_flow(40, temp);
			  printf("Temp = %d degreeCelcius, flow = %d gallons/min\n\r", temp, flow);  
					for(uint8_t i=0; i<flow; i++){
						PWM3 = ~PWM3;
						PWM4 = ~PWM4;
				}
				tick.stop();
				printf("time = %f\n\r",tick.read());
     }
}
