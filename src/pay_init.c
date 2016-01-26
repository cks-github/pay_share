#include "pay.h"

void init_transaction(transaction_data *trans_data)
{
    int i;

    trans_data->trans_count = 0;

    for (i = 0; i < MAX_TRANS_CNT; i++) {
        trans_data->trans_list[i].desc[0] = '\0';
        trans_data->trans_list[i].amount = 0.0;
    }
}

void init_pay_group(pay_group *group,
                    int        num_of_people)
{
    int i,j;
    group->num_of_people = num_of_people;
    group->total_trans = 0;
    group->per_person_total = 0;
    group->num_of_trans = 0;
    
    for (i=0; i<MAX_PEOPLE_CNT; i++) {
        for (j=0; j<MAX_PEOPLE_CNT; j++) {
            group->pay_list[i][j].owed = 0;
            group->pay_list[i][j].owes = 0;
        }
    }
}

int init_person(person_data *person_group,
                const char  *name)
{
    int person_index = person_group->person_count;

    if (DEBUG) {
        printf("%s():%d attempting to add %s\n", __FUNCTION__, __LINE__, name);
        printf("prior to adding person_count = %d\n",
               person_group->person_count);
    }

    if (person_group->person_count > MAX_PEOPLE_CNT-1) {
        printf("ERROR: surpassed max person cnt = %d\n", MAX_PEOPLE_CNT);
        return (ERROR);
    }

    strncpy(person_group->person_list[person_index].name, name, MAX_STR);
    person_group->person_list[person_index].person_id = person_group->person_count++;

    if (DEBUG) {
        printf("%s():%d SUCCESS adding %s id = %d, current cnt = %d\n",
               __FUNCTION__, __LINE__,
               person_group->person_list[person_index].name,
               person_group->person_list[person_index].person_id,
               person_group->person_count);
    }

    return (NO_ERROR);
}

