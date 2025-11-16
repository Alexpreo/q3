/* This file defines the abstract interface for an element. */
#pragma once

/* Forward struct declaration */
struct element;

struct element_class {
  /* Print this element (without any trailing newline) */
  void (*print)(struct element *);
  /* Compare two elements, "this" and "other". 
   * The "this" parameter is expected to be an instance of the subclass associated with the compare function.
   * int_element should always compare LESS than str_element.
   * The compare function should return:
   *   a number < 0 if the first element is less than the second element,
   *   0 if the elements compare equal,
   *   a number > 0 otherwise.
   */
  int (*compare)(struct element* this, struct element* other);
};

struct element {
  struct element_class *class;
};
