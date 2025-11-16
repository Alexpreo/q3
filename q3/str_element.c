#include <stdio.h>
#include <stdlib.h>
#include <string.h>     
#include "str_element.h"
#include "refcount.h"
#include "int_element.h"

/*
 * Definition of the str_element structure..
 */
struct str_element {
    struct element super;
    char *value;          
};

static void str_element_print(struct element *e);
static int str_element_compare(struct element *e_this, struct element *e_other);
static void str_element_finalizer(void *p);

// --- vtable for str_element ---
static struct element_class str_element_class = {
    .print = str_element_print,
    .compare = str_element_compare
};

/**
 * Static constructor for a new string element.
 */
struct str_element *str_element_new(char *value) {
    struct str_element *e = rc_malloc(sizeof(struct str_element), str_element_finalizer);
    if (e == NULL) {
        return NULL;
    }

    e->super.class = &str_element_class;
    e->value = strdup(value);

    if (e->value == NULL) {
        rc_free_ref(e); 
        return NULL;
    }
    
    return e;
}

/**
 * Static function to get the string value.
 */
char *str_element_get_value(struct str_element *e) {
    return e->value;
}

/**
 * Static function to check if an element is a str_element.
 */
int is_str_element(struct element *e) {
    // Check if the element's vtable is the str_element's vtable
    return e->class == &str_element_class;
}


/**
 * Finalizer function called by rc_free_ref just before freeing the struct.
 */
static void str_element_finalizer(void *p) {
    struct str_element *e = (struct str_element *)p;
    free(e->value);
}

/**
 * Print implementation for str_element.
 */
static void str_element_print(struct element *e) {
    struct str_element *se = (struct str_element *)e;
    printf("%s", se->value);
}

/**
 * Compare implementation for str_element.
 */
static int str_element_compare(struct element *e_this, struct element *e_other) {
    struct str_element *this_str = (struct str_element *)e_this;

    if (is_int_element(e_other)) {
        return 1;
    } else {
        struct str_element *other_str = (struct str_element *)e_other;
        return strcmp(this_str->value, other_str->value);
    }
}