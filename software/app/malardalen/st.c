/* stats.c */

/* 2012/09/28, Jan Gustafsson <jan.gustafsson@mdh.se>
 * Changes:
 *  - time is only enabled if the POUT flag is set
 *  - st.c:30:1:  main () warning: type specifier missing, defaults to 'int': fixed
 */

#include <hf-risc.h>

/* 2011/10/18, Benedikt Huber <benedikt@vmars.tuwien.ac.at>
 * Changes:
 *  - Measurement and Printing the Results is only enabled if the POUT flag is set
 *  - Added Prototypes for InitSeed and RandomInteger
 *  - Changed return type of InitSeed from 'missing (default int)' to 'void'
 */

//#include <sys/types.h>
//#include <sys/times.h>
//#include <math.h>


#define MAX 1000

void InitSeed(void);
int RandomInteger();


/* Statistics Program:
 * This program computes for two arrays of numbers the sum, the
 * mean, the variance, and standard deviation.  It then determines the
 * correlation coefficient between the two arrays.
 */

int Seed;
double ArrayA[MAX], ArrayB[MAX];
double SumA, SumB;
double Coef;

int _main ()
{
#ifdef POUT
   long StartTime, StopTime;
   float TotalTime;
#endif

   double MeanA, MeanB, VarA, VarB, StddevA, StddevB /*, Coef*/;
   int ttime();
   void Initialize(), Calc_Sum_Mean(), Calc_Var_Stddev();
   void Calc_LinCorrCoef();

   InitSeed ();
#ifdef POUT
   printf ("\n   *** Statictics TEST ***\n\n");
   StartTime = ttime();
#endif

   Initialize(ArrayA);
   Calc_Sum_Mean(ArrayA, &SumA, &MeanA);
   Calc_Var_Stddev(ArrayA, MeanA, &VarA, &StddevA);

   Initialize(ArrayB);
   Calc_Sum_Mean(ArrayB, &SumB, &MeanB);
   Calc_Var_Stddev(ArrayB, MeanB, &VarB, &StddevB);

   /* Coef will have to be used globally in Calc_LinCorrCoef since it would
      be beyond the 6 registers used for passing parameters
   */
   Calc_LinCorrCoef(ArrayA, ArrayB, MeanA, MeanB /*, &Coef*/);

#ifdef POUT
   StopTime = ttime();
   TotalTime = (StopTime - StartTime) / 1000.0;
   printf("     Sum A = %12.4f,      Sum B = %12.4f\n", SumA, SumB);
   printf("    Mean A = %12.4f,     Mean B = %12.4f\n", MeanA, MeanB);
   printf("Variance A = %12.4f, Variance B = %12.4f\n", VarA, VarB);
   printf(" Std Dev A = %12.4f, Variance B = %12.4f\n", StddevA, StddevB);
   printf("\nLinear Correlation Coefficient = %f\n", Coef);
#endif
}


void InitSeed ()
/*
 * Initializes the seed used in the random number generator.
 */
{
   Seed = 0;
}


void Calc_Sum_Mean(Array, Sum, Mean)
double Array[], *Sum;
double *Mean;
{
   int i;

   *Sum = 0;
   for (i = 0; i < MAX; i++)
      *Sum += Array[i];
   *Mean = *Sum / MAX;
}


double Square(x)
double x;
{
   return x*x;
}


void Calc_Var_Stddev(Array, Mean, Var, Stddev)
double Array[], Mean, *Var, *Stddev;
{
   int i;
   double diffs;

   diffs = 0.0;
   for (i = 0; i < MAX; i++)
      diffs += Square(Array[i] - Mean);
   *Var = diffs/MAX;
   *Stddev = sqrt(*Var);
}


void Calc_LinCorrCoef(ArrayA, ArrayB, MeanA, MeanB /*, Coef*/)
double ArrayA[], ArrayB[], MeanA, MeanB /*, *Coef*/;
{
   int i;
   double numerator, Aterm, Bterm;

   numerator = 0.0;
   Aterm = Bterm = 0.0;
   for (i = 0; i < MAX; i++) {
      numerator += (ArrayA[i] - MeanA) * (ArrayB[i] - MeanB);
      Aterm += Square(ArrayA[i] - MeanA);
      Bterm += Square(ArrayB[i] - MeanB);
      }

   /* Coef used globally */
   Coef = numerator / (sqrt(Aterm) * sqrt(Bterm));
}



void Initialize(Array)
double Array[];
/*
 * Intializes the given array with random integers.
 */
{
  register int i;

for (i=0; i < MAX; i++)
   Array [i] = i + RandomInteger ()/8095.0;
}


int RandomInteger()
/*
 * Generates random integers between 0 and 8095
 */
{
   Seed = ((Seed * 133) + 81) % 8095;
   return (Seed);
}

#ifdef POUT
int ttime()
/*
 * This function returns in milliseconds the amount of compiler time
 *  used prior to it being called.
 */
{
   struct tms buffer;
   int utime;

   times(&buffer);
   utime = (buffer.tms_utime / 60.0) * 1000.0;
   return (utime);
}
#endif


void main(void){
	volatile unsigned int cycles;

	printf("\nST benchmark");
	cycles = TIMER0;
	_main();
	cycles = TIMER0 - cycles;
	printf("\nWCET: %d cycles\n", cycles);

}

