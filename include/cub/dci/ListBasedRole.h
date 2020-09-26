#ifndef INCLUDE_CUB_DCI_LISTBASEDROLE_H_
#define INCLUDE_CUB_DCI_LISTBASEDROLE_H_

#include <cub/dci/Role.h>
#include <cub/repo/list/ListElem.h>

#define DEFINE_LIST_BASED_ROLE(role) \
   DEFINE_ROLE(role) EXTENDS(CUB_NS::ListElem<role>)

#endif /* INCLUDE_CUB_DCI_LISTBASEDROLE_H_ */
