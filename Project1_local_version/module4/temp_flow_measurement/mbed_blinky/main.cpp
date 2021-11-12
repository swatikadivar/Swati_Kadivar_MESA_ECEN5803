#define MAIN
#include "shared.h"
#include <math.h>

AnalogIn adc(A0);
DigitalOut led1(LED1);
uint8_t flag=0;
uint32_t val=0;

DigitalOut greenLED(LED_GREEN);

//extern volatile uint16_t SwTimerIsrCounter; 


Ticker tick;             //  Creates a timer interrupt using mbed methods
 /****************      ECEN 5803 add code as indicated   ***************/
                // Add code to control red, green and blue LEDs here
                                                    


Serial pc(USBTX, USBRX);
 
/*void flip() 
{
    greenLED = !greenLED;
}
*/


//--- ADC Interrupt handler -----------------
//extern "C" 
void ADC0_IRQHandler()
{
    NVIC_ClearPendingIRQ(ADC0_IRQn);            //Clear ADC Interrupt Request Flag
    uint16_t raw = ADC0->R[0];
    flag = 1;
    val = raw;
}


uint16_t adc_read(uint32_t ch) {
    ADC0->SC3 = ADC_SC3_AVGE_MASK               // Hardware Average Enable
              | ADC_SC3_AVGS(3);                // 32 Samples Averaged
    // start conversion
    ADC0->SC1[0] = ADC_SC1_AIEN_MASK | ch;      //Set channel, enable interrupt
    while(flag==0);
    flag = 0;
    return val;
}

/*float eq9(uint16_t temp){
	float density = 0.0;

	density = 1000 * (1 - (((temp + 288.9414) / (508929.2 * (temp + 68.12963))) * ((temp - 3.9863) * (temp - 3.9863))));
		
	return density;
}

float eq10(uint16_t temp){
	float viscosity=0.0;
	
	//float tk = (temp + 273.15);
	viscosity = 2.4 * 0.00001 * pow(10, (247.8/((temp + 273.15)-140)));
	
	return viscosity;
}
*/
uint32_t calculate_flow(uint16_t freq, uint16_t temp){
	//float flow=0.0;
	
	//float viscosity = eq10(temp);		// passing arg in celcius
	//float density = eq9(temp);			// passing arg in celcius
	
	float density = 1000 * (1 - (((temp + 288.9414) / (508929.2 * (temp + 68.12963))) * ((temp - 3.9863) * (temp - 3.9863))));
	float viscosity = 2.4 * 0.00001 * pow(10, (247.8/((temp + 273.15)-140)));
	
	//printf("density = %f viscosity = %f\n\r",density,viscosity);
	
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
	float b = (-1)*(3.79 * ((density * 0.07366)/viscosity) + 14.89)/((density * 0.07366)/viscosity);
	// c = 3.58;
	
	float root_x = (((-1) * b) + sqrt((b*b) - (14.32)))/2;
	float root_y = (((-1) * b) - sqrt((b*b) - (14.32)))/2;
	
	if(root_x > 0 ) 
		//v = root_x;
		return (uint32_t)(2.45 * root_x * (2.9 * 2.9) * 3.281);
	else
		//v = root_y;
		return (uint32_t)(2.45 * root_y * (2.9 * 2.9) * 3.281);
	//printf(" root_x= %f, root_y = %f\n\r",root_x, root_y);
	
	//flow = 2.45 * v * (2.9 * 2.9) * 3.281;
	//printf("flow = %f\n\r", flow);
	//return flow;
}

int main() {
/*
 * The v25 value is the voltage reading at 25C, it comes from the ADC
 * electricals table in the processor manual. V25 is in millivolts.
 */
    //int16_t v25 = 716;
		//tick.attach(&timer0, 0.0001);
	//uint16_t freq=40;
	uint32_t flow=0;

	//int32_t m = 1620;    
    //NVIC_SetVector(ADC0_IRQn, (uint32_t)&ADC0_IRQHandler);      //Attach ADC interrupt service routine
    //NVIC_EnableIRQ(ADC0_IRQn);                                  //Enable ADC interrupt requests    

//    while (true) {
        //led1 = !led1;
        //wait(1);
//    }

    while (true) {
        //uint16_t a1 = adc_read(8);                              //Measure voltage at A0 (PTB0)
        //uint16_t a2 = adc_read(26);                             //Internal temperature sensor
//        float v1 = a1*3.3f/65536;                               //Convert v1 to Volts
        //float v2 = a2*3300.0f/65536;                            //Convert v2 to millivolts
        //uint16_t temp = 25.0f-((adc_read(26)*3300.0f/65536)-716)*1000.0f/1620;                  //Calculate temp in Celsius                     
				//float temp = 30;
				//UART_put(temp);
        //printf("\rTemp = %5.2f C\n",temp);
			uint32_t temp = 30;
        wait(2);
			flow = calculate_flow(40, temp);
			//printf("flow = %f\n\r", flow);  
			UART_put(flow);
			
			/*if ((SwTimerIsrCounter & 0x1FFF) > 0x0FFF)

        {
            flip();  // Toggle Green LED
        }
 */
    }
}
