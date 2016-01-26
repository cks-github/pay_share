#include "pay.h"


void print_payouts (person person_list[],
                    pay_group *group)
{
    int i,j;
    float owed, owes;
    
    for (i=0; i<group->num_of_people; i++) {
        printf("Person = %s", person_list[i].name);
        printf(" already spent $%6.2f\n", group->pay_list[i][i].owed);
        for (j=0; j<group->num_of_people; j++) {
            if (i == j) continue;
            owed = group->pay_list[i][j].owed;
            owes = group->pay_list[i][j].owes;
            if (owed > owes) {
                printf(".... %s owes you $%6.2f\n", person_list[j].name, owed-owes);    
            } else if (owes > owed) {
                printf(".... you owe %s $%6.2f\n", person_list[j].name, owes-owed);    
            }
        }
    }
}

void print_group_summary (pay_group *group)
{
    printf("%d total transactions for a total of $%.2f dollars spent\n",
           group->num_of_trans, group->total_trans);
    printf("...split amongst %d people\n", group->num_of_people);
    printf("...everyone spends $%.2f\n", group->per_person_total);
}

void print_group_pay_list (pay_group *group)
{
    int i,j;

    printf("pay_list (owed, owes)\n");
    for (i=0; i<group->num_of_people; i++) {
        for (j=0; j<group->num_of_people; j++) {
            printf("[%d,%d] = $%6.2f, $%6.2f; ", i, j, group->pay_list[i][j].owed,
                   group->pay_list[i][j].owes);
        }
        printf("\n");
    }
}

int print_trans_summary (transaction_data *trans_data)
{
    int i;

    for (i = 0; i < trans_data->trans_count; i++) {
        printf("transaction -> \"%s\"\n", trans_data->trans_list[i].desc);
        printf("    payer.person_id = %s.%d\n", trans_data->trans_list[i].payer->name,
               trans_data->trans_list[i].payer->person_id);
        printf("    amount = $%.2f\n", trans_data->trans_list[i].amount);
    }
}
