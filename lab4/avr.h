#ifndef AVR_H
#define AVR_H

/* Bruce Segee's func - returns an int that talks directly to AVR chip */
int init(void);

/* Called when load value < 1.0
 * Pulses all LEDs   
 */
void condition1(int fd1); 

/* Called when 1.0 <= load value < 2.0
 * Lights all but two most sig LEDs
 */
void condition2(int fd1);

/* Called when 2.0 <= load value < 4.0
 * Lights all but most sig LED
 */
void condition3(int fd1);

/* Called when load value >= 4.0 
 * Lights all LEDs
 */
void condition4(int fd1);

#endif
