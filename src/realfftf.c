/********************************************************************************
*     Program: REALFFTF.C
*      Author: Philip VanBaren
*        Date: 2 September 1993
*
* Description: These routines perform an FFT on real data.
*              On a 486/33 compiled using Borland C++ 3.1 with full
*              speed optimization and a small memory model, a 1024 point
*              FFT takes about 16ms.
*              This code is for floating point data.
*
*  Note: Output is BIT-REVERSED! so you must use the BitReversed to
*        get legible output, (i.e. Real_i = buffer[ BitReversed[i] ]
*                                  Imag_i = buffer[ BitReversed[i]+1 ] )
*        Input is in normal order.
********************************************************************************/

#include "realfftf.h"

int *bit_reversed;
float *SinTable;
int Points = 0;

/********************************************************************************
 *  Initialize the Sine table and Twiddle pointers (bit-reversed pointers)
 *  for the FFT routine.
 ********************************************************************************/

void initialize_FFT(int fftlen)
{
    int i;
    int temp;
    int mask;

    /*****
     *  FFT size is only half the number of data points
     *  The full FFT output can be reconstructed from this FFT's output.
     *  (This optimization can be made since the data is real.)
     *****/
    Points = fftlen/2;
    int Points2 = Points + Points, Pointsd = Points / 2;

    if((SinTable=(float *)malloc(Points2*sizeof(float)))==NULL)
    {
        puts("Error allocating memory for Sine table.");
        exit(1);
    }
    if((bit_reversed=(int *)malloc(Points*sizeof(int)))==NULL)
    {
        puts("Error allocating memory for bit_reversed.");
        exit(1);
    }

    for(i=0; i<Points; i++)
    {
        temp=0;
        for(mask=Pointsd; mask>0; mask >>= 1)
            temp=(temp >> 1) + (i&mask ? Points : 0);

        bit_reversed[i]=temp;
    }

    float coefPI = (float)M_PI / Points, coefPIt = 0.0;
    for(i=0; i<Points; i++)
    {
        SinTable[bit_reversed[i]  ]=-sin(coefPIt);
        SinTable[bit_reversed[i]+1]=-cos(coefPIt);
        coefPIt += coefPI;
    }
}

/********************************************************************************
 *  Free up the memory allotted for Sin table and Twiddle Pointers
 ********************************************************************************/

void end_FFT()
{
    free(bit_reversed);
    free(SinTable);
    Points=0;
}

float *A,*B;
float *sptr;
float *endptr1,*endptr2;
int *br1,*br2;
float HRplus,HRminus,HIplus,HIminus;

/********************************************************************************
 *  Actual FFT routine.  Must call InitializeFFT(fftlen) first!
 ********************************************************************************/

void real_FFT(float *buffer)
{
    int ButterfliesPerGroup=Points/2;

    endptr1=buffer+Points*2;

    /*****
     *  Butterfly:
     *     Ain-----Aout
     *         \ /
     *         / \
     *     Bin-----Bout
     *****/

    while(ButterfliesPerGroup>0)
    {
        A=buffer;
        B=buffer+ButterfliesPerGroup+ButterfliesPerGroup;
        sptr=SinTable;

        while(A<endptr1)
        {
            register float sin=*sptr;
            register float cos=*(sptr+1);
            endptr2=B;
            while(A<endptr2)
            {
                float v1=*B*cos + *(B+1)*sin;
                float v2=*B*sin - *(B+1)*cos;
                *B=(*A+v1)*0.5;
                *(A++)=*(B++)-v1;
                *B=(*A-v2)*0.5;
                *(A++)=*(B++)+v2;
            }
            A=B;
            B+=ButterfliesPerGroup;
            B+=ButterfliesPerGroup;
            sptr+=2;
        }
        ButterfliesPerGroup >>= 1;
    }
    /*****
     *  Massage output to get the output for a real input sequence.
     *****/
    br1=bit_reversed+1;
    br2=bit_reversed+Points-1;

    while(br1<=br2)
    {
        register float temp1;
        register float temp2;
        float sin=SinTable[*br1];
        float cos=SinTable[*br1+1];
        A=buffer+*br1;
        B=buffer+*br2;
        HRplus = (HRminus = *A     - *B    ) + (*B     + *B);
        HIplus = (HIminus = *(A+1) - *(B+1)) + (*(B+1) + *(B+1));
        temp1  = (sin*HRminus - cos*HIplus);
        temp2  = (cos*HRminus + sin*HIplus);
        *B     = (*A     = (HRplus  + temp1) * 0.5) - temp1;
        *(B+1) = (*(A+1) = (HIminus + temp2) * 0.5) - HIminus;

        br1++;
        br2--;
    }
    /*****
     *  Handle DC bin separately
     *****/
    buffer[0]+=buffer[1];
    buffer[1]=0;
}

