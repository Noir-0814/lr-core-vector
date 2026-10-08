/* vector.c —— 你要实现的地方 */

#include "vector.h"
#include <stdlib.h>

int vector_init(vector *v, size_t capacity) {
    if(capacity == 0){
        (*v).data = NULL;
        (*v).end = NULL;
        (*v).cap = NULL;
        return 0;
    }else{
        if(capacity > SIZE_MAX / sizeof(int)){
            (*v).data = NULL;
            (*v).end = NULL;
            (*v).cap = NULL;
            return -1;
        }else{
            int *tmp = malloc(capacity * sizeof(int));
            if(tmp == NULL){
                (*v).data = NULL;
                (*v).end = NULL;
                (*v).cap = NULL;
                return -1;
            }else{
                (*v).data = tmp;
                (*v).end = tmp;
                (*v).cap = tmp + capacity;
                return 0;
            }
        }
    }
}

void vector_destroy(vector *v) {
    free((*v).data);
    (*v).data = NULL;
    (*v).end = NULL;
    (*v).cap = NULL;    
}

size_t size(const vector *v) {
    if((*v).data == NULL){
        return 0;
    }else{
        int ret = (*v).end - (*v).data;
        return ret;
    }
}

size_t capacity(const vector *v) {
    if((*v).data == NULL){
        return 0;
    }else{
        int ret = (*v).cap - (*v).data;
        return ret;
    }
}

int empty(const vector *v) {
    if(size(v) == 0){
        return 1;
    }else{
        return 0;
    }
}

int get(const vector *v, size_t index, int *out) {
    if(index >= size(v)){
        return -1;
    }else{
        *out = *((*v).data + index);
        return 0;
    }
}

int set(vector *v, size_t index, int value) {
    if(index >= size(v)){
        return -1;
    }else{
        *((*v).data + index) = value;
        return 0;
    }
}

int front(const vector *v, int *out) {
    if(empty(v)){
        return -1;
    }else{
        *out = *((*v).data);
        return 0;
    }
}

int back(const vector *v, int *out) {
    if(empty(v)){
        return -1;
    }else{
        *out = *((*v).end - 1);
        return 0;
    }
}

int push_back(vector *v, int value) {
    size_t new_capacity;
    size_t old_size = size(v);
    if(size(v) < capacity(v)){
        *((*v).end) = value;
        (*v).end++;
        return 0;
    }else{
        if(capacity(v) == 0){
            new_capacity = 1;
        }else if(capacity(v) <= SIZE_MAX / (sizeof(int) * 2)){
            new_capacity = 2 * capacity(v);
        }else{
            return -1;
        }

        int *tmp = realloc((*v).data,new_capacity * sizeof(int));
        if(tmp == NULL){
            return -1;
        }else{
            (*v).end = tmp + old_size;
            (*v).cap = tmp + new_capacity;
            (*v).data = tmp;
            *((*v).end) = value;
            (*v).end++;
            return 0;
        }
    }
}

int pop_back(vector *v, int *out) {
    if(empty(v)){
        return -1;
    }else{
        *out = *((*v).end - 1);
        (*v).end--;
        return 0;
    }
}

int reserve(vector *v, size_t new_capacity) {
    size_t old_size = size(v);
    if(new_capacity <= SIZE_MAX / sizeof(int)){
        if(new_capacity <= capacity(v)){
            return 0;
        }else{
            int *tmp = realloc((*v).data,new_capacity * sizeof(int));
            if(tmp == NULL){
                return -1;
            }else{
                (*v).end = tmp + old_size;
                (*v).cap = tmp + new_capacity;
                (*v).data = tmp;
                return 0;
            }
        }
    }else{
        return -1;
    }
}

int shrink_to_fit(vector *v) {
    size_t old_size = size(v);
    if(size(v) == 0){
        free((*v).data);
        (*v).data = NULL;
        (*v).end = NULL;
        (*v).cap = NULL;
        return 0;
    }else{
        int *tmp = realloc((*v).data,size(v) * sizeof(int));
        if(tmp == NULL){
            return -1;
        }else{
            (*v).end = tmp + old_size;
            (*v).cap = tmp + old_size;
            (*v).data = tmp;
            return 0;
        }
    }
}

void clear(vector *v) {
    (*v).end = (*v).data;
}