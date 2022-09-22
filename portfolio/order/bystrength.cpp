#include <iostream>

#include "../../aux/security.h"
#include "secList.h"

/* orderByStrength: takes an order and adds it to a linked list where it belongs by strength
 */
secList* orderByStrength(security toAdd, secList* list) {
    secList* addSec = (secList *)malloc(sizeof(secList));
    addSec->sec = toAdd;
    
    if (list == NULL) {
        return addSec;
    }

    secList* secI = list;
    while (secI->next != NULL) {
        if (addSec->sec.strength > secI->sec.strength) {
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