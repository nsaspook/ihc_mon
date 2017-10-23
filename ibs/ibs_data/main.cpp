/* 
 * File:   main.cpp
 * Author: root
 *
 * Created on December 26, 2013, 4:40 PM
 */

#include <cstdlib>
#include <stdio.h>
#include "../ibsdata.h"

int ibs_d = 1, ibs_block_done = 0, ibs_data[8], file_idx = 0,
        ihc_d, ihc_data[6];
unsigned char ibs_stream_file, ibs_stream_file_prev = 0;
FILE *IBS;

int main(int argc, char** argv) {

    if ((IBS = fopen("../putty3", "r")) == NULL) {
        printf("\r\n No file found!");
        return -1;
    }
    ibs_stream_file = fgetc(IBS);
    while (!ibs_block_done) {
        if (ibs_stream_file == 0x00) {
            ibs_d = 1;
            ibs_block_done = 1;
        }
        if (ibs_stream_file & 0x80) { // stream data bit 7 set
            ibs_data[ibs_d] = ibs_stream_file & 0x3f;
            ibs_d++;
        } else { // stream code
            ibs_d = 1;
            ihc_d = ((ibs_data[1]&0x0f) << 6)+(ibs_data[2]);
            printf("\r\n index %5i, code, %3i, data, %4i , hex stream %3x, %3x, %3x ", file_idx++, ibs_stream_file_prev, ihc_d, ibs_data[1], ibs_data[2], ibs_data[3]);
            ibs_data[0] = ibs_stream_file;
            ibs_stream_file_prev = ibs_stream_file;
            if (ibs_stream_file == 70) { // regulation feedback 0 center 512 = nom.
                ihc_data[0] = 0;
                if ((ihc_d > 350) && (ihc_d < 650)) {
                    ihc_data[0] = 1;
                    //                    printf("\r\n code 70 OK ");
                }
            }
            if (ibs_stream_file == 79) { // filament voltage, 700 = nom.
                ihc_data[1] = 0;
                if ((ihc_d > 400) && (ihc_d < 900)) {
                    ihc_data[1] = 1;
                    //                    printf("\r\n code 79 OK ");
                }
            }
            if (ibs_stream_file == 101) { // cathode current, 600 = nom.
                ihc_data[2] = 0;
                if ((ihc_d > 400) && (ihc_d < 900)) {
                    ihc_data[2] = 1;
                    //                    printf("\r\n code 101 OK ");
                }
            }
            if (ibs_stream_file == 105) { // cathode voltage 600v = 1023
                ihc_data[3] = 0;
                if ((ihc_d > 800) && (ihc_d < 1050)) {
                    ihc_data[3] = 1;
                    //                    printf("\r\n code 105 OK ");
                }
            }
            if (ibs_stream_file == 111) { // filament current, 425 is nom.
                ihc_data[4] = 0;
                if ((ihc_d > 300) && (ihc_d < 700)) {
                    ihc_data[4] = 1;
                    //                    printf("\r\n code 111 OK ");
                }
            }
            if (ibs_stream_file == 70) {
                if (ihc_data[0] & ihc_data[1] & ihc_data[2] & ihc_data[3] & ihc_data[4]) {
                    //                    printf("\r\n IHC Source OK ");
                } else {
                    //                    printf("\r\n IHC Source out of regulation. %i %i %i %i %i",ihc_data[0],ihc_data[1],ihc_data[2],ihc_data[3],ihc_data[4]);
                }
            }
        }
        if (!ibs_block_done) ibs_stream_file = fgetc(IBS);
    }

    fclose(IBS);
    return 0;
}


