#include <iostream>

#include "../../aux/security.h"
#include "secList.h"

/* orderByRisk: takes an order and adds it to a linked list where it belongs by risk
 */
secList* orderByRisk(security toAdd, secList* list) {
    secList* addSec = (secList *)malloc(sizeof(secList));
    addSec->sec = toAdd;
    
    if (list == NULL) {
        return addSec;
    }

    secList* secI = list;
    while (secI->next != NULL) {
        if (addSec->sec.risk < secI->sec.risk) {
            addSec->next = secI->next;
            secI->next = addSec;
            return list;
        } else {
            secI = secI->next;
        }
    }

    secI->next = addSec;
    return list;
}