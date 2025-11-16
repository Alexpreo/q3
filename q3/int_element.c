#include <stdio.h>
#include "int_element.h"
#include "refcount.h"
#include "str_element.h"

/*
 * Definition of the int_element structure.
 */
struct int_element {
    struct element super;
    int value;
};

static void int_element_print(struct element *e);
static int int_element_compare(struct element *e_this, struct element *e_other);

/*
 * The "vtable" for the int_element class.
 */
static struct element_class int_element_class = {
    .print = int_element_print,
    .compare = int_element_compare
};


/**
 * Static constructor for a new integer element.
 */
struct int_element *int_element_new(int value) {
    struct int_element *e = rc_malloc(sizeof(struct int_element), NULL);
    if (e == NULL) {
        return NULL;
    }

    // Initialize the superclass part
    e->super.class = &int_element_class;
    e->value = value;
    return e;
}

/**
 * Static function to get the integer value.
 */
int int_element_get_value(struct int_element *e) {
    return e->value;
}

/**
 * Static function to check if an element is an int_element.
 */
int is_int_element(struct element *e) {
    return e->class == &int_element_class;
}

/**
 * Print implementation for int_element.
 */
static void int_element_print(struct element *e) {
    struct int_element *ie = (struct int_element *)e;
    printf("%d", ie->value);
}

static int int_element_compare(struct element *e_this, struct element *e_other) {
    struct int_element *this_int = (struct int_element *)e_this;

    if (is_int_element(e_other)) {
        struct int_element *other_int = (struct int_element *)e_other;
        if (this_int->value < other_int->value) return -1;
        if (this_int->value > other_int->value) return 1;
        return 0;
    } else {
        return -1;
    }
}