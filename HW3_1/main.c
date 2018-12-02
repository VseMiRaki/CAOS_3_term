#include <stdint.h>
#include <stdio.h>
#include <stdio.h>
#include <stdlib.h>
typedef enum {
  PlusZero = 0x00,
  MinusZero = 0x01,
  PlusInf = 0xF0,
  MinusInf = 0xF1,
  PlusRegular = 0x10,
  MinusRegular = 0x11,
  PlusDenormal = 0x20,
  MinusDenormal = 0x21,
  SignalingNaN = 0x30,
  QuietNaN = 0x31
} float_class_t;

extern float_class_t classify(double *value_ptr);
int main() {
  double *val_ptr = (double *)malloc(sizeof(double));
  *val_ptr = 0.;
  printf("%d\n", classify(val_ptr) == PlusZero);
  *val_ptr = -0.;
  printf("%d\n", classify(val_ptr) == MinusZero);
  *((uint64_t *)val_ptr) =
      0b0111111111110000000000000000000000000000000000000000000000000000;
  printf("%d\n", classify(val_ptr) == PlusInf);
  *((uint64_t *)val_ptr) =
      0b1111111111110000000000000000000000000000000000000000000000000000;
  printf("%d\n", classify(val_ptr) == MinusInf);
  *((uint64_t *)val_ptr) =
      0b1111111111100000000000000000000000000000000000000000000000000000;
  printf("%d\n", classify(val_ptr) == MinusRegular);
  *((uint64_t *)val_ptr) =
      0b0111111111110000000000000000000000000000000000000000000000000100;
  printf("%d\n", classify(val_ptr) == SignalingNaN);
  *((uint64_t *)val_ptr) =
      0b0111111111111000000000000000000000000000000000000000000000000000;
  printf("%d\n", classify(val_ptr) == SignalingNaN);
  *((uint64_t *)val_ptr) =
      0b1111111111110000000000000000000000000000000000000000000000000001;
  printf("%d\n", classify(val_ptr) == QuietNaN);
  *((uint64_t *)val_ptr) =
      0b0000000000001000000000000000000000000000000000000000000000000000;
  printf("%d\n", classify(val_ptr) == PlusDenormal);
  *((uint64_t *)val_ptr) =
      0b0000000000000000000000000000000000000000000000000000000000000001;
  printf("%d\n", classify(val_ptr) == PlusDenormal);
  *((uint64_t *)val_ptr) =
      0b1000000000000011100000000000000000000000000000000000000000000000;
  printf("%d\n", classify(val_ptr) == MinusDenormal);
  *((uint64_t *)val_ptr) =
      0b1000000000001000000000000000000000000000000000000000000000000000;
  printf("%d\n", classify(val_ptr) == MinusDenormal);
  *val_ptr = 0.2;
  printf("%d\n", classify(val_ptr) == PlusRegular);
  *val_ptr = -0.2;
  printf("%d\n", classify(val_ptr) == MinusRegular);
  *val_ptr = 100000;
  printf("%d\n", classify(val_ptr) == PlusRegular);
  *val_ptr = -1000;
  printf("%d\n", classify(val_ptr) == MinusRegular);
  return 0;
}
