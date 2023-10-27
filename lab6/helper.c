

#include "open_interface.h"
#include "Timer.h"
#include "lcd.h"
#include "movement.h"
#include "cyBot_Scan.h"
#include "cyBot_uart.h"
#include "helper.h"

void cyBot_sendStr(char data[]){
    int i = 0;
    for(i = 0; data[i] != '\0'; i++){
        cyBot_sendByte(data[i]);
    }
}


