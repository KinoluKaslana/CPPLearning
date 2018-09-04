//
// Created by KinoluKaslana on 18-8-30.
//
#include <iostream>
#include "AllCore.h"
NS_VALUE_CAT
bool main_value_category();
NS_END;
NS_STAT_IDENT
bool main_statement_identifier_expression();
NS_END
NS_AGGREATE_POD
bool main_aggregate_and_pods();
NS_END
int main() {
    if(std::cout<<"Running example: value_category"<<std::endl,
           VALUE_CATEGORY::main_value_category())
        std::cout<<"Done!"<<std::endl;
    if(std::cout<<"Running example: statement & identifier & expression"<<std::endl,
            STAT_IDENTI::main_statement_identifier_expression())
        std::cout<<"Done!"<<std::endl;
    if(std::cout<<"Running example: aggregate and PODs"<<std::endl,
            Aggergates_POD::main_aggregate_and_pods())
        std::cout<<"Done!"<<std::endl;
    return 0;
}