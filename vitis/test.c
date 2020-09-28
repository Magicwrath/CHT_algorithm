#include <stdio.h>
#include <stdlib.h>

int main(void) {
  FILE *fptr;

  fptr = fopen("white_pix_coord.txt", "r");
  if(fptr == NULL) {
    printf("Unable to open text file\n");
    exit(1);
  }

  //test fscanf function
  int x_coordinate, y_coordinate;
  int num_of_pixels = 1;

  while(fscanf(fptr, "x = %d, y = %d\n", &x_coordinate, &y_coordinate) != EOF) {
    printf("%d : x = %d, y = %d\n", num_of_pixels, x_coordinate, y_coordinate);
    num_of_pixels++;
  }

  printf("Finished reading file, closing\n");
  fclose(fptr);

  return 0;
}
