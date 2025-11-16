#include <stdio.h>
#include <stdlib.h>

#include "int_element.h"
#include "str_element.h"
#include "element.h"
#include "refcount.h"

/* If the string is numeric, return an int_element. Otherwise return a str_element. */
struct element *parse_string(char *str) {
  char *endp;
  /* strtol returns a pointer to the first non-numeric character in endp.
     If it gets to the end of the string, that character will be the null terminator. */
  int value = strtol(str, &endp, 10);
  if(str[0] != '\0' && endp[0] == '\0') {
    /* String was non-empty and strtol conversion succeeded - integer */
    return (struct element *)int_element_new(value);
  } else {
    return (struct element *)str_element_new(str);
  }
}

/**
 * Comparison function for qsort.
 */
int element_qsort_compare(const void *p_a, const void *p_b) {

    struct element *elem_a = *(struct element **)p_a;
    struct element *elem_b = *(struct element **)p_b;
    return elem_a->class->compare(elem_a, elem_b);
}

int main(int argc, char **argv) {
  /* The number of elements is the number of arguments, minus the program name */
  int num_elements = argc - 1;

  /* Handle the case of no arguments */
  if (num_elements == 0) {
      printf("Sorted: \n");
      return 0;
  }
  struct element **elements = malloc(num_elements * sizeof(struct element *));
  if (elements == NULL) {
      return 1;
  }

  for (int i = 0; i < num_elements; i++) {
    elements[i] = parse_string(argv[i+1]);
  }
  
  qsort(elements, num_elements, sizeof(struct element *), element_qsort_compare);

  printf("Sorted: ");
  for (int i = 0; i < num_elements; i++) {
    if (i > 0) {
      printf(" ");
    }
    elements[i]->class->print(elements[i]);
  }
  printf("\n");

  for (int i = 0; i < num_elements; i++) {
    rc_free_ref(elements[i]);
  }
  
  free(elements);

  return 0;
}