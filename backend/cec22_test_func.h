#ifndef CEC22_TEST_FUNC_H
#define CEC22_TEST_FUNC_H

void ackley_func (double *, double *, int , double *,double *, int, int); /* Ackley's */
void bent_cigar_func(double *, double *, int , double *,double *, int, int); /* Discus */
void discus_func(double *, double *, int , double *,double *, int, int);  /* Bent_Cigar */
void ellips_func(double *, double *, int , double *,double *, int, int); /* Ellipsoidal */
void escaffer6_func (double *, double *, int , double *,double *, int, int); /* Expanded Scaffer¡¯s F6  */
void griewank_func (double *, double *, int , double *,double *, int, int); /* Griewank's  */
void grie_rosen_func (double *, double *, int , double *,double *, int, int); /* Griewank-Rosenbrock  */
void happycat_func (double *, double *, int , double *,double *, int, int); /* HappyCat */
void hgbat_func (double *, double *, int , double *,double *, int, int); /* HGBat  */
void rosenbrock_func (double *, double *, int , double *,double *, int, int); /* Rosenbrock's */
void rastrigin_func (double *, double *, int , double *,double *, int, int); /* Rastrigin's  */
void schwefel_func (double *, double *, int , double *,double *, int, int); /* Schwefel's */
void schaffer_F7_func (double *, double *, int , double *,double *, int, int); /* Schwefel's F7 */
void step_rastrigin_func (double *, double *, int , double *,double *, int, int); /* Noncontinuous Rastrigin's  */
void levy_func(double *, double *, int , double *,double *, int, int); /* Levy */
void zakharov_func(double *, double *, int , double *,double *, int, int); /* ZAKHAROV */
void katsuura_func (double *, double *, int , double *,double *, int, int); /* Katsuura */



void hf02 (double *, double *, int, double *,double *, int *,int, int); /* Hybrid Function 2 */
void hf06 (double *, double *, int, double *,double *, int *,int, int); /* Hybrid Function 6 */
void hf10 (double *, double *, int, double *,double *, int *,int, int); /* Hybrid Function 10 */


void cf01 (double *, double *, int , double *,double *, int); /* Composition Function 1 */
void cf02 (double *, double *, int , double *,double *, int); /* Composition Function 2 */
void cf06 (double *, double *, int , double *,double *, int); /* Composition Function 6 */
void cf07 (double *, double *, int , double *,double *, int); /* Composition Function 7 */



void shiftfunc (double*,double*,int,double*);
void rotatefunc (double*,double*,int, double*);
void sr_func (double *, double *, int, double*, double*, double, int, int); /* shift and rotate */
void asyfunc (double *, double *x, int, double);
void oszfunc (double *, double *, int);
void cf_cal(double *, double *, int, double *,double *,double *,double *,int);

extern void cec22_test_func(double *x, double *f, int nx, int mx,int func_num);

#endif // CEC22_TEST_FUNC_H
