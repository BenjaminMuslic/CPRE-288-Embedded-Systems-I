
//#include <stdio.h>
//#include <string.h>
//
//#include "Timer.h"
//#include "lcd.h"
//#include "open_interface.h"
//#include "uart-interrupt.h"
//#include "ping_template.h"
//#include "servo.h"
//
//#include "bno055.h"
//#include "uart.h"
//#include <stdint.h>
//#include "stdint.h"
//
//
//
//int main(void) {
//     uart_interrupt_init();
//     oi_t* sensor_data = oi_alloc();  // do this only once at start of main()
//     oi_init(sensor_data);
//     timer_init();
//     uart_init();
//    // timer_init2();
//     servo_init();
//     lcd_init();
//
//
//     bno_t *bno = bno_alloc();
//     bno_initCalib(&bno_calibrate);
//
//     oi_t *oi = oi_alloc();
//     oi_init(oi);
//
//     bno_update(bno);
//
//     char data1[200] = {};
//     char data2[200] = {};
//     char data3[200] = {};
//     char data4[200] = {};
//
//     float target = bno ->euler.heading / 16.;
//     lcd_printf("after target %f\n" , target); //TAKE NOTE OF THIS VALUE FOR MAIN PROGRAM
//     sprintf(data1, "In while loop: %f\n\r", target);
//     uart_sendStr(data1);
//
//     while(1) {
//         oi_update(oi);
//         if(oi -> wheelDropLeft | oi -> wheelDropRight) {
//             oi_setWheels(0,0);
//         }
//         else {
//             bno_update(bno);
//             sprintf(data2, "In while loop: %f\n\r", target);
//             uart_sendStr(data2);
//             float difference = remainderf(
//                     (target - (bno ->euler.heading / 16.) + 360), 360);
//             difference = difference > 180 ? difference -360 : difference; // If diff > 180, make it negative so math works.
//             difference *= 14; // Faster
//
//             //Ensure within bounds of -100, 100
//             uint16_t power = (uint16_t) (
//                     difference < -100 ?
//                             -100 : (difference > 100 ? 100 : difference));
//
//             oi_setWheels(-power, power);
//
//             sprintf(data3, "after difference in while loop: %f\n\r", target);
//                     uart_sendStr(data3);
//         }
//         timer_waitMillis(10);
//     }
//     sprintf(data4, "After while loop: %f\n\r", target);
//             uart_sendStr(data4);
//}
//
//
//    //oi_free(sensor_data);
//
