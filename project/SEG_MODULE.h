void seg_init();  // Initialization of I/O registers

char SEG_CODE(char num); // Convert the decimal number to 7-SEG device code
                         // and return it.
                         // Apply to the I/O register

char DISP_SEL(char num); // Convert the display number to 7-SEG device code
                         // and return it.
                         // Apply to the I/O register
                         
void seg_disp(int disp_num); // Display 'disp_num' on the 7-Segment display

void counter(int count);  // Count and display the numbers from 0 to 'count'

