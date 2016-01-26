/*
 * Charles Smith
 *
 * Wed Jan 20, 2016
 *
 * pay.h
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

/* macros */
#define DEBUG 0
#define ERROR 1
#define NO_ERROR 0
#define MAX_STR 500
#define MAX_PEOPLE_CNT 20
#define MAX_TRANS_CNT 20

/* structures */
typedef struct person_ {
    char name[MAX_STR];
    int  person_id;
} person;

typedef struct transaction_ {
    char    desc[MAX_STR];
    float   amount;
    person *payer;
} transaction;

typedef struct p2p_ {
    float owed; // amount owed to you
    float owes; // amount you owe to others
} p2p;

typedef struct pay_group_ {
    int     num_of_people;
    float   total_trans;
    float   per_person_total;
    int     num_of_trans;
    p2p     pay_list[MAX_PEOPLE_CNT][MAX_PEOPLE_CNT];
} pay_group;

typedef struct transaction_configuration_ {
    float amount;
    const char *desc;
    const char *person_name;
} transaction_configuration;

typedef struct transaction_data_ {
    transaction trans_list[MAX_TRANS_CNT];
    int         trans_count;
} transaction_data;

typedef struct person_data_ {
    person person_list[MAX_PEOPLE_CNT];
    int person_count;
} person_data;

/*
 * Global externs
 */
extern const char *names[];
extern transaction_configuration trans_config[];

/* Functions */
void init_transaction(transaction_data *trans_data);

void init_pay_group(pay_group *group,
                    int        num_of_people);

int init_person(person_data *person_group,
                const char   *name);


void print_payouts(person person_list[],
                   pay_group *group);
void print_group_summary(pay_group *group);
void print_group_pay_list(pay_group *group);
int print_trans_summary(transaction_data *trans_data);

