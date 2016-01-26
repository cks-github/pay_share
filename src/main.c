/*
 * Charles Smith
 *
 * Wed Jan 20, 2016
 *
 * main.c
 */

#include "pay.h"



/*
 * FUNCTION
 */
static
int calc_payment (transaction   *trans,
                  pay_group *group)
{
    if (group->num_of_people < 1) {
        printf("ERROR: num_of_people needs to be greater than 0\n");
        return ERROR;
    }
    
    group->total_trans += trans->amount;
    group->per_person_total = group->total_trans / (float)group->num_of_people;

    group->num_of_trans++;

    return NO_ERROR;
}

/*
 * FUNCTION
 */
static
void add_trans_to_pay_group(transaction *trans,
                            pay_group *group)
{
    int person_id;
    float per_person_amount = trans->amount / (float)group->num_of_people;

    for (person_id = 0; person_id < group->num_of_people; person_id++) {
        if (person_id == trans->payer->person_id) {
            group->pay_list[trans->payer->person_id][person_id].owed +=
                trans->amount;
        } else {
            group->pay_list[trans->payer->person_id][person_id].owed += per_person_amount;
        }
    }
}

/*
 * FUNCTION
 */
static
person* get_person_from_person_data_via_name (person_data *person_group,
                                              const char  *person_name)
{
    int i;

    for (i = 0; i < person_group->person_count; i++) {
        if (strncmp(person_name, person_group->person_list[i].name,
                    MAX_STR) == 0) {
            /* Found a match */
            return (&(person_group->person_list[i]));
        }
    }

    printf("ERROR: could not find person named \"%s\"\n", person_name);
    return (NULL);
}

/*
 * FUNCTION
 */
static 
int process_new_trans (transaction_data *trans_data,
                       float             amount,
                       const char       *desc,
                       const char       *person_name,
                       person_data      *person_group,
                       pay_group        *group)
{
    int rc;
    int index = trans_data->trans_count;
    person *payer = NULL;

    if (DEBUG) {
        printf("%s():%d attempting to process transaction \"%s\"\n",
               __FUNCTION__, __LINE__, desc);
    }

    if (trans_data->trans_count > MAX_TRANS_CNT-1) {
        printf("ERROR: surpassed max transaction count %d\n", MAX_TRANS_CNT);
        return (ERROR);
    }

    /* Verify that the person requested for the transaction exists in list */
    payer = get_person_from_person_data_via_name(person_group, person_name);
    if (payer == NULL) {
        return (ERROR);
    }

    trans_data->trans_count++;
    trans_data->trans_list[index].amount = amount;
    strncpy(trans_data->trans_list[index].desc, desc, MAX_STR);
    trans_data->trans_list[index].payer = payer;

    /* Add transaction to group */
    add_trans_to_pay_group(&(trans_data->trans_list[index]), group);
    rc = calc_payment(&(trans_data->trans_list[index]), group);

    return (rc);
}

static
void equalize_payouts (pay_group *group)
{
    int i,j;

    for (i=0; i<group->num_of_people; i++) {
        for (j=0; j< group->num_of_people; j++) {
            if (i == j) continue;
            group->pay_list[i][j].owes = group->pay_list[j][i].owed;
        }
    }    
}


/*
 * MAIN
 */
int main (void)
{
    transaction_data trans_data;
    pay_group        group;
    person_data      person_group;
    int              i = 0;
    int              rc;

    /* Initialize people */
    for (i = 0; names[i] != NULL; i++) {
        rc = init_person(&person_group, names[i]);
        if (rc == ERROR) {
            printf ("FUCKUP\n");
            exit(1);
        }
    }
    
    /* Initialize pay group */
    init_pay_group(&group, person_group.person_count);

    /* Initialize transaction scenarios */
    init_transaction(&trans_data);

    /* Process transactions */
    for (i = 0; trans_config[i].desc != NULL; i++) {
        rc = process_new_trans(&trans_data,
                               trans_config[i].amount,
                               trans_config[i].desc,
                               trans_config[i].person_name,
                               &person_group,
                               &group);
        if (rc == ERROR) {
            printf("FUCKUP\n");
            exit(1);
        }
    }

    equalize_payouts(&group);

    /* Print results */
    print_trans_summary(&trans_data);
    //print_group_pay_list(&group);
    printf("=============================\n");
    print_payouts(person_group.person_list, &group);

    printf("=============================\n");
    print_group_summary(&group);

    printf("SUCCESS\n");
    return (0);
}
